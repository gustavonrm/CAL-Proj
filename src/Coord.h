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
	int id;
	double lat,lon,x,y;
public:
	Coord();
	Coord(int id);
	Coord(int id,double lat, double lon);
	Coord(int id,double lat, double lon,double x, double y);
	int getId();
	double getLat();
	double getLon();
	double getX();
	double getY();
	void setId(int id);
	void setLat(double lat);
	void setLon(double lon);
	void setX(double x);
	void setY(double y);

	bool operator == (const Coord &c) const;
	Coord& operator = (const Coord &c)const;


};

#endif /* COORD_H_ */
