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
	//this->main_map.printGraph();
	this->Trucks= loadTrucks(truckFile);
	this->items=loadItems(itemFile);
}
void Company::setMainMap(Map main_map){
	this->main_map=main_map;
}
void Company::drawMap(){
	this->main_map.drawGraph();
}
/*
 * 1#   1 truck 1 item to deliver
 *  2#  1 truck multiple items
 *  3#  multiple trucks multiple items
 *  4#  multiple trucks multiple items considering volumes and sizes
 */
void Company::processRoute(){

}
void Company::blockStreet(){
//Todo destroy an edge basically
}
void Company::addExtratingPoint(){
	string id;
	int idnr;
	cout<<"========Points available========\n";
	for(auto v : this->main_map.getGraph().getVertexSet()){
		if (!v->getInfo().getTag().empty()){
			cout<< v->getInfo().getTag()<< " ID: "<<v->getInfo().getId()
					<< " Lat: "<<v->getInfo().getLat()<< "Lon: "<<v->getInfo().getLon()<<endl;
		}
	}
	//TODO control erros in case bad typing and id not matching, and repeting a node
	cout<<"Insert id -> ";
	cin>>id;
	idnr=stoi(id);
	for(auto v : this->main_map.getGraph().getVertexSet()){
			if(idnr == v->getInfo().getId()){
				this->extractation_points.push_back(v);
				break;
			}
		}
	cout<< "\n=====Extration points available=====\n";
	for(auto p : this->extractation_points){
		cout<<p->getInfo().getTag() <<" ID: "<<p->getInfo().getId()<<endl;
	}
	cout<<endl;
}
void Company::reset(){
	this->main_map.loadMap();
	this->extractation_points.clear();
}
