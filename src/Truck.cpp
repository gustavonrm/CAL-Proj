/*
 * Truck.cpp
 *
 *  Created on: 20/05/2019
 *      Author: gustavo
 */

#include "Truck.h"

Truck::Truck(double maxWeight,double maxVolume){
	this->maxWeight=maxWeight;
	this->maxVolume=maxVolume;
}
void Truck::setItems(vector<Item> items){
	this->items=items;
}
void Truck::addItem(Item item){
	this->items.push_back(item);
}

