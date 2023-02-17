// BucksThreadApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

DWORD WINAPI BasicThread(LPVOID param) {
    std::cout << "Thread start \n";
    Sleep(2000);
    std::cout << "Thread end \n";
    return 0;
}

DWORD WINAPI MessageThread(LPVOID param) {
    int tab = (int)param;
    for (int n = 0; n < 10; n++) {
        Sleep(50);
        for (int i = 0; i < 100000; i++);
        if (tab == 1)
            std::cout << "\t\t 1:Thread\n";
        else if (tab == 2)
            std::cout << "\t\t\t\t 2:Thread\n";
        else
            std::cout << "\t\t\t\t\t\t 3:Thread\n";
    }
    return 0;
}

int main()
{
    LPVOID param = NULL;
    DWORD threadId;
    HANDLE hdl[3];
    int label = 1;
    hdl[0] = CreateThread(NULL, 0, MessageThread, (LPVOID)label, 0, &threadId);
    SetThreadPriority(hdl[0], THREAD_PRIORITY_IDLE); //This thread has a low priority
    label = 2;
    hdl[1] = CreateThread(NULL, 0, MessageThread, (LPVOID)label, 0, &threadId);
    SetThreadPriority(hdl[1], THREAD_PRIORITY_TIME_CRITICAL); //This thread has the highest priority
    label = 3;
    hdl[2] = CreateThread(NULL, 0, MessageThread, (LPVOID)label, 0, &threadId);
    SetThreadPriority(hdl[2], THREAD_PRIORITY_LOWEST); //This thread has the lowest priority
    HANDLE mainThread = GetCurrentThread();
    SuspendThread(mainThread);
    system("pause");

    //When return on the main function is called, all other children thread are stopped because the parent main thread is stopped
    return 0;
}
