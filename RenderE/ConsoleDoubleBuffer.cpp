#include "ConsoleDoubleBuffer.h"

//Win api에서 배운 더블 버퍼링 이용한 스크립트, init과 랜더마다 호출해줄 예정 (배승현 핸들 모르면 검색 ㄱ)

HANDLE hConsole;
HANDLE g_hScreen[2];
bool screenIndex;

void InitConsoleBuffer()
{
	screenIndex = false;
	CONSOLE_CURSOR_INFO cci;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);


	// 콘솔 관련 설정
	CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE };  // 콘솔의 커서 깜빡임을 제거합니다.
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo{ 0, };
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	consoleInfo.dwSize.X = FOV;    // 콘솔의 Width
	consoleInfo.dwSize.Y = ScreenHeight + 50;    // 콘솔의 Height

	// 콘솔의 크기를 다시 계산 (나중에 그림 그릴때 사용)
	int nWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left;
	int nHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;


	// 커서를 숨긴다.
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleScreenBufferSize(g_hScreen[0], consoleInfo.dwSize);    // 화면 버퍼 크기 설정
	SetConsoleWindowInfo(g_hScreen[0], TRUE, &consoleInfo.srWindow); // 콘솔 설정
	SetConsoleCursorInfo(g_hScreen[1], &cci);
	SetConsoleScreenBufferSize(g_hScreen[1], consoleInfo.dwSize);    // 화면 버퍼 크기 설정
	SetConsoleWindowInfo(g_hScreen[1], TRUE, &consoleInfo.srWindow); // 콘솔 설정
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
	FillConsoleOutputCharacter(hConsole, ' ', (ScreenHeight+50) * FOV, Coord, &dw);
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
	ClearConsole();
	PrintConsoleBuffer(0, 0, s);
	FlipConsoleBuffer();
}

void ReleaseConsoleBuffer()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}
