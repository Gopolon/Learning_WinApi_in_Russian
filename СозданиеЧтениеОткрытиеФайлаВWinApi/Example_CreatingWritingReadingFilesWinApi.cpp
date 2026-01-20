#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine,
    int nCmdShow)
{
    //==========Создание файла и запись==========

    const wchar_t* WayToFile = L"Files/CreatedFile.txt";
    const wchar_t* TextForWriting = L"This file was created";
    LPVOID pText = (LPVOID)TextForWriting;
    DWORD NumberOfWrittenBytes = 0;
    LPDWORD pNumOfWrB = &NumberOfWrittenBytes;

    HANDLE hCreatedFile = CreateFile(WayToFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    WriteFile(hCreatedFile, pText, wcslen(TextForWriting) * sizeof(wchar_t), pNumOfWrB, NULL);

    //==========Открытие файла и чтение==========

    const wchar_t* WayToFile1 = L"Files/FileToRead.txt";
    wchar_t* ReadedText = new wchar_t[100];
    LPVOID pReadedText = (LPVOID)ReadedText;
    DWORD NumberOfReadedBytes = 0;
    LPDWORD pNumOfReadedB = &NumberOfReadedBytes;

    HANDLE hOpenedFile = CreateFile(WayToFile1, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    const wchar_t* WayToFile2 = L"Files/FileToCheck.txt";
    HANDLE hFileForChecking = CreateFile(WayToFile2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    ReadFile(hOpenedFile, pReadedText, 100 * sizeof(wchar_t), pNumOfReadedB, NULL);
    WriteFile(hFileForChecking, pReadedText, NumberOfReadedBytes, pNumOfWrB, NULL);

    //==========Возвращение ресурсов системе==========

    CloseHandle(hCreatedFile);
    CloseHandle(hOpenedFile);
    CloseHandle(hFileForChecking);
    delete[] ReadedText;

    //===========================================
}