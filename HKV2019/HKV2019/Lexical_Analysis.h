#pragma once
#include "IDTABLE.h"
#include "LEXTABLE.h"
#include "Input.h"

struct Tables
{
	IT::IdTable* IDTABLE;
	LT::LexTable* LEXTABLE;
};

struct ListId
{
	IT::Entry id;
	IT::Entry* pNext = nullptr;
};

void initLexem(const char* text, std::string tmp, LT::LexTable* tableOfLexem, int numberOfstring, int poz,
               IT::IdTable* newIdTable, int* typeData, int* typeID);
Tables createTables(In::INN newIN);
std::string StringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst);
