// Family List.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// The basic terminal GUI and menu.
void welcome();
void menu(int&, string[], int&);
void header(string[]);

// The Family functions
void addfamily(string[], int&);
void editfamily();
void lookupfamily(string[], int&);
void removefamily(string[], int&);

int main() {
	int input = 0, instore = 0;
	string familymem[500];

	welcome();
	menu(input, familymem, instore);

	exit(0);
}


void welcome() {
	cout << "Welcome to the Family Tree List" << endl;
	cout << "-------------------------------" << endl;
}

void menu(int& choice, string familymem[], int& instore) {
	while (choice != 4) {
		cout << "1. Add a member" << endl;
		cout << "2. Search a member" << endl;
		cout << "3. Remove a memeber" << endl;
		cout << "4. Quit Program" << endl;

		cin >> choice;
			switch (choice) {
			case 1:
				addfamily(familymem, instore);
				break;
			case 2:
				lookupfamily(familymem, instore);
				break;
			case 3:
				// removemem(familymem, instore);
				break;
			case 4:
				exit(0);
			}
		}
}

void addfamily(string familymem[], int& instore) {
	string newfamily, newname;

	cout << "Please enter the new family member name" << endl;
	cin >> newfamily;
	instore = 1 + instore;
	familymem[instore] = newfamily;
}


void lookupfamily(string familymem[], int& instore) {
	string lookfor;

	system("CLS");
	
	cout << "Please put in the family member name you're looking for; ";
	cin >> lookfor;

	for (int i = 0; i <= 500; i++) {
		if (familymem[i] == lookfor) {
			cout << lookfor << " is the " << i << " member of the family" << endl;
			break;
		}
	}
}

void removemem(string familymem[], int& instore) {

}