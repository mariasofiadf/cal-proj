//
// Created by ritaramada on 16/05/21.
//

#include <iostream>

#include "menu.h"

using namespace std;

int timeParked;

void initialMenu1(){

    int option, map;
    string text;

    do{
        clear();
        text = "             Menu Inicial";
        clear();
        printText(text);
        cout << "Escolha uma opção: \n" << "[1] Utilização normal\n[2] Testar conectividade\n[3] Sair\n";
        option = getInt(1, 3);

        switch (option) {
            case 1:
                text = "     À procura de estacionamento";
                clear();
                printText(text);
                map = chooseMap();
                displayMap(map);
                break;
            case 2:
                clear();
                text = "         Testar conectividade";
                printText(text);
                map = chooseMap();
                connectAnalysis(map);
                break;
            case 3:
                break;
        }
    }while(option != 3);


}

void connectAnalysis(int map){
    Graph myGraph;
    GraphLoader graphLoader(&myGraph);
    bool strong;
    if(map == 5 || map == 6 || map == 7){
        cout << "Quer o mapa fortemente conexo? (y/n)\n";
        strong = getYesNo();
    }
    switch (map) {
        case 1: //4x4
            graphLoader.loadMap("../data/GridGraphs/4x4/nodes.txt", "../data/GridGraphs/4x4/edges.txt", 1);
            break;
        case 2: //8x8
            graphLoader.loadMap("../data/GridGraphs/8x8/nodes.txt", "../data/GridGraphs/8x8/edges.txt", 1);
            break;
        case 3: //16x16
            graphLoader.loadMap("../data/GridGraphs/16x16/nodes.txt", "../data/GridGraphs/16x16/edges.txt", 1);
            break;
        case 4: //32x32
            graphLoader.loadMap("../data/GridGraphs/32x32/nodes.txt", "../data/GridGraphs/32x32/edges.txt", 1);
            break;
        case 5: //Porto
            if(strong)
                graphLoader.loadMap("../data/porto/porto_strong_nodes_xy.txt", "../data/porto/porto_strong_edges.txt");
            else
                graphLoader.loadMap("../data/porto/porto_full_nodes_xy.txt", "../data/porto/porto_full_edges.txt");
            break;
        case 6: //Penafiel
            if(strong)
                graphLoader.loadMap("../data/penafiel/penafiel_strong_nodes_xy.txt", "../data/penafiel/penafiel_strong_edges.txt");
            else
                graphLoader.loadMap("../data/penafiel/penafiel_full_nodes_xy.txt", "../data/penafiel/penafiel_full_edges.txt");

            break;
        case 7: //Espinho
            if(strong)
                graphLoader.loadMap("../data/espinho/espinho_strong_nodes_xy.txt", "../data/espinho/espinho_strong_edges.txt");
            else
                graphLoader.loadMap("../data/espinho/espinho_full_nodes_xy.txt", "../data/espinho/espinho_full_edges.txt");

            break;
        case 8:
            return;
    }

    vector<vector<Vertex *>> scc = myGraph.getSCC();
    clear();
    cout << "[Strongly connected components]\n";
    for(auto component : scc){
        for(auto vertex : component){
            cout << vertex->getPoint().getId() << " ";
        }
        cout << endl;
    }

    if(scc.size() == 1 && scc.at(0).size() == myGraph.getVertexSet().size())
        cout << "[Strongly connected]\n";
    else{
        cout << "[Not strongly connected]\n";
    }

    sleep(3);
}

int chooseMap(){
    int option ;

    cout << "Escolha o mapa: \n" << "[1] 4x4\n[2] 8x8\n[3] 16x16\n"
                                  "[4] 32x32\n[5] Porto\n[6] Penafiel\n[7] Espinho\n[8] Leave\n";
    option = getInt(1, 8);
    return option;
}


vector<int> chooseTasks(Graph * graph){
    int task;
    bool cont;
    vector<int> tasks;
    do{
        cout << "Insira o número da task\n";
        task = getID(graph);
        pointType type = graph->findVertex(Point(task, 0, 0))->getPoint().getPointType();
        while( type == POINT || type == PARK){
            cout << "O ponto escolhido não é uma task... tente outra vez\n";
            task =  getID(graph);
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
    startID =  getID(graph);;

    cout << "Insira o destino:\n";
    destinyID =  getID(graph);;

    //Coloring origin and destiny points
    Point origin(startID, 0, 0);
    Point destinyPoint(destinyID, 0, 0);
    int parkID = chooseOptimization(graph, &destinyPoint, &origin);
    if(parkID == -1) cout <<"Invalid Park\n";

    cout << "Vai realizar tarefas? (Y/N) \n";
    bool doTasks = getYesNo();

    Point parkPoint(parkID, 0, 0);


    GraphViewer::Node &start = gv.getNode(graph->findVertex(origin)->getViewerIndex()), &destiny = gv.getNode(graph->findVertex(destinyPoint)->getViewerIndex());
    start.setColor(GraphViewer::CYAN);
    //start.setOutlineThickness(4);
    destiny.setColor(GraphViewer::CYAN);
    //destiny.setOutlineThickness(4);

    GraphViewer::Node &park = gv.getNode(graph->findVertex(parkPoint)->getViewerIndex());
    park.setColor(GraphViewer::RED);
    park.setOutlineThickness(20);

    vector<Point> route;
    vector<int> ids = {startID ,parkID};

    if(doTasks){
        vector<int> tasks = chooseTasks(graph);//Getting tasks
        ids.insert(ids.end(), tasks.begin(), tasks.end());

        for(auto task: tasks ){
            GraphViewer::Node &node = gv.getNode(graph->findVertex(Point(task,0, 0))->getViewerIndex());
            node.setColor(GraphViewer::RED);
        }
    }



    graph->Christofides(ids, route);
    for(int i = 0; i < route.size()-1; i++){
        Point from = route.at(i), to = route.at(i+1);
        graph->dijkstraShortestPath(from);
        vector<Point> path = {};
        path =graph->getPath(from ,to);
        if(!path.empty()){
            gvl.colorPath(*graph, from, to);
            for(vector<Point>::iterator it = path.begin(); it != path.end(); it++)
                cout << it->getId() << " -> ";
            cout <<endl;
        }
    }


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
        case 7: //Espinho
            graphLoader.loadMap("../data/espinho/espinho_strong_nodes_xy.txt", "../data/espinho/espinho_strong_edges.txt");
            scale = 20;
            nodeSize = 100;
            thickness = 50;
            break;
        case 8:
            return;
    }

    gvl.loadGraph(g, scale, thickness, nodeSize);
    gv.createWindow(WIDTH, HEIGHT);

    // Join viewer thread (blocks till window closed)
    gv.join();
    gv.closeWindow();
    choosePoints(&g, gv, gvl);

}




