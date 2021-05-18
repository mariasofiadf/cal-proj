//
// Created by pedro on 26/04/21.
//

#include "GraphLoader.h"
#include <iostream>

#include <fstream>
void GraphLoader::loadMap(string nodesFilename, string edgesFilename, int loadBidirectional) {
    loadNodes(nodesFilename);
    loadEdges(edgesFilename, loadBidirectional);
}

void GraphLoader::loadNodes(string nodesFilename){
    fstream myNodesFile;
    myNodesFile.open(nodesFilename, ios::in);
    if (myNodesFile) {
        int nCount; int i;
        myNodesFile >> nCount;
        while(nCount){
            double latitude, longitude; char c;
            myNodesFile >> c >> i >> c >> latitude >> c >> longitude >> c;
            Point pt(i, latitude, longitude);
            graph->addVertex(pt);
            nCount--;
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

void GraphLoader::loadEdges(string edgesFilename, int loadBidirectional) {
    fstream myEdgesFile;
    myEdgesFile.open(edgesFilename, ios::in);
    if (myEdgesFile) {
        int eCount; int id1, id2;
        myEdgesFile >> eCount;
        while(eCount){
            double latitude, longitude; char c;
            myEdgesFile >> c >> id1 >> c >> id2>> c;
            Point p1(id1,0,0), p2(id2,0,0);
            if(loadBidirectional)
                graph->addBidirectionalEdge(p1,p2,p1.getPosition().distance(p2.getPosition()) );
            else
                graph->addEdge(p1,p2,p1.getPosition().distance(p2.getPosition()));
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
