#include <iostream>
#include <fstream>

struct Color {
    short red, green, blue;
};

struct TextColor : Color {};
struct BgColor : Color {};

std::ostream& operator<<(std::ostream &out, const TextColor &color) {
    out << "\e[38;2;" << color.red << ";" << color.green << ";" << color.blue << "m";
}