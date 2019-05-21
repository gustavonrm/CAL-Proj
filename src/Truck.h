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

#include "Item.h"

using namespace std;

class Truck {
private:
	vector<Item> items;
	double maxWeight;
	double maxVolume;
public:
	Truck(double maxWeight,double maxVolume);
	void setItems(vector<Item> items);
	void addItem(Item item);
};

#endif /* TRUCK_H_ */
