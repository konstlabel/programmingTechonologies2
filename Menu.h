#pragma once
#include <iostream>
#include <conio.h>

using namespace std;

namespace Menus {

	// START
	void startMenu() {
		cout << "=== Start Menu ===" << endl;
		cout << "1. Sign Menu"	<< endl;
		cout << "2. File Menu"	<< endl;
		cout << "0. Exit"		<< endl;
	}

	// SIGN
	void signMenu() {
		cout << "=== Sign Menu ===" << endl;
		cout << "1. Create new" << endl;
		cout << "2. View all" << endl;
		cout << "3. Search" << endl;
		cout << "0. Exit" << endl;
	}

	void reverseMenu() {
		cout << "View all records reverse?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cout << "0. Back" << endl;
	}

	void searchSign() {
		cout << "1. Find by name" << endl;
		cout << "2. Find by last name" << endl;
		cout << "3. Find by birthday" << endl;
		cout << "4. Find by zodiac" << endl;
		cout << "0. Back" << endl;
	}

	void recordMenu() {
		cout << "1. Edit" << endl;
		cout << "2. Delete" << endl;
		cout << "0. Back" << endl;
	}

	// FILE
	void fileMenu() {
		cout << "=== File Menu ===" << endl;
		cout << "1. find file" << endl;
		cout << "0. Exit" << endl;
	}

	// VALID
	char validChoice(char min = '0', char max = '9', void (*menu) () = startMenu) {
		char choice;

		menu();
		while (true) {
			choice = _getch();
			if (choice < min || choice > max)
				continue;
			break;
		}

		return choice;
	}
}