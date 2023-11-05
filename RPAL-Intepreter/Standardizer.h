#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include "Tree.h"

using namespace std;

#ifndef STANDARDIZER_H
#define STANDARDIZER_H

class Standardizer {

public:
	static Tree* standardizeTree(Tree *tree);
		
private:
	static void standardizeLet(Tree *tree);
	static void standardizeWithin(Tree *tree);
	static void standardizeFncForm(Tree *tree);
	static void standardizeLambda(Tree *tree);
	static void standardizeInfix(Tree *tree);
	static void standardizeAnd(Tree *tree);
	static void standardizeWhere(Tree *tree);
	static void standardizeRec(Tree *tree);
};

#endif // !STANDARDIZER_H
