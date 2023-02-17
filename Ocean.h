#include <iostream>
#include <ctime>

class Ocean {
public:
	// Values that can be assigned to the grid cells
	enum Cells { unknown_cell, visited_cell, ship_cell };
	// Players ids
	enum Players { unassigned = -1, redPlayer = 0, bluePlayer = 1 };
private:
	// Two 10 * 10 grids. One for each player
	Cells grids[2][10][10];
	Players players[2];
	int currentPlayer;
	// Flag indicating end of game
	bool finished;
public:
	Ocean();
	bool IsFinished();
	void SetFinished();
	bool setCurrentPlayer(Players player);
	char* GetPlayerDescription(Players player);
	Players AssignPlayer();
	Cells GetValue(Players player, int x, int y);
	bool Play(Players player, int x, int y);
};