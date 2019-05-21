/*
 * Utils.cpp
 *
 *  Created on: 21/05/2019
 *      Author: gustavo
 */

#include "utils.h"

vector<Truck> loadTrucks(string truckFile){
	vector<Truck>ret;
	ifstream file;
	string line;
	file.open(truckFile);
	if(file.is_open()){
		while(getline(file,line)){
			string w,v;
			w=line.substr(0,line.find(','));
			line.erase(0,line.find(';')+1);
			v=line.substr(0,line.find(';'));
			line.clear();
			Truck t(stod(w),stod(v));
			ret.push_back(t);
		}
	}else{
		cout <<"Error opening truck file!\n";
		exit(ERR_OP_TRUCK_FILE);
	}
	return ret;
}

vector<Item> loadItems(string itemFile){
	vector<Item>ret;
	ifstream file;
	string line;
	file.open(itemFile);
	if(file.is_open()){
		while(getline(file,line)){
			string lat,lon,w,v;
			lat=line.substr(0,line.find(';'));
			line.erase(0,line.find(';')+1);
			lon=line.substr(0,line.find(';'));
			line.erase(0,line.find(';')+1);
			w=line.substr(0,line.find(';'));
			line.erase(0,line.find(';')+1);
			v=line.substr(0,line.find(';'));
			line.clear();
			pair<double,double> a(stod(lat),stod(lon));
			Item i(a,stod(w),stod(v));
			ret.push_back(i);
		}
	}else{
		cout <<"Error opening truck file!\n";
		exit(ERR_OP_TRUCK_FILE);
	}
	return ret;
}
