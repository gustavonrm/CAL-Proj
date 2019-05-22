/*
 * Coord.cpp
 *
 *  Created on: 19/05/2019
 *      Author: gustavo
 */


#include "Coord.h"

Coord::Coord(){
	this->id=0;
}
Coord::Coord(int id){
this->id=id;
}
Coord::Coord(int id,double lat, double lon){
	this->id=id;
	this->lat=lat;
	this->lon=lon;
}
Coord::Coord(int id,double lat, double lon,int x, int y){
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
int Coord::getX(){
	return this->x;
}
int Coord::getY(){
	return this->y;
}
string Coord::getTag(){
	return this->tag;
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
void Coord::setX(int x){
	this->x=x;
}
void Coord::setY(int y){
	this->y=y;
}
void Coord::setTag(string tag){
	this->tag.assign(tag);
}
bool Coord::operator == (const Coord &c) const{
	return(id ==c.id && lat == c.lat && lon == c.lon && x == c.x && y == c.y);
}
