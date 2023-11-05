#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <stack>
#include <vector>
#include <cmath> 
#include "Tree.h"
#include "Tree.cpp"
#include "CSElement.h"
#include "CSElement.cpp"
#include "Environment.h"
#include "Environment.cpp"
#include "CSEMachine.h"



string CSEMachine:: getTypeString(int type) {
    if (type == 0)
        return "STRING";
    else if (type == 1)
        return "INTEGER";
    else if (type == 2)
        return "IDENTIFIER";
    else if (type == 3)
        return "RULE";
    else
        return "UNKNOWN!";
}

CSEMachine:: CSEMachine(Tree* tree) {
    stdTree = tree;

    printControlCreation = false;
    buildControlStructures(tree, 1);

    printControls = true;
    if(printControls)
        printControlStructures();
    initializeCSEMachine();
    runCSEMachine();
}

void CSEMachine:: buildControlStructures(Tree* tree, int index) {
    if (tree == NULL)
        return;
    if(printControlCreation)
        cout << index << ".\t" << tree->nodeValue << " is a " << getTypeString(tree->nodeType) << endl;
    if (controls.size() < index) {
        controls.push_back(*(new vector<CSElement>));
    }

    CSElement* currentEl;
    if (tree->nodeValue == "lambda") {
        string varName = tree->childNode->nodeValue;
        if (varName == ",") {
            Tree *temp = tree->childNode->childNode;
            varName = temp->nodeValue;
            temp = temp->siblingNode;
            while (temp != NULL) {
                varName = varName + "," + temp->nodeValue;
                temp = temp->siblingNode;
            }
        }
        int deltaNumber = controls.size();
        currentEl = new CSElement("lambda", deltaNumber, varName, -1);
        controls[index - 1].push_back(*currentEl);
        buildControlStructures(tree->childNode->siblingNode, deltaNumber + 1);
    }
    else if (tree->nodeValue == "tau") {
        currentEl = new CSElement(tree->nodeValue);
        int tauCnt = 0;
        Tree *runner = tree->childNode;
        while (runner != NULL) {
            tauCnt++;
            runner = runner->siblingNode;
        }
        currentEl->index = tauCnt;
        controls[index - 1].push_back(*currentEl);
        Tree *child = tree->childNode;
        while (child != NULL) {
            buildControlStructures(child, index);
           child = child->siblingNode;
        }
    }
    else {
        currentEl = new CSElement(tree->nodeValue);
        currentEl->type = tree->nodeType;
        controls[index - 1].push_back(*currentEl);
        buildControlStructures(tree->childNode, index);
        if(tree->childNode != NULL)
            buildControlStructures(tree->childNode->siblingNode, index);
    }

}


void CSEMachine:: printControlStructures() {
    cout << "Size: " << controls.size() << endl;

    for (int i = 0; i < controls.size(); i++) {
        cout << i << ".\t";
        for (int j = 0; j < controls[i].size(); j++) {
            if (controls[i].at(j).value == "lambda")
                cout << "(" + controls[i].at(j).boundVar + ")" + controls[i].at(j).value << controls[i].at(j).index << " ";
            else if(controls[i].at(j).value == "tau")
                cout << controls[i].at(j).value << controls[i].at(j).index << " ";
            else
                cout << controls[i].at(j).value << " ";
        }
        cout << endl;
    }
}

void CSEMachine:: pushDeltaOnStack(int delta) {
    
    CSElement *freshEnv = new CSElement("env", delta, "", -1);
    freshEnv->isEnvMarker = true;
    leftStack.push(*freshEnv);
    rightStack.push(*freshEnv);
    for (int i = 0; i < controls[delta].size(); i++) {
        leftStack.push( controls[delta].at(i) );
    }
}

void CSEMachine:: initializeCSEMachine(){
    pushDeltaOnStack(0);
    env = new Environment("", new CSElement("none"), GRAMMAR_RULE);
    envCounter = 0;
}

void CSEMachine:: printCSE() {
    cout << "LEFT:\t";
    stack<CSElement> tempLeft;
    while (!leftStack.empty()) {
        tempLeft.push(leftStack.top());
        leftStack.pop();
    }
    while (!tempLeft.empty()) {
        leftStack.push(tempLeft.top());
        if(leftStack.top().value == "lambda")
            cout << leftStack.top().value << leftStack.top().index << " ";
        else if (leftStack.top().value == "env")
            cout << leftStack.top().value << leftStack.top().index << " ";
        else if (leftStack.top().value == "tau")
            cout << leftStack.top().value << leftStack.top().index << " ";
        else
            cout << leftStack.top().value << " ";
        
        tempLeft.pop();
    }

    cout << endl << "RIGHT:\t";
    stack<CSElement> tempRight;
    while (!rightStack.empty()) {
        tempRight.push(rightStack.top());
        if (rightStack.top().value == "lambda")
            cout << rightStack.top().value << rightStack.top().index << " ";
        else if (rightStack.top().value == "env")
            cout << rightStack.top().value << rightStack.top().index << " ";
        else
            cout << rightStack.top().value << " ";
        rightStack.pop();
    }
    while (!tempRight.empty()) {
        rightStack.push(tempRight.top());
        tempRight.pop();
    }
    cout << endl << endl;
}

CSElement* CSEMachine:: lookupVar(string name) {
    for (int i = 0; i < env->variable.size(); i++) {
        if (env->variable[i] == name)
        {
            lookupVal = env->value[i];
            return lookupVal;
        }
    }

    Environment *temp = env->parent;
    while (temp != NULL) {
        for (int i = 0; i < env->variable.size(); i++) {
            if (env->variable[i] == name)
            {
                lookupVal = env->value[i];
                return lookupVal;
            }
        }
        temp = temp->parent;
    }
    return NULL;
}

void CSEMachine:: runCSEMachine(){
    while (!leftStack.empty()) {
        printCSE();
        processCSEMachine();
        leftStack.pop();
    }
}

void CSEMachine:: processCSEMachine() {

    // cout << "op1.value  is "<< rightStack.top().value  <<endl;
    if (leftStack.top().value == "not") {
        leftStack.pop();
        CSElement node = rightStack.top();
        rightStack.pop();
        if (node.value == "true")
            node.value = "false";
        else if (node.value == "false")
            node.value = "true";
        else {
            cout << "Not needs a boolean!" << endl;
            cin >> lookupType;
            exit(0);
        }
    }
    else if (leftStack.top().value == "+") {
        CSElement op1 = rightStack.top();
        rightStack.pop();
        CSElement op2 = rightStack.top();
        rightStack.pop();
        int in1 = stoi(op1.value);
        int in2 = stoi(op2.value);
        op1.value = to_string(in1 + in2);
        rightStack.push(op1);
        cout <<rightStack.top().value << "leftStack.top().value == +" << endl;
    }
    else if (leftStack.top().value == "-") {
        CSElement op1 = rightStack.top();
        rightStack.pop();
        CSElement op2 = rightStack.top();
        rightStack.pop();
        int in1 = stoi(op1.value);
        int in2 = stoi(op2.value);
        op1.value = to_string(in1 - in2);
        rightStack.push(op1);
    }
    else if (leftStack.top().value == "/") {
        CSElement op1 = rightStack.top();
        rightStack.pop();
        CSElement op2 = rightStack.top();
        rightStack.pop();
        int in1 = stoi(op1.value);
        int in2 = stoi(op2.value);
        op1.value = to_string(in1 / in2);
        rightStack.push(op1);
    }
    else if (leftStack.top().value == "*") {
        CSElement op1 = rightStack.top();
        rightStack.pop();
        CSElement op2 = rightStack.top();
        rightStack.pop();
        int in1 = stoi(op1.value);
        int in2 = stoi(op2.value);
        op1.value = to_string(in1 * in2);
        rightStack.push(op1);
    }
    else if (leftStack.top().value == "**") {
        CSElement op1 = rightStack.top();
        rightStack.pop();
        CSElement op2 = rightStack.top();
        rightStack.pop();
        int in1 = stoi(op1.value);
        int in2 = stoi(op2.value);
        float x = pow(in1, in2);
        op1.value = to_string(x);
        rightStack.push(op1);
    }
    



    
    // cout << "op1.value  iF" << rightStack.top().value  <<endl;
}
