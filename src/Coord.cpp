/*
 * Coord.cpp
 *
 *  Created on: 19/05/2019
 *      Author: gustavo
 */


#include "Coord.h"

Coord::Coord(){}
Coord::Coord(int lat, int lon){
	this->lat=lat;
	this->lon=lon;
}
Coord::Coord(int lat, int lon,int x, int y){
	this->lat=lat;
	this->lon=lon;
	this->x=x;
	this->y=y;
}

