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
	pair<int,int> adress;
	double weight;
	double volume;
public:
	Item(pair<int,int> adress,double weight,double volume);
	int getX();
	int getY();
};

#endif /* ITEM_H_ */
