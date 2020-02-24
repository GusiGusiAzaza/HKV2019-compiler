#include "pch.h"
using namespace std;

namespace polishNotation
{
	int operationPriority(const LT::Entry& entry)
	{
		int priority;
		switch (entry.operatorType)
		{
		case '(': priority = 0;
			break;
		case '+': priority = 2;
			break;
		case '-': priority = 2;
			break;
		case '*': priority = 3;
			break;
		case '>': priority = 4;
			break;
		case '<': priority = 4;
			break;
		default:
			priority = -1;
			break;
		}
		return priority;
	}

	bool PolishNotation(int lexTablePos, LT::LexTable* lexTable, IT::IdTable* idTable)
	{
		std::list<LT::Entry> outList;
		std::stack<LT::Entry> stack;
		std::stack<LT::Entry> parmStack;
		int i = 0;
		for (i = lexTablePos; lexTable->table[i].lexem != LEX_SEMICOLON; i++)
		{
			if ((lexTable->table[i].lexem == LEX_ID && idTable->table[lexTable->table[i].idInIdTable].type == IT::IDTYPE
				::F) || lexTable->table[i].lexem == LEX_DRAND)
			{
				const int tmp = i; //сохраняет запись функции
				while (lexTable->table[i].lexem != ')')
				{
					i++;
					if (lexTable->table[i].lexem == LEX_ID || lexTable->table[i].lexem == LEX_LITERAL)
					{
						parmStack.push(lexTable->table[i]);
					}
				}
				while (!parmStack.empty())
				{
					outList.push_back(parmStack.top());
					parmStack.pop();
				}
				outList.emplace_back('!', lexTable->table[i].stringN);
				outList.push_back(lexTable->table[tmp]);
				continue;
			}
			if (lexTable->table[i].lexem == LEX_ID || lexTable->table[i].lexem == LEX_LITERAL)
			{
				outList.push_back(lexTable->table[i]);
				continue;
			}
			if (lexTable->table[i].lexem == LEX_LEFTHESIS)
			{
				stack.push(lexTable->table[i]);
				continue;
			}
			if (lexTable->table[i].lexem == LEX_RIGHTHESIS)
			{
				while (stack.top().lexem != LEX_LEFTHESIS)
				{
					outList.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
				continue;
			}
			if (stack.empty() || operationPriority(stack.top()) < operationPriority(lexTable->table[i]))
			{
				stack.push(lexTable->table[i]);
				continue;
			}
			if (operationPriority(stack.top()) >= operationPriority(lexTable->table[i]))
			{
				while (!stack.empty() && operationPriority(stack.top()) >= operationPriority(lexTable->table[i]))
				{
					outList.push_back(stack.top());
					stack.pop();
				}
				if (stack.empty() || operationPriority(stack.top()) < operationPriority(lexTable->table[i]))
				{
					stack.push(lexTable->table[i]);
				}
			}
		}
		const int indSemicolon = i;
		while (!stack.empty())
		{
			outList.push_back(stack.top());
			stack.pop();
		}
		int stringNumber = 0;
		for (i = lexTablePos; i < indSemicolon; i++)
		{
			if (!outList.empty())
			{
				lexTable->table[i] = outList.front();
				outList.pop_front();
				stringNumber = lexTable->table[i].stringN;
			}
			else
			{
				lexTable->table[i] = LT::Entry('@', stringNumber);
			}
		}
		return false;
	}
}
