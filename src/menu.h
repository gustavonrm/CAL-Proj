/*
 * menu.h
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include<string>
#include <cstdlib>

#include "Map.h"
#include "Company.h"
using namespace std;

class Menu {
private:
	int option;
	string mapFolder, trucksFile, itemsFile;
	Company company;
public:
	Menu();
	//menu cicle and manipulation calling company methods
	bool menuManip();
	//output
	void drawMainMenu();
	//files handler
	void readFiles();
	void loadFiles();
	//input handler
	void readInput();

};

#endif /* MENU_H_ */
