//
// Created by pedro on 18/05/21.
//
#define WIDTH 800 //mudei para 800x800 porque como estava fica muito grande para o meu ecrã de pobre :( se quiserem voltem a trocar na paz
#define HEIGHT 800

#include <gtest/gtest.h>
#include <graphviewer.h>
#include "../src/Graph.h"
#include "../src/GraphLoader.h"
#include "../src/GraphViewerLoader.h"
#include "../test/GraphGenerator.h"

TEST(GlobalTest, _4x4){

    Graph graph;

    GraphLoader graphLoader(&graph);

    graphLoader.loadMap("../data/GridGraphs/16x16/nodes.txt", "../data/GridGraphs/16x16/edges.txt", 1);

    GraphViewer graphViewer;

    GraphViewerLoader graphViewerLoader(&graphViewer);

    graphViewerLoader.loadGraph(graph, 2, 2.5,25);

    int ids[] = {19, 175, 143, 235, 79, 59, 104};

    Graph abstractGraph;
    for(auto i: ids)
    {
        Point p =  graph.findVertex(Point(i,0,0))->getPoint();
        abstractGraph.addVertex(p);
    }

    for(auto v: abstractGraph.getVertexSet())
    {
        for(auto v2: abstractGraph.getVertexSet())
        {
            if(v->getPoint() != v2->getPoint())
                abstractGraph.addEdge(v->getPoint(), v2->getPoint(), v->getPoint().getPosition().distance(v2->getPoint().getPosition()));
        }
    }

    abstractGraph.primAlgorithm();
    abstractGraph.extractMSTfromPath();

    GraphViewer graphViewerAbs;
    GraphViewerLoader graphViewerLoaderAbs(&graphViewerAbs);
    graphViewerLoaderAbs.loadGraph(abstractGraph, 2, 2.5,25);

    graphViewer.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));
    graphViewer.createWindow(WIDTH, HEIGHT);

    graphViewer.join();
    graphViewer.closeWindow();

    graphViewerAbs.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));
    graphViewerAbs.createWindow(WIDTH, HEIGHT);
    graphViewerAbs.join();
    graphViewerAbs.closeWindow();

    abstractGraph.matchingOdd();

    GraphViewer graphViewerMatchingOdd;
    GraphViewerLoader graphViewerLoaderMatchingOdd(&graphViewerMatchingOdd);
    graphViewerLoaderMatchingOdd.loadGraph(abstractGraph,2, 2.5,25);
    graphViewerMatchingOdd.createWindow(WIDTH, HEIGHT);
    graphViewerMatchingOdd.join();

    vector<Point> route = abstractGraph.getEuler(abstractGraph.getVertexSet().at(0)->getPoint());
    abstractGraph.cutShort(&route);
    route.push_back(route.front());

    for(auto p : route){
        cout << p << " ; ";
    }
    cout <<endl;

    for(int i = 0; i < route.size()-1; i++){
        Point from = route.at(i), to = route.at(i+1);
        graph.dijkstraShortestPath(from);
        vector<Point> path = graph.getPath(from ,to);
        if(!path.empty()){
            for(vector<Point>::iterator it = path.begin(); it != path.end(); it++)
                cout << it->getId() << " -> ";
            cout <<endl;
        }
    }

    graphViewer.createWindow(WIDTH, HEIGHT);

    graphViewer.join();


}
