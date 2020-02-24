#include "pch.h"
using namespace std;

void codeGeneration::GenerationCode(Tables tables, Parm::PARM parm)
{
	ofstream fout(parm.out + wstring(L".asm"));
	IT::IdTable* idTable = tables.IDTABLE;
	LT::LexTable* lexTable = tables.LEXTABLE;

	fout <<
		".586 \n.model flat, stdcall\nincludelib kernel32.lib \nincludelib libucrt.lib \n\nExitProcess PROTO : DWORD \nGetStdHandle Proto : DWORD \nSetConsoleTitleA PROTO : DWORD\n"
		<< "WriteConsoleA PROTO : DWORD, : DWORD, : DWORD, : DWORD, : DWORD \nwout PROTO pstr : DWORD, _size : DWORD \nintToString PROTO number : DWORD, pstr : DWORD \n\n.stack 4096 \n.const \n\temptstr DB 0\n";
	bool isWordDataOuted = false;
	for (int i = 0; i < idTable->size; i++)
	{
		if (idTable->table[i].type == IT::IDTYPE::L)
		{
			fout << "\t" << idTable->table[i].id << "\t ";
			switch (idTable->table[i].datatype)
			{
			case IT::IDDATATYPE::INT: fout << "\tDWORD ";
				fout << idTable->table[i].value.intvalue << '\n';
				break;
			case IT::IDDATATYPE::CHAR: fout << "\tDB ";
			{
				int length = idTable->table[i].value.stringvalue->len;
				fout << length - 2;
				fout << ',';

				for (int j = 1; j < length - 1; j++)
				{
					fout << static_cast<unsigned int>(static_cast<unsigned char>(idTable->table[i]
						.value.stringvalue->str[j]));
					if (j != length - 2) fout << ',';
				}
				fout << "\t \n";
			}
			break;
			case IT::IDDATATYPE::STR: fout << "\tDB ";
			{
				int length = idTable->table[i].value.stringvalue->len;
				fout << length - 2;
				fout << ',';

				for (int j = 1; j < length - 1; j++)
				{
					if (idTable->table[i].value.stringvalue->str[j] == '@')
					{
						fout << static_cast<unsigned int>(static_cast<unsigned char>('\n'));
					}
					else
					{
						fout << static_cast<unsigned int>(static_cast<unsigned char>(idTable->table[i]
							.value.stringvalue->str[j]));
					}
					if (j != length - 2) fout << ',';
				}
				fout << "\t \n";
			}
			default:
				break;
			}
		}
	}
	if (!isWordDataOuted)
	{
		fout << "\n.data \n" << "\tnumberSize DWORD 0\n\tstrResult byte 11 dup(' ')\n\tseed DWORD 0\n\ttmp DWORD 0\n";
		isWordDataOuted = true;
	}
	for (int i = 0; i < idTable->size; i++)
	{
		if (idTable->table[i].type == IT::IDTYPE::V)
		{
			switch (idTable->table[i].datatype)
			{
			case IT::IDDATATYPE::INT:
			{
				fout << "\t" << idTable->table[i].id << "\t DWORD 0" << '\n';
			}
			break;

			case IT::IDDATATYPE::STR:
			{
				fout << "\t" << idTable->table[i].id << "\t DWORD 0" << '\n';
			}
			break;

			case IT::IDDATATYPE::CHAR:
			{
				fout << "\t" << idTable->table[i].id << "\t DWORD 0" << '\n';
			}
			break;
			default:
				break;
			}
		}
	}
	if (!isWordDataOuted)
	{
		fout << "\n.data \n" << "\tnumberSize DWORD 0\n\tstrResult byte 11 dup(' ')\n\tseed DWORD 0\n\ttmp DWORD 0\n";
		isWordDataOuted = true;
	}
	fout << "\n.code\n";

	fout << "\nstringlen PROC strptr: DWORD"
		<< "\n\tmov esi, [strptr]"
		<< "\n\txor eax, eax"
		<< "\nloop_len:"
		<< "\n\tmov dl, [esi]"
		<< "\n\tcmp dl, 9"
		<< "\n\tjbe done"
		<< "\n\tinc esi"
		<< "\n\tinc eax"
		<< "\n\tjmp loop_len"
		<< "\ndone:"
		<< "\n\tdec eax"
		<< "\n\tret"
		<< "\nstringlen ENDP\n";

	fout << "\nSRandom PROC"
		<< "\n\tpush edx"
		<< "\n\tpush ecx"
		<< "\n\tmov eax, [seed]"
		<< "\n\tor eax, eax"
		<< "\n\tjnz nn"
		<< "\n\trdtsc"
		<< "\n\txor eax, edx"
		<< "\n\tmov [seed], eax"
		<< "\nnn:"
		<< "\n\txor edx, edx"
		<< "\n\tmov ecx, 12773"
		<< "\n\tdiv ecx"
		<< "\n\tmov ecx, eax"
		<< "\n\tmov eax, 16807"
		<< "\n\tmul edx"
		<< "\n\tmov edx, ecx"
		<< "\n\tmov ecx, eax"
		<< "\n\tmov eax, 2836"
		<< "\n\tmul edx"
		<< "\n\tsub ecx, eax"
		<< "\n\txor edx, edx"
		<< "\n\tmov eax, ecx"
		<< "\n\tmov [seed], ecx"
		<< "\n\tmov ecx, 100000"
		<< "\n\tdiv ecx"
		<< "\n\tmov eax, edx"
		<< "\n\tpop ecx"
		<< "\n\tpop edx"
		<< "\n\tret"
		<< "\nSRandom ENDP\n";

	fout << "\nDRandom PROC rmin: DWORD,rmax: DWORD"
		<< "\n\tpush edx"
		<< "\n\tpush ecx"
		<< "\n\tmov ecx, rmax"
		<< "\n\tsub ecx, rmin"
		<< "\n\tinc ecx"
		<< "\n\tcall SRandom"
		<< "\n\txor edx, edx"
		<< "\n\tdiv ecx"
		<< "\n\tmov eax, edx"
		<< "\n\tadd eax, rmin"
		<< "\n\tpop ecx"
		<< "\n\tpop edx"
		<< "\n\tret"
		<< "\nDRandom ENDP\n";

	fout << "\nwout PROC  pstr : DWORD, _size : DWORD"
		<< "\n\tpush eax"
		<< "\n\tINVOKE GetStdHandle, -11"
		<< "\n\tINVOKE WriteConsoleA, eax, pstr, _size, 0, 0"
		<< "\n\tpop eax"
		<< "\n\tret"
		<< "\nwout ENDP\n";

	fout << "\nintToString PROC number: DWORD, pstr: DWORD\n"
		<< "\tpush eax\n"
		<< "\tpush ebx\n"
		<< "\tpush ecx\n"
		<< "\tpush edi\n"
		<< "\tpush esi\n"
		<< "\tmov esi, OFFSET strResult\n"
		<< "\tmov ecx, sizeof strResult\n"
		<< "\tmov al, ' '\n"
		<< "CLEARSTR:\n"
		<< "\tmov [esi], al\n"
		<< "\tinc esi\n"
		<< "\tLOOP CLEARSTR\n"
		<< "\tmov edi, pstr\n"
		<< "\tmov esi, 0\n"
		<< "\tcdq\n"
		<< "\tmov eax, number\n"
		<< "\tmov ebx, 10\n"
		<< "\tdiv ebx\n"
		<< "plus :\n"
		<< "\tpush dx\n"
		<< "\tinc esi\n"
		<< "\ttest eax, eax\n"
		<< "\tjz fin\n"
		<< "\tcdq\n"
		<< "\tdiv ebx\n"
		<< "\tjmp plus\n"
		<< "fin :\n"
		<< "\tmov ecx, esi\n"
		<< "write :\n"
		<< "\tpop bx \n"
		<< "\tadd bl, '0'\n"
		<< "\tmov[edi], bl\n"
		<< "\tinc edi\n"
		<< "\tloop write\n"
		<< "\tmov ecx, sizeof strResult\n"
		<< "\tmov esi, OFFSET strResult\n"
		<< "COUNTER :\n"
		<< "\tmov al, [esi]\n"
		<< "\tcmp al, 32\n"
		<< "\tjz IC\n"
		<< "\tinc numberSize\n"
		<< "IC :\n"
		<< "\tinc esi\n"
		<< "\tLOOP COUNTER\n"
		<< "\tpop esi\n"
		<< "\tpop edi\n"
		<< "\tpop ecx\n"
		<< "\tpop ebx\n"
		<< "\tpop eax\n"
		<< "\tret\n"
		<< "intToString ENDP\n";


	string lastDeclaredFunction;
	IT::IDDATATYPE typeLastFunction;
	string viewLastCycle;
	int loopCount = 0;
	for (int i = 0; i < lexTable->size; i++)
	{
		if (lexTable->table[i].lexem == LEX_FUNCTION)
		{
			if (!lastDeclaredFunction.empty())
			{
				fout << lastDeclaredFunction << " ENDP\n";
				lastDeclaredFunction = "";
			}
			fout << "\n" << string(idTable->table[lexTable->table[i + 1].idInIdTable].id) << " PROC ";
			int currentid = i + 3;

			while (lexTable->table[currentid].lexem != ')')
			{
				if (lexTable->table[currentid].lexem == LEX_ID)
				{
					fout << idTable->table[lexTable->table[currentid].idInIdTable].id;
					fout << " : ";
					switch (idTable->table[lexTable->table[currentid].idInIdTable].datatype)
					{
					case IT::IDDATATYPE::INT:
						fout << "DWORD ";
						break;
					case IT::IDDATATYPE::STR:
						fout << "DWORD ";
						break;
					case IT::IDDATATYPE::CHAR:
						fout << "DWORD ";
						break;
					default:
						break;
					}
					if (lexTable->table[currentid + 1].lexem != ')') fout << ", ";
				}
				currentid++;
			}
			fout << '\n';
			typeLastFunction = idTable->table[lexTable->table[i + 1].idInIdTable].datatype;
			lastDeclaredFunction = string(idTable->table[lexTable->table[i + 1].idInIdTable].id);
			i = currentid;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_EQUAL)
		{
			polishNotation::PolishNotation(i + 1, lexTable, idTable);
			int currentid = i;
			while (lexTable->table[currentid].lexem != LEX_SEMICOLON)
			{
				if (lexTable->table[currentid].lexem == LEX_STRLEN)
				{
					fout << "\tcall stringlen\n";
					fout << "\tpush eax\n";
				}

				if (lexTable->table[currentid].lexem == LEX_DRAND)
				{
					fout << "\tcall DRandom\n";
					fout << "\tpush eax\n";
				}

				if (lexTable->table[currentid].lexem == LEX_SRAND)
				{
					fout << "\tpush 100000\n";
					fout << "\tpush 0\n";
					fout << "\tcall DRandom\n";
					fout << "\tpush eax\n";
				}

				if (lexTable->table[currentid].lexem == LEX_ID && idTable->table[lexTable->table[currentid].
					idInIdTable].type == IT::IDTYPE::F)
				{
					fout << "\tcall " << idTable->table[lexTable->table[currentid].idInIdTable].id << '\n';
					fout << "\tpush eax \n";
				}
				else if (lexTable->table[currentid].lexem == LEX_ID)
				{
					fout << "\tpush " << idTable->table[lexTable->table[currentid].idInIdTable].id;
					fout << '\n';
				}
				if (lexTable->table[currentid].lexem == LEX_LITERAL)
				{
					switch (idTable->table[lexTable->table[currentid].idInIdTable].datatype)
					{
					case IT::IDDATATYPE::STR:
					{
						fout << "\tpush ";
						fout << "OFFSET " << idTable->table[lexTable->table[currentid].idInIdTable].id;
					}
					break;
					case IT::IDDATATYPE::CHAR:
					{
						fout << "\tpush ";
						fout << "OFFSET " << idTable->table[lexTable->table[currentid].idInIdTable].id;
					}
					break;
					case IT::IDDATATYPE::INT:
					{
						{
							fout << "\tpush ";
							fout << "\t" << idTable->table[lexTable->table[currentid].idInIdTable].id;
						}
					}
					break;
					default:
						break;
					}
					fout << '\n';
				}
				if (lexTable->table[currentid].lexem == LEX_OPERATOR)
				{
					switch (lexTable->table[currentid].operatorType)
					{
					case '+':
					{
						fout << "\tpop ebx \n" << "\tpop eax \n";
						fout << "\tADD eax, ebx\n";
						fout << "\tpush eax\n";
					}
					break;

					case '-':
					{
						fout << "\tpop ebx \n" << "\tpop eax\n";
						fout << "\tSUB eax, ebx \n";
						fout << "\tpush eax \n";
					}
					break;

					case '*':
					{
						fout << "\tpop ebx \n" << "\tpop eax \n";
						fout << "\tMUL ebx\n";
						fout << "\tpush eax\n";
					}
					break;

					case '>':
					{
						fout << "\tpop ebx \n" << "\tpop eax \n";
						fout << "\tmov cl, bl" << endl;
						fout << "\tshr eax, cl\n";
						fout << "\tpush eax\n";
					}
					break;

					case '<':
					{
						fout << "\tpop ebx \n" << "\tpop eax \n";
						fout << "\tmov cl, bl" << endl;
						fout << "\tshl eax, cl\n";
						fout << "\tpush eax\n";
					}
					break;
					default:
						break;
					}
				}
				currentid++;
			}
			fout << "\tpop " << idTable->table[lexTable->table[i - 1].idInIdTable].id << '\n';
			i = currentid - 1;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_RBACK)
		{
			fout << "\tpush ";
			if (idTable->table[lexTable->table[i + 1].idInIdTable].type == IT::IDTYPE::L)
			{
				if (idTable->table[lexTable->table[i + 1].idInIdTable].datatype == IT::IDDATATYPE::STR ||
					idTable->table[lexTable->table[i + 1].idInIdTable].datatype == IT::IDDATATYPE::CHAR)
				{
					fout << "OFFSET ";
				}
			}
			fout << idTable->table[lexTable->table[i + 1].idInIdTable].id << '\n';
			fout << "\tpop eax\n\tret\n";
			i++;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_WOUT)
		{
			switch (idTable->table[lexTable->table[i + 2].idInIdTable].datatype)
			{
			case IT::IDDATATYPE::INT:
			{
				if (idTable->table[lexTable->table[i + 2].idInIdTable].type == IT::IDTYPE::L)
				{
					{
						fout << "\tINVOKE intToString, " << idTable->table[lexTable->table[i + 2].idInIdTable].id <<
							", ADDR strResult\n";
						fout << "\tINVOKE wout, ADDR strResult, numberSize\n";
						fout << "\tmov numberSize, 0\n";
					}
				}
				else
				{
					fout << "\tINVOKE intToString, " << idTable->table[lexTable->table[i + 2].idInIdTable].id <<
						", ADDR strResult\n";
					fout << "\tINVOKE wout, ADDR strResult, numberSize\n";
					fout << "\tmov numberSize, 0\n";
				}
			}
			break;
			case IT::IDDATATYPE::STR:
			{
				if (idTable->table[lexTable->table[i + 2].idInIdTable].type == IT::IDTYPE::L)
				{
					fout << "\tmov edi, OFFSET " << idTable->table[lexTable->table[i + 2].idInIdTable].id << "\n";
					fout << "\tmov al, [edi]\n";
					fout << "\tinc edi\n";
					fout << "\tINVOKE wout, edi, al\n";
				}
				else
				{
					fout << "\tmov edi, " << idTable->table[lexTable->table[i + 2].idInIdTable].id << "\n";
					fout << "\tmov al, [edi]\n";
					fout << "\tinc edi\n";
					fout << "\tINVOKE wout, edi, al\n";
				}
			}
			break;
			case IT::IDDATATYPE::CHAR:
			{
				if (idTable->table[lexTable->table[i + 2].idInIdTable].type == IT::IDTYPE::L)
				{
					fout << "\tmov edi, OFFSET " << idTable->table[lexTable->table[i + 2].idInIdTable].id << "\n";
					fout << "\tmov al, [edi]\n";
					fout << "\tinc edi\n";
					fout << "\tINVOKE wout, edi, al\n";
				}
				else
				{
					fout << "\tmov edi, " << idTable->table[lexTable->table[i + 2].idInIdTable].id << "\t\n";
					fout << "\tmov al, [edi]\n";
					fout << "\tinc edi\n";
					fout << "\tINVOKE wout, edi, al\n";
				}
			}
			break;
			default:
				break;
			}
			i += 2;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_LOOP)
		{
				fout << "\tmov ecx, " << idTable->table[lexTable->table[i + 2].idInIdTable].id << '\n';
				fout << "LOOP" << loopCount << " :\n";
				fout << "\tmov tmp, ecx\n";
			viewLastCycle = lexTable->table[i].scope;
			i += 2;
			continue;
		}
		if (lexTable->table[i].lexem == LEX_BRACELET)
		{
			if (lexTable->table[i].scope == viewLastCycle)
			{
				fout << "\tmov ecx, tmp\n";
				fout << "\tloop LOOP" << loopCount++ << '\n';
			}
			continue;
		}
		if (lexTable->table[i].lexem == LEX_MAIN)
		{
			if (!lastDeclaredFunction.empty())
			{
				fout << lastDeclaredFunction << "\tENDP\n";
				lastDeclaredFunction = "";
			}
			fout << "\nmain PROC\n";
			continue;
		}
		if (lexTable->table[i].lexem == LEX_ID && lexTable->table[i + 1].lexem == '(')
		{
			polishNotation::PolishNotation(i, lexTable, idTable);
			int currentid = i;
			while (lexTable->table[currentid].lexem != ';')
			{
				if (lexTable->table[currentid].lexem == LEX_ID && idTable->table[lexTable->table[currentid].
					idInIdTable].type == IT::IDTYPE::F)
				{
					fout << "\tcall " << idTable->table[lexTable->table[currentid].idInIdTable].id << '\n';
					fout << "\tpush eax \n";
				}
				if (lexTable->table[currentid].lexem == LEX_ID)
				{
					fout << "\tpush " << idTable->table[lexTable->table[currentid].idInIdTable].id;
				}
				if (lexTable->table[currentid].lexem == LEX_LITERAL)
				{
					switch (idTable->table[lexTable->table[currentid].idInIdTable].datatype)
					{
					case IT::IDDATATYPE::STR:
					{
						fout << "\tpush OFFSET " << idTable->table[lexTable->table[currentid].idInIdTable].id;
						fout << '\n';
					}
					break;
					case IT::IDDATATYPE::CHAR:
					{
						fout << "\tpush OFFSET " << idTable->table[lexTable->table[currentid].idInIdTable].id;
						fout << '\n';
					}
					break;
					case IT::IDDATATYPE::INT:
					{
						fout << "\tpush " << idTable->table[lexTable->table[currentid].idInIdTable].id << '\n';
					}
					default:
						break;
					}
				}
				currentid++;
			}
			i = currentid - 1;
		}
	}
	fout << "\tpush 0\ncall ExitProcess\nmain ENDP\nend main ";
	fout.close();
}
