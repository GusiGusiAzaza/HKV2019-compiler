#include "pch.h"
#define FUNCTION_DECLARE "FUNCTION"
#define MAIN_DECLARE "MAIN"

void semantic::CheckSemantic(Tables tables)
{
	using namespace std;

	list<IT::Entry> valueList;
	list<IT::Entry> functionList;
	list<int> listnumberFunctionInIdTable; //Необходим для позднего связывания функции и её вызова
	string last_declare_global_block;
	char last_global_block_id[ID_MAXSIZE];
	int numberString_last_global_block;
	bool haveReturn = false;
	int ret = 0; //Необходим для возврата параметров из функции getFunction;
	IT::IDDATATYPE typeLastFunction = IT::IDDATATYPE::UNDEF;

	LT::LexTable* lexTable;
	IT::IdTable* idTable;
	lexTable = tables.LEXTABLE;
	idTable = tables.IDTABLE;
	for (int i = 0; i < lexTable->size; i++)
	{
		if (lexTable->table[i].lexem == LEX_FUNCTION)
		{
			LT::Entry lexEntryIdFunction = lexTable->table[i + 1];
			IT::Entry idEntryFunction = idTable->table[lexEntryIdFunction.idInIdTable];
			bool haveRback = false;
			int currentid = i + 3;
			idEntryFunction.parm_count = 0;
			while (lexTable->table[currentid].lexem != LEX_RIGHTHESIS)
			{
				if (lexTable->table[currentid].lexem == LEX_ID)
				{
					idEntryFunction.parm_count++;
					idEntryFunction.parms.push_back(idTable->table[lexTable->table[currentid].idInIdTable].datatype);
				}
				currentid++;
			}
			currentid = i+3;
			while (lexTable->table[currentid].lexem != LEX_BRACELET)
			{
				if (lexTable->table[currentid].lexem == LEX_RBACK)
					haveRback = true;
				currentid++;
			}
			if (!haveRback)
				throw ERROR_THROW_WNAME(517, lexTable->table[i+1].stringN, idTable->table[lexTable->table[i+1].idInIdTable].id);
			functionList.push_back(idEntryFunction);
			listnumberFunctionInIdTable.push_back(lexEntryIdFunction.idInIdTable);
			typeLastFunction = idEntryFunction.datatype;
			last_declare_global_block = FUNCTION_DECLARE;
			strcpy_s(last_global_block_id, idEntryFunction.id.c_str());
			numberString_last_global_block = lexEntryIdFunction.stringN;
			haveReturn = false;
			idTable->table[lexEntryIdFunction.idInIdTable] = idEntryFunction;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_RBACK)
		{
			int currentid = i + 1;
			switch (typeLastFunction)
			{
			case IT::IDDATATYPE::INT:
				{
					while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
					{
						if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem ==
							LEX_LITERAL)
						{
							if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::INT)
							{
								throw ERROR_THROW_WNAME(500, lexTable->table[i].stringN,
								                        string(idTable->table[lexTable->table[currentid].idInIdTable].id
								                        ));
							}
							if (idTable->table[lexTable->table[currentid].idInIdTable].type == IT::IDTYPE::F)
							{
								throw ERROR_THROW_WNAME(516, lexTable->table[currentid].stringN,
									string(idTable->table[lexTable->table[currentid].idInIdTable].id))
								
							}
						}

						currentid++;
					}
					haveReturn = true;
					continue;
				}
			case IT::IDDATATYPE::STR:
				{
					while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
					{
						int lexCount = 0;
						if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem ==
							LEX_LITERAL)
						{
							lexCount++;
							if (lexCount > 1)
								throw ERROR_THROW_WNAME(500, lexTable->table[currentid].stringN,
								                        string(idTable->table[lexTable->table[currentid].idInIdTable].id
								                        ))
							if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::STR)
								throw ERROR_THROW_WNAME(500, lexTable->table[currentid].stringN, string(""))
							if (idTable->table[lexTable->table[currentid].idInIdTable].type == IT::IDTYPE::F)
							{
									throw ERROR_THROW_WNAME(516, lexTable->table[currentid].stringN,
										string(idTable->table[lexTable->table[currentid].idInIdTable].id))

							}
						}
						else
							throw ERROR_THROW_WNAME(500, lexTable->table[currentid].stringN, string(""));

						currentid++;
						haveReturn = true;
					}
					haveReturn = true;
					continue;
				}
			case IT::IDDATATYPE::CHAR:
				{
					while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
					{
						int lexCount = 0;
						if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem ==
							LEX_LITERAL)
						{
							lexCount++;
							if (lexCount > 1)
							{
								throw ERROR_THROW_WNAME(500, lexTable->table[currentid].stringN,
									string(idTable->table[lexTable->table[currentid].idInIdTable].id))
							}

							if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::CHAR)
							{
								throw ERROR_THROW_WNAME(500, lexTable->table[currentid].stringN, string(""))
							}

							if (idTable->table[lexTable->table[currentid].idInIdTable].type == IT::IDTYPE::F)
							{
								throw ERROR_THROW_WNAME(516, lexTable->table[currentid].stringN,
										string(idTable->table[lexTable->table[currentid].idInIdTable].id))

							}
						}
						else
							throw ERROR_THROW_WNAME(500, lexTable->table[currentid].stringN, string(""));

						currentid++;
						haveReturn = true;
					}
					haveReturn = true;
					continue;
				}
			default:
				break;
			}
		}
		if (lexTable->table[i].lexem == LEX_MAIN)
		{
			last_declare_global_block = MAIN_DECLARE;
			numberString_last_global_block = lexTable->table[i].stringN;
			haveReturn = false;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_CREATE)
		{
			valueList.push_back(idTable->table[lexTable->table[i + 1].idInIdTable]);
			continue;
		}
		if ((lexTable->table[i - 2].lexem != LEX_CREATE && lexTable->table[i - 1].lexem != LEX_FUNCTION) && lexTable->
			table[i - 1].lexem != LEX_INTEGER && lexTable->table[i].lexem == LEX_ID && lexTable->table[i + 1].lexem == LEX_LEFTHESIS)
		{
			//идём по списку аргументов при вызове 
			int currentid = i + 2; // Индекс левой скобки
			list<IT::IDDATATYPE> callParmList;
			int leftBracket = 1;
			int rightBracket = 0;
			while (leftBracket != rightBracket) //Заполняем аргументы вызова
			{
				if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem == LEX_LITERAL)
				{
					callParmList.push_back(idTable->table[lexTable->table[currentid].idInIdTable].datatype);
				}
				if (lexTable->table[currentid].lexem == LEX_LEFTHESIS) leftBracket++;
				if (lexTable->table[currentid].lexem == LEX_RIGHTHESIS) rightBracket++;

				currentid++;
			}
			IT::Entry function = getFunction(idTable->table[lexTable->table[i].idInIdTable], ret,
			                                 listnumberFunctionInIdTable, functionList);

			if (ret == -1)
			{
				throw ERROR_THROW_WNAME(501, lexTable->table[i].stringN,
					string(idTable->table[lexTable->table[i].idInIdTable].id));
			}
			lexTable->table[i].idInIdTable = ret;
			//getFunction так же возвращает номер функции в таблице идентификаторов, т.к. лексический анализ, привязал её к переменной

			if (function.parm_count != callParmList.size())
			{
				throw ERROR_THROW_WNAME(502, lexTable->table[i].stringN,
					string(idTable->table[lexTable->table[i].idInIdTable].id))
			}

			//сравнение списка параметров
			for (auto i1 = callParmList.begin(), i2 = function.parms.begin(); i1 != callParmList.end(), i2 != function.parms.end(); ++i1, ++i2)
			{
				if (*i1 != *i2)
				{
					throw ERROR_THROW_WNAME(502, lexTable->table[i].stringN,
						string(idTable->table[lexTable->table[i].idInIdTable].id));
				}
			}
			continue;
		}
		if (lexTable->table[i].lexem == LEX_EQUAL)
		{
			int currentid = i + 1;
			int typeLastId = idTable->table[lexTable->table[i - 1].idInIdTable].datatype;
			switch (typeLastId)
			{
			case IT::IDDATATYPE::INT:
				{
					while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
					{
						if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem ==
							LEX_LITERAL)
						{
							if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::INT)
							{
								if (lexTable->table[currentid - 2].lexem == LEX_STRLEN || lexTable->table[currentid - 2]
									.lexem == LEX_DRAND)
								{
									currentid++;
									continue;
								}
								throw ERROR_THROW_WNAME(503, lexTable->table[i].stringN,
								                        string(idTable->table[lexTable->table[currentid].idInIdTable].id
								                        ));
							}
							if (idTable->table[lexTable->table[currentid].idInIdTable].type == IT::IDTYPE::F)
							{
								int openScopeCounter = 1;
								int closeScopeCounter = 0;
								currentid += 2;
								do
								{
									if (lexTable->table[currentid].lexem == LEX_LEFTHESIS) openScopeCounter++;
									if (lexTable->table[currentid].lexem == LEX_RIGHTHESIS) closeScopeCounter++;
									currentid++;
								}
								while (openScopeCounter != closeScopeCounter);
							}
						}
						if (lexTable->table[currentid].lexem == LEX_SEMICOLON) break;
						currentid++;
					}
					haveReturn = true;
					continue;
				}
			case IT::IDDATATYPE::STR:
				{
					while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
					{
						int lexCount = 0;
						if (lexTable->table[currentid].lexem == LEX_STRLEN)
							throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN, "strlen возвращает число");
						if (lexTable->table[currentid].lexem == LEX_DRAND)
							throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN,
							                        "rand() возвращает рандомное число");
						if (lexTable->table[currentid].lexem == LEX_OPERATOR)
							throw ERROR_THROW_IN(507, lexTable->table[currentid].stringN, -1);

						if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem ==
							LEX_LITERAL)
						{
							if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::STR)
								throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN, "");
							if (idTable->table[lexTable->table[currentid].idInIdTable].type == IT::IDTYPE::F)
							{
								int openScopeCounter = 1;
								int closeScopeCounter = 0;
								currentid += 2;
								do
								{
									if (lexTable->table[currentid].lexem == LEX_LEFTHESIS) openScopeCounter++;
									if (lexTable->table[currentid].lexem == LEX_RIGHTHESIS) closeScopeCounter++;
									currentid++;
								}
								while (openScopeCounter != closeScopeCounter);
							}
							lexCount++;
							if (lexCount > 1)
								throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN,
								                        string(idTable->table[lexTable->table[currentid].idInIdTable].id
								                        ));
						}
						else
							throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN, string(""));
						if (lexTable->table[currentid].lexem == LEX_SEMICOLON)
							break;
						currentid++;
						haveReturn = true;
					}
					haveReturn = true;
					continue;
				}
			case IT::IDDATATYPE::CHAR:
				{
					while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
					{
						int lexCount = 0;
						if (lexTable->table[currentid].lexem == LEX_STRLEN)
							throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN, "strlen возвращает число");
						if (lexTable->table[currentid].lexem == LEX_DRAND)
							throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN,
							                        "rand() возвращает рандомное число");
						if (lexTable->table[currentid].lexem == LEX_OPERATOR)
							throw ERROR_THROW_IN(508, lexTable->table[currentid].stringN, -1);
						if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem ==
							LEX_LITERAL)
						{
							if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::CHAR)
								throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN, "");
							if (idTable->table[lexTable->table[currentid].idInIdTable].type == IT::IDTYPE::F)
							{
								int openScopeCounter = 1;
								int closeScopeCounter = 0;
								currentid += 2;
								do
								{
									if (lexTable->table[currentid].lexem == LEX_LEFTHESIS) openScopeCounter++;
									if (lexTable->table[currentid].lexem == LEX_RIGHTHESIS) closeScopeCounter++;
									currentid++;
								}
								while (openScopeCounter != closeScopeCounter);
							}
							lexCount++;
							if (lexCount > 1)
								throw ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN,
								                        string(idTable->table[lexTable->table[currentid].idInIdTable].id
								                        ));
						}
						else
							ERROR_THROW_WNAME(503, lexTable->table[currentid].stringN, string(""));
						if (lexTable->table[currentid].lexem == LEX_SEMICOLON)
							break;
						currentid++;
						haveReturn = true;
					}
					haveReturn = true;
					continue;
				}

			default:
				break;
			}
		}

		if (lexTable->table[i].lexem == LEX_STRLEN)
		{
			int leftBracket = 1;
			int rightBracket = 0;
			int currentid = i + 2;
			int countParm = 0;
			while (leftBracket != rightBracket)
			{
				if (lexTable->table[currentid].lexem == LEX_LEFTHESIS) leftBracket++;
				if (lexTable->table[currentid].lexem == LEX_RIGHTHESIS) rightBracket++;
				if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem == LEX_LITERAL)
				{
					countParm++;
					if (countParm > 1)
					{
						throw ERROR_THROW_WNAME(506, lexTable->table[currentid].stringN, string(""))
					}
					if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::STR)
					{
						throw ERROR_THROW_WNAME(505, lexTable->table[currentid].stringN,
						                        idTable->table[lexTable->table[currentid].idInIdTable].id)
					}
				}
				currentid++;
			}
		}

		if (lexTable->table[i].lexem == LEX_DRAND)
		{
			int leftBracket = 1;
			int rightBracket = 0;
			int currentid = i + 2;
			int countParm = 0;
			while (leftBracket != rightBracket)
			{
				if (lexTable->table[currentid].lexem == LEX_LEFTHESIS) leftBracket++;
				if (lexTable->table[currentid].lexem == LEX_RIGHTHESIS) rightBracket++;
				if (lexTable->table[currentid].lexem == LEX_ID || lexTable->table[currentid].lexem == LEX_LITERAL)
				{
					countParm++;
					if (idTable->table[lexTable->table[currentid].idInIdTable].datatype != IT::IDDATATYPE::INT)
					{
						throw ERROR_THROW_WNAME(510, lexTable->table[currentid].stringN,
						                        idTable->table[lexTable->table[currentid].idInIdTable].id)
					}
				}
				currentid++;
			}
			if (countParm == 0)
				lexTable->table[i].lexem = LEX_SRAND;
			else if (countParm != 2 && countParm != 0)
			{
				throw ERROR_THROW_WNAME(509, lexTable->table[currentid].stringN, string(""))
			}
		}
	}
}

IT::Entry semantic::getFunction(const IT::Entry& callFunc, int& ret, std::list<int>& listnumberFunctionInIdTable,
                                std::list<IT::Entry>& functionList)
{
	ret = -1;
	int ind = 0;
	for (auto i : functionList)
	{
		if (callFunc.id == i.id)
		{
			int ind2 = 0;
			for (auto j : listnumberFunctionInIdTable)
			{
				if (ind2 == ind)
				{
					ret = j;
					break;
				}
				ind2++;
			}
			return i;
		}
		ind++;
	}
	return IT::Entry();
}
