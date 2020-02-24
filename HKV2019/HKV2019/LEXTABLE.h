#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 2048
#define LT_TI_NULLIDX 0xffffff

#define LEX_INTEGER 't'		//integer
#define LEX_STRING 't'		//string
#define LEX_CHAR 't'
#define LEX_ID 'i'			//id
#define LEX_LITERAL 'l'		//Literal
#define LEX_FUNCTION 'f'	//function
#define LEX_CREATE 'c'
#define LEX_MAIN 'm'		//main
#define LEX_RBACK 'r'		//rback
#define LEX_WOUT 'w'		//WriteLine
#define LEX_STRLEN 'e'		//string length
#define LEX_DRAND 'g'		//random number
#define LEX_SRAND 's'		//random number
#define LEX_LOOP 'o'		//loop
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_OPERATOR 'v'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_MULTIPLY '*'
#define LEX_EQUAL '='
#define LEX_RIGHTSHIFT '>'
#define LEX_LEFTSHIFT '<'
#define LEX_QUOTE '\''


namespace LT
{
	struct Entry
	{
		char lexem;
		int stringN;
		int idInIdTable;
		char operatorType = '`';
		std::string scope;
		Entry();
		Entry(char lex, int stringNumber, char opType = '`', int numberInIdTable = -1, std::string scope = "");
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		unsigned char* LexemText;
		int countEnd = 0;
	};

	LexTable* Create(int size);
	void Add(LexTable* lextable, Entry entry);
	Entry GetEntry(LexTable* lextable, int n);
	void Delete(LexTable* lextable);
}
