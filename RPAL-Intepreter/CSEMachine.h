#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <stack>
#include <vector>
#include <cmath> 
#include "Tree.h"
#include "CSElement.h"
#include "Environment.h"

using namespace std;

#ifndef CSEMACHINE_H_INCLUDED
#define CSEMACHINE_H_INCLUDED


class CSEMachine {

	enum NodeType {
		STRVALUE,
		INTVALUE,
		ID_NAME,
		GRAMMAR_RULE,
		TUPLE,
		COMMA_LIST,
		OPERATOR
	};

private:
	Tree* stdTree;
	int envCounter;
	Environment *env;
	vector<vector<CSElement>> controls;
	stack<CSElement> leftStack;
	stack<CSElement> rightStack;
	bool printControlCreation, printControls;
	CSElement *lookupVal;
	int lookupType;

private:
	string getTypeString(int type);
public:
	CSEMachine(Tree* tree);
	void buildControlStructures(Tree* tree, int index);
	void printControlStructures();
	void pushDeltaOnStack(int delta);
	void initializeCSEMachine();
	void printCSE();
	CSElement* lookupVar(string name);
	void runCSEMachine();
	void processCSEMachine();

};

#endif	//Close CSEMACHINE_H_INCLUDED