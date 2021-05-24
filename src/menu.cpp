//
// Created by ritaramada on 16/05/21.
//

#include <iostream>
#include "menu.h"

using namespace std;

int timeParked;

void initialMenu(){
    string text = "     À procura de estacionamento";

    int option = 0;
    Graph * graph;

    while(option != 6){
        clear();
        printText(text);
        cout << "Choose a map: \n" << "[1] 4x4\n[2] 8x8\n[3] 16x16\n[4] 32x32\n[5] Porto\n[6] Penafiel\n[7] Leave\n";
        option = getInt(1, 7);

        if(option != 7 && option != 0)
            displayMap(option);
    }
}

vector<int> chooseTasks(Graph * graph){
    int task;
    bool cont;
    vector<int> tasks;
    do{
        cout << "Insira o número da task\n";
        task = getInt(0, graph->getVertexSet().size() -1);
        pointType type = graph->findVertex(Point(task, 0, 0))->getPoint().getPointType();
        while( type == POINT || type == PARK){
            cout << "O ponto escolhido não é uma task... tente outra vez\n";
            task = getInt(0, graph->getVertexSet().size() -1);
            type = graph->findVertex(Point(task, 0, 0))->getPoint().getPointType();
        }
        tasks.push_back(task);
        cout << "Pretende fazer mais tasks? (Y/N)\n";
        cont = getYesNo();

    }while(cont);

    return tasks;
}

int chooseOptimization(Graph * graph, Point * destiny, Point * orig){
    int option;
    cout << "Pretende otimizar:\n";
    cout << "[1] Distância percorrida até ao parque de estacionamento\n"
            "[2] Preço a pagar pelo estacionamento\n"
            "[3] Distância a percorrer a pé até ao ponto de destino D\n"
            "[4] Leave\n";
    option = getInt(1, 4);
    cout << "Insira o tempo de estacionamento (min)...\n";
    timeParked = getInt(0, 500000);


    Point destPark = graph->getPark(option, destiny, orig, timeParked);
    return  destPark.getId();
}

void choosePoints(Graph  * graph, GraphViewer &gv, GraphViewerLoader &gvl){
    int startID, destinyID;
    cout << "Insira o ponto inicial:\n";
    startID = getInt(0, graph->getVertexSet().size() -1);

    cout << "Insira o destino:\n";
    destinyID = getInt(0, graph->getVertexSet().size() -1);

    //Coloring origin and destiny points
    Point origin(startID, 0, 0);
    Point destinyPoint(destinyID, 0, 0);
    int parkID = chooseOptimization(graph, &destinyPoint, &origin);

    cout << "Vai realizar tarefas? (Y/N) \n";
    bool doTasks = getYesNo();

    Point parkPoint(parkID, 0, 0);

    GraphViewer::Node &start = gv.getNode(startID), &destiny = gv.getNode(destinyID);
    start.setColor(GraphViewer::CYAN);
    //start.setOutlineThickness(4);
    destiny.setColor(GraphViewer::CYAN);
    //destiny.setOutlineThickness(4);

    GraphViewer::Node &park = gv.getNode(parkID);
    park.setColor(GraphViewer::RED);
    vector<Point> route;
    vector<int> ids = {startID ,parkID};

    if(doTasks){
        vector<int> tasks = chooseTasks(graph);//Getting tasks
        ids.insert(ids.end(), tasks.begin(), tasks.end());
    }

    graph->Christofides(ids, route);
    for(int i = 0; i < route.size()-1; i++){
        Point from = route.at(i), to = route.at(i+1);
        graph->dijkstraShortestPath(from);
        vector<Point> path = graph->getPath(from ,to);
        if(!path.empty()){
            gvl.colorPath(*graph, from, to);
            for(vector<Point>::iterator it = path.begin(); it != path.end(); it++)
                cout << it->getId() << " -> ";
            cout <<endl;
        }
    }
    //Unites the last two points
/*    Point from = route.back(), to = Point(startID,0, 0);
    vector<Point> path = graph->getPath(from ,to);
    graph->dijkstraShortestPath(from);
    //gvl.colorPath(*graph, from, to);
    for(vector<Point>::iterator it = path.begin(); it != path.end(); it++)
        cout << it->getId() << " -> ";
    cout <<endl;*/


    gv.createWindow(WIDTH, HEIGHT);
    // Join viewer thread (blocks till window closed)
    gv.join();

    float price = (float) graph->getPrice(timeParked, parkID) / 100.0;
    cout << "[Price Paid] = " << price << " euros\n";

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
        case 4: //32x32
            graphLoader.loadMap("../data/GridGraphs/32x32/nodes.txt", "../data/GridGraphs/32x32/edges.txt", 1);
            scale = 10;
            nodeSize = 70;
            thickness = 8;
            break;
        case 5: //Porto
            graphLoader.loadMap("../data/porto/porto_strong_nodes_xy.txt", "../data/porto/porto_strong_edges.txt");
            scale = 30;
            nodeSize = 100;
            thickness = 40;
            break;
        case 6: //Penafiel
            graphLoader.loadMap("../data/penafiel/penafiel_strong_nodes_xy.txt", "../data/penafiel/penafiel_strong_edges.txt");
            scale = 20;
            nodeSize = 100;
            thickness = 50;
            break;
    }

    gvl.loadGraph(g, scale, thickness, nodeSize);
    gv.createWindow(WIDTH, HEIGHT);

    // Join viewer thread (blocks till window closed)
    gv.join();
    gv.closeWindow();
    choosePoints(&g, gv, gvl);

}




