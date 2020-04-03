#pragma once
class game
{

public:
	game();
	int StartGame();

private:
	char CField[10][10];
	char PField[10][10];
	int GameDifficulty;
	void takeDifficulty();
	int PlayerShot();
	void PlayerCreate();
	int CheckPosition(char[][12]);
	void PlayerRandomCreate();
	int ComputerShot();
	void ComputerRandomCreate();
	void print();
	int CheckWin();
	int input_check_int();
	bool input_check_bool();
	void CheckDestroy(int);
};
