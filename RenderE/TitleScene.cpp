#include "TitleScene.h"

void StartTitle()
{
	std::cout << "A Maze In" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "By sinsanghyeon and baesunghyeon" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Press Any Key to Start" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Press WASD to Move" << std::endl;
	std::cout << "Press Shift to Dash/Slide" << std::endl;
	std::cout << "Press F to Shoot Bullets" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Have Fun!" << std::endl;

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
	SetFontSizeBig();
	int y = 0;
	RenderConsole("���� ������.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("���۽����� ���ƿ��� �����鿡�� �ʹ� ���� ���� �� ����.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("��... ���� �;��µ�...\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("2002.04.24 ����� �������� 2\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("GAMEOVER\n");
	while (true)if (_getch())break;
	Sleep(10);
	exit(404);
}

void GameClearTitle()
{
	SetFontSizeBig();
	int y = 0;
	RenderConsole("�߰��� �̻��� �������� �ֱ� ������\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("�ϴ� �� ���� �� ����.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("�Ѿ��� ���� �� �ᰡ�µ�, �̷δ� ���� ����δ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("��... ���� ��Ƶ��ư��� ����ڴ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("GPS�� ������ ������... ������û�̶� �õ��غ�����.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("�ϴ� ������ �� �� �� ���� �ڴ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("2002.04.24 ����� �������� 2\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("Ŭ���� �Դϴ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	RenderConsole("�÷������ּż� �����մϴ�.\n");
	while (true)if (_getch())break;
	Sleep(10);
	exit(200);
}
