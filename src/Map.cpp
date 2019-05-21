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
	this->processNodes();
	this->processEdges();
	this->processGraph();
	//this->printGraph();
}

void Map::processFiles(){
	string cityName= this->folder;
	cityName.erase(0,4);
	this->edgesFile=folder+"/T04_edges_"+cityName+".txt";
	this->nodesLatLonFile=folder+"/T04_nodes_lat_lon_"+cityName+".txt";
	this->nodesXYFile=folder+"/T04_nodes_X_Y_"+cityName+".txt";
	this->tagsFile=folder+"/T04_tags_"+cityName+".txt";
}

void Map::processNodes(){
	ifstream fileLatLon,fileXY;
	string line1,line2;
	string nodes;
	fileLatLon.open(this->nodesLatLonFile);
	fileXY.open(this->nodesXYFile);
	if(fileLatLon.is_open() && fileXY.is_open() ){
		cout << "Processing nodes...\n";
		getline(fileLatLon,nodes);
		getline(fileXY,nodes);
		while(getline(fileLatLon,line1)){
			//read Lat Lon
			string id, lat, lon,x,y;
			line1.erase(0,1);
			id=line1.substr(0,line1.find(','));
			line1.erase(0,line1.find(',')+2);
			lat=line1.substr(0,line1.find(','));
			line1.erase(0,line1.find(',')+2);
			lon=line1.substr(0,line1.find(')'));
			line1.clear();
			//read XY
			getline(fileXY,line2);
			line2.erase(0,1);
			id=line2.substr(0,line1.find(','));
			line2.erase(0,line2.find(',')+2);
			x=line2.substr(0,line2.find(','));
			line2.erase(0,line2.find(',')+2);
			y=line2.substr(0,line2.find(')'));
			line2.clear();
			Coord c(stod(id),stod(lat),stod(lon),stoi(x),stoi(y));
			//cout<< "id: "<<c.getId()<< " lat: "<<c.getLat()<< " lon; " << c.getLon()<< " x: "<<c.getX()<< " y: "<<c.getY()<<endl;
			this->nodes.push_back(c);
		}
	}else{
		cout << "Error opening files!\n";
		exit(ERR_OP_NODES_LAT_LON_FILE);
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
	GraphViewer *gv = new GraphViewer(1920, 1080, false);
	gv->createWindow(1920, 1080);
	gv->defineVertexColor("black");
	gv->defineEdgeColor("red");
	//make a translation
	int minX=100000000, minY=100000000;
	for(auto n : this->graph.getVertexSet()){
		if(n->getInfo().getX()<minX){
			minX=n->getInfo().getX();
		}
		if(n->getInfo().getY()<minY){
				minY=n->getInfo().getY();
			}
	}
	//process vertex
	for(auto n : this->graph.getVertexSet()){
		gv->addNode(n->getInfo().getId(),n->getInfo().getX()-minX,n->getInfo().getY()-minY);
	}
	int eId=0;
	for(auto n : this->graph.getVertexSet()){
		for(auto e : n->getAdj()){
			gv->addEdge(eId,n->getInfo().getId(),e.getDest()->getInfo().getId(),EdgeType::DIRECTED);
			eId++;
		}
	}
	gv->rearrange();
	cout<<"Succefully drawn!\n";
	getchar();
}

void Map::printGraph(){
	for (auto n : this->graph.getVertexSet()){
		cout<<"id: "<<n->getInfo().getId();
		cout<<" lat: "<<n->getInfo().getLat();
		cout<<" lon: "<<n->getInfo().getLon();
		cout<<" x: "<<n->getInfo().getX();
		cout<<" y: "<<n->getInfo().getY()<<endl;
	}
}
