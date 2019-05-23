/*
 * menu.cpp
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#include "Menu.h"

Menu::Menu() {
	this->option = 0;
	this->readFiles();
	this->company.init(this->mapFolder, this->trucksFile, this->itemsFile);
	this->menuManip();
}
bool Menu::menuManip() {
	while (true) {
		this->drawMainMenu();
		this->readInput();
		switch (this->option) {
		case 0:
			//this->company.processRoute();
			//this->company.drawMap();
			this->company.orderItems();
			break;
		case 1:
			break;
		case 2:
			this->company.addExtratingPoint();
			break;
		case 3:
			this->company.reset();
			break;
		case 4:
			return true;
			break;

		}
	}
}

void Menu::drawMainMenu() {
	cout << "================================================================"
			<< endl;
	cout << "          MAP: " << this->mapFolder << " | " << "TRUCKS: "
			<< this->trucksFile << " | " << "ITEMS: " << this->itemsFile
			<< endl;
	cout << "================================================================"
			<< endl;
	cout << "   0 - Process Route" << endl;
	cout << "   1 - Block Street" << endl;
	cout << "   2 - Create/Add extracting point" << endl;
	cout << "   3 - Reset" << endl;
	cout << "   4 - EXIT" << endl;
	cout << "================================================================"
			<< endl;
}

void Menu::readFiles() {
	cout << "Insert the map that you wish to read: ";
	cin >> this->mapFolder;
	cout << "Insert the trucks to make the transportation: ";
	cin >> this->trucksFile;
	cout << "Insert the items to deliver: ";
	cin >> this->itemsFile;
	cout << endl;

}

void Menu::readInput() {
	string input;
	cout << " -> ";
	cin >> input;
	cout << endl;
	this->option = stoi(input);
}

