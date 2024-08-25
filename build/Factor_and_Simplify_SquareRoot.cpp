// Factor_and_Simplify_SquareRoot.cpp : This file contains the 'main' function. Program execution begins and ends there.
/* This will factor a number and simplify the square root of the number if it is not a perfect square
*/

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

vector<int> getPrimeFactorization(int number) {
    vector<int> factors;
    int divisor = 2;
    while (number > divisor) {
        if (number % divisor == 0) {
            factors.push_back(divisor);
            number /= divisor;
        }
        else {
            divisor++;
        }
    }
    factors.push_back(divisor);

    return factors;
}

bool convertStringToInt(const string& number, int& convertedNumber) {
    try {
        convertedNumber = stoi(number);  // Try converting the string to an integer
        return true;     // If conversion is successful, return true
    }
    catch (const invalid_argument& e) {
        return false;    // If the string is not a valid integer, return false
    }
    catch (const out_of_range& e) {
        return false;    // If the integer is out of range, return false
    }
}

string vectorToString(const vector<int>& vec) {
    string result;
    if (vec.size() > 0) {
        result += u8"(";
    }
    for (size_t i = 0; i < vec.size(); i++) {
        if (i < vec.size() - 1) {
            result += to_string(vec[i]) + u8" * ";
        }
        else {
            result += to_string(vec[i]) + u8") ";
        }
    }
    return result;
}

void reduceTerms(vector<int>& factored, vector<int>& reduced) {
    int i = 0;
    while (i < factored.size()-1 && factored.size() > 1) {
        if (factored.at(i) == factored.at(i + 1)) {
            reduced.push_back(factored.at(i));
            factored.erase(factored.begin() + i);
            factored.erase(factored.begin() + i);
        }
        else {
            i++;
        }
    }
}

string processInput(int number) {
    if (number < 0) {
        return u8"Needs to be positive";
    }
    if (number == 0) {
        return u8"0";
    }
    if (number == 1) {
        return u8"1";
    }
    vector<int> factored, reduced;
    int firstTerm = 1;
    int secondTerm = 1;
    factored = getPrimeFactorization(number);

    string output;
    output += u8"Prime Factorization: \t\t" + vectorToString(factored) + u8"\n";
    output += u8"Square Root of \t\t\t\u221A" + to_string(number) + u8" =\n";
    output += u8"Prime Factors: \t\t\t\u221A" + vectorToString(factored) + u8" =\n";

    reduceTerms(factored, reduced);
    output += u8"Pull terms out of the radical: \t" + vectorToString(reduced);
    if (!factored.empty()) {
        output += u8"\u221A" + vectorToString(factored);
    }
    output += u8" =\nSimplify: \t\t\t";

    for (auto r : reduced) {
        firstTerm *= r;
    }
    for (auto f : factored) {
        secondTerm *= f;
    }
    if (firstTerm > 1) {
        output += to_string(firstTerm);
    }
    if (secondTerm > 1) {
        output += u8"\u221A" + to_string(secondTerm);
    }
    output += u8"\n";

    return output;
}

wstring utf8ToWstring(const string& utf8) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &utf8[0], (int)utf8.size(), NULL, 0);
    wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &utf8[0], (int)utf8.size(), &wstr[0], size_needed);
    return wstr;
}

int main(int argc, char* argv[]) {
    // Set console output code page to UTF-8
    SetConsoleOutputCP(CP_UTF8);

    if (argc != 2) {
        wcerr << u8"Usage: " << argv[0] << u8" <positive_integer>" << endl;
        return 1;
    }

    string numberStr = argv[1];
    //wstring numberWStr = utf8ToWstring(numberStr);
    int number;
    if (convertStringToInt(numberStr, number)) {
        string result = processInput(number);
        cout << result;
    }
    else {
        wcerr << u8"Invalid number" << endl;
        return 1;
    }

    return 0;
}