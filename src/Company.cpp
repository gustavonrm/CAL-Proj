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
	//this->Trucks= loadTrucks(truckFile); //TODO uncomment
	//this->items=loadItems(itemFile);
	//init origin
	for(int i=0; i < (int)this->main_map.getGraph().getVertexSet().size();i++){
		if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getTag() == "amenity=loading_dock"){
			this->origin = this->main_map.getGraph().getVertexSet().at(i)->getInfo();
			break;
		}
	}
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
	Vertex<Coord> *o;
	vector<Coord> res;
	for(int i=0; i < this->main_map.getGraph().getVertexSet().size();i++){
		if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getTag() == "amenity=loading_dock"){
			o = this->main_map.getGraph().getVertexSet().at(i);
			break;
		}
	}
	this->main_map.getGraph().dijkstraShortestPath(o->getInfo());
	cout<<"Processed dijkstra!\n";
	res = this->main_map.getGraph().getPath(o->getInfo(), this->extraction_points.at(0)->getInfo());

		for( auto r : res ){
			cout<< r.getId()<<endl;
		}
		//stuff
		GraphViewer *gv = new GraphViewer(1920, 1080, false);
		gv->createWindow(1920, 1080);
		gv->defineVertexColor("black");
		gv->defineEdgeColor("red");
		//make a translation
		int minX = 100000000, minY = 100000000;
		for (auto n : res) {
			if (n.getX() < minX) {
				minX = n.getX();
			}
			if (n.getY() < minY) {
				minY = n.getY();
			}
		}
		//process vertex
		for (auto n : res ) {
			gv->addNode(n.getId(), n.getX() - minX,n.getY() - minY);
		}
		gv->rearrange();
		cout << "Succefully drawn!\n";
		getchar();


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
					<< " || Lat: "<<v->getInfo().getLat()<< "Lon: "<<v->getInfo().getLon()<<endl;
		}
	}
	//TODO control erros in case bad typing and id not matching, and repeting a node
	cout<<"Insert id -> ";
	cin>>id;
	idnr=stoi(id);
	for(auto v : this->main_map.getGraph().getVertexSet()){
			if(idnr == v->getInfo().getId()){
				this->extraction_points.push_back(v);
				break;
			}
		}
	cout<< "\n=====Extration points available=====\n";
	for(auto p : this->extraction_points){
		cout<<p->getInfo().getTag() <<" ID: "<<p->getInfo().getId()<<endl;
	}
	cout<<endl;
}
void Company::reset(){
	this->main_map.loadMap();
	this->extraction_points.clear();
}

