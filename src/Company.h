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
#include "Utils.h"

using namespace std;

class Company {
private:
	Map main_map;
	Map modeling_map;
	vector<Truck> Trucks;
	vector<Item> items;
	vector<Vertex<Coord>*> extraction_points;
	Coord origin;
public:
	Company();
	void init(string mapFolder, string truckFile, string itemFile);
	void setMainMap(Map main_map);
	void processMap();
	void drawMap();
	void processRoute();
	void blockStreet();
	void addExtratingPoint();
	void reset();
};

#endif /* COMPANY_H_ */
