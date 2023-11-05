#pragma once

#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <stack>

#include "LexicalAnalyzer.h"

#include <math.h>
#include <sstream>
using namespace std;

#ifndef TREE_H
#define TREE_H

class Tree {

enum NodeType {
		STRING_VALUE,
		INTEGER_VALUE,
		ID_NAME,
		GRAMMAR_RULE
	};

public:
	int nodeType;
	
	string nodeValue;
	Tree *childNode;
	Tree *siblingNode;

public:
	Tree(string mVal, int mType, Tree *mChild, Tree *mSib);
	Tree(Tree *copyTree);
	void operator=(Tree t);

	static void prettyPrint(Tree* mTree, int count = 0) {
    if (mTree != NULL) {
        for (int i = 0; i < count; i++)
            cout << ".";
        if (mTree->nodeType == GRAMMAR_RULE)
            cout << mTree->nodeValue << endl;
        else if (mTree->nodeType == INTEGER_VALUE)
            cout << "<INT:" << (mTree->nodeValue) << ">" << endl;
        else if (mTree->nodeType == STRING_VALUE)
            cout << "<STR:'" << mTree->nodeValue << "'>" << endl;
        else if (mTree->nodeType == ID_NAME)
            cout << "<ID:" << mTree->nodeValue << ">" << endl;
        prettyPrint(mTree->childNode, count + 1);
        prettyPrint(mTree->siblingNode, count);
    }

}

};


#endif // TREE_H