#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <cstdio>
#include "LexicalAnalyzer.h"


LexicalAnalyzer:: LexicalAnalyzer(string Source) {
		str = Source;
		charNext = ' ';
		charClass = ERROR;
		lexeme = "";
}

LexicalAnalyzer:: ~LexicalAnalyzer() {
}

void LexicalAnalyzer:: getChar() {
	if (str.size() > 0) {
		charNext = str[0];
		str.erase(0, 1);
	}
	else
		charNext = EOF;

	charClass = getcharClass(charNext);
}

int LexicalAnalyzer:: getcharClass(char symbol) {

		int Classchr = ERROR;

		if (isalpha(symbol))
			Classchr = LETTER;
		if (isalnum(symbol) && !isalpha(symbol))
			Classchr = DIGIT;
		if (isspace(symbol) || symbol == ' ')
			Classchr = SPACE;
		if (symbol == EOF)
			Classchr = STOP;
		if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '<'
			|| symbol == '>' || symbol == '&' || symbol == '.'
			|| symbol == '@' || symbol == '/' || symbol == ':'
			|| symbol == '=' || symbol == '~' || symbol == '|'
			|| symbol == '!' || symbol == '#' || symbol == '%'
			|| symbol == '^' || symbol == '_' || symbol == '['
			|| symbol == ']' || symbol == '{' || symbol == '}'
			|| symbol == '"' || symbol == '`' || symbol == '?'
			|| symbol == '\'' || symbol == '$')
			Classchr = OP_CODE;

		if (symbol == '(')
			Classchr = OPENING;
		if (symbol == ')')
			Classchr = CLOSING;
		if (symbol == ',')
			Classchr = COMMA;
		if (symbol == ';')
			Classchr = SEMICOL;

		return Classchr;
	}

void LexicalAnalyzer:: addCharLexeme() {
	lexeme += charNext;
}

int LexicalAnalyzer:: processNext() {
		lexeme = "";

		while (charClass == SPACE) {
			getChar();
		}

		if (charClass == ERROR) {
			addCharLexeme();
			getChar();
			return ERROR;
		}

		if (charClass == STOP)
			return STOP;
		if (charClass == OPENING) {
			addCharLexeme();
			getChar();
			return OPENING;
		}
		if (charClass == CLOSING) {
			addCharLexeme();
			getChar();
			return CLOSING;
		}
		if (charClass == SEMICOL) {
			addCharLexeme();
			getChar();
			return SEMICOL;
		}
		if (charClass == COMMA) {
			addCharLexeme();
			getChar();
			return COMMA;
		}

		switch (charClass) {
		case LETTER:
			addCharLexeme();
			getChar();
			while (charClass == LETTER || charClass == DIGIT || charNext == '_') {
				addCharLexeme();
				getChar();
			}
			return IDENTIFIER;
			break;

		case DIGIT:
			addCharLexeme();
			getChar();
			while (charClass == DIGIT) {
				addCharLexeme();
				getChar();
			}
			return INT_LITERAL;
			break;

		case OP_CODE:
			if (charNext == '\'') {
				getChar();
				while (charNext != '\'') {
					addCharLexeme();
					getChar();
				}
				getChar();
				return STRING;
			}
			else if (charNext == '/') {
				addCharLexeme();
				getChar();
                
				if (charNext == '/') {				
					addCharLexeme();
					getChar();
					while (charNext != '\n' && charNext != '\r'
						&& charNext != EOF && charNext != '!') {
						
						addCharLexeme();
						getChar();
					}
					
					return COMMENT;
				}
				else if(getcharClass(charNext) == OP_CODE && charNext != '/'){
					getChar();
					while (getcharClass(charNext) == OP_CODE && charNext != '/') {
						addCharLexeme();
						getChar();
					}
					return OPERATOR_CODE;
				}
                
			}
			else {
				addCharLexeme();
				getChar();
				while (getcharClass(charNext) == OP_CODE && charNext != '\'') {
					addCharLexeme();
					getChar();
				}
				return OPERATOR_CODE;
			}
			break;
		default:
			return ERROR;

		}
		return ERROR;
	}

string LexicalAnalyzer:: getString(int code) {
		switch (code) {
        case IDENTIFIER:
			return "IDENTIFIER";
			break;
		case SPACE:
			return "SPACE";
			break;
		case COMMENT:
			return "COMMENT";
			break;
		case OPENING:
			return "OPENING";
		case CLOSING:
			return "CLOSING";
			break;
		case SEMICOL:
			return "SEMICOL";
			break;
		case COMMA:
			return "COMMA";
			break;

		case DIGIT:
			return "DIGIT";
			break;
		case LETTER:
			return "LETTER";
			break;
		case INT_LITERAL:
			return "INT_LITERAL";
			break;
		case STRING:
			return "STRING";
			break;

		case ERROR:
			return "ERROR";
			break;
		case STOP:
			return "STOP";
			break;
		case OP_CODE:
			return "OP_CODE";
			break;
		case OPERATOR_CODE:
			return "OPERATOR_CODE";
			break;
		}
		return "ERROR";
}