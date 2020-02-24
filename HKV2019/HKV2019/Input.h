#pragma once

#define IN_MAX_TEXT_LEN 1024*250
#define IN_CODE_TABLE {\
	/*+0	 +1      +2	     +3	     +4	     +5 	 +6      +7	     +8 	 +9      +10     +11     +12     +13     +14     +15*/\
	 INN::T,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::T,  INN::S,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 0-15 */ \
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F, /* 16-31 */\
	 INN::T,  INN::T,  INN::T,  INN::T,  INN::F,  INN::T,  INN::T,  INN::T,  INN::S,  INN::S,  INN::S,  INN::S,  INN::S,  INN::S,  INN::T,  INN::T,	/* 32-47 */\
	 INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::S,  INN::S,  INN::S,  INN::S,  INN::T,	/* 48-63 */\
	 INN::F,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,	/* 64-79 */\
	 INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,	/* 80-95 */\
	 INN::F,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,	/* 96-111 */\
	 INN::T,  INN::T,  INN::T,  INN::T,	 INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::T,  INN::S,  INN::F,  INN::S,  INN::F,  INN::F,	/* 112-127 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 128-143 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F, /* 144-159 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 160-175 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 176-191 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 192-207 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 208-223 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,	/* 224-239 */\
	 INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F,  INN::F  /* 240-255 */}

namespace In
{
	struct INN
	{
		enum { T = 1024, F = 2048, I = 4096, S = 8192 };

		int size = 0;
		int lines = 0;
		int ignor = 0;
		unsigned char* text;
		unsigned char* finalText;
		long long int lexemCount;
		int code[256] = IN_CODE_TABLE;
	};

	INN getin(wchar_t infile[]);
}
