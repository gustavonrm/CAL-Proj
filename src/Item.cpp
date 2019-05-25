/*
 * Item.cpp
 *
 *  Created on: 20/05/2019
 *      Author: gustavo
 */

#include "item.h"

Item::Item(pair<int,int> adress,double weight,double volume){
	this->adress=adress;
	this->weight=weight;
	this->volume=volume;
}

int Item::getX(){
	return this->adress.first;
}

int Item::getY(){
	return this->adress.second;
}

