// BucksThreadApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

class GameObject {
public:
    int health;
    GameObject() {
        health = 100;
    }
};

DWORD WINAPI SyncThread(LPVOID param) {
    GameObject* syncObj = (GameObject*)param; //Cast the LPVOID param back to being a GameObject but it is a pointer
    std::cout << "Game Object Health : " << syncObj->health << "\n";
    return 0;
}

int main()
{
    DWORD threadId;
    HANDLE hdl[2];
    GameObject* obj = new GameObject();
    hdl[0] = CreateThread(NULL, 0, SyncThread, (LPVOID)obj, 0, &threadId); //Again the obj variable needs to be cast to LPVOID to pass as a parameter for a thread
    hdl[1] = CreateThread(NULL, 0, SyncThread, (LPVOID)obj, 0, &threadId);
    HANDLE mainThread = GetCurrentThread();
    SuspendThread(mainThread); //Main thread gets suspended, otherwise if it finishes, all child threads will stop
    system("pause");
    delete obj;
    return 0;
}