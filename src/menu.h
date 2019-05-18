/*
 * menu.h
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <iomanip>
#include<string>

using namespace std;

class Menu {
private:
	int option;
	string mapFile, trucksFile, itemsFile;
public:
	void menu(){};
	bool menuManip();
	void drawMainMenu();
	void readInput();

};

#endif /* MENU_H_ */
