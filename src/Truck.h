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
	vector<Vertex<Coord>*> item_delivery; //this is the one mainly used, bc items, wasnt that powerfull
	vector<Item> items; //structure to save items
	double maxWeight;
	double maxVolume;
	double currentWeight;
	double currentVolume;
public:
	Truck(double maxWeight,double maxVolume);
	//selfexplanaory
	void setItems(vector<Item> items);
	//set nem item to delivery vector
	void setItemDelivery(	vector<Vertex<Coord>*> item_delivery);
	//add item_delivery to the main vector
	void addTruckItemDelivery(Vertex<Coord>*item_delivery);
	//used to debug to see items to deliver
	vector<Vertex<Coord>*> getItemDelivery();
	//set item updating current volume and weight for item distribuition
	void addItem(Item item);
	//selfexplanatory
	double getCurrentWeight();
	//selfexplanatory
	double getCurrentVolume();
};

#endif /* TRUCK_H_ */
