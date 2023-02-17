// BucksThreadApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "Ocean.h"

char mutexName[] = "MUTEX1";
HANDLE hMutex;

class GameObject {
public:
    int health;
    GameObject() {
        health = 100;
    }
};

//DWORD WINAPI SyncThread(LPVOID param) {
//    GameObject* syncObj = (GameObject*)param; //Cast the LPVOID param back to being a GameObject but it is a pointer
//    WaitForSingleObject(hMutex, INFINITE);
//    std::cout << "Game Object Health : " << syncObj->health << "\n";
//    ReleaseMutex(hMutex);
//    return 0;
//}

DWORD WINAPI SyncThread(LPVOID param) {
    Ocean* ocean = (Ocean*)param;
    Ocean::Cells target;
    int x, y;
    char playerDescription[5];

    // Get a unique player for this thread - either red or blue
    Ocean::Players player = ocean->AssignPlayer();
    if (player == Ocean::Players::redPlayer)
        strcpy_s(playerDescription, "Red");
    else
        strcpy_s(playerDescription, "Blue");

    srand(player);

    do {
        if (!ocean->IsFinished() && ocean->setCurrentPlayer(player)) {
            do {
                // Select a random cell
                x = rand() % 10;
                y = rand() % 10;
                
                // Get the cells value
                target = ocean->GetValue(player, x, y);
                
                // If the cell has not been visited before
                if (target == Ocean::Cells::unknown_cell) {
                    ocean->Play(player, x, y);
                    std::cout << ocean->GetPlayerDescription(player) << " x:" << x << " y: " << y << "\n";
                    break;
                }
                
                else {
                    // Opponent's ship found!
                    if (target == Ocean::Cells::ship_cell) {
                        ocean->SetFinished();
                        std::cout << ocean->GetPlayerDescription(player) << " x:" << x << " y: " << y << "\n";
                        std::cout << "Player " << ocean -> GetPlayerDescription(player) << " Wins\n";
                        break;
                    }
                }
            }
            // If the random cell has been visited before then try another one
            while (target == Ocean::Cells::visited_cell);
        }
    }
    // Until a ship has been found
    while (!ocean->IsFinished());
    return 0;
}

int main()
{
    srand(time(0));
    LPVOID param = NULL;
    DWORD threadId;
    HANDLE hdl[2];
    Ocean* ocean = new Ocean();
    hdl[0] = CreateThread(NULL, 0, SyncThread, (LPVOID)ocean, 0, &threadId);
    hdl[1] = CreateThread(NULL, 0, SyncThread, (LPVOID)ocean, 0, &threadId);
    HANDLE mainThread = GetCurrentThread();
    SuspendThread(mainThread);
    system("pause");
    delete ocean;
}