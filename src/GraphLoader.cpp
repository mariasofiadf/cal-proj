//
// Created by pedro on 26/04/21.
//

#include "GraphLoader.h"
#include <iostream>

#include <fstream>
void GraphLoader::loadMap(string nodesFilename, string edgesFilename) {
    fstream myNodesFile;
    myNodesFile.open(nodesFilename, ios::in);
    if (myNodesFile) {
        int nCount; int i;
        myNodesFile >> nCount;
        while(i < nCount){
            double latitude, longitude; char c;
            myNodesFile >> c >> i >> c >> latitude >> c >> longitude >> c;
            Point pt(latitude, longitude, i);
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