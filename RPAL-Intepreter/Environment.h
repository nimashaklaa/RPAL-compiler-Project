#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef ENV_H_INCLUDED 
#define ENV_H_INCLUDED

class Environment {

	enum NodeType {
		STRVALUE,
		INTVALUE,
		ID_NAME,
		GRAM_RULE,
		TUPLE,
		COMMA_LIST,
		OPERATOR
	};

public:
	Environment *parent;
	Environment *child;
	Environment *sibling;
	vector<string> variable;
	vector<CSElement*> value;

public:

	Environment();
	Environment(string var, CSElement *mValue, int mType);

};

#endif	// Close ENV_H_INCLUDED


