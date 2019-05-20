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
	this->processNodesLatLon();
	this->processNodesXY();
	this->processEdges();
	this->processGraph();
}

void Map::processFiles(){
	string cityName= this->folder;
	cityName.erase(0,4);
	this->edgesFile=folder+"/T04_edges_"+cityName+".txt";
	this->nodesLatLonFile=folder+"/T04_nodes_lat_lon_"+cityName+".txt";
	this->nodesXYFile=folder+"/T04_nodes_X_Y_"+cityName+".txt";
	this->tagsFile=folder+"/T04_tags_"+cityName+".txt";
}

void Map::processNodesLatLon(){
	ifstream file;
	string line;
	string nodes;
	file.open(this->nodesLatLonFile);
	if(file.is_open()){
		cout << "Processing nodes(lat,lon)...\n";
		getline(file,nodes);
		while(getline(file,line)){
			//read values
			string id, lat, lon;
			line.erase(0,1);
			id=line.substr(0,line.find(','));
			line.erase(0,line.find(',')+2);
			lat=line.substr(0,line.find(','));
			line.erase(0,line.find(',')+2);
			lon=line.substr(0,line.find(')'));
			line.clear();
			Coord c(stod(id),stod(lat),stod(lon));
			this->nodes.push_back(c);
		}
	}else{
		cout << "Error opening files!\n";
		exit(ERR_OP_NODES_LAT_LON_FILE);
	}
}
void Map::processNodesXY(){
	ifstream file;
	string line;
	string nodes;
	file.open(this->nodesXYFile);
	if(file.is_open()){
		cout << "Processing nodes(x,y)...\n";
		getline(file,nodes);
		while(getline(file,line)){
			//read values
			string id, x, y;
			line.erase(0,1);
			id=line.substr(0,line.find(','));
			line.erase(0,line.find(',')+2);
			x=line.substr(0,line.find(','));
			line.erase(0,line.find(',')+2);
			y=line.substr(0,line.find(')'));
			line.clear();
			for(auto v : this->nodes){
				if(stoi(id) == v.getId()){ //TODO use another algo to imprvs search
					v.setX(stod(x));
					v.setY(stod(y));
					break;
				}
			}
		}
	}else{
		cout << "Error opening files!\n";
		exit(ERR_OP_NODES_X_Y_FILE);
	}
}

void Map::processEdges(){
	ifstream file;
	string line;
	string edges;
	file.open(this->edgesFile);
	if(file.is_open()){
		cout << "Processing edges...\n";
		getline(file,edges);
		while(getline(file,line)){
			//read values
			string src, dest;
			line.erase(0,1);
			src=line.substr(0,line.find(','));
			line.erase(0,line.find(',')+2);
			dest=line.substr(0,line.find(')'));
			line.clear();
			pair<int,int> edge(stoi(src),stoi(dest));
			this->edges.push_back(edge);
			}
		}else{
			cout << "Error opening files!\n";
			exit(ERR_OP_EDGES_FILE);
		}
	}
void Map::processGraph(){
	cout << "Processing graphviewer...\n";
	for(auto v : this->nodes){
		this->graph.addVertex(v);
	}
	for(auto e : this->edges){
		int srcId = e.first;
		int destId = e.second;
		Coord src ;
		Coord dest;
		//TODO use binary search
		for(auto n : nodes){
			if(n.getId() == srcId){
				src=n;
			}
			if(n.getId() == destId){
				dest=n;
			}
			if(dest.getId() != 0 && src.getId() != 0 ){
				break;
			}
		}
		this->graph.addEdge(src,dest,0);
		//TODO check weight
	}
}
void Map::drawGraph(){
	GraphViewer *gv = new GraphViewer(1920, 1920, true);
	gv->createWindow(1920, 1080);
	gv->defineVertexColor("black");
	gv->defineEdgeColor("red");

	//process vertex
	for(auto n : this->graph.getVertexSet()){
		gv->addNode(n->getInfo().getId(),n->getInfo().getX(),n->getInfo().getY());
	}
	int eId=0;
	for(auto n : this->graph.getVertexSet()){
		for(auto e : n->getAdj()){
			gv->addEdge(eId,n->getInfo().getId(),e.getDest()->getInfo().getId(),EdgeType::UNDIRECTED);
			eId++;
		}
	}

	gv->rearrange();
	getchar();
}
