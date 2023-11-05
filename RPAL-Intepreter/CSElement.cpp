#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "CSElement.h"


CSElement:: CSElement(string mVal) {
    value = mVal;
    index = 0;
    boundVar = "";
    parEnv = -1;
    isEnvMarker = false;
    isTau = false;
    type = GRAMMAR_RULE;
}

CSElement:: CSElement(string mVal, int mIndex, string mPar1, int mparEnv) {
    value = mVal;
    index = mIndex;
    boundVar = mPar1;
    parEnv = mparEnv;
    isEnvMarker = false;
    isTau = false;
    type = GRAMMAR_RULE;
}
