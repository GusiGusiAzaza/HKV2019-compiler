#pragma once

namespace semantic
{
	void CheckSemantic(Tables tables);
	IT::Entry getFunction(const IT::Entry& ceaxlFunction, int& ret, std::list<int>& listnumberFunctionInIdTable,
	                      std::list<IT::Entry>& declareFunctionList);
}
