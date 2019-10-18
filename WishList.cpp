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
void cleanup();

// The Family functions
void addfamily(string[], int&);
void editfamily();
void lookupfamily(string[], int&);
void removemem(string[], int&);
void listfamily(string[], int&);

// Info/Storage manager
void readin(string[], int&);
void save(string[], int&);
void cleaner(string[], int&);

int main() {
	int input = 0, instore = 1;
	string familymem[500];

	welcome();
	readin(familymem, instore);
	cleaner(familymem, instore);
	
	menu(input, familymem, instore);

	exit(0);
}

void readin(string familymem[], int& instore) {
	string name;
	ifstream wishlist;

	wishlist.open("WishList.txt");
	
	/*
	for (int i = 0; i <= 500; i++) {
			wishlist >> familymem[instore];
			instore++;
		}*/
	
	
	while (getline(wishlist, name)) {
		familymem[instore] = name;
		instore++;
	}

	for (int i = 1; i <= instore; i++)
		if (familymem[instore] == "")
			instore--;
	
	wishlist.close();
}

void save(string familymem[], int& instore) {
	ofstream wishlist;

	wishlist.open("WishList.txt");

	for (int familyamount = 1; familyamount <= instore; familyamount++)
		wishlist << familymem[familyamount] << endl;

	wishlist.close();
}

void welcome() {
	cout << "Welcome to the Family Tree List" << endl;
	cout << "-------------------------------" << endl;
}

void menu(int& choice, string familymem[], int& instore) {
	while (choice != 5) {
		cout << "1. Add a member" << endl;
		cout << "2. Select a Family Member" << endl;
		cout << "3. Remove a memeber" << endl;
		cout << "4. List Family Memebers" << endl;
		cout << "5. Quit Program" << endl;

		cin >> choice;
			switch (choice) {
			case 1:
				addfamily(familymem, instore);
				save(familymem, instore);
				break;
			case 2:
				lookupfamily(familymem, instore);
				save(familymem, instore);
				break;
			case 3:
				removemem(familymem, instore);
				save(familymem, instore);
				break;
			case 4:
				listfamily(familymem, instore);
				save(familymem, instore);
				break;
			case 5:
				exit(0);
				break;
			}
		}
}

void addfamily(string familymem[], int& instore) {
	string newfamily, newname;
	bool exist = 0;

	cleanup();

	cout << "Please enter the new family member name" << endl;
	cin >> newfamily;

	while (exist == 0) {
		for (int i = 1; i <= instore; i++) {
			if (familymem[i] == newfamily) {
				cout << newfamily << " already exist." << endl;
				break;
			}
		}
		exist = 1;

		/*
		if(exist == 0){
			cout << "Please put in another family memeber name: ";
			cin >> newfamily;
		}
		*/
	}
	
	if (exist == 1) {
		instore = 1 + instore;
		familymem[instore] = newfamily;
	}
}

void lookupfamily(string familymem[], int& instore) {
	string lookfor;

	cleanup();

	cout << "Please put in the family member name you're looking for; ";
	cin >> lookfor;
		for (int i = 1; i <= instore; i++) {
			if (familymem[i] == lookfor) {
				cout << "-------------------------------" << endl;
				cout << lookfor << " is the " << i << " member of the family" << endl;
				break;
			}
		}
}

void listfamily(string familymem[], int& instore) {
	string lookfor;

	cleanup();

	cout << "Here's a list of your family" << endl;
	cout << "-------------------------------" << endl;

		for (int i = 1; i <= instore; i++) {
			cout << i << ". " << familymem[i] << endl;
			}

	cout << "-------------------------------" << endl;
}

void removemem(string familymem[], int& instore) {
	int remove, family;
	cleanup();

	cout << "Who do you want to remove from the family" << endl;
	cout << "-------------------------------" << endl;

	for (int family = 1; family <= instore; family++) {
		cout << family << ". " << familymem[family] << endl;
	}
	cout << "-------------------------------" << endl;

	cin >> remove;

		familymem[remove] = "";

		for (int family = 1; family <= instore; family++) {
			familymem[remove] = familymem[remove + 1];
		}
		
}

void cleaner(string familymem[], int& instore) {
	struct Node* list;

}
void cleanup() {
	system("CLS");
}