/*
 * Coord.cpp
 *
 *  Created on: 19/05/2019
 *      Author: gustavo
 */


#include "Coord.h"

Coord::Coord(){}
Coord::Coord(int id){
this->id=id;
}
Coord::Coord(int id,double lat, double lon){
	this->id=id;
	this->lat=lat;
	this->lon=lon;
}
Coord::Coord(int id,double lat, double lon,double x, double y){
	this->id=id;
	this->lat=lat;
	this->lon=lon;
	this->x=x;
	this->y=y;
}
int Coord::getId(){
	return this->id;
}
double Coord::getLat(){
	return this->lat;
}
double Coord::getLon(){
	return this->lon;
}
double Coord::getX(){
	return this->x;
}
double Coord::getY(){
	return this->y;
}
void Coord::setId(int id){
	this->id=id;
}
void Coord::setLat(double lat){
	this->lat=lat;
}
void Coord::setLon(double lon){
	this->lon=lon;
}
void Coord::setX(double x){
	this->x=x;
}
void Coord::setY(double y){
	this->y=y;
}
bool Coord::operator == (const Coord &c) const{
	return(id ==c.id && lat == c.lat && lon == c.lon && x == c.x && y == c.y);
}
