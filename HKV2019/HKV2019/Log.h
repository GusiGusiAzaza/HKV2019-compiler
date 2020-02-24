#pragma once
#include "Parm.h"
#include "Input.h"
#include "Exception.h"
#include "Lexical_Analysis.h"


namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LOG INITLOG = {L"", nullptr};
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, const char* c, ...);
	void WriteLine(LOG log, const wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::INN in);
	void printTables(LOG log, In::INN input, Parm::PARM parm, Tables tables);
	void WriteError(LOG log, Error::ERRORR error);
	void CreateBat(const LOG log, Parm::PARM parm);
	void openVScmd();
	void runasm();
	void Close(LOG log);
};
