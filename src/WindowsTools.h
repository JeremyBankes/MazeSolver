//
// Created by Jeremy on 2/19/2021.
//

#ifndef WINDOWS_TOOLS_H
#define WINDOWS_TOOLS_H

#include <windows.h>
#include <string>

class WindowsTools {

    public:

        // Retrieves the last win32 error as an std::string.
        static std::string getLastErrorAsString();

        // Outputs the last win32 error to stdout.
        static void outputLastError();

        // Outputs the last win32 error to stdout alongside a custom message.
        static void outputLastError(const char* message);

};

#endif
