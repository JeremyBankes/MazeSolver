//
// Created by Jeremy on 2/19/2021.
//

#include "ConsoleCanvas.h"
#include "WindowsTools.h"

ConsoleCanvas::ConsoleCanvas(const char* title, short width, short height) :
    size({(SHORT) width, (SHORT) height}),
    character(' '),
    backgroundColor(0),
    foregroundColor(0),
    console(nullptr) {
    strcpy(this->title, title);
    data = new CHAR_INFO[width * height];
}

ConsoleCanvas::~ConsoleCanvas() {
    delete[] data;
}

bool ConsoleCanvas::create() {
    console = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    if (!console) {
        WindowsTools::outputLastError("Failed to create console screen buffer.");
        return false;
    }

    SetConsoleTitle(title);

    // Use a custom console (square) font so that the cells have a 1:1 aspect ratio
    CONSOLE_FONT_INFOEX fontInfo = {0};
    fontInfo.cbSize = sizeof(fontInfo);
    // The windows console has a 1 pixel spacing between characters, to ensure the cells appear
    // square, the font size's width should be one pixel less than it's height
    fontInfo.dwFontSize.X = 7;
    fontInfo.dwFontSize.Y = 8;
    fontInfo.FontWeight = FW_REGULAR;
    fontInfo.FontFamily = FF_DONTCARE;
    SetCurrentConsoleFontEx(console, 0, &fontInfo);

    // Hide the console cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);

    // The window cannot be larger than the screen buffer, so to allow for setting an arbitrary
    // screen buffer size, first set the window to be small, then resize it after setting the
    // desired screen buffer size.
    SMALL_RECT bounds = {0, 0, 0, 0};
    if (!SetConsoleWindowInfo(console, TRUE, &bounds)) {
        WindowsTools::outputLastError("Failed to shrink console window.");
        return false;
    }

    if (!SetConsoleScreenBufferSize(console, size)) {
        WindowsTools::outputLastError("Failed to set screen buffer size.");
        return false;
    }

    bounds.Right = size.X - 1;
    bounds.Bottom = size.Y - 1;
    if (!SetConsoleWindowInfo(console, TRUE, &bounds)) {
        WindowsTools::outputLastError("Failed to set console window info.");
        return false;
    }

    // Change the active screen buffer from stdout, to our custom one.
    // Note that std::cout messages will no longer be received.
    if (!SetConsoleActiveScreenBuffer(console)) {
        WindowsTools::outputLastError("Failed to set console active screen buffer.");
        return false;
    }
    return true;
}

bool ConsoleCanvas::destroy() {
    if (!CloseHandle(console)) {
        WindowsTools::outputLastError("Failed to close console handle.");
        return false;
    }
    if (!SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE))) {
        WindowsTools::outputLastError("Failed to switch active screen buffer back to stdout.");
        return false;
    }
    return true;
}

void ConsoleCanvas::paint(short x, short y) {
    data[y * size.X + x].Attributes = getPaint();
    data[y * size.X + x].Char.AsciiChar = getCharacter();
}


bool ConsoleCanvas::fill() {
    return fillRectangle(0, 0, size.X, size.Y);
}

bool ConsoleCanvas::drawDot(short x, short y) {
    paint(x, y);
    DWORD written;
    return FillConsoleOutputAttribute(console, getPaint(), 1, {x, y}, &written);
}

bool ConsoleCanvas::fillRectangle(short x, short y, short width, short height) {
    for (short i = 0; i < height; i++) {
        for (short j = 0; j < width; j++) {
            paint(j, i);
        }
    }
    SMALL_RECT region = {x, y, (short) (x + width - 1), (short) (y + height - 1)};
    return WriteConsoleOutput(console, data, size, {0, 0}, &region);
}