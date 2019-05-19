/*
 * map.cpp
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#include "Map.h"

Map::Map(){

}
void Map::setFolder(string folder){
	this->folder=folder;
}
int Map::loadMap(){
	this->processFiles();
	//processGraph
}

void Map::processFiles(){
	string cityName= this->folder;
	cityName.erase(0,4);
	this->edgesFile=folder+"/T04_edges_"+cityName+".txt";
	this->nodesLatLonFile=folder+"/T04_nodes_lat_lon_"+cityName+".txt";
	this->nodesXYFile=folder+"/T04_nodes_X_Y_"+cityName+".txt";
	this->tagsFile=folder+"/T04_tags_"+cityName+".txt";
}

