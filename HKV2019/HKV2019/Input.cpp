#include "pch.h"

using namespace std;

namespace In
{
	INN getin(wchar_t infile[])
	{
		ifstream fin(infile);
		INN newIn;
		if (!fin.is_open())
			throw ERROR_THROW(110);

		unsigned int fileLength;
		fin.seekg(0, ios::end);
		fileLength = static_cast<unsigned int>(fin.tellg());
		fin.seekg(0, ios::beg);
		if (fileLength > IN_MAX_TEXT_LEN)
			throw ERROR_THROW(113);

		string text;
		int line = 1;
		int col = 1;
		while (!fin.eof())
		{
			string textLine;
			textLine.clear();
			getline(fin, textLine);
			char symb;
			for (char i : textLine)
			{
				symb = i;
				if (newIn.code[static_cast<int>(static_cast<unsigned char>(symb))] == INN::T ||
					newIn.code[static_cast<int>(static_cast<unsigned char>(symb))] == INN::S)
				{
					if (symb == '\t') text += ' ';
					else text += symb;
				}
				else
				{
					if (newIn.code[static_cast<int>(static_cast<unsigned char>(symb))] == INN::F)
					{
						string s;
						s.push_back(static_cast<char>(symb));
						throw ERROR_THROW_WNAME(111, line, s);
					}
					if (newIn.code[static_cast<int>(static_cast<unsigned char>(symb))] == INN::I)
					{
						newIn.ignor++;
					}
					else
						text += static_cast<unsigned char>(newIn.code[static_cast<int>(static_cast<unsigned char>(symb))
						]);
				}
				col++;
			}
			text += '\n';
			line++;
			col = 1;
		}
		text.insert(0, " ");
		string textFormated;
		bool quote = false;
		for (char i : text)
		{
			if (i == '\'' || i == '\"')
			{
				if (!quote) quote = true;
				else quote = false;
			}
			if (newIn.code[static_cast<int>(static_cast<unsigned char>(i))] == INN::S && !quote)
			{
				textFormated = textFormated + ' ' + i + ' ';
			}
			else
			{
				textFormated += i;
			}
		}
		newIn.finalText = new unsigned char[textFormated.length()];
		int indNewInTextFormated = 0;
		bool spaceAdded = false;
		newIn.lexemCount = 10;
		for (char i : textFormated)
		{
			if (i == ' ')
			{
				if (!spaceAdded)
				{
					newIn.lexemCount++;
					newIn.finalText[indNewInTextFormated++] = i;
					spaceAdded = true;
				}
			}
			else
			{
				newIn.finalText[indNewInTextFormated++] = i;
				spaceAdded = false;
			}
		}
		newIn.finalText[indNewInTextFormated] = '\0';
		newIn.size = strlen(reinterpret_cast<char*>(newIn.finalText));
		return newIn;
	}
}
