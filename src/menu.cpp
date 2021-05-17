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

void chooseStart(Graph &graph, GraphViewer &gv){
    int startID;
    cout << "Please enter your starting point:\n";
    startID = getInt(0, graph.getVertexSet().size());

    GraphViewer::Node &node0 = gv.getNode(startID);
    node0.setColor(GraphViewer::GREEN);
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
            break;
        case 3: //Maia
            break;
        case 4: //Porto
            graphLoader.loadMap("../data/porto/porto_strong_nodes_xy.txt", "../data/porto/porto_strong_edges.txt");
            scale = 10;
            nodeSize = 100;
            thickness =30;
            break;


    }

    gvl.loadGraph(g, scale, thickness, nodeSize);


    chooseStart(g, gv);
}



void showMapOptions(){
    int option;
    do
    {
        //system("clear");
        clear();
        cout << "Choose a map: \n" << "[1] 4x4\n[2] 8x8\n[3] Maia\n[4] Porto\n[5] Leave\n";
        option = getInt(1, 5);
        switch (option) {
            case 1:
                displayMap(1);
                break;
            case 2:
                displayMap(2);
                break;
            case 3:
                displayMap(3);
                break;
            case 4:
                displayMap(4);
                break;
            case 5:
                break;
        }
    } while (option != 5);

}



