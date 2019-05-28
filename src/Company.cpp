/*
 * Company.cpp
 *
 *  Created on: 21/05/2019
 *      Author: gustavo
 */

#include "Company.h"
#include <iterator>

Company::Company(){

}
void Company::init(string mapFolder, string truckFile, string itemFile){
	this->main_map.setFolder(mapFolder);
	this->main_map.loadMap();
	this->Trucks= loadTrucks(truckFile);
	this->items=loadItems(itemFile);
	//init origin
	for(int i=0; i < (int)this->main_map.getGraph().getVertexSet().size();i++){
			if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getTag() == "amenity=loading_dock"){
				break;
			}
		}
		if( this->main_map.getGraph().isDAG()){
			cout<<"\nThis graph is Directed and acyclic!\n";
		}else
			cout<<"\nThis graph is not Directed and acyclic!\n";

}
void Company::setMainMap(Map main_map){
	this->main_map=main_map;
}
void Company::drawMap(){
	cout << "hey";
	this->main_map.drawGraph();
}
/*
 * 1#   1 truck 1 item to deliver
 *  2#  1 truck multiple items
 *  3#  multiple trucks multiple items
 *  4#  multiple trucks multiple items considering volumes and sizes
 */
void Company::processRoute(){ //TODO SELECIONAR O ALGORITMO A USA
	string colors [5] = {"CYAN", "ORANGE", "RED", "MAGENTA", "BLUE"};
	int c = 0;
	if(this->extraction_points.empty()){
		cout<<"Can't process a route without extraction points!\n";
		return;
	}


	int algo =0;
	cout << "Select an algorithm to use:\n";
	cout << "1 - Dijkstra\n";
	cout << "2 - Bidirectional Dijkstra\n";
	cout << "3 - A * \n";
	while(true){
		cout<< " -> ";
		cin>> algo;
		cout<< algo;
		if(algo > 1 || algo < 3){
			break;
		}
		cout<< algo;
	}
	cout << "Started processing...";



	vector<Vertex<Coord>*>::const_iterator it = item_delivery.begin();
	//item_delivery.insert(it,origin);
	vector<Vertex<Coord>*> res;

		//stuff
		GraphViewer *gv = new GraphViewer(1920, 1080, false);
		gv->createWindow(1920, 1080);
		gv->defineVertexColor("LIGHT_GRAY");
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
					gv->setVertexLabel(n->getInfo().getId(),n->getInfo().getTag());
					gv->setVertexColor(n->getInfo().getId(),"pink");
				}
					else {
						gv->setVertexSize(n->getInfo().getId(),1);
						gv->setVertexLabel(n->getInfo().getId(), " ");
						}
				}



			for (auto n : this->main_map.getGraph().getVertexSet()) {
				for (auto e : n->getAdj()) {
					//gv->setEdgeLabel(e.eId, to_string(e.eId));
					gv->addEdge(e.eId, n->getInfo().getId(),
							e.getDest()->getInfo().getId(), EdgeType::DIRECTED);
				}
			}
		gv->rearrange();

		unsigned int j = 0;
		//Vertex<Coord>* final = item_delivery.back();

			vector<Truck>::iterator itK;
			for(itK = Trucks.begin(); itK!= Trucks.end(); itK++)
			{
					for(unsigned int i=0; i < this->main_map.getGraph().getVertexSet().size();i++){
						if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getId() == 1109149480){
							origin = this->main_map.getGraph().getVertexSet().at(i);
							break;
						}
					}

					if(itK->getItems().size() == 0)
					{
						continue;
					}
		//cout<<endl << item_delivery.size()<<endl;

		itK->getItemDelivery().push_back(findClosestExtractionPoint(itK->getItemDelivery().back()));
		//cout<<endl << item_delivery.size()<<endl;
		gv->setVertexColor(itK->getItemDelivery().back()->getInfo().getId(), "yellow");
		gv->rearrange();
		while( j < itK->getItemDelivery().size())
				{
					switch(algo){
					case 1:
						this->main_map.getGraph().dijkstraShortestPath(origin->getInfo());
						cout<<"Processed dijkstra!\n";
						res = this->main_map.getGraph().getPath(origin->getInfo(), itK->getItemDelivery().at(j)->getInfo());
						break;
					case 2:
					{
						this->main_map.getGraph().dijkstraBidirectionalPath(origin->getInfo(),itK->getItemDelivery().at(j)->getInfo());
						cout<<"Processed bidirectional dijkstra!\n";
						vector<Vertex<Coord>*> res1;
						res = this->main_map.getGraph().getPath1(origin->getInfo(), itK->getItemDelivery().at(j)->getInfo());
						res1 = this->main_map.getGraph().getPath1(origin->getInfo(),itK->getItemDelivery().at(j)->getInfo());
						res.insert(res.end(),res1.begin(),res1.end());
						break;
					}
					case 3:
						cout<<"not implemented\n";
						return;
						break;
					}

					const int size = res.size();
					if(size==0)
						{	j++;
							continue;
						}
					//process vertex
					vector<Vertex<Coord>*>::iterator n;
					for (n = res.begin(); n!= res.end(); n++)  {
						gv->setVertexColor((*n)->getInfo().getId(),"green");
						for( unsigned int i = 0; i < (*n)->getAdj().size(); i++)
						{
							if(*next(n,1) != NULL)
							{
								if ((*next(n,1))->getInfo().getId() == (*n)->getAdj().at(i).getDest()->getInfo().getId())
								{
									if((*n)->getAdj().at(i).getDest()->getInfo().getId() == (*next(n,1))->getInfo().getId())
									{

										cout << "HELLO";
										gv->setEdgeColor((*n)->getAdj().at(i).eId, colors[c]);
										gv->setEdgeThickness((*n)->getAdj().at(i).eId, 3);}
										gv->rearrange();
										c++;
										if(c==5)
										{
											c= 0;
										}

								}
							}
						}
						//gv->addNode((*n)->getInfo().getId(), (*n)->getInfo().getX() - minX,(*n)->getInfo().getY() - minY);
					}
					gv->setVertexColor(origin->getInfo().getId(), "black");
					gv->rearrange();

					//gv->setVertexLabel(origin->getInfo().getId(), "Hello");
					origin = itK->getItemDelivery().at(j);
					cout<<endl << itK->getItemDelivery().size()<<endl;
					cout << j << endl;
					j++;
				}



		gv->rearrange();
		for (auto n : this->main_map.getGraph().getVertexSet()) {
						for (auto e : n->getAdj()) {
							for(unsigned int i = 0; i<blockedEdges.size(); i++){
								if(e.eId == blockedEdges[i]){
									gv->setEdgeLabel(e.eId,"blocked");
								}
							}
						}
					}
		gv->rearrange();
		cout << "Succefully drawn!\n";
		getchar();
			}
}
void Company::orderItems(){
	vector<Vertex<Coord>*> res;
	vector<Truck>::iterator itT;
for(itT = Trucks.begin(); itT!= Trucks.end(); itT++)
{
	for(auto v : this->main_map.getGraph().getVertexSet()){
		for( auto i : itT->getItems()){
			if(i.getX()== v->getInfo().getX() && i.getY() == v->getInfo().getY()){
				this->item_delivery.push_back(v);
				cout << v->getInfo().getId();
			}
		}
	}

	for(unsigned int i=0; i < this->main_map.getGraph().getVertexSet().size();i++){
			if(this->main_map.getGraph().getVertexSet().at(i)->getInfo().getId() == 1109149480){
				origin = this->main_map.getGraph().getVertexSet().at(i);
				break;
			}
		}
	vector< pair<double,Vertex<Coord>*> > distances;
	double distance;
	double deltaX, deltaY;

	vector<Vertex<Coord>*>::iterator it;
	for(it = itT->getItemDelivery().begin(); it !=itT->getItemDelivery().end();it++)
	{
		 deltaX = origin->getInfo().getX() - (*it)->getInfo().getX();
		 deltaY = origin->getInfo().getY() - (*it)->getInfo().getY();
		 distance = sqrt(pow(deltaX,2) + pow(deltaY,2));
		 cout << endl << distance << endl;

		distances.push_back(make_pair(distance, *it));
	}
	sort(distances.begin(), distances.end());

	cout<<"Printing res\n";
	for(auto p : item_delivery){
		cout << p->getInfo().getX()<<endl;
	}
	cout << endl << endl << "printing sorted"<< endl;
	for(auto p : distances){
			cout << p.second->getInfo().getX()<<endl;
		}

	vector<Vertex<Coord>*> itemDelivery;
	itemDelivery.clear();

		vector< pair<double,Vertex<Coord>*> >::iterator it2;
		for(it2 = distances.begin(); it2 !=distances.end();it2++)
		{
			itemDelivery.push_back((*it2).second);
		}
		cout<<endl << itemDelivery.size()<<endl;
		itT->setItemDelivery(itemDelivery);
	}
}
Vertex<Coord>* Company::findClosestExtractionPoint(Vertex<Coord>* origin)
{
	double deltaX, deltaY, distance, tempdistance;
	Vertex<Coord>* closest;
	for(unsigned int i = 0; i < extraction_points.size(); i++)
	{
		tempdistance = 0;
		 deltaX = origin->getInfo().getX() - extraction_points[i]->getInfo().getX();
		 deltaY = origin->getInfo().getY() - extraction_points[i]->getInfo().getY();
		 tempdistance = sqrt(pow(deltaX,2) + pow(deltaY,2));
		 if(i == 0)
			{
				closest = extraction_points[i];
				distance = tempdistance;
			}
		 if(tempdistance < distance)
		 {
			 closest = extraction_points[i];
			 distance = tempdistance;
		 }
	}
	cout << distance;
	return closest;
}
//TODO n ta A DAR
void Company::orderTrucks()
{
	vector<Truck>::iterator it;
	vector<Item>::iterator it2;
	for(it = Trucks.begin(); it != Trucks.end();it++)
	{
		for(it2 = items.begin(); it2 != items.end(); it2++)
		{
			if(it2->getVolume() < it->getCurrentVolume() && it2->getWeight() < it->getCurrentWeight())
			{
				it->addItem(*it2);
			}
			else
			{
				items.erase(items.begin(),prev(it2,1));
				break;
			}
		}
	}
}/*
void Company::orderTrucks(){
	unsigned index =0;
	bool flag = true;
	for (auto t : this->Trucks){
		if(index > item_delivery.size())
			break;
		flag=true;
		vector<Vertex<Coord>*> truck_item_delivery;
		while(flag){
		auto id  = item_delivery[index];
			for(auto i : items){
				if(i.getX()==id->getInfo().getX() && i.getY()==id->getInfo().getY() ){
					if(i.getWeight() < t.getCurrentWeight() && i.getVolume() < t.getCurrentVolume()){
						cout<<"\nxD\n";
						t.addItem(i);
						truck_item_delivery.push_back(id);
						index++;
					}else{
						flag = false;
						break;
					}
				}
			}
		}
		t.setItemDelivery(truck_item_delivery);
		truck_item_delivery.clear();
	}
	for(auto t : this->Trucks){
		cout<<"ola\n";
		for(auto i : t.getItemDelivery()){
			cout<<" :: " <<i->getInfo().getX();
		}
	}
}
*/
void Company::blockStreet(){
		int id;
		cout << "Insert id ->";
		cin >> id;

		if( id == 0 ||  id%2 == 0){ //is even
			blockedEdges.push_back(id);
			blockedEdges.push_back(id+1);
			this->main_map.getGraph().removeEdge(id);
			this->main_map.getGraph().removeEdge(id+1);
		}
		if( id%2 !=0){ //is odd
					blockedEdges.push_back(id-1);
					blockedEdges.push_back(id);
					this->main_map.getGraph().removeEdge(id-1);
					this->main_map.getGraph().removeEdge(id);
		}
}
void Company::addExtratingPoint(){
	string id;
	int idnr;
	cout<<"========Points available========\n";
	for(auto v : this->main_map.getGraph().getVertexSet()){
		if (v->getInfo().getTag() =="amenity=loading_dock" ){
			cout<< v->getInfo().getTag()<< " ID: "<<v->getInfo().getId()
					<< " || Lat: "<<v->getInfo().getLat()<< "Lon: "<<v->getInfo().getLon()<<endl;
		}
	}
	//1346179432
	//4694
	//3396
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
	this->blockedEdges = {};
	this->extraction_points.clear();
}

