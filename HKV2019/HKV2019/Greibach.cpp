#include "pch.h"

#define GRB_ERROR_SERIES 700

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 6, //Стартовый символ 
	                  Rule(NS('S'), GRB_ERROR_SERIES + 0,
	                       2,
	                       Rule::Chain(5, TS('t'), TS('f'), TS('i'), NS('F'), NS('S')),
	                       Rule::Chain(4, TS('m'), TS('{'), NS('B'), TS('}'))
	                  ),
	                  Rule(NS('B'), GRB_ERROR_SERIES + 1, // Тело программной конструкции(проверка операторов)
	                       17,
	                       Rule::Chain(5, TS('t'), TS('c'), TS('i'), TS(';'), NS('B')),
	                       Rule::Chain(4, TS('t'), TS('c'), TS('i'), TS(';')),
	                       Rule::Chain(7, TS('t'), TS('c'), TS('i'), TS('='), NS('E'), TS(';'), NS('B')),
	                       Rule::Chain(6, TS('t'), TS('c'), TS('i'), TS('='), NS('E'), TS(';')),
	                       Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('B')),
	                       Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
	                       Rule::Chain(6, TS('i'), TS('('), NS('C'), TS(')'), TS(';'), NS('B')),
	                       Rule::Chain(5, TS('i'), TS('('), NS('C'), TS(')'), TS(';')),
	                       Rule::Chain(3, TS('r'), NS('E'), TS(';')),
	                       Rule::Chain(8, TS('o'), TS('('), TS('i'), TS(')'), TS('{'), NS('B'), TS('}'), NS('B')),
	                       Rule::Chain(8, TS('o'), TS('('), TS('l'), TS(')'), TS('{'), NS('B'), TS('}'), NS('B')),
	                       Rule::Chain(7, TS('o'), TS('('), TS('i'), TS(')'), TS('{'), NS('B'), TS('}')),
	                       Rule::Chain(7, TS('o'), TS('('), TS('l'), TS(')'), TS('{'), NS('B'), TS('}')),
	                       Rule::Chain(6, TS('w'), TS('('), TS('i'), TS(')'), TS(';'), NS('B')),
	                       Rule::Chain(6, TS('w'), TS('('), TS('l'), TS(')'), TS(';'), NS('B')),
	                       Rule::Chain(5, TS('w'), TS('('), TS('i'), TS(')'), TS(';')),
	                       Rule::Chain(5, TS('w'), TS('('), TS('l'), TS(')'), TS(';'))
	                  ),
	                  Rule(NS('E'), GRB_ERROR_SERIES + 2, //выражение
	                       16,
	                       Rule::Chain(1, TS('i')),
	                       Rule::Chain(1, TS('l')),
	                       Rule::Chain(5, TS('('), NS('E'), TS(')'), TS('v'), NS('E')),
	                       Rule::Chain(3, TS('('), NS('E'), TS(')')),
	                       Rule::Chain(3, TS('i'), TS('v'), NS('E')),
	                       Rule::Chain(3, TS('l'), TS('v'), NS('E')),
	                       Rule::Chain(6, TS('i'), TS('('), NS('C'), TS(')'), TS('v'), NS('E')),
	                       Rule::Chain(4, TS('i'), TS('('), NS('C'), TS(')')),
	                       Rule::Chain(3, TS('i'), TS('('), TS(')')),
	                       Rule::Chain(5, TS('i'), TS('('), TS(')'), TS('v'), NS('E')),
	                       Rule::Chain(4, TS('e'), TS('('), NS('C'), TS(')')),
	                       Rule::Chain(6, TS('e'), TS('('), NS('C'), TS(')'), TS('v'), NS('E')),
	                       Rule::Chain(3, TS('g'), TS('('), TS(')')),
	                       Rule::Chain(5, TS('g'), TS('('), TS(')'), TS('v'), NS('E')),
	                       Rule::Chain(4, TS('g'), TS('('), NS('C'), TS(')')),
	                       Rule::Chain(6, TS('g'), TS('('), NS('C'), TS(')'), TS('v'), NS('E'))
	                  ),

	                  Rule(NS('P'), GRB_ERROR_SERIES + 3, //параметы функции
	                       2,
	                       Rule::Chain(2, TS('t'), TS('i')),
	                       Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P'))
	                  ),
	                  Rule(NS('C'), GRB_ERROR_SERIES + 4, //Программная конструкция (функция или главная функция)
	                       4,
	                       Rule::Chain(1, TS('i')),
	                       Rule::Chain(1, TS('l')),
	                       Rule::Chain(3, TS('i'), TS(','), NS('C')),
	                       Rule::Chain(3, TS('l'), TS(','), NS('C'))
	                  ),
	                  Rule(NS('F'), GRB_ERROR_SERIES + 5,
	                       2,
	                       Rule::Chain(5, TS('('), TS(')'), TS('{'), NS('B'), TS('}')),
	                       Rule::Chain(6, TS('('), NS('P'), TS(')'), TS('{'), NS('B'), TS('}'))
	                  ));


	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
	//конструктор цепочки - праыой части правила(кол-во символов в цепочке, терминал или нетерминал...)
	{
		nt = new GRBALPHABET[size = psize];
		int* o = reinterpret_cast<int*>(&s);
		for (short i = 0; i < psize; ++i)
		{
			nt[i] = static_cast<GRBALPHABET>(o[i]);
		}
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) //конструктор правила
	{
		//(нетерминал, идентификатор диагностического сообщения, количество цепочек(правых частей правила), множество цепочек (правых частей правила)
		nn = pnn;
		iderror = piderror;
		chains = new Chain[size = psize];
		Chain* o = &c;
		for (int i = 0; i < size; i++)
		{
			chains[i] = o[i];
		}
	};

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
	//конструктор гграматики Грейбаха(стартовый символ, дно стека, количество правил, правила...)
	{
		startN = pstartN;
		stbottomT = pstbottom;
		rules = new Rule[size = psize];
		Rule* o = &r;
		for (int i = 0; i < size; i++)
		{
			rules[i] = o[i];
		}
	};

	Greibach getGreibach()
	{
		return greibach;
	};

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) const
	//получить правило (левый символ правила, возвращаемое правило грамматики)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn)
			k++; //пока К меньше количества правил и пока левый символ правила не равен парметру ф-ции?????????
		if (k < size)
			prule = rules[rc = k]; //возвращаемое правило граматики равно правилу с индексом К
		return rc; //возвращается номер правила или -1
	};

	Rule Greibach::getRule(short n) const
	//получить правило по номеру
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	};

	char* Rule::getCRule(char* b, short nchain) const
	//получить правило в виде N->цепочка (буфер, номер цепочки(правой части) в правиле)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn); //???
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain); //добавляем строку (куда, с какого элемента, строку)
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Chain& pchain, short j) const
	//получить следующую за j подходящую цепочку, вернуть её номер или -1 
	{
		//(первый символ цепочки, возвращаемая цепочка, номер цепочки)
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getChain(char* b) const
	{
		for (int i = 0; i < size; i++)
			b[i] = alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
};
