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

#include "Map.h"

using namespace std;

class Menu {
private:
	int option;
	string mapFolder, trucksFile, itemsFile;
	Map map;
public:
	Menu();
	bool menuManip();
	void drawMainMenu();
	void readFiles();
	void loadFiles();
	void readInput();

};

#endif /* MENU_H_ */