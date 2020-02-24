#include "pch.h"

namespace Error
{
	ERRORR errors[ERROR_MAX_ENTRY]
	{
		ERROR_ENTRY(0, "| SYS | Недопустимый код ошибки"),
		ERROR_ENTRY(1, "| SYS | Системный сбой"),


		ERROR_ENTRY(100, "| INN | Параметр -in должен быть задан"),
		ERROR_ENTRY(104, "| INN | Превышена длина входного параметра"),
		ERROR_ENTRY(110, "| INN | Ошибка при открытии файла с иходным кодом (-in)"),
		ERROR_ENTRY(111, "| INN | Недопустимый символ в исходном коде (-in): "),
		ERROR_ENTRY(112, "| INN | Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "| INN | Превышен максимальный размер исходного кода"),


		ERROR_ENTRY(300, "| LEX | Превышен размер таблицы лексем"),
		ERROR_ENTRY(301, "| LEX | Превышен размер таблицы идентификаторов"),
		ERROR_ENTRY(302, "| LEX | Имя идентификатора не может начинаться с цифры: "),
		ERROR_ENTRY(303, "| LEX | Превышен максимальный размер строкового литерала "),
		ERROR_ENTRY(304, "| LEX | Идентификатору не может быть присвоено имя ключевого слова: "),
		ERROR_ENTRY(305, "| LEX | Нераспознанная лексема: "),
		ERROR_ENTRY(306, "| LEX | Превышено максимальное значение числового литерала: "),


		ERROR_ENTRY(500, "| SEM | Неверный тип параметра rback: "),
		ERROR_ENTRY(501, "| SEM | Функция не найдена: "),
		ERROR_ENTRY(502, "| SEM | Превышено количество параметров: "),
		ERROR_ENTRY(503, "| SEM | Несоответствие типов левой и правой части выражения: "),
		ERROR_ENTRY(505, "| SEM | strlen: аргумент не является строкой: "),
		ERROR_ENTRY(506, "| SEM | strlen: не может содержать более одного аргумента"),
		ERROR_ENTRY(507, "| SEM | Операторы не применимы к строкам"),
		ERROR_ENTRY(508, "| SEM | Операторы не применимы к символам"),
		ERROR_ENTRY(509, "| SEM | rand(): может принимать только 2 аргумента"),
		ERROR_ENTRY(510, "| SEM | rand(): аргумент не является числом: "),
		ERROR_ENTRY(511, "| SEM | Необъявленный идентификатор: "),
		ERROR_ENTRY(512, "| SEM | Повторное объявление функции: "),
		ERROR_ENTRY(513, "| SEM | Повторное объявление идентификатора: "),
		ERROR_ENTRY(514, "| SEM | Функция main объявлена более одного раза"),
		ERROR_ENTRY(515, "| SEM | Отсутствует функция main"),
		ERROR_ENTRY(516, "| SEM | Функция не может возвращать функцию"),
		ERROR_ENTRY(517, "| SEM | Отсутствие rback. Функция должна возвращать значение: "),


		ERROR_ENTRY(700, "| SYN | Неверная структура программы"),
		ERROR_ENTRY(701, "| SYN | Ошибочный оператор"),
		ERROR_ENTRY(702, "| SYN | Ошибка в выражении"),
		ERROR_ENTRY(703, "| SYN | Ошибка в параметрах функции"),
		ERROR_ENTRY(704, "| SYN | Ошибка программной конструкции"),
		ERROR_ENTRY(705, "| SYN | Ошибка, неверная структура параметров функции"),
		ERROR_ENTRY(706, "| SYN | Превышено количество синтаксических ошибок"),
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
