#include "pch.h"
using namespace std;

int _tmain(const int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Russian");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		const In::INN in = In::getin(parm.in);
		log = Log::getlog(parm.log);
		WriteLog(log);
		WriteParm(log, parm);
		WriteIn(log, in);
		const Tables tables = createTables(in);
		printTables(log, in, parm, tables);

		MFST_TRACE_START(log); // шапка
		MFST::Mfst mfst(tables, GRB::getGreibach()); // инициализация для синтаксического анализатора
		mfst.start(log); // старт синтаксического aнализа
		mfst.savededucation(); // сохранить правила вывода
		mfst.printrules(log);

		semantic::CheckSemantic(tables);

		modifyIdTable(tables.IDTABLE);
		codeGeneration::GenerationCode(tables, parm);
		CreateBat(log, parm);
		cout << "Done" << endl;

		cout << "Желаете открыть консоль VS? (1-5 да, 6-0 нет)" << endl;
		short choice;
		do { cin >> choice; } while (choice < 0 && choice >9);
		if (choice >= 1 && choice <=5)
				Log::openVScmd();
		//Log::runasm();
	}
	catch (Error::ERRORR e)
	{
		cout << "-------------------------------------------------------------------------------------" << endl;
		WriteError(log, e);
		cout << "-------------------------------------------------------------------------------------" << endl;
		system("pause");
	}
	Close(log);
	return 0;
}
