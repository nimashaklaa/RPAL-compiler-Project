#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <stack>
#include "LexicalAnalyzer.h"
// #include "LexicalAnalyzer.cpp"
#include "Tree.h"

Tree:: Tree(string mVal, int mType, Tree *mChild, Tree *mSib) {
    nodeValue = mVal;
    nodeType = mType;
    childNode = mChild;
    siblingNode = mSib;
}


Tree:: Tree(Tree *copyTree) {
    nodeValue = copyTree->nodeValue;
    nodeType = copyTree->nodeType;
    childNode = copyTree->childNode;
    siblingNode = copyTree->siblingNode;
}

void Tree:: operator=(Tree t) {
    childNode = t.childNode;
    siblingNode = t.siblingNode;
    nodeType = t.nodeType;
    nodeValue = t.nodeValue;
}
