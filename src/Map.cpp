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
	}
}
void Map::processNodesXY(){
	ifstream file;
	string line;
	string nodes;
	file.open(this->nodesXYFile);
	if(file.is_open()){
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
	}
}

void Map::processEdges(){
	ifstream file;
	string line;
	string edges;
	file.open(this->edgesFile);
	if(file.is_open()){
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
			cout<<src<<endl<<dest<<endl;
			}
		}
	}
void Map::processGraph(){
	for(auto v : this->nodes){
		this->graph.addVertex(v);
	}
	for(auto e : this->edges){
		int srcId = e.first;
		int destId = e.second;
		Vertex<Coord>* src , dest;
		int i=0;
		for(auto v : this->graph.getVertexSet()){
			if(v->getInfo().getId() == srcId){
				src=v;
				i++;
			}
			if(v->getInfo().getId() == destId){
				dest=v;
				i++;
			}
			if(i == 2){
				break;
			}
		}
		this->graph.addEdge(&src&,dest,0); //TODO check weight
	}
}
void drawGraph(){
	//TODO
}
