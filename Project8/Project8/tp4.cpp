#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "game.h"
#include <ctime>

bool input_check_bool();
void main()
{
	setlocale(0, "rus");
	srand(time(0));
	do
	{
		game *g = new game;
		if (g->StartGame() == 1) std::cout << std::endl << "�� ��������!"; else std::cout << std::endl << "�� ��������� :(";
		delete g;
		std::cout << std::endl << "������ ������� ��� ���? (0-���, 1-��): ";
	} while (input_check_bool());
}
/*�������� �� ���� 1 ��� 0*/
bool input_check_bool()
{
	bool i;
	std::cin >> i;
	while ((std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "������������ ����, ��������� �������: "; std::cin >> i;
	}
	return i;
}

