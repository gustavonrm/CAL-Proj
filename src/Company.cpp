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
	this->items=loadItems(itemFile);
	//init origin
	for(int i=0; i < (int)this->main_map.getGraph().getVertexSet().size();i++){
		if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getTag() == "amenity=loading_dock"){
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
	vector<Coord> res;
	for(int i=0; i < this->main_map.getGraph().getVertexSet().size();i++){
		if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getId() == 1109149480){
			origin = this->main_map.getGraph().getVertexSet().at(i);
			break;
		}
	}
	this->main_map.getGraph().dijkstraShortestPath(origin->getInfo());
	cout<<"Processed dijkstra!\n";
	res = this->main_map.getGraph().getPath(origin->getInfo(), this->extraction_points.at(0)->getInfo());

		for( auto r : res ){
			cout<< r.getId()<<endl;
		}
		//stuff
		GraphViewer *gv = new GraphViewer(1920, 1080, false);
		gv->createWindow(1920, 1080);
		gv->defineVertexColor("black");
		gv->defineEdgeColor("red");
		gv->defineEdgeCurved(false);
		//make a translation
		int minX = 100000000, minY = 100000000;

		//make a translation
			for (auto n : this->main_map.getGraph().getVertexSet()) {
				if (n->getInfo().getX() < minX) {
					minX = n->getInfo().getX();
				}
				if (n->getInfo().getY() < minY) {
					minY = n->getInfo().getY();
				}
			}
			//process vertex
			for (auto n : this->main_map.getGraph().getVertexSet()) {
				gv->addNode(n->getInfo().getId(), n->getInfo().getX() - minX,n->getInfo().getY() - minY);
				if(!n->getInfo().getTag().empty()){
					gv->setVertexColor(n->getInfo().getId(),"pink");
				}
			}
			int eId = 0;
			for (auto n : this->main_map.getGraph().getVertexSet()) {
				for (auto e : n->getAdj()) {
					gv->addEdge(eId, n->getInfo().getId(),
							e.getDest()->getInfo().getId(), EdgeType::DIRECTED);
					eId++;
				}
			}
		gv->rearrange();
		//process vertex
		for (auto n : res ) {
			gv->setVertexColor(n.getId(),"green");
			gv->addNode(n.getId(), n.getX() - minX,n.getY() - minY);
		}
		gv->rearrange();
		cout << "Succefully drawn!\n";
		getchar();


}
void Company::orderItems(){
	for(auto v : this->main_map.getGraph().getVertexSet()){
		for( auto i : items){
			if(i.getLat()== v->getInfo().getLat() && i.getLon() == v->getInfo().getLon()){
				this->item_delivery.push_back(v);
			}
		}
	}

	this->main_map.getGraph().closestNeighbour(item_delivery,origin);
	cout<<"Printing res\n";
	for(auto p : item_delivery){
		cout << p->getInfo().getId()<<endl;
	}
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

