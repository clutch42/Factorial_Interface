#include <iostream>
#include <string>

std::string printMessage(int number) {

    return "The number doubled is: " + std::to_string(number * 2);
}

extern "C" {
    const char* printToWeb(int number) {
        static std::string result;
        result = printMessage(number); // Use the function to generate the result
        return result.c_str();
    }
}

int main() {
    std::cout << printMessage(1) << std::endl;
    return 0;
}