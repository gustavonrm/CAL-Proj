/*
 * Item.h
 *
 *  Created on: 20/05/2019
 *      Author: gustavo
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <iostream>
#include<string>
#include<utility>

using namespace std;

class Item {
private:
	pair<double,double> adress;
	double weight;
	double volume;
public:
	Item(pair<double,double> adress,double weight,double volume);
	double getLat();
	double getLon();

};

#endif /* ITEM_H_ */
