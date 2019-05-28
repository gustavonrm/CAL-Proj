/*
 * utils.h
 *
 *  Created on: 21/05/2019
 *      Author: gustavo
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include  <vector>
#include <cstdlib>
#include <utility>

#include "Truck.h"
#include "Item.h"
#include "types.h"

using namespace std;

//load truck files
vector<Truck> loadTrucks(string truckFile);
//load item files
vector<Item> loadItems(string itemFile);

#endif /* UTILS_H_ */
