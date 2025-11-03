#pragma once

#include <regex>
#include <sstream>
#include <limits>

#include "List.h"
#include "Sign.h"
#include "Menu.h"

using namespace Signs;
using namespace Lists;
using namespace Menus;

int* inputBirthday() {
	string line;
	int d, m, y;

	while (true) {
		cout << "Enter birthday (sample 30 08 2005): ";
		getline(cin >> ws, line);

		stringstream ss(line);
		if (!(ss >> d >> m >> y)) {
			cout << "Invalid input. Please enter 3 integers separated by spaces" << endl;
			continue;
		}

		if (m < 1 || m > 12 || d < 1 || y < 1900) {
			cout << "Invalid date range. Please enter a valid date" << endl;
			continue;
		}

		int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
			daysInMonth[1] = 29;

		if (d > daysInMonth[m - 1]) {
			cout << "Invalid day for this month" << endl;
			continue;
		}

		return new int[3] {d, m, y};
	}
}

Zodiac inputZodiac() {
	string value;
	while (true) {
		cout << "Enter zodiac: ";
		getline(cin >> ws, value);

		try {
			Zodiac z = from_string(value);
			return z;
		}
		catch (const invalid_argument& e) {
			cout << e.what() << ". Please try again" << endl;
			continue;
		}
	}
}

string inputString(const string& prompt) {
	string value;
	while (true) {
		cout << prompt;
		getline(cin >> ws, value);

		if (regex_match(value, regex("^[A-Za-z]+$")))
			return value;

		cout << "Invalid input. Please try again." << endl;
	}
}

Sign* createSign() {
	Sign obj;
	cout << "Enter name, last name, day, month and year of birtday " << endl;
	cin >> obj;

	Sign* sign = new Sign(obj);
	return sign;
}

List<Sign>* findByName(const List<Sign>* signs, const string& name) {

	List<Sign>* found = new List<Sign>();

	for (auto it = signs->begin(); it != signs->end(); ++it) {
		Sign* sign = *it;
		if (sign->getName() == name)
			found->add(sign);
	}

	return found;
}

List<Sign>* findByLastName(const List<Sign>* signs, const string& lastName) {

	List<Sign>* found = new List<Sign>();

	for (auto it = signs->begin(); it != signs->end(); ++it) {
		Sign* sign = *it;
		if (sign->getLastName() == lastName)
			found->add(sign);
	}

	return found;
}

List<Sign>* findByBirthday(const List<Sign>* signs, int birthday[3]) {

	List<Sign>* found = new List<Sign>();

	for (auto it = signs->begin(); it != signs->end(); ++it) {
		Sign* sign = *it;
		int* signBirthday = sign->getBirthday();
		if (signBirthday[0] == birthday[0] &&
			signBirthday[1] == birthday[1] &&
			signBirthday[2] == birthday[2])
			found->add(sign);

		delete signBirthday;
	}

	return found;
}

List<Sign>* findByZodiac(const List<Sign>* signs, Signs::Zodiac zodiac) {

	List<Sign>* found = new List<Sign>();

	for (auto it = signs->begin(); it != signs->end(); ++it) {
		Sign* sign = *it;
		if (sign->getZodiac() == zodiac)
			found->add(sign);
	}

	return found;
}

void SignProject() {
	List<Sign>* signs = new List<Sign>();

	bool exit = false;
	while (!exit) {
		system("cls");
		char choice = validChoice('0', '3', signMenu);
		switch (choice) {

		// Create new
		case '1': {
			system("cls");
			Sign* sign = createSign();
			signs->add(sign);
			signs->sort(false);
			break;
		}

		// View all
		case '2': {
			system("cls");
			if (signs->isEmpty())
				cout << "Not any record in data" << endl;
			else {
				choice = validChoice('0', '2', reverseMenu);
				switch (choice) {
				case '1':
					signs->sort(true);
					break;
				case '2':
					signs->sort(false);
					break;
				default:
					break;
				}

				system("cls");
				if (choice == '1' || choice == '2') {

					for (int i = 0; i < signs->size(); i++) {
						Sign* sign = signs->get(i);
						cout << i + 1 << ". " << *sign << endl;
					}

					_getch();
				}
			}

			break;
		}

		// Search
		case '3': {
			system("cls");
			choice = validChoice('0', '4', searchSign);
			List<Sign>* found = nullptr;
			switch (choice) {
			case '1': {
				string name = inputString("Enter name: ");
				found = findByName(signs, name);

				break;
			}
			case '2': {
				string lastName = inputString("Enter last name: ");
				found = findByLastName(signs, lastName);
				
				break;
			}
			case '3': {
				int* birthday = inputBirthday();
				found = findByBirthday(signs, birthday);
				
				delete birthday;
				break;
			}
			case '4': {
				Zodiac zodiac = inputZodiac();
				found = findByZodiac(signs, zodiac);

				break;
			}
			default: break;
			}

			system("cls");
			if (found != nullptr && (choice >= '1' && choice <= '4')) {
				if (found->isEmpty())
					cout << "Not found any record" << endl;
				else {
					for (int i = 0; i < found->size(); i++) {
						Sign* sign = found->get(i);
						cout << i + 1 << ". " << *sign << endl;
					}
				}

				_getch();
				delete found;
			}

			break;
		}

		default:
			delete signs;
			exit = true;
			return;
		}
	}
}
