/*
 * Coord.h
 *
 *  Created on: 19/05/2019
 *      Author: gustavo
 */

#ifndef COORD_H_
#define COORD_H_

#include <iostream>
#include<string>

using namespace std;

class Coord {
private:
	int lat,lon,x,y;
public:
	Coord();
	Coord(int lat, int lon);
	Coord(int lat, int lon,int x, int y);

};

#endif /* COORD_H_ */
