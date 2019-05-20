/*
 * map.h
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

#include "graph.h"
#include "Coord.h"
#include "graphviewer.h"

using namespace std;

class Map {
private:
	vector<pair<int,int>> edges;
	vector<Coord> nodes;
	Graph<Coord> graph;
	string folder;
	string edgesFile, nodesLatLonFile, nodesXYFile, tagsFile;
public:
	Map();
	void setFolder(string folder);
	int loadMap();
	void processFiles();
	void processNodesLatLon();
	void processNodesXY();
	void processEdges();
	void processGraph();
	void drawGraph();
	//TODO algorithm to look for edges
};

#endif /* MAP_H_ */
