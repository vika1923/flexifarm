#include "coloredOutputs.h"

// ANSI escape codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Print functions with colors (includes reset)
void printRed(const std::string& text) {
    std::cout << RED << text << RESET;
}

void printGreen(const std::string& text) {
    std::cout << GREEN << text << RESET;
}

void printYellow(const std::string& text) {
    std::cout << YELLOW << text << RESET;
}

void printBlue(const std::string& text) {
    std::cout << BLUE << text << RESET;
}

void printMagenta(const std::string& text) {
    std::cout << MAGENTA << text << RESET;
}

void printCyan(const std::string& text) {
    std::cout << CYAN << text << RESET;
}

void printBold(const std::string& text) {
    std::cout << BOLD << text << RESET;
}

