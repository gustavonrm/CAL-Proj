/*
 * Company.cpp
 *
 *  Created on: 21/05/2019
 *      Author: gustavo
 */

#include "Company.h"

Company::Company(){

}
void Company::init(string mapFolder, string truckFile, string itemFile){
	this->main_map.setFolder(mapFolder);
	this->main_map.loadMap();
}
void Company::setMainMap(Map main_map){
	this->main_map=main_map;
}
void Company::drawMap(){
	this->main_map.drawGraph();
}
