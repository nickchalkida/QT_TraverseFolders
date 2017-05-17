#include "traverse.h"
#include "auxobject.h"
#include "mainwindow.h"
#include <windows.h>

TCHAR mainDir[MAX_PATH];
MainWindow *winptr;
AuxObject *theauxptr;
HANDLE hthread;
DWORD dwthreadid;

DWORD WINAPI ProcessFolders(TCHAR *curdir) {

    WIN32_FIND_DATA ffd;
    //LARGE_INTEGER filesize;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;
    TCHAR path[MAX_PATH];
    TCHAR fullname[MAX_PATH];
    TCHAR *pattern = TEXT("\\*.*");

    lstrcpy(path,curdir); lstrcat(path,pattern);
    hFind = FindFirstFile(path, &ffd);
    if (hFind == INVALID_HANDLE_VALUE) {
        //MessageBox(NULL,L"FindFirstFile",L"Error",MB_OK);
        return -1;
    }

    do {
        lstrcpy(fullname,curdir); lstrcat(fullname,L"\\"); lstrcat(fullname,ffd.cFileName);
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (ffd.cFileName[0]!='.')
                ProcessFolders(fullname);
        } else {
            //filesize.LowPart = ffd.nFileSizeLow;
            //filesize.HighPart = ffd.nFileSizeHigh;
            QString qstr = QString::fromStdWString(fullname);

            winptr->slotformessage(qstr);
            //emit theauxptr->SendSomeInfo(qstr);

            QThread::currentThread()->msleep(20);

        }
    }
    while (FindNextFile(hFind, &ffd) != 0);
    FindClose(hFind);

    return dwError;

}

DWORD ProcessFunction(LPVOID) {
    //MessageBox(NULL,mainDir,L"DEB",MB_OK);
    ProcessFolders(mainDir);
    return 0;
}

int StartThreads(MainWindow *thewin, AuxObject *auxptr) {

    winptr = (MainWindow *)thewin;
    lstrcpy(mainDir,winptr->appmdir.toStdWString().c_str());
    theauxptr = auxptr;

    hthread =
    CreateThread(
                0,             // default security attributes
                0,                // use default stack size
                (LPTHREAD_START_ROUTINE)&ProcessFunction,  // thread function name
                NULL,             // argument to thread function
                0,                // use default creation flags
                &dwthreadid);     // returns the thread identifier
    //&winptr->dwid);     // returns the thread identifier

    //MessageBox(NULL,L"Hi111",L"DEB",MB_OK);
    return 0;
}
