#include "pch.h"
using namespace std;

namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		if (argc < 1)
			throw ERROR_THROW(100);
		PARM newParm;
		wstring wParm(argv[1]);
		wstring parm;
		if (wParm.length() < 5)
			throw ERROR_THROW(100);
		if (wParm.length() - 4 > PARM_MAX_SIZE)
			throw ERROR_THROW(104);
		for (auto i = 0; i < 4; i++)
		{
			parm += wParm[i];
		}
		if (parm != PARM_IN)
			ERROR_THROW(100);
		int ind = 0;
		for (auto i = 4; i < wParm.length(); i++)
		{
			newParm.in[ind++] = wParm[i];
		}
		newParm.in[ind] = '\0';
		wParm.clear();
		bool isOut = false, isLog = false;
		for (auto i = 2; i < argc; i++)
		{
			parm.clear();
			ind = 0;
			wstring wParm_(argv[i]);
			for (auto j = 0; j < 5; j++)
			{
				parm += wParm_[j];
			}
			if (parm == PARM_OUT)
			{
				isOut = true;
				for (auto j = 5; j < wParm_.length(); j++)
				{
					newParm.out[ind++] = wParm_[j];
				}
				newParm.out[ind] = '\0';
			}
			if (parm == PARM_LOG)
			{
				isLog = true;
				for (auto j = 5; j < wParm_.length(); j++)
				{
					newParm.log[ind++] = wParm_[j];
				}
				newParm.log[ind] = '\0';
			}
		}

		if (!isOut)
		{
			wstring newString(newParm.in);
			newString = newString + L".out";
			ind = 0;
			for (wchar_t i : newString)
				newParm.out[ind++] = i;
			newParm.out[ind] = '\0';
		}

		if (!isLog)
		{
			wstring newString(newParm.in);
			newString = newString + L".log";
			ind = 0;
			for (wchar_t i : newString)
				newParm.log[ind++] = i;
			newParm.log[ind] = '\0';
		}

		return newParm;
	}
}
