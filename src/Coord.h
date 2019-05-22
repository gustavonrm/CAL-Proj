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
	double lat,lon;
	int x,y; //int bc graph only process int
	string tag;

public:
	Coord();
	Coord(int id);
	Coord(int id,double lat, double lon);
	Coord(int id,double lat, double lon,int x, int y);
	int getId();
	double getLat();
	double getLon();
	int getX();
	int getY();
	string getTag();
	void setId(int id);
	void setLat(double lat);
	void setLon(double lon);
	void setX(int x);
	void setY(int y);
	void setTag(string tag);

	bool operator == (const Coord &c) const;

};

#endif /* COORD_H_ */
