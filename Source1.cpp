#pragma warning(disable : 4996)
#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
using namespace std;

void writeToFile(string fileName, string phone, string soc, string ram, string bat, string ss, string mp, string price, string num) {
	ofstream fout;
	fout.open(fileName, ios::app);
	fout << "\n" << phone << soc << ram << bat << ss << mp << price << num;
	fout.close();
}

void searchPhone(string search, string fileName, bool showRelatedPhones) {
	string showPhone = " ", end = "x", relatedPhones = "";
	char colon = ':', hash = '#';
	int isFound = 0;
	ifstream phoneIn;
	phoneIn.open(fileName);
	while (!phoneIn.eof()) {
		getline(phoneIn, showPhone);
		if (showPhone == search)
			isFound = 1;
		if (showPhone == end && isFound == 1) {
			isFound = -1;
			break;
		}
		if (isFound == 1) {
			if (showPhone[0] == hash) {
				if (!showRelatedPhones) {
					break;
				}
				int j = 1;
				string relatedPhone = "";
				while (showPhone[j] != colon) {
					relatedPhone += showPhone[j];
					j++;
				}
				string file = "";
				for (int k = j + 1; k < showPhone.size(); k++) {
					file += showPhone[k];
				}
				cout << "\n" << "*********** Related phone ***********\n";
				searchPhone(relatedPhone, file, false);
			}
			else {
				for (int i = 0; i < showPhone.size(); i++) {
					cout << showPhone[i];
				}
			}
			cout << "\n\n";
		}
	}
	if (isFound == 0) {
		cout << "Phone not found!";
	}
}

int passCheck() {
	char password[10], ch;
	int i = 0, flag = 0;
	while (1) {
		ch = _getch();
		if (ch == 13)
			break;
		else if(ch == 8) {
			if(i > 0) {
				i--;
				password[i] = '\0';
				cout<<"\b \b";
			}
		}
		else {
			password[i] = ch;
			_putch('*');
			i++;
		}
	}
	password[i] = '\0';
	if (strcmp(password, "9890") == 0) {
		cout << "\nWELCOME!";
		flag = 1;
	}
	else {
		cout << "\nIncorrect Password!";
		flag = 0;
	}
	return flag;
}

void addPhone(string allphones, string phonefile, string brandfile) {
	string phone, soc = "SoC: ", soc1, ram = "Ram: ", ram1, bat = "Battery: ", bat1, ss = "Screen Size: ", ss1, mp = "Megapixel: ", mp1, price = "Price: ", price1, num;
	cout << "Name of the Phone: ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, phone);
	cout << "Processor: ";
	getline(cin, soc1);
	soc.append(soc1.append("\n"));
	cout << "RAM: ";
	cin >> ram1;
	ram.append(ram1.append("\n"));
	cout << "Battery: ";
	cin >> bat1;
	bat.append(bat1.append("\n"));
	cout << "Screen size: ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(cin, ss1);
	ss.append(ss1.append("\n"));
	cout << "MegaPixel: ";
	cin >> mp1;
	mp.append(mp1.append("\n"));
	cout << "Price: ";
	cin >> price1;
	price.append(price1.append("\n"));
	writeToFile(brandfile, phone, "", "", "", "", "", "", "");
	writeToFile(phonefile, phone.append("\n"), soc, ram, bat, ss, mp, price, "x");
	writeToFile(allphones, phone, soc, ram, bat, ss, mp, price, "x");
}

void deletePhone(string search, string phonefile, string brandfile) {
	string showPhone = " ", end = "x";
	int isFound = 0;

	ifstream phoneIn, brandIn, allIn;
	ofstream temp1, temp2, temp3;

	char phone[20], brand[20];
	strcpy(phone, phonefile.c_str());
	strcpy(brand, brandfile.c_str());

	allIn.open("allphones.txt");
	phoneIn.open(phone);
	brandIn.open(brand);

	temp3.open("temp3.txt", ios::app);

	while (!allIn.eof()) {
		getline(allIn, showPhone);
		if (showPhone == search)
			isFound = 1;
		if (showPhone == end && isFound == 1)
			isFound = 0;
		if (isFound == 0)
			temp3 << showPhone << "\n";
	}
	allIn.close();
	temp3.close();
	remove("allphones.txt");
	if (rename("temp3.txt", "allphones.txt") == 0)
		cout << "\n";

	temp2.open("temp2.txt", ios::app);
	isFound = 0;
	while (!phoneIn.eof()) {
		getline(phoneIn, showPhone);
		if (showPhone == search)
			isFound = 1;
		if (showPhone == end && isFound == 1)
			isFound = 0;
		if (isFound == 0)
			temp2 << showPhone << "\n";
	}
	phoneIn.close();
	temp2.close();
	remove(phone);
	if (rename("temp2.txt", phone) == 0)
		cout << "\n";

	temp1.open("temp1.txt", ios::app);
	isFound = 0;
	while (!brandIn.eof()) {
		getline(brandIn, showPhone);
		if (showPhone == search) {
			isFound = 1;
		}
		else
			isFound = 0;
		if (isFound == 0) {
			temp1 << showPhone << "\n";
		}
	}
	brandIn.close();
	temp1.close();
	remove(brand);
	if (rename("temp1.txt", brand) == 0)
		cout << "\n";
}

void modPrice(string search, string phonefile) {
	string showPhone = " ", price = "Price:", newP;
	int isFound = 0;
	ifstream phoneIn, allIn;
	ofstream temp1, temp2;

	temp1.open("temp1.txt", ios::out);
	allIn.open("allphones.txt");

	char phone[20];
	strcpy(phone, phonefile.c_str());

	while (!allIn.eof()) {
		getline(allIn, showPhone);
		if (showPhone == search)
			isFound = 1;
		if (isFound == 1) {
			for (int i = 0; i < price.size(); i++) {
				if (showPhone[i] == price[i])
					isFound = 2;
				else {
					isFound = 1;
					break;
				}
			}
		}
		if (isFound != 2)
			temp1 << showPhone << "\n";
		else
		{
			cout << "\nEnter new price:";
			cin >> newP;
			temp1 << "Price: " << newP << "\n";
			isFound = 0;
		}
	}

	temp1.close();
	allIn.close();
	if (remove("allphones.txt") == 0);
	cout << "\n";
	if (rename("temp1.txt", "allphones.txt") == 0)
		cout << "\n";

	isFound = 0;
	phoneIn.open(phone, ios::out);
	temp2.open("temp2.txt", ios::out);

	while (!phoneIn.eof()) {
		getline(phoneIn, showPhone);
		if (showPhone == search)
			isFound = 1;
		if (isFound == 1) {
			for (int i = 0; i < price.size(); i++) {
				if (showPhone[i] == price[i])
					isFound = 2;
				else {
					isFound = 1;
					break;
				}
			}
		}
		if (isFound != 2)
			temp2 << showPhone << "\n";
		else {
			temp2 << "Price:" << newP << "\n";
			isFound = 0;
		}
	}

	temp2.close();
	phoneIn.close();
	if (remove(phone) == 0);
	cout << "\n";
	if (rename("temp2.txt", phone) == 0)
		cout << "\n";
}

int main() {
	int ch, flag = 0, pass, chk = 0;
	char yesOrNo;
	string adorus;
	cout << "\nEnter username: ";
	cin >> adorus;
	if (adorus == "admin") {
		do {
			cout << "\nEnter password:";
			chk = passCheck();
		} while (chk != 1);
	}
	do { 
		if (chk == 1) {
			cout << "\nSelect 1 or 2: \n1)Search by name \n2)Search by brand \n3)Add Phone \n4)Delete Phone \n5)Modify Price" << endl;
			cin >> ch;
		}
		else {
			if (adorus == "user") {
				cout << "\nSelect 1 or 2: \n1)Search by name \n2)Search by brand" << endl;
				cin >> ch;
				if (ch > 2) {
					cout << "\nWorng choice! Please choose between 1 and 2";
					return 0;
				}
			}
		}
		switch (ch) {
		case 1:
		{
			string search;
			cout << "Enter the name of the phone: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, search);
			searchPhone(search, "allphones.txt", false);
			break;
		}
		case 2:
		{
			int brand;
			cout << "\nChoose from one of the brands listed below. \n1) Apple \n2) Google \n3) OnePlus \n4) Redmi \n5) Samsung" << endl;
			cin >> brand;
			switch (brand) {
			case 1:
			{
				cout << "\nChoose one option:" << endl;
				ifstream appleIn;
				string showApple = " ";
				appleIn.open("apple.txt");
				int count = 0;
				while (!appleIn.eof()) {
					getline(appleIn, showApple);
					count++;
					cout << "\n" << count << ") ";
					for (int i = 0; i < showApple.size(); i++)
						cout << showApple[i];
				}
				appleIn.close();
				int phone; cin >> phone;
				switch (phone) {
				case 1:	searchPhone("iPhone 11 Pro Max", "iPhone.txt", true);
					break;
				case 2: searchPhone("iPhone 11 Pro", "iPhone.txt", true);
					break;
				case 3: searchPhone("iPhone 11", "iPhone.txt", true);
					break;
				case 4: searchPhone("iPhone XR", "iPhone.txt", true);
					break;
				case 5: searchPhone("iPhone X", "iPhone.txt", true);
					break;
				default: cout << "\nWorng Choice!";
					break;
				}
				break;
			}
			case 2:
			{
				cout << "\nChoose one option:" << endl;
				ifstream googleIn;
				string showGoogle = " ";
				googleIn.open("pixel.txt");
				int count = 0;
				while (!googleIn.eof()) {
					getline(googleIn, showGoogle);
					count++;
					cout << "\n" << count << ") ";
					for (int i = 0; i < showGoogle.size(); i++)
						cout << showGoogle[i];
				}
				googleIn.close();
				int phone; cin >> phone;
				switch (phone) {
				case 1: searchPhone("Pixel 4A", "pixelphone.txt", true);
					break;
				case 2: searchPhone("Pixel 4 XL", "pixelphone.txt", true);
					break;
				case 3: searchPhone("Pixel 4", "pixelphone.txt", true);
					break;
				case 4: searchPhone("Pixel 3A XL", "pixelphone.txt", true);
					break;
				case 5: searchPhone("Pixel 3A", "pixelphone.txt", true);
					break;
				default: cout << "\nWorng Choice!";

				}
				break;
			}
			case 3:
			{
				cout << "\nChoose one option:" << endl;
				ifstream opIn;
				string showOp = " ";
				opIn.open("oneplus.txt");
				int count = 0;
				while (!opIn.eof()) {
					getline(opIn, showOp);
					count++;
					cout << "\n" << count << ") ";
					for (int i = 0; i < showOp.size(); i++)
						cout << showOp[i];
				}
				opIn.close();
				int phone; cin >> phone;
				switch (phone) {
				case 1: searchPhone("OnePlus 7", "oneplusphone.txt", true);
					break;
				case 2: searchPhone("OnePlus 7 Pro", "oneplusphone.txt", true);
					break;
				case 3: searchPhone("OnePlus 8", "oneplusphone.txt", true);
					break;
				case 4: searchPhone("OnePlus 8 Pro", "oneplusphone.txt", true);
					break;
				case 5: searchPhone("OnePlus Nord", "oneplusphone.txt", true);
					break;
				default: cout << "\nWorng Choice!";
				}
				break;
			}
			case 4:
			{
				cout << "\nChoose one option:" << endl;
				ifstream redmiIn;
				string showRedmi = " ";
				redmiIn.open("redmi.txt");
				int count = 0;
				while (!redmiIn.eof()) {
					getline(redmiIn, showRedmi);
					count++;
					cout << "\n" << count << ") ";
					for (int i = 0; i < showRedmi.size(); i++)
						cout << showRedmi[i];
				}
				redmiIn.close();
				cout << "\n";
				int phone; cin >> phone;
				switch (phone) {
				case 1: searchPhone("Redmi 9", "redmiphone.txt", true);
					break;
				case 2: searchPhone("Redmi 9A", "redmiphone.txt", true);
					break;
				case 3: searchPhone("Redmi Note 9", "redmiphone.txt", true);
					break;
				case 4: searchPhone("Redmi Note 9 Pro", "redmiphone.txt", true);
					break;
				case 5: searchPhone("Redmi Note 9 Pro Max", "redmiphone.txt", true);
					break;
				default: cout << "\nWorng Choice!";
				}
				break;
			}
			case 5:
			{
				cout << "\nChoose one option:" << endl;
				ifstream samIn;
				string showSam = " ";
				samIn.open("samsung.txt");
				int count = 0;
				while (!samIn.eof()) {
					getline(samIn, showSam);
					count++;
					cout << "\n" << count << ") ";
					for (int i = 0; i < showSam.size(); i++)
						cout << showSam[i];
				}
				samIn.close();
				cout << "\n";
				int phone; cin >> phone;
				switch (phone) {
				case 1: searchPhone("Samsung Galaxy S20", "samsungphone.txt", true);
					break;
				case 2: searchPhone("Samsung Galaxy S20+", "samsungphone.txt", true);
					break;
				case 3: searchPhone("Samsung Galaxy Z Fold 2", "samsungphone.txt", true);
					break;
				case 4: searchPhone("Samsung Galaxy M21", "samsungphone.txt", true);
					break;
				case 5: searchPhone("Samsung Galaxy A31", "samsungphone.txt", true);
					break;
				default: cout << "\nWorng Choice!";
				}
				break;
			}
			break;
			default: cout << "\nWrong choice.";
				break;
			}
		}
		break;
		case 3:
		{
			int phone;
			cout << "\nWhich brand does the phone belong to?\n1) Apple \n2) Google \n3) OnePlus \n4) Redmi \n5) Smasung" << endl;
			cin >> phone;
			switch (phone)
			{
			case 1: addPhone("allphones.txt", "iPhone.txt", "apple.txt");
				break;
			case 2: addPhone("allphones.txt", "pixelphone.txt", "pixel.txt");
				break;
			case 3: addPhone("allphones.txt", "oneplusphone.txt", "oneplus.txt");
				break;
			case 4: addPhone("allphones.txt", "redmiphone.txt", "redmi.txt");
				break;
			case 5: addPhone("allphones.txt", "samsungphone.txt", "samsung.txt");
				break;
			default: cout << "\nWrong Choice!";
			}
			break;
		}
		case 4:
		{
			string st_del, phonefile, brandfile;
			char ch;
			cout << "\nEnter the name of the phone you want to delete: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, st_del);
			for (int i = 0; i <= 0; i++) {
				if (st_del[i] == 'i') {
					phonefile = "iPhone.txt";
					brandfile = "apple.txt";
				}
				else if (st_del[i] == 'P') {
					phonefile == "pixelphone.txt";
					brandfile = "pixel.txt";
				}
				else if (st_del[i] == 'O') {
					phonefile = "oneplusphone.txt";
					brandfile = "oneplus.txt";
				}
				else if (st_del[i] == 'R') {
					phonefile = "redmiphone.txt";
					brandfile = "redmi.txt";
				}
				else if (st_del[i] == 'S') {
					phonefile = "samsungphone.txt";
					brandfile = "samsung.txt";
				}
				cout << "\nAre you sure you want to delete this phone record?(y,n): ";
				cin >> ch;
				if (ch == 'Y' || ch == 'y') {
					deletePhone(st_del, phonefile, brandfile);
					cout << "\nPhone deleted successfully!";
					break;
				}
				else {
					return 0;
				}
			}
			break;
		}
		case 5:
		{
			string name, phonefile;
			cout << "\nEnter the name of the phone you want to update: ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			getline(cin, name);
			searchPhone(name, "allphones.txt", false);
			for (int i = 0; i < 5; i++) {
				if (name[i] == 'i')
					phonefile = "iPhone.txt";
				else if (name[i] == 'P')
					phonefile == "pixelphone.txt";
				else if (name[i] == 'O')
					phonefile = "oneplusphone.txt";
				else if (name[i] == 'R')
					phonefile = "redmiphone.txt";
				else if (name[i] == 'S')
					phonefile = "samsungphone.txt";
			}
			modPrice(name, phonefile);
			cout << "\nThe price has been updated successfully." << endl;
			searchPhone(name, "allphones.txt", false);
			break;
		}
		default: cout << "\nWrong Choice!";
		}
		cout<<"Do you want to continue? (y/n)";
		cin>>yesOrNo;
	}while(yesOrNo == 'y' || yesOrNo == 'Y');
	return 0;
}