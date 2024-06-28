#include "ConsoleDoubleBuffer.h"

//Win api에서 배운 더블 버퍼링 이용한 스크립트, init과 랜더마다 호출해줄 예정 (배승현 핸들 모르면 검색 ㄱ)

HANDLE hConsole;
HANDLE g_hScreen[2];
bool screenIndex;

void InitConsoleBuffer()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;                   // Width of each character in the font
	cfi.dwFontSize.Y = 8;                  // Height
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);

	screenIndex = false;
	CONSOLE_CURSOR_INFO cci;

	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	CONSOLE_SCREEN_BUFFER_INFOEX consoleInfo{ 0, };
	GetConsoleScreenBufferInfoEx(hConsole, &consoleInfo);
	//system("mode con: cols=960 lines=540");
	consoleInfo.srWindow.Left = 0;
	consoleInfo.srWindow.Top = 0;
	consoleInfo.srWindow.Bottom = 800;    // 콘솔의 Height
	consoleInfo.srWindow.Right = 960;    // 콘솔의 Width


	// 커서를 숨긴다.
	cci.dwSize = 1;
	cci.bVisible = FALSE; 
	SetConsoleScreenBufferInfoEx(hConsole, &consoleInfo);

	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleScreenBufferInfoEx(g_hScreen[0], &consoleInfo); // 콘솔 설정

	SetConsoleCursorInfo(g_hScreen[1], &cci);
	SetConsoleScreenBufferInfoEx(g_hScreen[1], &consoleInfo); // 콘솔 설정

}

void FlipConsoleBuffer()
{
	SetConsoleActiveScreenBuffer(g_hScreen[screenIndex?1:0]);
	screenIndex = !screenIndex;
}

void ClearConsole()//재사용전 클리어
{
	COORD Coord = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hConsole, ' ', (SCREEN_HEIGHT) * FOV, Coord, &dw);
}

void PrintConsoleBuffer(int x, int y, std::string s)
{
	DWORD dw;
	COORD CursorPosition = { x, y };

	SetConsoleCursorPosition(g_hScreen[screenIndex ? 1 : 0], CursorPosition);
	WriteFile(g_hScreen[screenIndex ? 1 : 0], s.c_str(), strlen(s.c_str()), &dw, NULL);
}

void RenderConsole(std::string s)
{
	//ClearConsole();
	PrintConsoleBuffer(0, 0, s);
	FlipConsoleBuffer();
}

void ReleaseConsoleBuffer()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}
