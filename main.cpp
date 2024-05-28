#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cctype>

bool isNumeric(const std::string& password) {
    return std::all_of(password.begin(), password.end(), ::isdigit);
}

bool hasFourConsecutiveASCII(const std::string& password) {
    if (password.size() < 4) return false;
    std::vector<int> ascii_values;
    for (char c : password) {
        ascii_values.push_back(static_cast<int>(c));
    }
    std::sort(ascii_values.begin(), ascii_values.end());
    for (size_t i = 0; i <= ascii_values.size() - 4; ++i) {
        if (ascii_values[i + 3] - ascii_values[i] == 3 && 
            std::set<int>(ascii_values.begin() + i, ascii_values.begin() + i + 4).size() == 4) {
            return true;
        }
    }
    return false;
}

bool isComplex(const std::string& password) {
    bool hasDigit = false, hasLower = false, hasUpper = false;
    for (char c : password) {
        if (isdigit(c)) hasDigit = true;
        if (islower(c)) hasLower = true;
        if (isupper(c)) hasUpper = true;
        if (hasDigit && hasLower && hasUpper) return true;
    }
    return false;
}

int main() {
    std::ifstream inputFile("hasla.txt");
    std::ofstream outputFile("wyniki_hasla.txt");
    
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<std::string> passwords;
    std::string line;
    while (std::getline(inputFile, line)) {
        passwords.push_back(line);
    }

    int numericCount = 0;
    std::unordered_map<std::string, int> passwordCount;
    int asciiConsecutiveCount = 0;
    int complexCount = 0;

    for (const auto& password : passwords) {
        if (isNumeric(password)) {
            ++numericCount;
        }
        ++passwordCount[password];
        if (hasFourConsecutiveASCII(password)) {
            ++asciiConsecutiveCount;
        }
        if (isComplex(password)) {
            ++complexCount;
        }
    }

    std::set<std::string> duplicates;
    for (const auto& entry : passwordCount) {
        if (entry.second > 1) {
            duplicates.insert(entry.first);
        }
    }

    outputFile << "74.1. " << numericCount << std::endl;
    outputFile << "74.2." << std::endl;
    for (const auto& duplicate : duplicates) {
        outputFile << duplicate << std::endl;
    }
    outputFile << "74.3. " << asciiConsecutiveCount << std::endl;
    outputFile << "74.4. " << complexCount << std::endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
