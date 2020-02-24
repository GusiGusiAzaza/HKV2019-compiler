#pragma once
#define ID_MAXSIZE 16
#define TI_MAXSIZE 1024
#define TI_STR_MAXSIZE 49
#define TI_INT_MAXSIZE 4294967295

namespace IT
{
	enum IDDATATYPE
	{
		INT = 1,
		STR = 2,
		CHAR = 3,
		UNDEF = 4,
	};

	enum IDTYPE
	{
		V = 1,
		F = 2,
		P = 3,
		L = 4,
		UNDEFF = 5,
	};

	union iValue
	{
		unsigned int intvalue;

		struct
		{
			char len;
			char str[TI_STR_MAXSIZE - 1];
		} stringvalue[TI_STR_MAXSIZE];
	};

	struct Entry
	{
		Entry();
		Entry(int NumberString, char id[ID_MAXSIZE], IDDATATYPE idDataType, IDTYPE idType, iValue value,
		      std::string view, int numberSystem = 10);
		int string_number;
		std::string id;
		IDDATATYPE datatype;
		IDTYPE type;
		std::string scope;
		int number_system = 0;
		int parm_count = -1;
		std::list<IDDATATYPE> parms;
		iValue value;
	};

	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};

	IdTable* Create(int size);
	int Add(IdTable* idtable, Entry);
	int GetIndexLastElement(IdTable* idTable);
	void Delete(IdTable* idtable);
	int idInIT(IdTable idTable, const Entry& entry);

	void modifyIdTable(IdTable* idTable);
}
