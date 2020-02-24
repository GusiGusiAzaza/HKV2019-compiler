#include "pch.h"

#define GRB_ERROR_SERIES 700

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 6, //��������� ������ 
	                  Rule(NS('S'), GRB_ERROR_SERIES + 0,
	                       2,
	                       Rule::Chain(5, TS('t'), TS('f'), TS('i'), NS('F'), NS('S')),
	                       Rule::Chain(4, TS('m'), TS('{'), NS('B'), TS('}'))
	                  ),
	                  Rule(NS('B'), GRB_ERROR_SERIES + 1, // ���� ����������� �����������(�������� ����������)
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
	                  Rule(NS('E'), GRB_ERROR_SERIES + 2, //���������
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

	                  Rule(NS('P'), GRB_ERROR_SERIES + 3, //�������� �������
	                       2,
	                       Rule::Chain(2, TS('t'), TS('i')),
	                       Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('P'))
	                  ),
	                  Rule(NS('C'), GRB_ERROR_SERIES + 4, //����������� ����������� (������� ��� ������� �������)
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
	//����������� ������� - ������ ����� �������(���-�� �������� � �������, �������� ��� ����������...)
	{
		nt = new GRBALPHABET[size = psize];
		int* o = reinterpret_cast<int*>(&s);
		for (short i = 0; i < psize; ++i)
		{
			nt[i] = static_cast<GRBALPHABET>(o[i]);
		}
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) //����������� �������
	{
		//(����������, ������������� ���������������� ���������, ���������� �������(������ ������ �������), ��������� ������� (������ ������ �������)
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
	//����������� ���������� ��������(��������� ������, ��� �����, ���������� ������, �������...)
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
	//�������� ������� (����� ������ �������, ������������ ������� ����������)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn)
			k++; //���� � ������ ���������� ������ � ���� ����� ������ ������� �� ����� �������� �-���?????????
		if (k < size)
			prule = rules[rc = k]; //������������ ������� ��������� ����� ������� � �������� �
		return rc; //������������ ����� ������� ��� -1
	};

	Rule Greibach::getRule(short n) const
	//�������� ������� �� ������
	{
		Rule rc;
		if (n < size)
			rc = rules[n];
		return rc;
	};

	char* Rule::getCRule(char* b, short nchain) const
	//�������� ������� � ���� N->������� (�����, ����� �������(������ �����) � �������)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn); //???
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain); //��������� ������ (����, � ������ ��������, ������)
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Chain& pchain, short j) const
	//�������� ��������� �� j ���������� �������, ������� � ����� ��� -1 
	{
		//(������ ������ �������, ������������ �������, ����� �������)
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
