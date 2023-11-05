#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef CSELEMENT_H_INCLUDED
#define CSELEMENT_H_INCLUDED

class CSElement {
	enum NodeType {
		STRVALUE,
		INTVALUE,
		ID_NAME,
		GRAMMAR_RULE,
		TUPLE,
		COMMA_LIST,
		OPERATOR
	};

public:
	vector<CSElement*> taus; 
	string value;
	int index;
	string boundVar;
	int parEnv;
	bool isEnvMarker;
	bool isTau;
	int type;

	CSElement(string mVal) ;
	CSElement(string mVal, int mIndex, string mPar1, int mparEnv);
};

#endif	//Close CSELEMENT_H_INCLUDED