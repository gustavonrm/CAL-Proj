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
	this->currentVolume = maxVolume;
	this->currentWeight = maxWeight;
}
void Truck::setItemDelivery(	vector<Vertex<Coord>*> item_delivery)
{
	this->item_delivery=item_delivery;
}
vector<Vertex<Coord>*> Truck::getItemDelivery(){
	return this->item_delivery;
}

void Truck::addItem(Item item){
	this->items.push_back(item);
	this->currentVolume -=item.getVolume();
	this->currentWeight -=item.getWeight();
}
double Truck::getCurrentWeight(){
	return  this->currentWeight;

}
double Truck::getCurrentVolume(){
	return this->currentVolume;
}

