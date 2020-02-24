#include "pch.h"

namespace Error
{
	ERRORR errors[ERROR_MAX_ENTRY]
	{
		ERROR_ENTRY(0, "| SYS | ������������ ��� ������"),
		ERROR_ENTRY(1, "| SYS | ��������� ����"),


		ERROR_ENTRY(100, "| INN | �������� -in ������ ���� �����"),
		ERROR_ENTRY(104, "| INN | ��������� ����� �������� ���������"),
		ERROR_ENTRY(110, "| INN | ������ ��� �������� ����� � ������� ����� (-in)"),
		ERROR_ENTRY(111, "| INN | ������������ ������ � �������� ���� (-in): "),
		ERROR_ENTRY(112, "| INN | ������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY(113, "| INN | �������� ������������ ������ ��������� ����"),


		ERROR_ENTRY(300, "| LEX | �������� ������ ������� ������"),
		ERROR_ENTRY(301, "| LEX | �������� ������ ������� ���������������"),
		ERROR_ENTRY(302, "| LEX | ��� �������������� �� ����� ���������� � �����: "),
		ERROR_ENTRY(303, "| LEX | �������� ������������ ������ ���������� �������� "),
		ERROR_ENTRY(304, "| LEX | �������������� �� ����� ���� ��������� ��� ��������� �����: "),
		ERROR_ENTRY(305, "| LEX | �������������� �������: "),
		ERROR_ENTRY(306, "| LEX | ��������� ������������ �������� ��������� ��������: "),


		ERROR_ENTRY(500, "| SEM | �������� ��� ��������� rback: "),
		ERROR_ENTRY(501, "| SEM | ������� �� �������: "),
		ERROR_ENTRY(502, "| SEM | ��������� ���������� ����������: "),
		ERROR_ENTRY(503, "| SEM | �������������� ����� ����� � ������ ����� ���������: "),
		ERROR_ENTRY(505, "| SEM | strlen: �������� �� �������� �������: "),
		ERROR_ENTRY(506, "| SEM | strlen: �� ����� ��������� ����� ������ ���������"),
		ERROR_ENTRY(507, "| SEM | ��������� �� ��������� � �������"),
		ERROR_ENTRY(508, "| SEM | ��������� �� ��������� � ��������"),
		ERROR_ENTRY(509, "| SEM | rand(): ����� ��������� ������ 2 ���������"),
		ERROR_ENTRY(510, "| SEM | rand(): �������� �� �������� ������: "),
		ERROR_ENTRY(511, "| SEM | ������������� �������������: "),
		ERROR_ENTRY(512, "| SEM | ��������� ���������� �������: "),
		ERROR_ENTRY(513, "| SEM | ��������� ���������� ��������������: "),
		ERROR_ENTRY(514, "| SEM | ������� main ��������� ����� ������ ����"),
		ERROR_ENTRY(515, "| SEM | ����������� ������� main"),
		ERROR_ENTRY(516, "| SEM | ������� �� ����� ���������� �������"),
		ERROR_ENTRY(517, "| SEM | ���������� rback. ������� ������ ���������� ��������: "),


		ERROR_ENTRY(700, "| SYN | �������� ��������� ���������"),
		ERROR_ENTRY(701, "| SYN | ��������� ��������"),
		ERROR_ENTRY(702, "| SYN | ������ � ���������"),
		ERROR_ENTRY(703, "| SYN | ������ � ���������� �������"),
		ERROR_ENTRY(704, "| SYN | ������ ����������� �����������"),
		ERROR_ENTRY(705, "| SYN | ������, �������� ��������� ���������� �������"),
		ERROR_ENTRY(706, "| SYN | ��������� ���������� �������������� ������"),
	};

	ERRORR geterror(const int id)
	{
		for (auto& error : errors)
			if (id == error.id)
			{
				error.id = id;
				return error;
			}
		return errors[0];
	}

	ERRORR geterrorin(const int id, const int line, const int col)
	{
		for (auto& error : errors)
			if (id == error.id)
			{
				error.id = id;
				error.inext.line = line;
				error.inext.col = col;
				return error;
			}
		return errors[0];
	}

	ERRORR geterrorwithinfo(int id, int line, const std::string& idName)
	{
		for (auto& error : errors)
			if (id == error.id)
			{
				error.inext.line = line;
				strcat_s(error.message, idName.c_str());
				return error;
			}
		return errors[0];
	}
};
