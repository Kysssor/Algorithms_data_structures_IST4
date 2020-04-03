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
		if (g->StartGame() == 1) std::cout << std::endl << "Вы выиграли!"; else std::cout << std::endl << "Вы проиграли :(";
		delete g;
		std::cout << std::endl << "Хотите сыграть еще раз? (0-нет, 1-да): ";
	} while (input_check_bool());
}
/*проверка на ввод 1 или 0*/
bool input_check_bool()
{
	bool i;
	std::cin >> i;
	while ((std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Некорректный ввод, повторите попытку: "; std::cin >> i;
	}
	return i;
}

