#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>

using namespace std;


#ifndef LEXANALYZER_H_INCLUDED
#define LEXANALYZER_H_INCLUDED


class LexicalAnalyzer {
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
	char charNext;
	int charClass;
	string lexeme;  // sequences that make up the token 

private:
	string str;

public:
	LexicalAnalyzer(string Source) ;

	~LexicalAnalyzer();

	void getChar();

	static int getcharClass(char symbol);
	void addCharLexeme();

	int processNext();

	string getString(int code);

};

#endif // LEXANALYZER_H_INCLUDED