//
// Created by pedro on 26/04/21.
//

#include "GraphLoader.h"
#include <iostream>

#include <fstream>
void GraphLoader::loadMap(string nodesFilename, string edgesFilename) {
    loadNodes(nodesFilename);
    loadEdges(edgesFilename);
}

void GraphLoader::loadNodes(string nodesFilename){
    fstream myNodesFile;
    myNodesFile.open(nodesFilename, ios::in);
    if (myNodesFile) {
        int nCount; int i = 0;
        myNodesFile >> nCount;
        while(i < nCount){
            double latitude, longitude; char c;
            myNodesFile >> c >> i >> c >> latitude >> c >> longitude >> c;
            Point pt(i, latitude, longitude);
            graph->addVertex(pt);
            if (myNodesFile.eof())
                break;
        }

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
