#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include "Tree.h"
#include "Standardizer.h"

Tree* Standardizer:: standardizeTree(Tree *tree) {
    if (tree == NULL)
        return NULL;
    if (tree->nodeValue == "tau") {
        Tree *child = tree->childNode->siblingNode;
        standardizeTree(tree->childNode);
        while (child != NULL) {
            Tree *temp = child->siblingNode;
            standardizeTree(child);
            child = temp;
        }
        return tree;
    }

    if (tree->childNode != NULL) standardizeTree(tree->childNode);
    if (tree->siblingNode != NULL) standardizeTree(tree->siblingNode);
    if (tree->nodeValue == "let") standardizeLet(tree);
    else if (tree->nodeValue == "within") standardizeWithin(tree);
    else if (tree->nodeValue == "function_form") standardizeFncForm(tree);
    else if (tree->nodeValue == "lambda") standardizeLambda(tree);
    else if (tree->nodeValue == "@") standardizeInfix(tree);
    else if (tree->nodeValue == "and") standardizeAnd(tree);
    else if (tree->nodeValue == "where") standardizeWhere(tree);
    else if (tree->nodeValue == "rec") standardizeRec(tree);


    return tree;
}

void Standardizer:: standardizeLet(Tree *tree) {
    tree->nodeValue = "gamma";
    Tree *eq = tree->childNode;
    Tree *p = eq->siblingNode;
    Tree *x = eq->childNode;
    Tree *e = x->siblingNode;
    eq->nodeValue = "lambda";
    x->siblingNode = p;
    eq->siblingNode = e;
}

void Standardizer:: standardizeWithin(Tree *tree) {
    tree->nodeValue = "=";

    Tree *eq1 = tree->childNode;
    Tree *eq2 = eq1->siblingNode;

    Tree *x1 = eq1->childNode;
    Tree *x2 = eq2->childNode;
    eq1->childNode = NULL;
    eq1->siblingNode = NULL;
    eq2->childNode = NULL;

    Tree *e1 = x1->siblingNode;
    Tree *e2 = x2->siblingNode;
    x1->siblingNode = NULL;
    x2->siblingNode = NULL;

    tree->childNode = x2;
    x2->siblingNode = eq2;
    eq2->nodeValue = "gamma";
    eq2->childNode = eq1;
    eq1->nodeValue = "lambda";
    eq1->siblingNode = e1;
    eq1->childNode = x1;
    x1->siblingNode = e2;
}

void Standardizer:: standardizeFncForm(Tree *tree) {
    Tree *p = tree->childNode;
    Tree *v = p->siblingNode;
    tree->nodeValue;

    Tree *lam = new Tree("lambda", 3, v, NULL);
    p->siblingNode = lam;
    Tree *next = v->siblingNode;
    while (next->siblingNode != NULL) {
        lam = new Tree("lambda", 3, NULL, NULL);
        v->siblingNode = lam;
        lam->childNode = next;
        v = next;
        next = v->siblingNode;
    }
}

void Standardizer:: standardizeLambda(Tree *tree) {
    Tree *v = tree->childNode;
    Tree *next = v->siblingNode;
    while (next->siblingNode != NULL) {
        Tree *lam = new Tree("lambda", 3, next, NULL);
        v->siblingNode = lam;
        v = next;
        next = next->siblingNode;
    }
}

void Standardizer:: standardizeInfix(Tree *tree) {
    tree->nodeValue = "gamma";
    Tree *e1 = tree->childNode;
    Tree *n = e1->siblingNode;
    Tree *e2 = n->siblingNode;
    Tree *gamma = new Tree("gamma", 3, n, NULL);
    gamma->siblingNode = e2;
    tree->childNode = gamma;
    n->siblingNode = e1;
    e1->siblingNode = NULL;
}

void Standardizer:: standardizeAnd(Tree *tree) {
    Tree *comma = new Tree(",", 3, NULL, NULL);
    Tree *tau = new Tree("tau", 3, NULL, NULL);
    comma->siblingNode = tau;
    Tree *eq = tree->childNode;
    Tree *x = eq->childNode;
    Tree *e = x->siblingNode;
    comma->childNode = x;
    tau->childNode = e;
    eq = eq->siblingNode;
    while (eq != NULL) {
        x->siblingNode = eq->childNode;
        x = x->siblingNode;
        e->siblingNode = eq->childNode->siblingNode;
        e = e->siblingNode;
        eq = eq->siblingNode;
    }
    x->siblingNode = NULL;
    tree->nodeValue = "=";
    tree->childNode = comma;
}

void Standardizer:: standardizeWhere(Tree *tree) {
    tree->nodeValue = "gamma";
    Tree *p = tree->childNode;
    Tree *eq = p->siblingNode;
    Tree *x = eq->childNode;
    Tree *e = x->siblingNode;
    eq->nodeValue = "lambda";
    tree->childNode = eq;
    x->siblingNode = p;
    p->siblingNode = NULL;
    eq->siblingNode = e;
}

void Standardizer:: standardizeRec(Tree *tree) {
    tree->nodeValue = "=";
    Tree *x = tree->childNode->childNode;
    delete tree->childNode;
    tree->childNode = new Tree(x);
    Tree *ystar = new Tree("<Y*>", 3, NULL, NULL);
    Tree *gamma = new Tree("gamma", 3, ystar, NULL);
    tree->childNode->siblingNode = gamma;
    Tree *lambda = new Tree("lambda", 3, x, NULL);
    gamma->childNode->siblingNode = lambda;
}

