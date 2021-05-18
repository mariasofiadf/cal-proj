//
// Created by pedro on 26/04/21.
//

#include "GraphLoader.h"
#include <iostream>
#include <cstdlib>

#include <fstream>
void GraphLoader::loadMap(string nodesFilename, string edgesFilename) {
    loadNodes(nodesFilename);
    loadEdges(edgesFilename);
}

void GraphLoader::loadNodes(string nodesFilename, int Pnumber, int Cnumber, int Gnumber, int Snumber){
    Pnumber = Pnumber * this->graph->getVertexSet().size();
    Cnumber = Cnumber * this->graph->getVertexSet().size();
    Gnumber = Gnumber * this->graph->getVertexSet().size();
    Snumber = Snumber * this->graph->getVertexSet().size();
    srand((unsigned) time(0));
    fstream myNodesFile;
    myNodesFile.open(nodesFilename, ios::in);
    if (myNodesFile) {
        int nCount; int i;
        myNodesFile >> nCount;
        while(nCount){
            double latitude, longitude; char c;
            myNodesFile >> c >> i >> c >> latitude >> c >> longitude >> c;
            Point pt(i, latitude, longitude);
            int r = (rand() % this->graph->getVertexSet().size());
            if(r <= Pnumber && Pnumber > 0) {
                Pnumber--;
                PointPark pt2= PointPark(i, latitude, longitude,(rand() % 99)+1);
                graph->addVertex(pt2);
            }
            else if(r <= Pnumber+Cnumber && Cnumber > 0) {
                Cnumber--;
                PointCoffe pt2= PointCoffe(i, latitude, longitude);
                graph->addVertex(pt2);
            }
            else if(r <= Pnumber+Cnumber+Gnumber && Gnumber > 0) {
                Gnumber--;
                PointGas pt2= PointGas(i, latitude, longitude);
                graph->addVertex(pt2);
            }
            else if(r <= Pnumber+Cnumber+Gnumber+Snumber && Snumber > 0) {
                Snumber--;
                PointStore pt2= PointStore(i, latitude, longitude);
                graph->addVertex(pt2);
            }
            else {
                Point pt2(i, latitude, longitude);
                graph->addVertex(pt2);
            }

            nCount--;
            if (myNodesFile.eof())
                break;
        }
        /*
        graph->setParks(numberParks);
        graph->setGas(numberGas);
        graph->setCoffe(numberCoffe);
        graph->setStore(numberStore);
         */

        myNodesFile.close();
    }
    else{
        cout << "Error opening Nodes file";
        return;
    }


}

void GraphLoader::loadEdges(string edgesFilename) {
    fstream myEdgesFile;
    myEdgesFile.open(edgesFilename, ios::in);
    if (myEdgesFile) {
        int eCount; int id1, id2;
        myEdgesFile >> eCount;
        while(eCount){
            double latitude, longitude; char c;
            myEdgesFile >> c >> id1 >> c >> id2>> c;
            graph->addEdge(Point(id1,0,0), Point(id2, 0,0), 0);
            if (myEdgesFile.eof())
                break;
            eCount--;
        }

        myEdgesFile.close();
    }
    else{
        cout << "Error opening Edges file";
        return;
    }
}
