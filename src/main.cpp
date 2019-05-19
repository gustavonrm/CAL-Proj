#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

#include "graphviewer.h"
#include "Menu.h"

void graphviewer_sample();

void graphviewer_sample()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("panquecas.jpg");

	//window configs
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	//add stuff
	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0,0,1,EdgeType::DIRECTED);

	gv->rearrange(); //NEEDED TO APPLY NEW INFO
	Sleep(100);

	gv->removeNode(1);
	gv->addNode(2);

	gv->rearrange(); //NEEDED TO APPLY NEW INFO
	Sleep(100);

	gv->addEdge(1,1,2,EdgeType::UNDIRECTED);
	gv->setVertexLabel(2, "Isto e um no");
	gv->setEdgeLabel(1, "Isto e uma aresta");
	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->rearrange(); //NEEDED TO APPLY NEW INFO
}


int main() {
	Menu menu;
	cout<<"end";
		return 0;
	/*
	graphviewer_sample();
	getchar();
	*/
}
