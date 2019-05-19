/*
 * map.h
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <string>

#include "graph.h"
#include "Coord.h"

using namespace std;

class Map {
private:
	Graph<Coord> graph;
	string folder;
	string edgesFile, nodesLatLonFile, nodesXYFile, tagsFile;
public:
	Map();
	void setFolder(string folder);
	int loadMap();
	void processFiles();
};

#endif /* MAP_H_ */
