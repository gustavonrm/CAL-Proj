/*
 * Item.cpp
 *
 *  Created on: 20/05/2019
 *      Author: gustavo
 */

#include "item.h"

Item::Item(pair<double,double> adress,double weight,double volume){
	this->adress=adress;
	this->weight=weight;
	this->volume=volume;
}

double Item::getLat(){
	return this->adress.first;
}

double Item::getLon(){
	return this->adress.second;
}
