//
// Created by Jeremy on 2/19/2021.
//

#ifndef CONSOLE_CANVAS_H
#define CONSOLE_CANVAS_H

#include <windows.h>

class ConsoleCanvas {

    private:

        char title[128];
        HANDLE console;
        COORD size;
        CHAR_INFO* data;

        char character;
        int backgroundColor;
        int foregroundColor;

        int getPaint() const { return backgroundColor | foregroundColor; }

        // Place the currently active character and background and foreground attributes into our CHAR_INFO data buffer.
        // Content from this buffer is outputted to the console screen buffer during draw and fill method calls.
        void paint(short x, short y);

    public:

        ConsoleCanvas(const char* title, short width, short height);

        virtual ~ConsoleCanvas();

        // Creates a new windows console screen buffer with the specifications defined in the constructor
        // Returns true if the buffer is successfully created, false otherwise
        bool create();

        bool destroy();

        int getBackgroundColor() const { return backgroundColor; }

        void setBackgroundColor(int background) { this->backgroundColor = background; }

        int getForegroundColor() const { return foregroundColor; }

        void setForegroundColor(int foreground) { this->foregroundColor = foreground; }

        char getCharacter() const { return this->character; }

        void setCharacter(char character) { this->character = character; }

        // Fill the console screen buffer with the current background, foreground and character
        // Returns true if successful, false otherwise
        bool fill();

        // Draw a dot into the console screen buffer with the current background, foreground and character
        // Returns true if successful, false otherwise
        bool drawDot(short x, short y);

        // Fill a rectangle with the current background, foreground and character
        // Returns true if successful, false otherwise
        bool fillRectangle(short x, short y, short width, short height);

};


#endif
