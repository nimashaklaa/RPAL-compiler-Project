#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CSElement.h"
#include "Environment.h"

using namespace std;

Environment:: Environment()
	{ }

Environment:: Environment(string var, CSElement *mValue, int mType) {
    parent = NULL;
    child = NULL;
    sibling = NULL;
    variable.push_back(var);
    value.push_back(mValue);
}
