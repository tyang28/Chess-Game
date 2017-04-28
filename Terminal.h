#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <iostream>

static const char *CSI = "\x1b[";


// The Terminal class abstracts away things we need to draw to the terminal.
class Terminal {
public:
    // The possible colors. Note that foreground colors can also be 'bright',
    // adding another 8 colors
    enum Color {
        BLACK = 0,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        DEFAULT_COLOR = 9
    };

    // Set the foreground color for the next piece of text, keeping the
    // background color as is.
    static void colorFg(bool bright, Color color) {
        std::cout << CSI << 30 + color << (bright ? ";1" : "") << "m";
    }
    // Set the background color for the next piece of text, keeping the
    // foreground color as is.
    static void colorBg(Color color) {
        std::cout << CSI << 40 + color << "m";
    }
    // Set both background and foreground colors at the same time.
    static void colorAll(bool bright, Color foreColor, Color backColor) {
    std::cout << CSI << 30 + foreColor << (bright ? ";1;" : ";") <<
        40 + backColor << "m";
    }

    // Reset the color to the default
    void set_default() {
        std::cout << CSI << "0m";
    }
};

#endif