#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <stack>
#include <cstdlib>
#include "Tree.h"
using namespace std;

#ifndef PARSER_H
#define PARSER_H

class Parser {

	enum NodeType {
		STRING_VALUE,
		INTEGER_VALUE,
		ID_NAME,
		GRAMMAR_RULE
	};

	enum Token {
		IDENTIFIER,
        SPACE,
        COMMENT, 
        OPENING, 
        CLOSING, 
        SEMICOL, 
        COMMA,

        DIGIT, 
        LETTER,
        INT_LITERAL, // Integer Literals
        STRING,

        ERROR,
        STOP, 
        OP_CODE,    // Operation code
        OPERATOR_CODE
	};


public:
	stack<Tree> treeStack;
	int tokenType;
	string tokenValue;
	bool isDebug;

private:
	LexicalAnalyzer *mLex;

public:

	Parser(LexicalAnalyzer *mLexNew) ;

	Tree makeTree(string mVal, int popCount);


	Tree* getTopTree();

	void readToken(string mToken);
	static bool isKeyword(string mTok);
	void E();
	void Ew();
	void T();
	void Ta();
	void Tc();
	void B();
	void Bt();
	void Bs();
	void Bp();
	void A();
	void At();
	void Af();
	void Ap();
	void R();
	void Rn();
	void D();
	void Da();
	void Dr();
	void Db();
	void Vb();
	void Vl();
};

#endif // !PARSER_H