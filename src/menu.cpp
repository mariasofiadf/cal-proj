//
// Created by ritaramada on 16/05/21.
//

#include <iostream>
#include "menu.h"

using namespace std;

void printText( string text ) {
    cout << std::setfill( '*' ) << setw( 40 ) << '*' <<  endl;
    cout << '*' << left << setfill(' ' )<< setw( 40 - 2 ) << text<< setw( 40 - 2 )<< " *"<< endl;
    cout << setfill( '*') << setw( 40 ) << '*' <<  endl;
}

void initialMenu(){
    string text = "     À procura de estacionamento";
    printText(text);
    showMapOptions();
}

void choosePoints(Graph &graph, GraphViewer &gv){
    int startID, destinyID;
    cout << "Enter your starting point:\n";
    startID = getInt(0, graph.getVertexSet().size() -1);

    cout << "Enter your destiny:\n";
    destinyID = getInt(0, graph.getVertexSet().size() -1);

    GraphViewer::Node &start = gv.getNode(startID), &destiny = gv.getNode(destinyID);
    start.setColor(GraphViewer::GREEN);
    destiny.setColor(GraphViewer::RED);
    gv.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    gv.join();



}

void displayMap(int map){
    int scale = 1, nodeSize = 10, thickness = 5;
    GraphViewer gv;
    gv.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));     // Set coordinates of window center
    GraphViewerLoader gvl(&gv);

    Graph g;
    GraphLoader graphLoader(&g);
    switch (map) {
        case 1: //4x4
            graphLoader.loadMap("../data/GridGraphs/4x4/nodes.txt", "../data/GridGraphs/4x4/edges.txt");
            nodeSize = 20;
            break;
        case 2: //8x8
            graphLoader.loadMap("../data/GridGraphs/8x8/nodes.txt", "../data/GridGraphs/8x8/edges.txt");
            nodeSize = 20;
            break;
        case 3: //16x16
            graphLoader.loadMap("../data/GridGraphs/16x16/nodes.txt", "../data/GridGraphs/16x16/edges.txt");
            scale = 3;
            nodeSize = 50;
            //thickness = 20;
            break;
        case 4: //Maia
            break;
        case 5: //Porto
            graphLoader.loadMap("../data/porto/porto_strong_nodes_xy.txt", "../data/porto/porto_strong_edges.txt");
            scale = 10;
            nodeSize = 100;
            thickness =30;
            break;


    }

    gvl.loadGraph(g, scale, thickness, nodeSize);


    choosePoints(g, gv);
}

void chooseTasks(){
}


void showMapOptions(){
    int option = 0;
    while(option != 6){
        //system("clear");
        clear();
        cout << "Choose a map: \n" << "[1] 4x4\n[2] 8x8\n[3] 16x16\n[4] Maia\n[5] Porto\n[6] Leave\n";
        option = getInt(1, 6);

        if(option != 6 && option != 0) displayMap(option);
    }

    chooseTasks();
}



