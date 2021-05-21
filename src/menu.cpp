//
// Created by ritaramada on 16/05/21.
//

#include <iostream>
#include "menu.h"

using namespace std;



void initialMenu(){
    string text = "     À procura de estacionamento";

    int option = 0;
    Graph * graph;

    while(option != 6){
        clear();
        printText(text);
        cout << "Choose a map: \n" << "[1] 4x4\n[2] 8x8\n[3] 16x16\n[4] Maia\n[5] Porto\n[6] Leave\n";
        option = getInt(1, 6);

        if(option != 6 && option != 0)
            displayMap(option);
    }
}

void chooseTasks(Graph * graph){

}

int chooseOptimization(Graph * graph, Point * destiny, Point * orig){
    int option;
    int timeParked = 0;
    cout << "Pretende otimizar:\n";
    cout << "[1] Distância percorrida até ao parque de estacionamento\n"
            "[2] Preço a pagar pelo estacionamento\n"
            "[3] Distância a percorrer a pé até ao ponto de destino D\n"
            "[4] Leave\n";
    option = getInt(1, 4);
    cout << "Insira o tempo de estacionamento (min)...\n";
    timeParked = getInt(0, 500000);


    Point * destPark = graph->getPark(option, destiny, orig, 15);
    return  destPark->getId();
}

void choosePoints(Graph  * graph, GraphViewer &gv, GraphViewerLoader &gvl){
    int startID, destinyID;
    cout << "Enter your starting point:\n";
    startID = getInt(0, graph->getVertexSet().size() -1);

    cout << "Enter your destiny:\n";
    destinyID = getInt(0, graph->getVertexSet().size() -1);

    //Coloring origin and destiny points
    GraphViewer::Node &start = gv.getNode(startID), &destiny = gv.getNode(destinyID);
    start.setColor(GraphViewer::GREEN);
    destiny.setColor(GraphViewer::RED);
    Point origin(startID, 0, 0);
    Point destinyPoint(destinyID, 0, 0);

    cout << "Are you doing tasks? (Y/N) \n";
    bool doTasks = getYesNo();

    if(!doTasks){

        graph->dijkstraShortestPath(origin);
        if(!graph->getPath(origin, destinyPoint).empty())
            gvl.colorPath(*graph, origin, destinyPoint);
        //graph->getPath(origin, destinyPoint);
    }

    //chooseTasks(graph);

    int parkID = chooseOptimization(graph, &destinyPoint, &origin);
    GraphViewer::Node &park = gv.getNode(parkID);
    park.setColor(GraphViewer::RED);

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
            graphLoader.loadMap("../data/GridGraphs/4x4/nodes.txt", "../data/GridGraphs/4x4/edges.txt", 1);
            nodeSize = 20;
            break;
        case 2: //8x8
            graphLoader.loadMap("../data/GridGraphs/8x8/nodes.txt", "../data/GridGraphs/8x8/edges.txt", 1);
            nodeSize = 20;
            break;
        case 3: //16x16
            graphLoader.loadMap("../data/GridGraphs/16x16/nodes.txt", "../data/GridGraphs/16x16/edges.txt", 1);
            scale = 3;
            nodeSize = 50;
            //thickness = 20;
            break;
        case 4: //Maia
            break;
        case 5: //Porto
            graphLoader.loadMap("../data/porto/porto_strong_nodes_xy.txt", "../data/porto/porto_strong_edges.txt");
            scale = 30;
            nodeSize = 100;
            thickness = 40;
            break;
    }

    gvl.loadGraph(g, scale, thickness, nodeSize);
    gv.createWindow(WIDTH, HEIGHT);

    // Join viewer thread (blocks till window closed)
    gv.join();
    gv.closeWindow();
    choosePoints(&g, gv, gvl);


}




