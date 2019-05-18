/*
 * menu.cpp
 *
 *  Created on: 18/05/2019
 *      Author: gustavo
 */

#include "menu.h"

	bool Menu::menuManip(){
		while(true){
			this->drawMainMenu();
			this->readInput();
			switch(this->option){
					case 0:
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
		cout<<"MAP: "<<this->mapFile<<" | "<<"TRUCKS: "<< this->trucksFile<<" | "<<"ITEMS: "<<this->itemsFile<<endl;
		cout<<"================================================================"<<endl;
		cout<< setw(10);
		cout<<"0 - Process Route"<<endl;
		cout<<"1 - Block Street"<<endl;
		cout<<"2 - Create/Add extracting point"<<endl;
		cout<<"3 - Reset"<<endl;
		cout<<"4 - EXIT"<<endl;
		cout<<"================================================================"<<endl;
	}

	void Menu::readInput(){
		string input;
		cout<< " -> ";
		cin>>input;
		cout<<endl;
		this->option = stoi(input);
	}



