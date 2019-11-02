// Family List.cpp

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdio.h> 
#include <io.h>

using namespace std;

// Basic Terminal GUI and Menu
void welcome();
void menu(string[], int&, int&);
void menu2(string[], int&, int&);
void header(string[], int&);
void cleanup();

// Family functions
void addfamily(string[], int&);
void selectfamily(string[], int&);
void removemem(string[], int&);
void listfamily(string[], int&);
void selectedfamily(string[], int&, int&);
void editfamily(string[], int&);

// Wish List Functions
void listassigner(string[], string familymemb[50][20][1], int&, int&);
void currentwishlist(string[], string familymemb[50][20][1], int&, int&);
void purchaseditems(string[], string familymemb[50][20][1], int&, int&);
void editwishlist(string[], string familymemb[50][20][1], int&, int&);
void addItem(string[], string familymemb[50][20][1], int&, int&);
void suggestions(string[], string familymemb[50][20][1], int&, int&);
void suggestionsList(int);

// Info/Storage Manager
void readin(string[], int&);
void save(string[], int&);
void cleaner(string[], int&);
void wishSave(string[], string familymemb[50][20][1], int&, int&);
void wishReadin(string[], string familymemb[50][20][1], int&, int&);
void wishCleaner(string[], string familymemb[50][20][1], int&, int&);

int main() {
	int input = 0, instore = 1;
	string familymem[50];

	welcome();
	readin(familymem, instore);
	cleaner(familymem, instore);

	menu(familymem, input, instore);

	exit(0);
}

/*------------------------------------------------------------------------*/

// Menu Functions

/*------------------------------------------------------------------------*/

void menu(string familymem[], int& choice, int& instore) {
	while (choice != 6) {
		cout << "1. Add A Member" << endl;
		cout << "2. Select a Family Member" << endl;
		cout << "3. List Family Members" << endl;
		cout << "4. Edit Family Member" << endl;
		cout << "5. Remove Family Member" << endl;
		cout << "6. Quit Program" << endl;

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

void menu2(string familymem[], int& instore, int& chosenmem) {
	string familymemb[50][20][1];

	int choice = 0, items = 0, amount = 1;

	wishReadin(familymem, familymemb, chosenmem, amount);
	//wishCleaner(familymem, familymemb, chosenmem, amount);
	listassigner(familymem, familymemb, instore, chosenmem);

	header(familymem, chosenmem);

	while (choice != 8) {
		cout << "1. Current Wish List" << endl;
		cout << "2. Items Already Aquried" << endl;
		cout << "3. Edit Wish List" << endl;
		cout << "4. Type of items" << endl;
		cout << "5. Add a item" << endl;
		cout << "6. Change Family Member" << endl;
		cout << "7. Go Back" << endl;
		cout << "8. Exit Program" << endl;

		cin >> choice;

		switch (choice) {
		case 1:
			currentwishlist(familymem, familymemb, amount, chosenmem);
			wishSave(familymem, familymemb, chosenmem, instore);
			break;
		case 2:
			purchaseditems(familymem, familymemb, items, chosenmem);
			wishSave(familymem, familymemb, chosenmem, instore);
			break;
		case 3:
			editwishlist(familymem, familymemb, items, chosenmem);
			wishSave(familymem, familymemb, chosenmem, instore);
			break;
		case 4:
			//	listfamily(familymem, instore);
			wishSave(familymem, familymemb, chosenmem, instore);
			break;
		case 5:
			addItem(familymem, familymemb, chosenmem, instore);
			wishSave(familymem, familymemb, chosenmem, instore);
			break;
		case 6:
			selectfamily(familymem, instore);
			wishSave(familymem, familymemb, chosenmem, instore);
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

/*------------------------------------------------------------------------*/

// File Manager

/*------------------------------------------------------------------------*/

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

void save(string familymem[], int& instore) {
	ofstream namelist;

	namelist.open("WishList.txt");

	for (int familyamount = 1; familyamount <= instore; familyamount++)
		namelist << familymem[familyamount] << endl;

	namelist.close();
}

void cleaner(string familymem[], int& instore) {
	for (int i = 1; i <= instore; i++) {
		if (familymem[i] == "")
			instore--;
	}
}

void wishSave(string familymem[], string familymemb[50][20][1], int& chosenmem, int& instore) {
	ofstream wishlist;
	string newfile;
	newfile = familymem[chosenmem];
	newfile = newfile + ".txt";

	wishlist.open(newfile);

	for (int wishitem = 1; wishitem <= 20; wishitem++) {
		if (familymemb[chosenmem][wishitem][0] != " ")
			wishlist << familymemb[chosenmem][wishitem][0] << endl;
		wishlist.close();
	}
}

void wishReadin(string familymem[], string familymemb[50][20][1], int& chosenmem, int& amount) {
	string storedFam, items, test;
	ifstream wishingList;
	ofstream newWishlist;

	storedFam = familymem[chosenmem];
	storedFam = storedFam + ".txt";

	cout << storedFam << " IS LOADED " << endl;

	wishingList.open(storedFam);
	if (wishingList.fail()) {
		ofstream newWishlist;
		newWishlist.open(storedFam);
	}

	while (getline(wishingList, items)) {
		familymemb[chosenmem][amount][1] = items;
		amount++;
	}
	wishingList.close();
}

void wishCleaner(string familymem[], string familymemb[50][20][1], int& chosenmem, int& amount) {
	string move;
	/*
	for (int item = 1; item <= amount; item++) {
		if (familymemb[chosenmem][item][0] == "") {
			move = familymemb[chosenmem][item][0];
			familymemb[chosenmem][item][0] = familymemb[chosenmem][item + 1][0];
			familymemb[chosenmem][item + 1][0] = move;
		}
	}
	*/

	for (int i = 1; i <= amount; i++) {
		if (familymemb[chosenmem][i][0] == "")
			amount--;
	}
}

/*------------------------------------------------------------------------*/

// Family Functions

/*------------------------------------------------------------------------*/

void addfamily(string familymem[], int& instore) {
	string newfamily, newname;
	bool exist = 0;

	cleanup();

	cout << "Please enter the new family member name" << endl;

	cin.ignore();
	getline(cin, newfamily);

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
		
		cin.ignore();
		getline(cin, replace);

		familymem[choice] = replace;
		cout << "-------------------------------" << endl;
	}
	else
		cleanup();

	cleanup();
}

void selectfamily(string familymem[], int& instore) {
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
	if (familymem[1] != "" && choice != 0 && choice <= instore)
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
	int removeMem;
	string move, file2;

	cleanup();

	if (familymem[1] != "") {
		cout << "Who do you want to remove from the family" << endl;
		cout << "-------------------------------" << endl;

		for (int family = 1; family <= instore; family++) {
			cout << family << ". " << familymem[family] << endl;
		}
		cout << "-------------------------------" << endl;

		cin >> removeMem;
		file2 = familymem[removeMem];
		file2 = file2 + ".txt";
		remove(file2.c_str());

		familymem[removeMem] = "";

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

/*------------------------------------------------------------------------*/

// Wish List Functions

/*------------------------------------------------------------------------*/

void listassigner(string familymem[], string familymemb[50][20][1], int& instore, int& chosenmem) {
	string name;
	for (int i = 1; i <= instore; i++) {
		name = familymem[i];
		familymemb[i][0][0] = name;
	}
}

void currentwishlist(string familymem[], string familymemb[50][20][1], int& amount, int& chosenmem) {
	header(familymem, chosenmem);
	if (amount != 0) {
		cout << "This is the current Wish List for " << familymem[chosenmem] << endl;
		for (int i = 1; i <= amount; i++) {
			cout << i << ". " << familymemb[chosenmem][i][0] << endl;
		}
		cout << "-------------------------------" << endl;
	}
	else {
		cout << "The list is empty" << endl;
		cout << "-------------------------------" << endl;
	}
}

void purchaseditems(string familymem[], string familymemb[50][20][1], int& items, int& chosenmem) {
	header(familymem, chosenmem);
	int bought = 0;
	
	for (int i = 1; i <= items; i++) {
		if (familymemb[chosenmem][i][1] != "") {
			familymemb[chosenmem][i][1];
			bought++;
		}
	}

	if (bought > 0) {
		cout << "This is the list of items that have been purchased already" << endl;
		//cout << "-------------------------------" << endl;
		for (int i = 1; i <= items; i++) {
			if (familymemb[chosenmem][i][1] != "")
			cout << i << ". " << familymemb[chosenmem][i][1] << endl;

			cout << "The value is 1 " << familymemb[chosenmem][i][1] << endl;
			cout << "The value is 0 "  << familymemb[chosenmem][i][0] << endl;

		}
	}
	else {
		cout << "You haven't bought anything" << endl;
	}

	cout << "-------------------------------" << endl;
}

void editwishlist(string familymem[], string familymemb[50][20][1], int& items, int& chosenmem) {
	header(familymem, chosenmem);
	string item, rename;
	int input, number, bought = 0;
	char response;

	//cout << "1. Add an item" << endl;
	cout << "1. Edit an existing item" << endl;
	cout << "2. Change the status of an item" << endl;

	cin >> input;

	while (input != 0) {
		/*
		// Adding an item
		if (input == 1) {
			header(familymem, chosenmem);
			if (items != 20) {
				items++;
				cout << "Put in the item you want to add" << endl;
				cin.ignore();
				getline(cin, item);
				familymemb[chosenmem][items][0] = item;/*
				if (familymemb[chosenmem][items][1] != "") {
					familymemb[chosenmem][items][0] = familymemb[chosenmem][items][1];
					familymemb[chosenmem][items][1] = "";
				}
				
			}
			else
				cout << "Your list is full" << endl;
			break;
		}
		*/

		// Editin an existing item
		if (input == 1) {
			header(familymem, chosenmem);
			for (int i = 1; i <= items; i++) {
				cout << i << ". " << familymemb[chosenmem][i][0] << endl;
			}

			cout << "Which item you want to edit" << endl;
			cin >> number;
				cout << "What do you want to rename it to?" << endl;
				cin.ignore();
				getline(cin, rename);
				familymemb[chosenmem][number][0] = rename;
			break;
		}
		else if (items == 0) {
			cout << "There's nothing on the list" << endl;
			break;
		}

		// Change the purchase status of an item
		if (input == 2) {
			header(familymem, chosenmem);
			cout << "Wishlist items" << endl;
			
			for (int i = 1; i <= items; i++) {
				cout << i << ". " << familymemb[chosenmem][i][0] << endl;
				cout << "-------------------------------" << endl;
			}
			cout << "Which item you want to change the purchase status for?" << endl;
			cin >> number;
			cleanup();
			cout << familymemb[chosenmem][number][0] << endl;
			cout << "Does " << familymem[chosenmem] << " owns this item now? [Y/N]" << endl;
			cin >> response;
				if ((response == 'Y') || (response == 'y')) {
					if(familymemb[chosenmem][number][0] != "")
						familymemb[chosenmem][number][1] = familymemb[chosenmem][number][0];
					}
				else if ((response == 'N') || (response == 'n'))
					if(familymemb[chosenmem][number][0] != "")
						familymemb[chosenmem][number][0] = familymemb[chosenmem][number][1];
		}
		else if (items == 0)
			cout << "There's nothing on the list" << endl;
			break;

	}
}

void suggestions(string familymem[], string familymemb[50][20][1], int& items, int& chosenmem) {
	header(familymem, chosenmem);

	int choice;

	cout << "What type of items is this person intreseted in?" << endl;

	cin >> choice;

	suggestionsList(choice);

}

void suggestionsList(int choice) {


}

void addItem(string familymem[], string familymemb[50][20][1], int& items, int& chosenmem) {
	cleanup();
	if (items != 20) {
		items++;
		cout << "Please enter the item you want to add to the Wishlist" << endl;
		cin >> familymemb[chosenmem][items][0];
	}
	else
		cout << familymem[chosenmem] << " Wishlist is full" << endl;
}
/*------------------------------------------------------------------------*/

// GUI/Terminal Functions

/*------------------------------------------------------------------------*/

void welcome() {
	cout << "Welcome to the Family Wish List" << endl;
	cout << "-------------------------------" << endl;
}

void cleanup() {
	system("CLS");
}

void header(string familymem[], int& chosenmem) {
	cleanup();
	cout << "Family member: " << familymem[chosenmem] << endl;
	cout << "-------------------------------" << endl;
}

void selectedfamily(string familymem[], int& instore, int& chosenmem) {
	header(familymem, chosenmem);
	menu2(familymem, instore, chosenmem);
}

/*------------------------------------------------------------------------*/

// Select Family bug fixed