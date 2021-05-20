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

void GraphLoader::loadNodes(string nodesFilename, float pPark, float pCoffee, float pGas, float pStore){

    fstream myNodesFile;
    myNodesFile.open(nodesFilename, ios::in);
    if (myNodesFile) {
        int nCount; int i;
        myNodesFile >> nCount;
        int totalNodes = nCount;
        int nPark = pPark * totalNodes;
        int nCoffee = pCoffee * totalNodes;
        int nGas = pGas * totalNodes;
        int nStore = pStore * totalNodes;
        int nNormal = totalNodes-pPark-pStore-pGas-pCoffee;

        while(nCount){
            double latitude, longitude; char c;
            myNodesFile >> c >> i >> c >> latitude >> c >> longitude >> c;
            pointType type = getRandomPointType(nCount,nNormal, nPark, nCoffee, nGas, nStore);
            if(type == PARK) {
                PointPark ptp(i, latitude, longitude, 1.0); //MUDAR O PREÇO!
                graph->addVertex(ptp);
            } else if(type == COFFE){
                PointCoffe ptc(i, latitude, longitude);
                graph->addVertex(ptc);
            } else if(type == GAS) {
                PointGas ptg(i, latitude, longitude);
                graph->addVertex(ptg);
            } else if(type == STORE){
                PointStore pts(i, latitude, longitude);
                graph->addVertex(pts);
            } else{
                Point pt(i, latitude, longitude);
                graph->addVertex(pt);
            }
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

pointType GraphLoader::getRandomPointType(int nodes, int &normal, int &park, int &coffee, int &gas, int &store) {
    srand((unsigned) time(0));
    while(1)
    {
        int r = rand() % nodes;
        if(r < park && park > 0){
            park--;
            return PARK;
        }
        else if(r < coffee+park && coffee > 0)
        {
            coffee--;
            return COFFE;
        }
        else if(r < park+coffee+gas && gas > 0)
        {
            gas--;
            return GAS;
        }
        else if(r < park+coffee+gas+store && store > 0){
            store--;
            return STORE;
        }
        else if (normal > 0){
            normal--;
            return POINT;
        }
    }
}
