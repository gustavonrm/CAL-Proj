/*
 * Company.cpp
 *
 *  Created on: 21/05/2019
 *      Author: gustavo
 */

#include "Company.h"
#include <iterator>

Company::Company() {

}
void Company::init(string mapFolder, string truckFile, string itemFile) {
	this->main_map.setFolder(mapFolder);
	this->main_map.loadMap();
	this->Trucks = loadTrucks(truckFile);
	this->items = loadItems(itemFile);
	//init origin
	for (int i = 0; i < (int) this->main_map.getGraph().getVertexSet().size();
			i++) {
		if (this->main_map.getGraph().getVertexSet().at(i)->getInfo().getTag()
				== "amenity=loading_dock") {
			break;
		}
	}
	if (this->main_map.getGraph().isDAG()) {
		cout << "\nThis graph is Directed and acyclic!\n";
	} else
		cout << "\nThis graph is not Directed and acyclic!\n";

}
void Company::setMainMap(Map main_map) {
	this->main_map = main_map;
}
void Company::drawMap() {
	cout << "hey";
	this->main_map.drawGraph();
}
/*
 * 1#   1 truck 1 item to deliver
 *  2#  1 truck multiple items
 *  3#  multiple trucks multiple items
 *  4#  multiple trucks multiple items considering volumes and sizes
 */
void Company::processRoute() { //TODO SELECIONAR O ALGORITMO A USA

	if (this->extraction_points.empty()) {
		cout << "Can't process a route without extraction points!\n";
		return;
	}

	int algo = 0;
	cout << "Select an algorithm to use:\n";
	cout << "1 - Dijkstra\n";
	cout << "2 - Bidirectional Dijkstra\n";
	cout << "3 - A * \n";
	while (true) {
		cout << " -> ";
		cin >> algo;
		cout << algo;
		if (algo > 1 || algo < 3) {
			break;
		}
		cout << algo;
	}
	cout << "Started processing...";

	vector<Vertex<Coord>*> res;
	for (unsigned int i = 0;
			i < this->main_map.getGraph().getVertexSet().size(); i++) {
		if (this->main_map.getGraph().getVertexSet().at(i)->getInfo().getId()
				== 1109149480) {
			origin = this->main_map.getGraph().getVertexSet().at(i);
			break;
		}
	}

	for (auto r : res) {
		cout << r->getInfo().getId() << endl;
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
		gv->addNode(n->getInfo().getId(), n->getInfo().getX() - minX,
				n->getInfo().getY() - minY);
		if (!n->getInfo().getTag().empty()) {
			gv->setVertexLabel(n->getInfo().getId(), n->getInfo().getTag());
			gv->setVertexColor(n->getInfo().getId(), "pink");
		}
	}

	for (auto n : this->main_map.getGraph().getVertexSet()) {
		for (auto e : n->getAdj()) {
			gv->setEdgeLabel(e.eId, to_string(e.eId));
			gv->addEdge(e.eId, n->getInfo().getId(),
					e.getDest()->getInfo().getId(), EdgeType::DIRECTED);
		}
	}
	gv->rearrange();
	unsigned int j = 0;
	while (j < item_delivery.size()) {
		switch (algo) {
		case 1:
			this->main_map.getGraph().dijkstraShortestPath(origin->getInfo());
			cout << "Processed dijkstra!\n";
			res = this->main_map.getGraph().getPath(origin->getInfo(),
					item_delivery.at(j)->getInfo());
			break;
		case 2: {
			cout<< "Processing with errors\n";
			return;
			this->main_map.getGraph().dijkstraBidirectionalPath(
					origin->getInfo(), item_delivery.at(j)->getInfo());
			cout << "Processed bidirectional dijkstra!\n";
			vector<Vertex<Coord>*> res1;
			res = this->main_map.getGraph().getPath1(origin->getInfo(),
					item_delivery.at(j)->getInfo());
			res1 = this->main_map.getGraph().getPath2(
					item_delivery.at(j)->getInfo(), origin->getInfo());
			res.insert(res.end(), res1.begin(), res1.end());
			break;
		}
		case 3:
			cout << "not implemented\n";
			return;
			break;
		}

		//process vertex
		vector<Vertex<Coord>*>::iterator n;
		for (n = res.begin(); n != res.end(); n++) {
			gv->setVertexColor((*n)->getInfo().getId(), "green");
			for (unsigned int i = 0; i < (*n)->getAdj().size(); i++) {
				if (*next(n, 1) != NULL) {
					if ((*next(n, 1))->getInfo().getId()
							== (*n)->getAdj().at(i).getDest()->getInfo().getId()) {
						if ((*n)->getAdj().at(i).getDest()->getInfo().getId()
								== (*next(n, 1))->getInfo().getId()) {
							gv->setEdgeColor((*n)->getAdj().at(i).eId, "blue");
							gv->setEdgeThickness((*n)->getAdj().at(i).eId, 3);
						}
					}
				}
			}
			gv->addNode((*n)->getInfo().getId(), (*n)->getInfo().getX() - minX,
					(*n)->getInfo().getY() - minY);
		}
		gv->setVertexColor(origin->getInfo().getId(), "yellow");
		gv->setVertexLabel(origin->getInfo().getId(), "Hello");
		origin = item_delivery.at(j);
		j++;
	}

	gv->rearrange();
	for (auto n : this->main_map.getGraph().getVertexSet()) {
		for (auto e : n->getAdj()) {
			for (unsigned int i = 0; i < blockedEdges.size(); i++) {
				if (e.eId == blockedEdges[i]) {
					gv->setEdgeLabel(e.eId, "blocked");
				}
			}
		}
	}
	gv->rearrange();
	cout << "Succefully drawn!\n";
	getchar();

}
void Company::orderItems() {
	vector<Vertex<Coord>*> res;

	for (auto v : this->main_map.getGraph().getVertexSet()) {
		for (auto i : items) {
			if (i.getX() == v->getInfo().getX()
					&& i.getY() == v->getInfo().getY()) {
				this->item_delivery.push_back(v);
			}
		}
	}

	for (unsigned int i = 0;
			i < this->main_map.getGraph().getVertexSet().size(); i++) {
		if (this->main_map.getGraph().getVertexSet().at(i)->getInfo().getId()
				== 1109149480) {
			origin = this->main_map.getGraph().getVertexSet().at(i);
			break;
		}
	}
	vector<pair<double, Vertex<Coord>*> > distances;
	double distance;

	vector<Vertex<Coord>*>::iterator it;
	for (it = item_delivery.begin(); it != item_delivery.end(); it++) {
		distance = 0;
		res = this->main_map.getGraph().getPath(origin->getInfo(),
				(*it)->getInfo());
		for (unsigned int j = 0; j < res.size(); j++) {
			distance += res[j]->getDist();
		}
		distances.push_back(make_pair(distance, *it));
	}
	sort(distances.begin(), distances.end());

	cout << "Printing res\n";
	for (auto p : item_delivery) {
		cout << p->getInfo().getId() << endl;
	}
	cout << endl << endl << "printing sorted";
	for (auto p : distances) {
		cout << p.second->getInfo().getId() << endl;
	}

	item_delivery.clear();

	vector<pair<double, Vertex<Coord>*> >::reverse_iterator it2;
	for (it2 = distances.rbegin(); it2 != distances.rend(); it2++) {
		item_delivery.push_back((*it2).second);
	}
}
//TODO n ta A DAR
void Company::orderTrucks() {
	unsigned index = 0;
	bool flag = true;
	for (auto t : this->Trucks) {
		cout<<" truck"<<t.getCurrentVolume()<<endl;
		if (index >= item_delivery.size())
			break;
		flag = true;
		while (flag) {
			cout<<"ola\n";
			if (index >= item_delivery.size())
				break;;
			auto id = item_delivery[index];
			for (auto i : items) {
				if (i.getX() == id->getInfo().getX()
						&& i.getY() == id->getInfo().getY()) {
					cout<<" found item"<<i.getVolume() <<" !" << i.getWeight()<<endl;
					cout<<"turck current coiso "<<t.getCurrentVolume()<<" | "<<t.getCurrentWeight()<<endl;
					if (i.getWeight() < t.getCurrentWeight()
							&& i.getVolume() < t.getCurrentVolume()) {
						cout << " alocated\n";

						t.addItem(i);
						t.addTruckItemDelivery(id);  //IDK Y ELE N ALOCA
						index++;
					} else {
						flag = false;
						break;
					}
				}
			}
		}
		}
cout<< "\n\n";
	for (auto t : this->Trucks) {
		cout<<"one truck\n";
		for (auto i : t.getItemDelivery()) {
			cout << " :: " << i->getInfo().getX();
		}
	}
}
void Company::blockStreet() {
	int id;
	cout << "Insert id ->";
	cin >> id;

	if (id == 0 || id % 2 == 0) { //is even
		blockedEdges.push_back(id);
		blockedEdges.push_back(id + 1);
		this->main_map.getGraph().removeEdge(id);
		this->main_map.getGraph().removeEdge(id + 1);
	}
	if (id % 2 != 0) { //is odd
		blockedEdges.push_back(id - 1);
		blockedEdges.push_back(id);
		this->main_map.getGraph().removeEdge(id - 1);
		this->main_map.getGraph().removeEdge(id);
	}
}
void Company::addExtratingPoint() {
	string id;
	int idnr;
	cout << "========Points available========\n";
	for (auto v : this->main_map.getGraph().getVertexSet()) {
		if (!v->getInfo().getTag().empty()) {
			cout << v->getInfo().getTag() << " ID: " << v->getInfo().getId()
					<< " || Lat: " << v->getInfo().getLat() << "Lon: "
					<< v->getInfo().getLon() << endl;
		}
	}
	//1346179432
	//4694
	//3396
	//TODO control erros in case bad typing and id not matching, and repeting a node
	cout << "Insert id -> ";
	cin >> id;
	idnr = stoi(id);
	for (auto v : this->main_map.getGraph().getVertexSet()) {
		if (idnr == v->getInfo().getId()) {
			this->extraction_points.push_back(v);
			break;
		}
	}
	cout << "\n=====Extration points available=====\n";
	for (auto p : this->extraction_points) {
		cout << p->getInfo().getTag() << " ID: " << p->getInfo().getId()
				<< endl;
	}
	cout << endl;
}
void Company::reset() {
	this->main_map.loadMap();
	this->blockedEdges = {};
	this->extraction_points.clear();
}

