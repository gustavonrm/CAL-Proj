/*
 * Company.h
 *
 *  Created on: 21/05/2019
 *      Author: gustavo
 */

#ifndef COMPANY_H_
#define COMPANY_H_


#include <iostream>
#include<string>
#include <vector>

#include "Map.h"
#include "Truck.h"
#include "Item.h"

using namespace std;

class Company {
private:
	Map main_map;
	vector<Truck> Trucks;
	vector<Item> items;
public:
	Company();
	void init(string mapFolder, string truckFile, string itemFile);
	void setMainMap(Map main_map);
	void drawMap();
};

#endif /* COMPANY_H_ */
