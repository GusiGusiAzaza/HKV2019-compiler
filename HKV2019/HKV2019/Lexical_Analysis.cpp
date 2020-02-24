#include "pch.h"

#define NAMERANDOM 10000000
using namespace fst;
using namespace std;
using namespace LT;
IT::IDDATATYPE DataType = IT::IDDATATYPE::UNDEF;
IT::IDTYPE IdType = IT::IDTYPE::V;
short key = 0;
int mainCount = 0;
int lexemCount = 0;
int randCount = 0;
int loopCount = 0;
int endCount = 0;

string currentView;
list<string> keywords = {
	"integer", "string", "char", "main", "create", "function", "rback", "wout", "strlen", "rand", "loop"
};

void initLexem(string currentLexem, int stringNumber, int poz, LexTable* lexTable, IT::IdTable* idTable)
{
	const char* text = currentLexem.c_str();

	FST fst_Integer(text, 8,
	                NODE(1, RELATION('i', 1)),
	                NODE(1, RELATION('n', 2)),
	                NODE(1, RELATION('t', 3)),
	                NODE(1, RELATION('e', 4)),
	                NODE(1, RELATION('g', 5)),
	                NODE(1, RELATION('e', 6)),
	                NODE(1, RELATION('r', 7)),
	                NODE());

	FST fst_String(text, 7,
	               NODE(1, RELATION('s', 1)),
	               NODE(1, RELATION('t', 2)),
	               NODE(1, RELATION('r', 3)),
	               NODE(1, RELATION('i', 4)),
	               NODE(1, RELATION('n', 5)),
	               NODE(1, RELATION('g', 6)),
	               NODE());

	FST fst_Char(text, 5,
	             NODE(1, RELATION('c', 1)),
	             NODE(1, RELATION('h', 2)),
	             NODE(1, RELATION('a', 3)),
	             NODE(1, RELATION('r', 4)),
	             NODE());

	FST fst_Main(text, 5,
	             NODE(1, RELATION('m', 1)),
	             NODE(1, RELATION('a', 2)),
	             NODE(1, RELATION('i', 3)),
	             NODE(1, RELATION('n', 4)),
	             NODE());

	FST fst_Create(text, 7,
	               NODE(1, RELATION('c', 1)),
	               NODE(1, RELATION('r', 2)),
	               NODE(1, RELATION('e', 3)),
	               NODE(1, RELATION('a', 4)),
	               NODE(1, RELATION('t', 5)),
	               NODE(1, RELATION('e', 6)),
	               NODE());

	FST fst_Function(text, 9,
	                 NODE(1, RELATION('f', 1)),
	                 NODE(1, RELATION('u', 2)),
	                 NODE(1, RELATION('n', 3)),
	                 NODE(1, RELATION('c', 4)),
	                 NODE(1, RELATION('t', 5)),
	                 NODE(1, RELATION('i', 6)),
	                 NODE(1, RELATION('o', 7)),
	                 NODE(1, RELATION('n', 8)),
	                 NODE());

	FST fst_Rback(text, 6,
	              NODE(1, RELATION('r', 1)),
	              NODE(1, RELATION('b', 2)),
	              NODE(1, RELATION('a', 3)),
	              NODE(1, RELATION('c', 4)),
	              NODE(1, RELATION('k', 5)),
	              NODE());

	FST fst_Wout(text, 5,
	             NODE(1, RELATION('w', 1)),
	             NODE(1, RELATION('o', 2)),
	             NODE(1, RELATION('u', 3)),
	             NODE(1, RELATION('t', 4)),
	             NODE());

	FST fst_Strlen(text, 7,
	               NODE(1, RELATION('s', 1)),
	               NODE(1, RELATION('t', 2)),
	               NODE(1, RELATION('r', 3)),
	               NODE(1, RELATION('l', 4)),
	               NODE(1, RELATION('e', 5)),
	               NODE(1, RELATION('n', 6)),
	               NODE());

	FST fst_Rand(text, 5,
	             NODE(1, RELATION('r', 1)),
	             NODE(1, RELATION('a', 2)),
	             NODE(1, RELATION('n', 3)),
	             NODE(1, RELATION('d', 4)),
	             NODE());

	FST fst_Loop(text, 5,
	             NODE(1, RELATION('l', 1)),
	             NODE(1, RELATION('o', 2)),
	             NODE(1, RELATION('o', 3)),
	             NODE(1, RELATION('p', 4)),
	             NODE());

	FST fst_Semicolon(text, 2,
	                  NODE(1, RELATION(';', 1)),
	                  NODE());

	FST fst_Comma(text, 2,
	              NODE(1, RELATION(',', 1)),
	              NODE());

	FST fst_Leftbrace(text, 2,
	                  NODE(1, RELATION('{', 1)),
	                  NODE());

	FST fst_Bracelet(text, 2,
	                 NODE(1, RELATION('}', 1)),
	                 NODE());

	FST fst_Lefthesis(text, 2,
	                  NODE(1, RELATION('(', 1)),
	                  NODE());

	FST fst_Righthesis(text, 2,
	                   NODE(1, RELATION(')', 1)),
	                   NODE());

	FST fst_Operator(text, 2,
	                 NODE(6, RELATION('+', 1), RELATION('-', 1),
	                      RELATION('*', 1), RELATION('/', 1), RELATION('>', 1),
	                      RELATION('<', 1)),
	                 NODE());

	FST fst_Equal(text, 2,
	              NODE(1, RELATION('=', 1)),
	              NODE());

	FST fst_Id(text, 2,
	           NODE(72, RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0),
	                RELATION('f', 0), RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0),
	                RELATION('k', 0),
	                RELATION('l', 0), RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0),
	                RELATION('q', 0),
	                RELATION('r', 0), RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0),
	                RELATION('w', 0),
	                RELATION('x', 0), RELATION('y', 0), RELATION('z', 0),
	                RELATION('0', 0), RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0),
	                RELATION('5', 0), RELATION('6', 0), RELATION('7', 0), RELATION('8', 0), RELATION('9', 0),
	                RELATION('0', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),
	                RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1),
	                RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1),
	                RELATION('f', 1), RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1),
	                RELATION('k', 1),
	                RELATION('l', 1), RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1),
	                RELATION('q', 1),
	                RELATION('r', 1), RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1),
	                RELATION('w', 1),
	                RELATION('x', 1), RELATION('y', 1), RELATION('z', 1)),
	           NODE());

	FST fst_IntegerLiteral(text, 2,
	                       NODE(20, RELATION('0', 0), RELATION('1', 0), RELATION('2', 0),
	                            RELATION('3', 0), RELATION('4', 0), RELATION('5', 0),
	                            RELATION('6', 0), RELATION('7', 0), RELATION('8', 0),
	                            RELATION('9', 0), RELATION('0', 1), RELATION('1', 1),
	                            RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
	                            RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1)),
	                       NODE());

	FST fst_HexLiteral(text, 4,
	                   NODE(1, RELATION('0', 1)),
	                   NODE(1, RELATION('h', 2)),
	                   NODE(32, RELATION('0', 3), RELATION('1', 3), RELATION('2', 3),
	                        RELATION('3', 3), RELATION('4', 3), RELATION('5', 3),
	                        RELATION('6', 3), RELATION('7', 3), RELATION('8', 3),
	                        RELATION('9', 3), RELATION('a', 3), RELATION('b', 3), RELATION('c', 3), RELATION('d', 3),
	                        RELATION('e', 3),
	                        RELATION('f', 3),
	                        RELATION('0', 2), RELATION('1', 2), RELATION('2', 2),
	                        RELATION('3', 2), RELATION('4', 2), RELATION('5', 2),
	                        RELATION('6', 2), RELATION('7', 2), RELATION('8', 2),
	                        RELATION('9', 2), RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2),
	                        RELATION('e', 2),
	                        RELATION('f', 2)),
	                   NODE());

	FST fst_StringLiteral(text, 4,
	                      NODE(1, RELATION('\"', 1)),
	                      NODE(164,
	                           RELATION('!', 2), RELATION('?', 2),
	                           RELATION('%', 2), RELATION('#', 2),
	                           RELATION(':', 2), RELATION('<', 2),
	                           RELATION('>', 2), RELATION('.', 2),
	                           RELATION('{', 2), RELATION('}', 2),
	                           RELATION('(', 2), RELATION(')', 2),
	                           RELATION('=', 2), RELATION('-', 2),
	                           RELATION('+', 2), RELATION('*', 2),
	                           RELATION('\\', 2), RELATION(',', 2),
	                           RELATION(';', 2), RELATION(' ', 2),
	                           RELATION('/', 2),
	                           RELATION('0', 2), RELATION('1', 2),
	                           RELATION('2', 2), RELATION('3', 2),
	                           RELATION('4', 2), RELATION('5', 2),
	                           RELATION('6', 2), RELATION('7', 2),
	                           RELATION('8', 2), RELATION('9', 2),
	                           RELATION('a', 2), RELATION('b', 2),
	                           RELATION('c', 2), RELATION('d', 2),
	                           RELATION('e', 2), RELATION('f', 2),
	                           RELATION('g', 2), RELATION('h', 2),
	                           RELATION('i', 2), RELATION('j', 2),
	                           RELATION('k', 2), RELATION('l', 2),
	                           RELATION('m', 2), RELATION('n', 2),
	                           RELATION('o', 2), RELATION('p', 2),
	                           RELATION('q', 2), RELATION('r', 2),
	                           RELATION('s', 2), RELATION('t', 2),
	                           RELATION('u', 2), RELATION('v', 2),
	                           RELATION('w', 2), RELATION('x', 2),
	                           RELATION('y', 2), RELATION('z', 2),
	                           RELATION('A', 2), RELATION('B', 2),
	                           RELATION('C', 2), RELATION('D', 2),
	                           RELATION('E', 2), RELATION('F', 2),
	                           RELATION('G', 2), RELATION('H', 2),
	                           RELATION('I', 2), RELATION('J', 2),
	                           RELATION('K', 2), RELATION('L', 2),
	                           RELATION('M', 2), RELATION('N', 2),
	                           RELATION('O', 2), RELATION('P', 2),
	                           RELATION('Q', 2), RELATION('R', 2),
	                           RELATION('S', 2), RELATION('T', 2),
	                           RELATION('U', 2), RELATION('V', 2),
	                           RELATION('W', 2), RELATION('X', 2),
	                           RELATION('Y', 2), RELATION('Z', 2),
	                           RELATION('!', 1), RELATION('?', 1),
	                           RELATION('%', 1), RELATION('#', 1),
	                           RELATION(':', 1), RELATION('<', 1),
	                           RELATION('>', 1), RELATION('.', 1),
	                           RELATION('{', 1), RELATION('}', 1),
	                           RELATION('(', 1), RELATION(')', 1),
	                           RELATION('=', 1), RELATION('-', 1),
	                           RELATION('+', 1), RELATION('*', 1),
	                           RELATION('\\', 1), RELATION(',', 1),
	                           RELATION(';', 1), RELATION(' ', 1),
	                           RELATION('/', 1),
	                           RELATION('0', 1), RELATION('1', 1),
	                           RELATION('2', 1), RELATION('3', 1),
	                           RELATION('4', 1), RELATION('5', 1),
	                           RELATION('6', 1), RELATION('7', 1),
	                           RELATION('8', 1), RELATION('9', 1),
	                           RELATION('a', 1), RELATION('b', 1),
	                           RELATION('c', 1), RELATION('d', 1),
	                           RELATION('e', 1), RELATION('f', 1),
	                           RELATION('g', 1), RELATION('h', 1),
	                           RELATION('i', 1), RELATION('j', 1),
	                           RELATION('k', 1), RELATION('l', 1),
	                           RELATION('m', 1), RELATION('n', 1),
	                           RELATION('o', 1), RELATION('p', 1),
	                           RELATION('q', 1), RELATION('r', 1),
	                           RELATION('s', 1), RELATION('t', 1),
	                           RELATION('u', 1), RELATION('v', 1),
	                           RELATION('w', 1), RELATION('x', 1),
	                           RELATION('y', 1), RELATION('z', 1),
	                           RELATION('A', 1), RELATION('B', 1),
	                           RELATION('C', 1), RELATION('D', 1),
	                           RELATION('E', 1), RELATION('F', 1),
	                           RELATION('G', 1), RELATION('H', 1),
	                           RELATION('I', 1), RELATION('J', 1),
	                           RELATION('K', 1), RELATION('L', 1),
	                           RELATION('M', 1), RELATION('N', 1),
	                           RELATION('O', 1), RELATION('P', 1),
	                           RELATION('Q', 1), RELATION('R', 1),
	                           RELATION('S', 1), RELATION('T', 1),
	                           RELATION('U', 1), RELATION('V', 1),
	                           RELATION('W', 1), RELATION('X', 1),
	                           RELATION('Y', 1), RELATION('Z', 1)),
	                      NODE(1, RELATION('\"', 3)),
	                      NODE());

	FST fst_CharLiteral(text, 4,
	                    NODE(1, RELATION('\'', 1)),
	                    NODE(132,
	                         RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2),
	                         RELATION('e', 2), RELATION('f', 2), RELATION('g', 2), RELATION('h', 2), RELATION('i', 2),
	                         RELATION('j', 2),
	                         RELATION('k', 2), RELATION('l', 2), RELATION('m', 2), RELATION('n', 2), RELATION('o', 2),
	                         RELATION('p', 2),
	                         RELATION('q', 2), RELATION('r', 2), RELATION('s', 2), RELATION('t', 2), RELATION('u', 2),
	                         RELATION('v', 2),
	                         RELATION('w', 2), RELATION('x', 2), RELATION('y', 2), RELATION('z', 2), RELATION('0', 2),
	                         RELATION('2', 2),
	                         RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2), RELATION('6', 2),
	                         RELATION('7', 2),
	                         RELATION('8', 2), RELATION('9', 2), RELATION('а', 2), RELATION('б', 2), RELATION('в', 2),
	                         RELATION('г', 2),
	                         RELATION('д', 2), RELATION('е', 2), RELATION('ё', 2), RELATION('ж', 2), RELATION('з', 2),
	                         RELATION('и', 2),
	                         RELATION('й', 2), RELATION('к', 2), RELATION('л', 2), RELATION('м', 2), RELATION('н', 2),
	                         RELATION('о', 2),
	                         RELATION('п', 2), RELATION('р', 2), RELATION('с', 2), RELATION('т', 2), RELATION('у', 2),
	                         RELATION('ф', 2),
	                         RELATION('х', 2), RELATION('ц', 2), RELATION('ч', 2), RELATION('ш', 2), RELATION('щ', 2),
	                         RELATION('ъ', 2),
	                         RELATION('ы', 2), RELATION('ь', 2), RELATION('э', 2), RELATION('ю', 2), RELATION('я', 2),
	                         RELATION(' ', 2),
	                         RELATION('A', 2), RELATION('B', 2), RELATION('C', 2), RELATION('D', 2), RELATION('E', 2),
	                         RELATION('F', 2), RELATION('G', 2), RELATION('H', 2), RELATION('I', 2), RELATION('J', 2),
	                         RELATION('K', 2),
	                         RELATION('L', 2), RELATION('M', 2), RELATION('N', 2), RELATION('O', 2), RELATION('P', 2),
	                         RELATION('Q', 2),
	                         RELATION('R', 2), RELATION('S', 2), RELATION('T', 2), RELATION('U', 2), RELATION('V', 2),
	                         RELATION('W', 2),
	                         RELATION('X', 2), RELATION('Y', 2), RELATION('Z', 2), RELATION('\\', 2), RELATION('А', 2),
	                         RELATION('Б', 2),
	                         RELATION('В', 2), RELATION('Г', 2), RELATION('Д', 2), RELATION('Е', 2), RELATION('Ё', 2),
	                         RELATION('Ж', 2),
	                         RELATION('З', 2), RELATION('И', 2), RELATION('Й', 2), RELATION('К', 2), RELATION('Л', 2),
	                         RELATION('М', 2),
	                         RELATION('Н', 2), RELATION('О', 2), RELATION('П', 2), RELATION('Р', 2), RELATION('С', 2),
	                         RELATION('Т', 2),
	                         RELATION('У', 2), RELATION('Ф', 2), RELATION('Х', 2), RELATION('Ц', 2), RELATION('Ч', 2),
	                         RELATION('Ш', 2),
	                         RELATION('Щ', 2), RELATION('Ъ', 2), RELATION('Ы', 2), RELATION('Ь', 2), RELATION('Э', 2),
	                         RELATION('Ю', 2),
	                         RELATION('Я', 2), RELATION(':', 2), RELATION('-', 2), RELATION('"', 2)),
	                    NODE(1, RELATION('\'', 3)),
	                    NODE());

	if (execute(fst_Integer))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		DataType = IT::IDDATATYPE::INT;
		Add(lexTable, Entry(LEX_INTEGER, stringNumber));
		key++;
		return;
	}

	if (execute(fst_String))
	{
		if (key > 1)
			throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		DataType = IT::IDDATATYPE::STR;
		Add(lexTable, Entry(LEX_STRING, stringNumber));
		key++;
		return;
	}

	if (execute(fst_Char))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		DataType = IT::IDDATATYPE::CHAR;
		Add(lexTable, Entry(LEX_STRING, stringNumber));
		key++;
		return;
	}

	if (execute(fst_Create))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		IdType = IT::IDTYPE::V;
		Add(lexTable, Entry(LEX_CREATE, stringNumber));
		key++;
		return;
	}

	if (execute(fst_Function))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		IdType = IT::IDTYPE::F;
		Add(lexTable, Entry(LEX_FUNCTION, stringNumber));
		key++;
		return;
	}

	if (execute(fst_Rback))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		IdType = IT::IDTYPE::UNDEFF;
		DataType = IT::IDDATATYPE::UNDEF;
		Add(lexTable, Entry(LEX_RBACK, stringNumber));
		return;
	}

	if (execute(fst_Wout))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_WOUT, stringNumber));
		return;
	}

	if (execute(fst_Strlen))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_STRLEN, stringNumber));
		return;
	}

	if (execute(fst_Rand))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_DRAND, stringNumber));
		return;
	}

	if (execute(fst_Loop))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		IdType = IT::IDTYPE::UNDEFF;
		DataType = IT::IDDATATYPE::UNDEF;
		char buf[5];
		_itoa_s(loopCount++, buf, 10);
		currentView = currentView + ' ' + "LOOP_" + string(buf) + ' ';
		Add(lexTable, Entry(LEX_LOOP, stringNumber, '`', -1, currentView));
		return;
	}

	if (execute(fst_Main))
	{
		if (key > 1) throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);
		mainCount++;
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		currentView = currentView + ' ' + "MAIN" + ' ';
		Add(lexTable, Entry(LEX_MAIN, stringNumber));
		return;
	}

	if (execute(fst_Semicolon))
	{
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_SEMICOLON, stringNumber));
		return;
	}

	if (execute(fst_Comma))
	{
		DataType = IT::IDDATATYPE::UNDEF;
		Add(lexTable, Entry(LEX_COMMA, stringNumber));
		return;
	}

	if (execute(fst_Leftbrace))
	{
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_LEFTBRACE, stringNumber));
		return;
	}

	if (execute(fst_Bracelet))
	{
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_BRACELET, stringNumber, '`', -1, currentView));
		int indPrevLastSpace = 0;
		int countSPACE = 0;
		for (int i = currentView.length() - 1; i >= 0; i--)
		{
			if (currentView[i] == ' ')
			{
				countSPACE++;
				if (countSPACE == 2)
				{
					indPrevLastSpace = i;
					break;
				}
			}
		}
		string tmp;
		for (int i = 0; i <= indPrevLastSpace; i++)
		{
			tmp += currentView[i];
		}
		currentView = tmp;
		tmp.clear();
		endCount++;
		return;
	}

	if (execute(fst_Lefthesis))
	{
		if (IdType == IT::IDTYPE::F) IdType = IT::IDTYPE::P;
		Add(lexTable, Entry(LEX_LEFTHESIS, stringNumber));
		DataType = IT::IDDATATYPE::UNDEF;
		return;
	}

	if (execute(fst_Righthesis))
	{
		IdType = IT::IDTYPE::UNDEFF;
		DataType = IT::IDDATATYPE::UNDEF;
		Add(lexTable, Entry(LEX_RIGHTHESIS, stringNumber));
		return;
	}

	if (execute(fst_Operator))
	{
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_OPERATOR, stringNumber, text[0]));
		return;
	}

	if (execute(fst_Equal))
	{
		DataType = IT::IDDATATYPE::UNDEF;
		IdType = IT::IDTYPE::UNDEFF;
		Add(lexTable, Entry(LEX_EQUAL, stringNumber));
		return;
	}

	if (execute(fst_IntegerLiteral))
	{
		IT::iValue value;
		
		if (strtoull(text, nullptr, 10) > TI_INT_MAXSIZE)
		{
			throw ERROR_THROW_WNAME(306, stringNumber, currentLexem);
		}
		value.intvalue = stoul(text, nullptr, 10);
		char name[20] = "Lit_";
		char num[5];
		_itoa_s(lexemCount++, num, 10);
		strcat_s(name, num);
		int numberInIdTable = IT::Add(idTable, IT::Entry(stringNumber, name, IT::IDDATATYPE::INT, IT::IDTYPE::L,
		                                                 value, currentView));
		Add(lexTable, Entry(LEX_LITERAL, stringNumber, '`', numberInIdTable));
		return;
	}

	if (execute(fst_HexLiteral))
	{
		IT::iValue value;
		replace(currentLexem.begin(), currentLexem.end(), 'h', 'x');
		if (strtoull(text, nullptr, 16) > TI_INT_MAXSIZE)
		{
			throw ERROR_THROW_WNAME(306, stringNumber, currentLexem);
		}
		value.intvalue = std::stoul(text, nullptr, 16);
		char name[20] = "Lit_";
		char num[5];
		_itoa_s(lexemCount++, num, 10);
		strcat_s(name, num);
		int numberInIdTable = IT::Add(idTable, IT::Entry(stringNumber, name, IT::IDDATATYPE::INT, IT::IDTYPE::L,
		                                                 value, currentView, 16));
		Add(lexTable, Entry(LEX_LITERAL, stringNumber, '`', numberInIdTable));
		return;
	}

	if (execute(fst_StringLiteral))
	{
		if (currentLexem.size() > TI_STR_MAXSIZE)
			throw ERROR_THROW_IN(303, stringNumber, -1);
		currentLexem = StringReplacer(currentLexem, "\\n", "@");
		const char* text2 = currentLexem.c_str();
		IT::iValue value;
		strcpy_s(value.stringvalue->str, text2);
		value.stringvalue->len = strlen(value.stringvalue->str);
		char name[20] = "Lit_";
		char num[5];
		_itoa_s(lexemCount++, num, 10);
		strcat_s(name, num);
		int numberInIdTable = IT::Add(idTable, IT::Entry(stringNumber, name, IT::IDDATATYPE::STR, IT::IDTYPE::L, value,
		                                                 currentView));
		Add(lexTable, Entry(LEX_LITERAL, stringNumber, '`', numberInIdTable));
		return;
	}

	if (execute(fst_CharLiteral))
	{
		IT::iValue value;
		strcpy_s(value.stringvalue->str, text);
		value.stringvalue->len = strlen(value.stringvalue->str);
		char name[20] = "Lit_";
		char num[5];
		_itoa_s(lexemCount++, num, 10);
		strcat_s(name, num);
		int numberInIdTable = IT::Add(idTable, IT::Entry(stringNumber, name, IT::IDDATATYPE::CHAR, IT::IDTYPE::L, value,
		                                                 currentView));
		Add(lexTable, Entry(LEX_LITERAL, stringNumber, '`', numberInIdTable));
		return;
	}

	if (execute(fst_Id))
	{
		if (std::isdigit(currentLexem[0]))
			throw ERROR_THROW_WNAME(302, stringNumber, currentLexem);

		if (currentLexem.length() > ID_MAXSIZE)
		{
			currentLexem = currentLexem.substr(0, 15);
			text = const_cast<char*>(currentLexem.c_str());
		}

		IT::iValue value;
		value.intvalue = 0;
		if (!(std::find(keywords.begin(), keywords.end(), currentLexem) == keywords.end()))
			throw ERROR_THROW_WNAME(304, stringNumber, currentLexem);

		IT::Entry myEntry = IT::Entry(stringNumber, const_cast<char*>(text), DataType, IdType, value, currentView, 10);
		if (IdType == IT::IDTYPE::UNDEFF || DataType == IT::IDDATATYPE::UNDEF)
		{
			int numberInIdTable = idInIT(*idTable, myEntry);
			if (numberInIdTable == -1)
			{
				throw ERROR_THROW_WNAME(511, stringNumber, currentLexem);
			}
			Add(lexTable, Entry(LEX_ID, stringNumber, '`', numberInIdTable));
		}
		else
		{
			if (IdType == IT::IDTYPE::F)
			{
				currentView = currentView + ' ' + currentLexem + ' ';
				int numberInIdTable = idInIT(*idTable, myEntry);
				if (numberInIdTable != -1)
					throw ERROR_THROW_WNAME(512, stringNumber, currentLexem);
				numberInIdTable = IT::Add(idTable, myEntry);
				Add(lexTable, Entry(LEX_ID, stringNumber, '`', numberInIdTable));
			}
			else
			{
				int numberInIdTable = idInIT(*idTable, myEntry);
				if (numberInIdTable != -1)
					throw ERROR_THROW_WNAME(513, stringNumber, currentLexem);
				numberInIdTable = IT::Add(idTable, myEntry);
				Add(lexTable, Entry(LEX_ID, stringNumber, '`', numberInIdTable));
			}
		}
		key = 0;
		return;
	}
	throw ERROR_THROW_WNAME(305, stringNumber, currentLexem);
}

Tables createTables(In::INN newIN) //создаем таблицу лексем
{
	currentView = " GLOBAL ";
	Tables newTables;
	LexTable* mainTable = Create(newIN.lexemCount * 10);
	IT::IdTable* idMainTable = IT::Create(newIN.lexemCount * 10);
	int numberString = 1;
	int numberPosition = 1;
	string currentLexem;
	bool quote = false;
	for (int i = 0; i < newIN.size; i++)
	{
		if (newIN.finalText[i] == '\"')
		{
			if (quote) quote = false;
			else quote = true;
			currentLexem += '\"';
		}
		else if (newIN.finalText[i] == ' ' && !quote)
		{
			if (!currentLexem.empty())
			{
				initLexem(currentLexem, numberString, numberPosition, mainTable, idMainTable);
				currentLexem.clear();
			}
		}
		else
		{
			if (newIN.finalText[i] == '\n')
			{
				numberString++;
				numberPosition = 1;
			}
			else currentLexem += newIN.finalText[i];
		}
		numberPosition++;
	}
	newTables.LEXTABLE = mainTable;
	newTables.IDTABLE = idMainTable;
	newTables.LEXTABLE->countEnd = endCount;
	if (mainCount > 1)
		throw ERROR_THROW(514)
	if (mainCount < 1)
		throw ERROR_THROW(515)
	return newTables;
}

string StringReplacer(const std::string& inputStr, const std::string& src, const std::string& dst)
{
	std::string result(inputStr);

	size_t pos = result.find(src);
	while (pos != std::string::npos)
	{
		result.replace(pos, src.size(), dst);
		pos = result.find(src, pos);
	}

	return result;
}
