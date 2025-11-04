#pragma once

#include <regex>
#include <sstream>
#include <cctype>
#include <limits>
#include <fstream>
#include <functional>

#include "Menu.h"
#include "List.h"
#include "Pair.h"

using namespace Menus;
using namespace Pairs;

string inputFilePath(const string& prompt) {
    string path;

    // –егул€рка дл€ Windows-пути, вроде C:\Folder\Subfolder\file.txt
    regex pathPattern(R"(^[A-Za-z]:\\(?:[^\\/:*?"<>|\r\n]+\\)*[^\\/:*?"<>|\r\n]*$)");

    while (true) {
        cout << prompt;
        getline(cin >> ws, path);

        if (path == "q") {
            throw exception();
        }
        if (regex_match(path, pathPattern))
            return path;

        cout << "Invalid file path. Please try again." << endl;
    }
}

ifstream openFile() {
    while (true) {
        string path = inputFilePath("Enter full file path (enter 'q' to exit): ");

        ifstream file(path);
        if (file.is_open()) {
            cout << "File opened successfully!" << endl;
            return file;
        }

        cout << "Failed to open file. Please try again." << endl;
    }
}


std::string trimString(const std::string& str) {
    std::string result;

    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char ch = static_cast<unsigned char>(str[i]);

        if (std::isalnum(ch)) {
            result += ch;
        }
        else if (ch == '-' && i > 0 && i < str.size() - 1 &&
            std::isalnum(static_cast<unsigned char>(str[i - 1])) &&
            std::isalnum(static_cast<unsigned char>(str[i + 1]))) {
            result += ch;
        }
        else {
            result += ' ';
        }
    }

    size_t start = result.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";

    size_t end = result.find_last_not_of(" \t\n\r");
    return result.substr(start, end - start + 1);
}

void FileProject() {

    while (true) {
        system("cls");
        try {
            ifstream file = openFile();
            if (!file.is_open()) return;

            List<Pair<string, int>> longestWords;

            std::string line;
            size_t maxLen = 0;

            while (getline(file, line)) {

                std::string cleaned = trimString(line);
                std::stringstream ss(cleaned);
                std::string word;

                while (ss >> word) {

                    if (word.empty())
                        continue;

                    for (auto& ch : word)
                        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));

                    size_t len = word.length();

                    if (len > maxLen) {
                        maxLen = len;
                        longestWords.clear();

                        Pair<string, int> p(word, 1);
                        longestWords.add(&p);
                    }

                    else if (len == maxLen) {
                        bool exists = false;

                        for (auto it = longestWords.begin(); it != longestWords.end(); ++it) {
                            Pair<string, int>* pair = *it;
                            if (pair->first == word) {
                                pair->second++;
                                exists = true;
                                break;
                            }
                        }

                        if (!exists) {
                            Pair<string, int> p(word, 1);
                            longestWords.add(&p);
                        }
                    }
                }
            }

            file.close();

            if (longestWords.isEmpty()) {
                cout << "File is empty or contains no valid words." << endl;
                return;
            }

            cout << endl << "Longest Words in File have " << longestWords.get(0)->first.size() << " length" << endl;
            int index = 1;
            for (auto it = longestWords.begin(); it != longestWords.end(); ++it) {
                auto* p = *it;
                cout << index++ << ". " << p->first << " --- " << p->second
                    << ((p->second == 1) ? " time" : " times") << endl;
            }

            _getch();
        }
        catch (const exception&) {
            return;
        }
    }
}