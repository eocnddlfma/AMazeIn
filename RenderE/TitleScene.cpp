#include "TitleScene.h"

void StartTitle()
{
	std::cout << "A Maze In" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "By sinsanghyeon and baesunghyeon" << std::endl;
	std::cout << "" << std::endl; 
	std::cout << "Press Any Key to Start" << std::endl; 

	while (true)if (_getch())break;
	Sleep(100);
	system("cls");

	std::cout << "�׷� ���� �ִ�." << std::endl;
	while (true)if (_getch())break;
	Sleep(100);
	std::cout << "���� 2�ÿ� ������ ���Ϳ� ����." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "�̻��� �̷ΰ� �ִٰ�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "�������� ���߾���." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "���������� ����� ���� �ʴ´�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "������ �ϳ��� Ȯ���ϴ�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "�׵��� �ᱹ �̷η� ���ߴٴ� ��." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	system("cls");

	std::cout << "���� �����̴�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "�׸��� �� ���������� 20��° ���� �Ű� ���Դ�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "��ε� �̷η� ���ٰ� �Ѵ�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "5���� �츮 ��ó��." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "��ο��� ����� �����Դ�." << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "�ᱹ ���� ������ ���� ���� �̷η� �� ����̿�������" << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	std::cout << "2002.04.24 ����� �������� 1" << std::endl;
	while (true)if (_getch())break;
	Sleep(10);
	system("cls");
}

void GameOverTitle()
{
	int y = 0;
	PrintConsoleBuffer(0, y++, "���� ������.\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "���۽����� ���ƿ��� �����鿡�� �ʹ� ���� ���� �� ����.\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "��... ���� �;��µ�...\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "2002.04.24 ����� �������� 2\n");
	while (true)if (_getch())break;
	Sleep(10);
	ClearConsole();
	PrintConsoleBuffer(0, 0, "GAMEOVER\n");
	while (true)if (_getch())break;
	Sleep(10);
	exit(404);
}

void GameClearTitle()
{
	int y = 0;
	PrintConsoleBuffer(0, y++, "�߰��� �̻��� �������� �ֱ� ������\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "�ϴ� �� ���� �� ����.\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "�Ѿ��� ���� �� �ᰡ�µ�, �̷δ� ���� ����δ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "��... ���� ��Ƶ��ư��� ����ڴ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "GPS�� ������ ������... ������û�̶� �õ��غ�����.\n");
	while (true)if (_getch())break;
	Sleep(10);
	PrintConsoleBuffer(0, y++, "2002.04.24 ����� �������� 2\n");
	while (true)if (_getch())break;
	Sleep(10);
	exit(200);
}
