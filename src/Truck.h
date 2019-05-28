/*
 * Truck.h
 *
 *  Created on: 20/05/2019
 *      Author: gustavo
 */

#ifndef TRUCK_H_
#define TRUCK_H_


#include <iostream>
#include<string>
#include <vector>

#include "graph.h"
#include "coord.h"
#include "Item.h"

using namespace std;

class Truck {
private:
	vector<Vertex<Coord>*> item_delivery;
	vector<Item> items;
	double maxWeight;
	double maxVolume;
	double currentWeight;
	double currentVolume;
public:
	Truck(double maxWeight,double maxVolume);
	void setItems(vector<Item> items);
	void setItemDelivery(	vector<Vertex<Coord>*> item_delivery);
	vector<Vertex<Coord>*> getItemDelivery();
	void addItem(Item item);
	double getCurrentWeight();
	double getCurrentVolume();
};

#endif /* TRUCK_H_ */
