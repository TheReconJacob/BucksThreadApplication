#include "Ocean.h"

Ocean::Ocean() {

	finished = false;
	int posX, posY;
	extern char mutexName[];

	// Initialise players and grid cells
	players[0] = Players::unassigned;
	players[1] = Players::unassigned;
	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++) {
			grids[0][x][y] = Cells::unknown_cell;
			grids[1][x][y] = Cells::unknown_cell;
		}

	// Assign ship to a randon cell within the first grid
	posX = rand() % 10;
	posY = rand() % 10;
	grids[0][posX][posY] = Cells::ship_cell;
	std::cout << "Player 0 ship x:" << posX << " y:" << posY << "\n";

	// Assign ship to a randon cell within the second grid
	posX = rand() % 10;
	posY = rand() % 10;
	grids[1][posX][posY] = Cells::ship_cell;
	std::cout << "Player 1 ship x:" << posX << " y:" << posY << "\n";
}

bool Ocean::IsFinished() {
	return finished;
}

void Ocean::SetFinished() {
	finished = true;
}

// Turn based logic
bool Ocean::setCurrentPlayer(Players player) {
	if (currentPlayer != player) {
		currentPlayer = player;
		return true;
	}
	else {
		return false;
	}
}

char* Ocean::GetPlayerDescription(Players player) {
	if (player == Ocean::Players::redPlayer)
		return (char*)"Red";
	else
		return (char*)"Blue";
}

// Players are assigned an ID of 0 or 1 at the start of play
Ocean::Players Ocean::AssignPlayer() {
	if (players[0] == Players::unassigned) {
		players[0] = Players::redPlayer;
		std::cout << "Red player assigned \n";
		return Players::redPlayer;
	}
	else {
		players[1] = Players::bluePlayer;
		std::cout << "Blue player assigned \n";
		return Players::bluePlayer;
	}
}

// Return the value within a cell
Ocean::Cells Ocean::GetValue(Players player, int x, int y) {
	return grids[!player][x][y];
}

// Returns true if a ship is located within the
// player's grid at position x,y.
// If not flags the cell as being visited
bool Ocean::Play(Players player, int x, int y) {
	if (player == Players::redPlayer) {
		if (grids[Players::bluePlayer][x][y] == ship_cell) {
			finished = true;
		}
		else {
			grids[Players::bluePlayer][x][y] = visited_cell;
		}
	}
	else {
		if (grids[Players::redPlayer][x][y] == ship_cell) {
			finished = true;
		}
		else {
			grids[Players::redPlayer][x][y] = visited_cell;
		}
	}
	return finished;
}