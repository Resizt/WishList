// Family List.cpp

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// Basic Terminal GUI and Menu
void welcome();
void menu	(string[], int&, int&);
void menu2	(string[], int&, int&);
void header	(string[], int&);
void cleanup();

// Family functions
void addfamily		(string[], int&);
void selectfamily	(string[], int&);
void removemem		(string[], int&);
void listfamily		(string[], int&);
void selectedfamily	(string[], int&, int&);
void editfamily		(string[], int&);

// Wish List Functions
void listassigner	(string[], string familymemb[50][20][1], int&, int&);
void currentwishlist(string[], string familymemb[50][20][1], int&, int&);
void purchaseditems(string[], string familymemb[50][20][1], int&, int&);

// Info/Storage Manager
void readin	(string[], int&);
void save	(string[], int&);
void cleaner(string[], int&);

/*------------------------------------------------------------------------*/

int main() {
	int input = 0, instore = 1;
	string familymem[50];

	welcome();
	readin(familymem, instore);
	cleaner(familymem, instore);

	menu(familymem, input, instore);

	exit(0);
}

void readin(string familymem[], int& instore) {
	string name;
	ifstream wishlist;

	wishlist.open("WishList.txt");

	while (getline(wishlist, name)) {
		familymem[instore] = name;
		instore++;
	}

	for (int i = 1; i <= instore; i++)
		if (familymem[instore] == "")
			instore--;

	wishlist.close();
}

void cleaner(string familymem[], int& instore) {
	int replace = instore;

	for (int i = 1; i <= instore; i++) {
		if (familymem[i] == "")
			instore--;
	}
}

void save(string familymem[], int& instore) {
	ofstream wishlist;

	wishlist.open("WishList.txt");

	for (int familyamount = 1; familyamount <= instore; familyamount++)
		wishlist << familymem[familyamount] << endl;

	wishlist.close();
}

void welcome() {
	cout << "Welcome to the Family Wish List" << endl;
	cout << "-------------------------------" << endl;
}

void menu(string familymem[], int& choice, int& instore) {
	while (choice != 6) {
		cout << "1. Add A Member"			<< endl;
		cout << "2. Select a Family Member" << endl;
		cout << "3. List Family Members"	<< endl;
		cout << "4. Edit Family Member"		<< endl;
		cout << "5. Remove Family Member"	<< endl;
		cout << "6. Quit Program"			<< endl;

		cin >> choice;
		switch (choice) {
		case 1:
			addfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 2:
			selectfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 3:
			listfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 4:
			editfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 5:
			removemem(familymem, instore);
			break;
		case 6:
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
				cout << "-------------------------------" << endl;
				break;
			}
		}
		exist = 1;
	}

	if (exist == 1) {
		instore = 1 + instore;
		familymem[instore] = newfamily;
		cout << "-------------------------------" << endl;
	}
}

void editfamily(string familymem[], int& instore){
	int choice;
	string replace;
	
	cleanup();

	if (familymem[1] != ""){
		cout << "Select a family member to edit their name (type in 0 to go back) " << endl;
		cout << "-------------------------------" << endl;
		for (int i = 1; i <= instore; i++) {
			cout << i << ". " << familymem[i] << endl;
		}
		cin >> choice;
	}
	else {
		cout << "There's no one to select up" << endl;
		cout << "-------------------------------" << endl;
	}
	while (choice > instore || choice < 0){
		cout << "Please make a valid input" << endl;
		cin >> choice;
	}
		if (choice != 0) {
		cout << "Enter a replacement for the user name: " << endl;
		cin >> replace;
		familymem[choice] = replace;
		cout << "-------------------------------" << endl;
	}
	else
		cleanup();

	cleanup();
}

void selectfamily(string familymem[], int& instore){
	string lookfor;
	int choice;

	cleanup();
	if (familymem[1] != "") {
		cout << "Select a family member (type in 0 to go back) " << endl;
		cout << "-------------------------------" << endl;
		for (int i = 1; i <= instore; i++) {
			cout << i << ". " << familymem[i] << endl;
		}
		cin >> choice;
	}
	else {
		cout << "There's no one to select up" << endl;
		cout << "-------------------------------" << endl;
	}
	if (choice != 0 && choice <= instore)
		selectedfamily(familymem, instore, choice);
	else
		cleanup();
}

void listfamily(string familymem[], int& instore) {
	string lookfor;

	cleanup();
	if (familymem[1] != "") {
		cout << "Here's a list of your family" << endl;
		cout << "-------------------------------" << endl;

		for (int i = 1; i <= instore; i++) {
			cout << i << ". " << familymem[i] << endl;
		}

		cout << "-------------------------------" << endl;
	}
	else {
		cout << "There's no one to look up" << endl;
		cout << "-------------------------------" << endl;
	}
}

void removemem(string familymem[], int& instore) {
	int remove, family;
	string move;

	cleanup();

	if (familymem[1] != "") {
		cout << "Who do you want to remove from the family" << endl;
		cout << "-------------------------------" << endl;

		for (int family = 1; family <= instore; family++) {
			cout << family << ". " << familymem[family] << endl;
		}
		cout << "-------------------------------" << endl;

		cin >> remove;

		familymem[remove] = "";

		for (int family = 1; family <= instore; family++) {
			if (familymem[family] == "") {
				move = familymem[family];
				familymem[family] = familymem[family + 1];
				familymem[family + 1] = move;
			}
		}
		cleaner(familymem, instore);
	}
	else {
		cout << "You have no one in the family to remove" << endl;
		cout << "-------------------------------" << endl;
	}
}

void cleanup() {
	system("CLS");
}

/*------------------------------------------------------------------------*/

void selectedfamily(string familymem[], int& instore, int& chosenmem) {
	header(familymem, chosenmem);
	menu2(familymem, instore, chosenmem);
}

void header(string familymem[], int& chosenmem) {
	cleanup();
	cout << "Family member: " << familymem[chosenmem] << endl;
	cout << "-------------------------------" << endl;
}

void listassigner(string familymem[], string familymemb[50][20][1], int& instore, int& chosenmem) {
	string name;
	for (int i = 1; i <= instore; i++) {
		name = familymem[i];
		familymemb[i][0][0] = name;
	}
}

void menu2(string familymem[], int& instore, int& chosenmem) {
	string familymemb[50][20][1];

	listassigner(familymem, familymemb, instore, chosenmem);
	header(familymem, chosenmem);
	int choice = 0;

	while (choice != 7 || choice != 8) {
		cout << "1. Current Wish List" << endl;
		cout << "2. Items Already Aquried" << endl;
		cout << "3. Edit Wish List" << endl;
		cout << "4. Type of items" << endl;
		cout << "5. Find suggestions" << endl;
		cout << "6. Change Family Member" << endl;
		cout << "7. Go Back" << endl;
		cout << "8. Exit Program" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			currentwishlist(familymem, familymemb, instore, chosenmem);
			save(familymem, instore);
			break;
		case 2:
			//	selectfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 3:
			//	removemem(familymem, instore);
			save(familymem, instore);
			break;
		case 4:
			//	listfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 5:
			//	exit(0);
			save(familymem, instore);
			break;
		case 6:
			selectfamily(familymem, instore);
			save(familymem, instore);
			break;
		case 7:
			cleanup();
			menu(familymem, choice, instore);
			break;
		case 8:
			exit(0);
			break;
		}
	}
}

void currentwishlist(string familymem[], string familymemb[50][20][1], int& instore, int& chosenmem) {
	header(familymem, chosenmem);

	cout << "This is the current Wish List for " << familymem[chosenmem] << endl;
	for (int i = 1; i <= instore; i++) {
		cout << familymemb[chosenmem][i][1];
	}
	cout << "-------------------------------" << endl;
}

void purchaseditems(string familymem[], string familymemb[50][20][1], int& instore, int& chosenmem) {
	header(familymem, chosenmem);

	cout << "This is the list of items that have been purchased already" << endl;
	cout << "-------------------------------" << endl;

	for (int i = 0; i <= 20; i++) {
		familymemb[chosenmem][i][0];
	}


}

/*------------------------------------------------------------------------*/

/*
void editwishlist

void suggestions

void purchaseditems
	bool purchaseassigner (Controls familymemb[chosenmem][0][i])
*/