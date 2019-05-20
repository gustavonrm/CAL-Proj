/*
 * menu.cpp
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#include "Menu.h"

Menu::Menu(){
	this->option = 0;
	 this->readFiles();
	 this->loadFiles();
	 this->menuManip();
}
	bool Menu::menuManip(){
		while(true){
			this->drawMainMenu();
			this->readInput();
			switch(this->option){
					case 0:
						this->map.drawGraph();
							break;
					case 1:
							break;
					case 2:
							break;
					case 3:
						break;
					case 4:
						return true;
						break;

				}
		}
	}

	void Menu::drawMainMenu(){
		cout<<"================================================================"<<endl;
		cout<<setw(5);
		cout<<"MAP: "<<this->mapFolder<<" | "<<"TRUCKS: "<< this->trucksFile<<" | "<<"ITEMS: "<<this->itemsFile<<endl;
		cout<<"================================================================"<<endl;
		cout<< setw(10);
		cout<<"0 - Process Route"<<endl;
		cout<<"1 - Block Street"<<endl;
		cout<<"2 - Create/Add extracting point"<<endl;
		cout<<"3 - Reset"<<endl;
		cout<<"4 - EXIT"<<endl;
		cout<<"================================================================"<<endl;
	}

	void Menu::readFiles(){
		cout << "Insert the map that you wish to read: ";
		cin >> this->mapFolder;
		cout << endl << " Insert the trucks to make the transportation: ";
		cin>> this->trucksFile;
		cout << endl << "Insert the items to deliver: ";
		cin>> this->itemsFile;
		cout<<endl;

	}
	void Menu::loadFiles(){
		this->map.setFolder(this->mapFolder);
		this->map.loadMap();
	}

	void Menu::readInput(){
		string input;
		cout<< " -> ";
		cin>>input;
		cout<<endl;
		this->option = stoi(input);
	}



