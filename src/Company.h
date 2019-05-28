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
	vector<int> blockedEdges;
	Map main_map;
	Map modeling_map;
	vector<Truck> Trucks;
	vector<Item> items;
	vector<Vertex<Coord>*> item_delivery;
	vector<Vertex<Coord>*> extraction_points;
	Vertex<Coord> *origin;
public:
	Company();
	//load company assets
	void init(string mapFolder, string truckFile, string itemFile);
	//set main graph to use
	void setMainMap(Map main_map);
	//read map
	void processMap();
	//draw map utility using graph viewr, mainly used to debug
	void drawMap();
	//process route usingshortestpath algorithms
	void processRoute();
	//oder items
	void orderItems();
	//distributeitemsto trucks
	void orderTrucks();
	//delete graph edges
	void blockStreet();
	//self explanatory
	void addExtratingPoint();
	//relload everything deleting routes blocked andextraction points
	Vertex<Coord>* findClosestExtractionPoint( Vertex<Coord>* origin);
	void reset();
};

#endif /* COMPANY_H_ */
