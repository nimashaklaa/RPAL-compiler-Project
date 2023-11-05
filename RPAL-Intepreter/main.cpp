#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stack>
#include "LexicalAnalyzer.h"
#include "LexicalAnalyzer.cpp"
#include "Tree.h"
#include "Tree.cpp"
#include "Parser.h"
#include "Parser.cpp"
#include "Standardizer.h"
#include "Standardizer.cpp"
#include "CSElement.h"
#include "CSElement.cpp"
#include "CSEMachine.h"
#include "CSEMachine.cpp"


using namespace std;

int main(int argc, char* argv[]) {

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
	
    string filename="tests\\add";
	ifstream f(filename);
	string content((istreambuf_iterator<char>(f)), (istreambuf_iterator<char>()));
	LexicalAnalyzer Lex(content);
	int tokType = Lex.processNext();
	
	
	Parser Par(&Lex);
	Par.E();
    cout << "\n\n ABSTRACT SYNTAXT TREE\n\n" << endl;
	Tree::prettyPrint(Par.getTopTree());
	cout << "\n\n STDANDARDIZED TREE\n\n" << endl;
	Tree::prettyPrint(Standardizer::standardizeTree(Par.getTopTree()));
	cout << "\n\n CSE Machine structure \n\n" << endl;
	CSEMachine csemachine(Par.getTopTree());
	cout << "\n\n" << endl;
	cout << "Terminated succesfully! Press any key to continue..." << endl;
	// cin >> content;

    return 0;
}
