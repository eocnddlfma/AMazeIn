#include "ConsoleDoubleBuffer.h"

//Win api���� ��� ���� ���۸� �̿��� ��ũ��Ʈ, init�� �������� ȣ������ ���� (����� �ڵ� �𸣸� �˻� ��)

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


	// �ܼ� ���� ����
	CONSOLE_CURSOR_INFO consoleCursor{ 1, FALSE };  // �ܼ��� Ŀ�� �������� �����մϴ�.
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo{ 0, };
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	consoleInfo.dwSize.X = FOV;    // �ܼ��� Width
	consoleInfo.dwSize.Y = ScreenHeight + 50;    // �ܼ��� Height

	// �ܼ��� ũ�⸦ �ٽ� ��� (���߿� �׸� �׸��� ���)
	int nWidth = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left;
	int nHeight = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top;


	// Ŀ���� �����.
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleScreenBufferSize(g_hScreen[0], consoleInfo.dwSize);    // ȭ�� ���� ũ�� ����
	SetConsoleWindowInfo(g_hScreen[0], TRUE, &consoleInfo.srWindow); // �ܼ� ����
	SetConsoleCursorInfo(g_hScreen[1], &cci);
	SetConsoleScreenBufferSize(g_hScreen[1], consoleInfo.dwSize);    // ȭ�� ���� ũ�� ����
	SetConsoleWindowInfo(g_hScreen[1], TRUE, &consoleInfo.srWindow); // �ܼ� ����
}

void FlipConsoleBuffer()
{
	SetConsoleActiveScreenBuffer(g_hScreen[screenIndex?1:0]);
	screenIndex = !screenIndex;
}

void ClearConsole()//������ Ŭ����
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
