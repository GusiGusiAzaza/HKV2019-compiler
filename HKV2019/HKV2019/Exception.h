#pragma once
#define ERROR_THROW(id) Error::geterror(id);
#define ERROR_THROW_IN(id,l,c) Error::geterrorin(id,l,c);
#define ERROR_THROW_WNAME(id,l, name) Error::geterrorwithinfo(id,l,name);
#define ERROR_ENTRY(id,m) {id, m, {-1,-1}}
#define ERROR_MESSAGE_MAXSIZE 200
#define ERROR_ENTRY_NODEF(id)	ERROR_ENTRY(id, "Неопределенная ошибка")


#define ERROR_MAX_ENTRY 1000

namespace Error
{
	struct ERRORR
	{
		int id;
		char message[ERROR_MESSAGE_MAXSIZE];

		struct INN
		{
			short line;
			short col;
		} inext;
	};

	ERRORR geterror(int id);
	ERRORR geterrorin(int id, int line, int col);
	ERRORR geterrorwithinfo(int id, int line, const std::string& idName);
};
