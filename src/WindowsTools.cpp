//
// Created by Jeremy on 2/19/2021.
//

#include "WindowsTools.h"
#include <iostream>

std::string WindowsTools::getLastErrorAsString() {
    DWORD errorId = GetLastError();
    if (errorId == 0) return std::string();
    LPSTR buffer = nullptr;
    DWORD size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &buffer, 0, NULL
    );
    std::string message(buffer, size);
    LocalFree(buffer);
    return message;
}

void WindowsTools::outputLastError() {
    std::cout << getLastErrorAsString() << std::endl;
}

void WindowsTools::outputLastError(const char* message) {
    std::cout << message << ' ';
    outputLastError();
}
