#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "game.h"
#include <windows.h>

/*создает поля и определяет очередность хода*/
int game::StartGame()
{
	/*создание полей*/
	ComputerRandomCreate();
	PlayerCreate();
	/*установка сложности*/
	game::takeDifficulty();
	print();
	while (!CheckWin())//цикл игры
	{
		while (PlayerShot())//ход игрока
		{
			print();
			if (CheckWin()) return CheckWin();
		}
		print();
		std::cout << std::endl << std::endl << "Ход противника!";
		while (ComputerShot())//ход компьютера
		{
			print();
			std::cout << std::endl << std::endl << "Ход противника!";
			if (CheckWin()) return CheckWin();
		}
		print();
	}
}
/*стрельба компьютера*/
int game::ComputerShot()
{
	int x = rand() % 10;
	int y = rand() % 10;
	/*повышаем вероятность попасть по облаку в зависимости от сложности*/ for (int i = 0; i < GameDifficulty * 2; i++) {
		if (PField[y][x] != '#')
		{
			x = rand() % 10;
			y = rand() % 10;
		}
		else break;
	}
	if (PField[y][x] == '#')//попадание
	{
		Sleep(1000);
		PField[y][x] = '+';
		CheckDestroy(0);
		return 1;
	}
	else if (PField[y][x] == 'o')//промах
	{
		Sleep(1000);
		PField[y][x] = '*';
		return 0;
	}
	else	game::ComputerShot();//если стреляет повторно в одну и туже ячейку
}

/*стрельба игрока*/
int game::PlayerShot()
{
	int x;
	int y;
	std::cout << std::endl << std::endl << "Ваш выстрел! Введите координаты выстрела: " << std::endl;
	std::cout << "x= ";
	x = input_check_int();
	std::cout << "y= ";
	y = input_check_int();
	if (CField[y][x] == 'o' || CField[y][x] == '*')//промах
	{
		CField[y][x] = '*';
		return 0;
	}
	else if (CField[y][x] == '#' || CField[y][x] == '+' || CField[y][x] == '^')//попадание
	{
		CField[y][x] = '+';
		CheckDestroy(1);
		return 1;
	}
}
/*констрктор*/
game::game()
{
	for (int i = 0; i < 10; ++i) for (int k = 0; k < 10; ++k) PField[i][k] = 'o';
}

/*заполнение поля компьютера*/
void game::ComputerRandomCreate()
{
	/*создание временного массива, для удобства создания поля*/ char temp[12][12];
	for (int i = 0; i < 12; ++i) for (int k = 0; k < 12; ++k) temp[i][k] = 'o';
	for (int a = 1; a < (rand() % 5 + 5); a++)
	{
		/* x и y - размеры облака*/
		int x = rand() % 3 + 2;
		int y = rand() % 3 + 2;
		/*тыкаем в рандомную ячейку и пытаемся туда поместить наше облако */
		for (int b = 0; b < 15; b++)
		{
			int flag = 0;
			int x1 = rand() % (11 - x) + 1;
			int y1 = rand() % (11 - y) + 1;
			for (int i = x1 - 1; i < x1 + x + 1; i++) for (int k = y1 - 1; k < y1 + y + 1; k++) if (temp[i][k] != 'o') flag = 1;
			if (flag) continue;
			for (int i = x1; i < x1 + x; i++) for (int k = y1; k < y1 + y; k++)	temp[i][k] = '#';
			break;
		}
	}
	/*запись в массив поля*/
	for (int i = 0; i < 10; ++i) for (int k = 0; k < 10; ++k) CField[i][k] = temp[i + 1][k + 1];
}
/*графическая часть программы*/
void game::print()
{
	system("cls");
	std::cout << "o - не известно" << std::endl;
	std::cout << "+ - ранил" << std::endl;
	std::cout << "* - промах" << std::endl;
	std::cout << "^ - убил" << std::endl;
	std::cout << "# - свое облако" << std::endl;
	std::cout << "Поле противника: " << std::endl;
	std::cout << std::endl << " ";
	for (int i = 0; i < 10; ++i)
	{
		std::cout << i;
	}
	for (int i = 0; i < 10; ++i)
	{
		std::cout << std::endl << " " << i << " ";
		for (int k = 0; k < 10; ++k)
		{
			if (CField[i][k] == '*' || CField[i][k] == '+' || CField[i][k] == '^') std::cout << CField[i][k];
			else std::cout << "o";
		}
	}
	std::cout << std::endl << std::endl << "Ваше поле: " << std::endl; std::cout << std::endl << " ";
	for (int i = 0; i < 10; ++i)
	{
		std::cout << i;
	}
	for (int i = 0; i < 10; ++i)
	{
		std::cout << std::endl << " " << i << " ";
		for (int k = 0; k < 10; ++k)
		{
			std::cout << PField[i][k];
		}
	}
}
/*создание поля игрока*/
void game::PlayerCreate()
{
	std::cout << "Создание игрового поля\n";
	game::PlayerRandomCreate();
}
/*заполнение поля игрока рандомно*/
void game::PlayerRandomCreate()
{
	char temp[12][12];
	for (int i = 0; i < 12; ++i) for (int k = 0; k < 12; ++k) temp[i][k] = 'o';
	for (int a = 1; a < (rand() % 5 + 5); a++)
	{
		/* x и y - размеры облака*/
		int x = rand() % 3 + 2;
		int y = rand() % 3 + 2;
		/*тыкаем в рандомную ячейку и пытаемся туда поместить наше облако */
		for (int b = 0; b < 15; b++)
		{
			int flag = 0;
			int x1 = rand() % (11 - x) + 1;
			int y1 = rand() % (11 - y) + 1;
			for (int i = x1 - 1; i < x1 + x + 1; i++) for (int k = y1 - 1; k < y1 + y + 1; k++) if (temp[i][k] != 'o') flag = 1;
			if (flag) continue;
			for (int i = x1; i < x1 + x; i++) for (int k = y1; k < y1 + y; k++)	temp[i][k] = '#';
			break;
		}
	}
	for (int i = 0; i < 10; ++i) for (int k = 0; k < 10; ++k) PField[i][k] = temp[i + 1][k + 1];
}

/*проверка на правила игры*/

int game::CheckPosition(char temp[12][12])
{
	for (int y1 = 1; y1 <= 10; ++y1)
	{
		for (int x1 = 10; x1 >= 1; --x1)
		{
			if (temp[x1][y1] == '1')
			{
				int x2, y2;
				for (y2 = y1; temp[x1][y2] == '1'; ++y2);
				for (x2 = x1; temp[x2][y1] == '1'; --x2);
				/*облако должно быть не меньше 2х2*/
				if ((x1 - x2) < 2 || (y2 - y1 < 2)) return -1;
				/*облако должно быть заполнено внутри '1' */
				for (int i = x2 + 1; i <= x1; ++i) for (int k = y1; k <= y2 - 1; ++k) if (temp[i][k] == '0') return -1;
				/*облака не должны соприкосаться*/
				for (int i = x2; i <= x1 + 1; ++i) if (temp[i][y1 - 1] == '1') return -1;
				for (int i = x2; i <= x1 + 1; ++i) if (temp[i][y2] == '1') return -1;
				for (int i = y1 - 1; i <= y2; ++i) if (temp[x1 + 1][i] == '1') return -1;
				for (int i = y1 - 1; i <= y2; ++i) if (temp[x2][i] == '1') return -1;
				/*записываем	облака в поле*/
				for (int i = x2 + 1; i <= x1; ++i) for (int k = y1; k <= y2 - 1; ++k)
				{
					PField[i - 1][k - 1] = '#';
					temp[i][k] = '0';
				}
			}
		}

	}
	return 0;
}
/*определяет продолжается ли игра и кто в ней победил*/ int game::CheckWin()
{
	bool ComputerWin = 1;
	bool PlayerWin = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (PField[i][k] == '#') ComputerWin = 0;
			if (CField[i][k] == '#') PlayerWin = 0;
		}
	}
	if (ComputerWin) return -1;//выиграл компьютер
	else if (PlayerWin) return 1;//выиграл игрок
	else return 0; //игра продолжается
}
/*проверка на ввод координат*/
int game::input_check_int()
{
	int i;
	std::cin >> i;
	while ((std::cin.peek() != '\n') || i < 0 || i>9)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Некорректный ввод, повторите попытку: "; std::cin >> i;
	}
	return i;
}
/*закрашывание поностью уничтоженных облаков*/
void game::CheckDestroy(int PlayerOrPC)
{
	char temp[12][12];
	for (int i = 0; i < 12; ++i) for (int k = 0; k < 12; ++k) temp[i][k] = 'o';
	if (PlayerOrPC) for (int i = 0; i < 10; ++i) for (int k = 0; k < 10; ++k) temp[i + 1][k + 1] = CField[i][k];
	else for (int i = 0; i < 10; ++i) for (int k = 0; k < 10; ++k) temp[i + 1][k + 1] = PField[i][k];
	for (int y1 = 1; y1 <= 10; ++y1)
	{
		for (int x1 = 10; x1 >= 1; --x1)
		{
			int flag = 0;
			if (temp[x1][y1] == '+')
			{
				int x2, y2;
				for (y2 = y1; temp[x1][y2] == '+'; ++y2);
				for (x2 = x1; temp[x2][y1] == '+'; --x2);
				/*облако должно быть не менешь 2х2*/
				if ((x1 - x2) < 2 || (y2 - y1 < 2)) flag = 1;
				if (flag) continue;
				/*уничтоженное облако должно быть заполнено внутри '+' */
				for (int i = x2 + 1; i <= x1; ++i) for (int k = y1; k <= y2 - 1; ++k) if (temp[i][k] != '+') flag = 1;
				if (flag) continue;
				/*уничтожиться может только все облако*/
				for (int i = x2; i <= x1 + 1; ++i) if (temp[i][y1 - 1] == '#' || temp[i][y1 - 1] == '+') flag = 1;
				for (int i = x2; i <= x1 + 1; ++i) if (temp[i][y2] == '#' || temp[i][y2] == '+') flag = 1;
				for (int i = y1 - 1; i <= y2; ++i) if (temp[x1 + 1][i] == '#' || temp[x1 + 1][i] == '+') flag = 1;
				for (int i = y1 - 1; i <= y2; ++i) if (temp[x2][i] == '#' || temp[x2][i] == '+') flag = 1;
				if (flag) continue;
				/*заменяем ранненое облако на уничтоженное*/
				for (int i = x2 + 1; i <= x1; ++i) for (int k = y1; k <= y2 - 1; ++k)
				{
					if (PlayerOrPC) CField[i - 1][k - 1] = '^';
					else PField[i - 1][k - 1] = '^';
					temp[i][k] = '0';
				}
			}
		}
	}
}
/*проверка на ввод 1 или 0*/
bool game::input_check_bool()
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


/*установка сложности игры*/
void game::takeDifficulty()

{
	std::cout << "Введите уровень сложности от 0 до 10: ";
	std::cin >> GameDifficulty;
	while ((std::cin.peek() != '\n') || GameDifficulty < 0 || GameDifficulty>10)
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Некорректный ввод, повторите попытку: ";
		std::cin >> GameDifficulty;
	}
}
