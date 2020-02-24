#include "pch.h"
#include <tlhelp32.h>
#include <dos.h>
using namespace std;

namespace Log
{
	LOG Log::getlog(wchar_t logfile[])
	{
		LOG res;
		res.stream = new ofstream;
		res.stream->open(logfile);
		if (!res.stream->is_open())
		{
			throw ERROR_THROW(112);
		}
		wcscpy_s(res.logfile, logfile);
		return res;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** ptr(&c);
		while (strlen(*ptr))
		{
			*log.stream << *ptr;
			++ptr;
		}
		*log.stream << endl;
	}

	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** ptr(&c);
		while (wcslen(*ptr))
		{
			char cnv[PARM_MAX_SIZE];
			size_t charsConverted(0);
			wcstombs_s(&charsConverted, cnv, *ptr, PARM_MAX_SIZE);
			*log.stream << cnv;
			++ptr;
		}
		*log.stream << endl;
	}

	void WriteLog(LOG log)
	{
		time_t t = time(nullptr);
		tm now;
		localtime_s(&now, &t);
		char tmChars[PARM_MAX_SIZE];
		strftime(tmChars, PARM_MAX_SIZE, "%d.%m.%Y %H:%M:%S", &now);
		*log.stream << "---- Протокол ------- Дата: " << tmChars << endl;
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		*log.stream << "---- Параметры -------" << endl;
		char cnv[PARM_MAX_SIZE];
		size_t charsConverted(0);
		wcstombs_s(&charsConverted, cnv, parm.log, PARM_MAX_SIZE);
		*log.stream << "-log: " << cnv << endl;
		wcstombs_s(&charsConverted, cnv, parm.out, PARM_MAX_SIZE);
		*log.stream << "-out: " << cnv << endl;
		wcstombs_s(&charsConverted, cnv, parm.in, PARM_MAX_SIZE);
		*log.stream << "-in: " << cnv << endl;
	}

	void WriteIn(LOG log, In::INN in)
	{
		*log.stream << "---- Исходные данные -----" << endl;
		*log.stream << "Количество символов: " << in.size << endl;
		*log.stream << "Проигнорировано:     " << in.ignor << endl;
		*log.stream << "Количество строк:    " << in.lines << endl;
	}

	void printTables(LOG log, In::INN input, Parm::PARM parm, Tables tables)
	{
		*log.stream << "\n\n\n\n\n\n---------- Таблица лексем -----------\n\n";
		*log.stream << '1' << "  ";
		for (int i = 0, str = 1; i < tables.LEXTABLE->size; i++)
		{
			if (str != tables.LEXTABLE->table[i].stringN)
			{
				*log.stream << '\n';
				*log.stream << ++str << "  ";
			}
			*log.stream << tables.LEXTABLE->table[i].lexem;
		}


		*log.stream << endl << endl << endl << "---------- Таблица лексем -----------" << endl << endl <<
			setw(5) << left << "№" <<
			setw(10) << left << "str №" <<
			setw(13) << left << "Lexem" <<
			setw(15) << left << "id Num" <<
			setw(17) << left << "operator" <<
			endl << endl;
		for (auto i = 0; i < tables.LEXTABLE->size; i++)
		{
			*log.stream << setw(5) << left << i <<
				setw(10) << left <<
				setw(10) << left << tables.LEXTABLE->table[i].stringN <<
				setw(13) << left;
			*log.stream << tables.LEXTABLE->table[i].lexem;

			*log.stream << setw(15) << left
				<< tables.LEXTABLE->table[i].idInIdTable;

			*log.stream << setw(17) << left
				<< tables.LEXTABLE->table[i].operatorType << endl;
		}
		*log.stream << endl << endl << endl << "---------- Таблица идентификаторов -----------" << endl << endl <<
			setw(5) << left << "№" <<
			setw(10) << left << "id" <<
			setw(13) << left << "idType" <<
			setw(15) << left << "dataType" <<
			setw(35) << left << "value" <<
			setw(38) << left << "scopeName" <<
			endl << endl;
		for (auto i = 0; i < tables.IDTABLE->size; i++)
		{
			*log.stream << setw(5) << left << i <<
				setw(10) << left <<
				setw(10) << left << tables.IDTABLE->table[i].id <<
				setw(13) << left;
			if (tables.IDTABLE->table[i].type == IT::V) *log.stream << "variable";
			if (tables.IDTABLE->table[i].type == IT::F) *log.stream << "function";
			if (tables.IDTABLE->table[i].type == IT::P) *log.stream << "argument";
			if (tables.IDTABLE->table[i].type == IT::L) *log.stream << "literal";

			*log.stream << setw(15) << left;
			if (tables.IDTABLE->table[i].datatype == IT::INT) *log.stream << "integer";
			if (tables.IDTABLE->table[i].datatype == IT::STR) *log.stream << "string";
			if (tables.IDTABLE->table[i].datatype == IT::CHAR) *log.stream << "char";

			*log.stream << setw(35) << left;
			if (static_cast<int>(tables.IDTABLE->table[i].datatype) == 1)
				*log.stream << tables.IDTABLE->table[i]
				               .value.intvalue;
			if (static_cast<int>(tables.IDTABLE->table[i].datatype) == 2)
				*log.stream << tables.IDTABLE->table[i]
				               .value.stringvalue->str;
			if (static_cast<int>(tables.IDTABLE->table[i].datatype) == 3)
				*log.stream << tables.IDTABLE->table[i]
				               .value.stringvalue->str;

			*log.stream << tables.IDTABLE->table[i].scope.c_str() << endl;
		}
	}

	void WriteError(const LOG log, Error::ERRORR error)
	{
		if (log.stream == nullptr || !log.stream->is_open())
		{
			if (error.inext.line == -1 && error.inext.col == -1)
				cout << "Ошибка " << error.id << ": " << error.message << endl;

			else if (error.inext.col == -1)
				cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << endl;

			else
				cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line <<
					", позиция " << error.inext.col << endl;
		}
		else
		{
			if (error.inext.line == -1 && error.inext.col == -1)
			{
				cout << "Ошибка " << error.id << ": " << error.message << endl;
				*log.stream << "Ошибка " << error.id << ": " << error.message << endl;
			}

			else if (error.inext.col == -1)
			{
				cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << endl;
				*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line <<
					endl;
			}

			else
			{
				cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line <<
					", позиция " << error.inext.col << endl;
				*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line <<
					", позиция " << error.inext.col << endl;
			}
		}
	}

	void CreateBat(const LOG log, Parm::PARM parm)
	{
		wstring ws(parm.out);
		string bat(ws.begin(), ws.end());
		bat.append(".asm");
		std::ofstream batfile;
		std::ofstream exebat;
		batfile.open("AsmToExe.bat");
		batfile << "ml ";
		batfile << bat;
		batfile << " /link /SUBSYSTEM:CONSOLE /OUT:";
		batfile << bat.substr(0, bat.find_last_of(".")).append(".exe");
		batfile.close();
		exebat.open("ExeAsm.bat");
		exebat << bat.substr(0, bat.find_last_of(".")).append(".exe");
		exebat.close();
	}

	//bool isProcessRun(LPCWSTR process_name)
	//{
	//	HANDLE hSnap = nullptr;
	//	PROCESSENTRY32 pe32;
	//	pe32.dwSize = sizeof(PROCESSENTRY32);
	//	hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//	if (hSnap != nullptr)
	//	{
	//		if (Process32First(hSnap, &pe32))
	//		{
	//			if (pe32.szExeFile == process_name)
	//				return TRUE;
	//			while (Process32Next(hSnap, &pe32))
	//				if (pe32.szExeFile == process_name)
	//					return TRUE;
	//		}
	//	}
	//	CloseHandle(hSnap);
	//	return FALSE;
	//}
	
	void openVScmd()
	{
		const TCHAR* target = _T("C:\\WINDOWS\\system32\\cmd.exe");
		TCHAR pars[102] = L"%comspec% /k \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Preview\\Common7\\Tools\\VsDevCmd.bat\"";
		//if (isProcessRun(target) == TRUE)
		//	return;
		STARTUPINFO si = {};
		si.cb = sizeof si;
		PROCESS_INFORMATION pi = {};

		if (!CreateProcess(target, pars, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
		{
			cerr << "CreateProcess failed (" << GetLastError() << ").\n";
		}
		else
		{
			WaitForSingleObject(pi.hProcess, 5 * 1000);
			if (PostThreadMessage(pi.dwThreadId, WM_QUIT, 0, 0)) // Good
				cout << "Request to terminate process has been sent!";

			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
	}

	void runasm()
	{
		/*Sleep(3000);*/
		system("AsmToExe.bat");
	}


	void Close(LOG log)
	{
		if (log.stream != nullptr)
		{
			log.stream->close();
			delete log.stream;
		}
	}
};
