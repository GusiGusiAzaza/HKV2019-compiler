#include "pch.h"

namespace IT
{
	IdTable* IT::Create(int size)
	{
		IdTable* newIdTable = new IdTable;
		newIdTable->maxsize = size;
		newIdTable->table = new Entry[size];
		newIdTable->size = 0;
		return newIdTable;
	}

	int IT::Add(IdTable* idtable, Entry newEntry)
	{
		if (idtable->size > idtable->maxsize)
			throw ERROR_THROW(301)
		idtable->table[idtable->size] = std::move(newEntry);
		return idtable->size++;
	}

	int IT::GetIndexLastElement(IdTable* idtable)
	{
		return (idtable->size - 1);
	}

	void IT::Delete(IdTable* idtable)
	{
		delete idtable->table;
		delete idtable;
	}

	void modifyIdTable(IdTable* idTable)
	{
		for (auto i = 0; i < idTable->size; i++)
		{
			if (idTable->table[i].type == F)
				idTable->table[i].id.append("_f");
			else if (idTable->table[i].id.find("Lit_") == string::npos)
				idTable->table[i].id.append("_i");
		}

		for (auto i = 0; i < idTable->size; i++)
		{
			for (auto j = 0, n = 1; j < i; j++)
			{
				if (idTable->table[i].type == F)
					continue;
				if (idTable->table[i].id.find("Lit_") == string::npos)
				{
					if (idTable->table[i].id == idTable->table[j].id)
					{
						if (n == 1)
							idTable->table[i].id.push_back(n++ + '0');
						else
						{
							idTable->table[i].id.pop_back();
							idTable->table[i].id.push_back(n++ + '0');
						}
					}
				}
			}
		}
	}

	int IT::idInIT(IdTable idTable, const Entry& entry)
	{
		std::string compare;
		std::list<int> coincidences;
		for (int i = 0; i < idTable.size; i++) //перебираем все id
		{
			if (idTable.table[i].id == entry.id)
			{
				for (char j : entry.scope)
				{
					compare += j;
					if (j == ' ')
					{
						if (compare == idTable.table[i].scope) //GLOBAL FLEN //GLOBAL MAIN
							coincidences.push_back(i);
					}
				}
				compare.clear();
			}
		}
		int maxLength = INT_MIN;
		int indViewMaxLength = -1;
		if (coincidences.empty())
		{
			return -1;
		}
		for (auto i : coincidences)
		{
			if (maxLength < static_cast<int>(idTable.table[i].scope.length()))
			{
				indViewMaxLength = i;
				maxLength = idTable.table[i].scope.length();
			}
		}
		return indViewMaxLength;
	}

	Entry::Entry()
	{
		this->datatype = UNDEF;
		this->type = UNDEFF;
		this->string_number = NULL;
		this->scope = "";
	}

	Entry::Entry(int NumberString, char id[ID_MAXSIZE], IDDATATYPE idDataType, IDTYPE idType, iValue value,
	             std::string view, int numberSystem)
	{
		this->string_number = NumberString;
		this->id = id;
		this->datatype = idDataType;
		this->type = idType;
		this->number_system = numberSystem;
		this->value = value;
		this->scope = std::move(view);
	}
}
