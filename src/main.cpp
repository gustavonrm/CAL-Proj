#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
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

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	//a)
	gv->addNode(0,300,50);
	gv->addNode(1,318,58);
	gv->addNode(2,325,75);
	gv->addNode(3,318,93);
	gv->addNode(4,300,100);
	gv->addNode(5,282,93);
	gv->addNode(6,275,75);
	gv->addNode(7,282,58);
	gv->addNode(8,150,200);
	gv->addNode(9,300,200);
	gv->addNode(10,450,200);
	gv->addNode(11,300,400);
	gv->addNode(12,200,400);
	gv->addNode(13,400,550);

	//b)
	gv->addEdge(0,0,1,EdgeType::DIRECTED);
	gv->addEdge(1,1,2,EdgeType::DIRECTED);
	gv->addEdge(2,2,3,EdgeType::DIRECTED);
	gv->addEdge(3,3,4,EdgeType::DIRECTED);
	gv->addEdge(4,4,5,EdgeType::DIRECTED);
	gv->addEdge(5,5,6,EdgeType::DIRECTED);
	gv->addEdge(6,6,7,EdgeType::DIRECTED);
	gv->addEdge(7,7,0,EdgeType::DIRECTED);
	gv->addEdge(8,4,9,EdgeType::DIRECTED);
	gv->addEdge(9,9,8,EdgeType::DIRECTED);
	gv->addEdge(10,9,10,EdgeType::DIRECTED);
	gv->addEdge(11,9,11,EdgeType::DIRECTED);
	gv->addEdge(12,11,12,EdgeType::DIRECTED);
	gv->addEdge(13,11,13,EdgeType::DIRECTED);

	gv->rearrange(); //NEEDED TO APPLY NEW INFO
//b)
	Sleep(300);
	gv->removeNode(12);
	gv->removeNode(13);

	gv->rearrange();

	Sleep(300);
	gv->addNode(14,250,550);
	gv->addNode(15,350,550);

	gv->rearrange();

	while(1){
		int e = 0;
		int n=0;
		while(e != 14){
			gv->removeEdge(e);
			e++;
		}

		while(n != 16){
					gv->removeNode(n);
					n++;
				}


		//a)
		gv->addNode(0,300,50);
		Sleep(100);
		gv->addNode(1,318,58);
		Sleep(100);
		Sleep(100);
		gv->addNode(2,325,75);
		Sleep(100);
		gv->addNode(3,318,93);
		Sleep(100);
		gv->addNode(4,300,100);
		Sleep(100);
		gv->addNode(5,282,93);
		Sleep(100);
		gv->addNode(6,275,75);
		Sleep(100);
		gv->addNode(7,282,58);
		Sleep(100);
		gv->addNode(8,150,200);
		Sleep(100);
		gv->addNode(9,300,200);
		Sleep(100);
		gv->addNode(10,450,200);
		Sleep(100);
		gv->addNode(11,300,400);
		Sleep(100);
		gv->addNode(12,200,400);
		Sleep(100);
		gv->addNode(13,400,550);
		Sleep(100);

		//b)

		gv->addEdge(0,0,1,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(1,1,2,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(2,2,3,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(3,3,4,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(4,4,5,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(5,5,6,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(6,6,7,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(7,7,0,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(8,4,9,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(9,9,8,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(10,9,10,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(11,9,11,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(12,11,12,EdgeType::DIRECTED);
		Sleep(100);
		gv->addEdge(13,11,13,EdgeType::DIRECTED);
		Sleep(100);
		gv->rearrange(); //NEEDED TO APPLY NEW INFO
	//b)
		Sleep(100);
		gv->removeNode(12);
		gv->removeNode(13);

		gv->rearrange();

		Sleep(100);
		gv->addNode(14,250,550);
		gv->addNode(15,350,550);

		gv->rearrange();
	}
}

void exercicio3()
{

}


int main() {

	exercicio1();
	//exercicio2();
	//exercicio3();
	getchar();
	return 0;
}
