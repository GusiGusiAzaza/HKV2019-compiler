#include "pch.h"

using namespace std;

namespace LT
{
	LexTable* Create(int size)
	{
		LexTable* newTable = new LexTable;
		newTable->table = new Entry[size];
		newTable->size = 0;
		newTable->maxsize = size;

		return newTable;
	}

	Entry::Entry()
	{
		char lexem = '`';
		stringN = -1;
		int idInIdTable = -1;
		operatorType = '`';
	}

	Entry::Entry(const char lex, int stringNumber, const char opType, const int numberInIdTable, std::string scope)
	{
		this->lexem = lex;
		this->stringN = stringNumber;
		this->operatorType = opType;
		this->idInIdTable = numberInIdTable;
		this->scope = std::move(scope);
	}

	void Add(LexTable* lextable, Entry entry)
	{
		if (lextable->size > LT_MAXSIZE)
			throw ERROR_THROW(300);
		lextable->table[lextable->size] = std::move(entry);
		lextable->size++;
	}

	Entry GetEntry(LexTable* lextable, int n)
	{
		return lextable->table[n - 1];
	}

	void Delete(LexTable* lextable)
	{
		delete lextable->LexemText;
		delete lextable->table;
		delete lextable;
	}
}
