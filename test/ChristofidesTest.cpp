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

    graphLoader.loadMap("../data/GridGraphs/32x32/nodes.txt", "../data/GridGraphs/32x32/edges.txt", 1);

    GraphViewer graphViewer;

    GraphViewerLoader graphViewerLoader(&graphViewer);

    graphViewerLoader.loadGraph(graph);

    int ids[] = {100, 1010, 962, 561,768, 195};

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
    graphViewerLoaderAbs.loadGraph(abstractGraph);

    graphViewer.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));
    graphViewer.createWindow(WIDTH, HEIGHT);

    graphViewer.join();

    graphViewerAbs.setCenter(sf::Vector2f(WIDTH/2, HEIGHT/2));
    graphViewerAbs.createWindow(WIDTH, HEIGHT);
    graphViewerAbs.join();
    graphViewerAbs.closeWindow();

    abstractGraph.matchingOdd();

    GraphViewer graphViewerMatchingOdd;
    GraphViewerLoader graphViewerLoaderMatchingOdd(&graphViewerMatchingOdd);
    graphViewerLoaderMatchingOdd.loadGraph(abstractGraph);
    graphViewerMatchingOdd.createWindow(WIDTH, HEIGHT);
    graphViewerMatchingOdd.join();

    vector<Point> route = abstractGraph.getEuler(abstractGraph.getVertexSet().at(0)->getPoint());

    for(auto p : route){
        cout << p << " ; ";
    }



}


Graph getGridGraph(int x,int y){
    stringstream nodes;
    nodes << "../data/GridGraphs/"<<x<<"x"<<y<<"/nodes.txt";
    string nodeFile; nodes >> nodeFile;
    stringstream edges;
    edges << "../data/GridGraphs/"<<x<<"x"<<y<<"/edges.txt";
    string edgesFile; edges >> edgesFile;

    Graph g; GraphLoader graphLoader(&g); graphLoader.loadMap(nodeFile, edgesFile,1);
    return g;
}



int DIST = 10;
void addNodes(Graph * graph, int x, int y){
    int id = 0;
    for(int i = 0; i <= x; i++)
    {
        for(int j = 0; j <= y; j++){
            Point p(id++, i*DIST, j*DIST);
            graph->addVertex(p);
        }
    }
}

void addEdges(Graph * graph, int x, int y){
    int id1 = 0, id2 = 0;

    for(int i = 0; i <= x; i++){
        for(int j = 0; j < y; j++){
            id1 = j + i*(y+1);
            id2 = j+1 + i*(y+1);
            Point source(id1, 0, 0);
            Point dest(id2, 0,0);
            double w = source.getPosition().distance(dest.getPosition());
            graph->addBidirectionalEdge(source, dest, w);
        }
    }

    for(int j = 0; j <= y; j++){
        for(int i = 0; i < x; i++){
            id1 = j + i*(y+1);
            id2 = j+y+1 + i*(y+1);
            Point source(id1, 0, 0);
            Point dest(id2, 0,0);
            double w = source.getPosition().distance(dest.getPosition());
            graph->addBidirectionalEdge(source, dest, w);
        }
    }

}

Graph generateGridGraph(int x, int y){
    Graph graph;
    addNodes(&graph, x, y);
    addEdges(&graph, x, y);
    return graph;
}

vector<int> getRandomNodes(int x, int y, int n) {
    srand(time(NULL));
    int totalNodes = (x+1)*(y+1);
    vector<int> res; int id;
    for(int i = 0; i < n; i++){
        do{
            id = rand()%totalNodes;
        }while(find(res.begin(), res.end(), id) != res.end());
        res.push_back(id);
    }

    return res;
}

#include "../lib/pbPlots-master/pbPlots.h"
#include "../lib/pbPlots-master/supportLib.h"
#include<iostream>
#include<string.h>

void plot(vector<double>size, vector<double> time, string fileName){

    ScatterPlotSettings * settings = GetDefaultScatterPlotSettings();
    settings->width = 600;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->showGrid = true;

    RGBABitmapImageReference * imageReference = CreateRGBABitmapImageReference();

    DrawScatterPlot(imageReference, 500, 500, &size, &time);


    vector<double> * pngData = ConvertToPNG(imageReference->image);
    stringstream s;
    s << "plot/" << fileName;
    string path; s >> path;
    WriteToFile(pngData, path);
    DeleteImage(imageReference->image);
}

TEST(Christofides, test_performance_christofides_increasing_node_number){
    int tries = 10; int intPoints = 5;
    vector<double> size={};
    vector<double> time={};
    for(int x = 10; x <= 100; x += 10) {
        int nNodes = (x + 1) * (x + 1);
        size.push_back(nNodes);
        DIST = 600 / x;
        Graph g = generateGridGraph(x, x);
        vector<int> ids = getRandomNodes(x, x, intPoints);
        vector<Point> route = {};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < tries; i++) {
            g.Christofides(ids, route);
            for (int i = 0; i < route.size() - 1; i++) {
                Point from = route.at(i), to = route.at(i + 1);
                g.dijkstraShortestPath(from);
                vector<Point> path = g.getPath(from, to);
/*                if(!path.empty()){
                    for(vector<Point>::iterator it = path.begin(); it != path.end(); it++)
                        cout << it->getId() << " -> ";
                    cout <<endl;
                }*/
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
        auto average = (elapsed) / tries;
        time.push_back((double) average / 1000000);
        std::cout << "Christofides processing grid " << x << " x " << x << "("<< nNodes<< " nodes)"<< " with " <<  intPoints << " interest points "<<  "average time (micro-seconds)="
        << average << std::endl;

    }

    plot(size, time, "plot_increasing_node_number.png");

}

TEST(Christofides, test_performance_christofides_increasing_number_of_interest_points){
    int tries = 10; ;
    vector<double> size={};
    vector<double> time={};
    int x = 30;
    for(int intPoints = 2; intPoints < 15; intPoints++) {
        size.push_back(intPoints);
        int nNodes = (x + 1) * (x + 1);
        DIST = 600 / x;
        Graph g = generateGridGraph(x, x);
        vector<int> ids = getRandomNodes(x, x, intPoints);
        vector<Point> route = {};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < tries; i++) {
            g.Christofides(ids, route);
            for (int i = 0; i < route.size() - 1; i++) {
                Point from = route.at(i), to = route.at(i + 1);
                g.dijkstraShortestPath(from);
                vector<Point> path = g.getPath(from, to);
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
        auto average = (elapsed) / tries;
        time.push_back((double) average / 1000000);
        std::cout << "Christofides processing grid " << x << " x " << x << "("<< nNodes<< " nodes)"<<  " with " <<  intPoints<< " interest points "<<  "average time (micro-seconds)="
                  << average << std::endl;

    }

    plot(size, time, "plot_increasing_number_interest_points.png");

}



TEST(Christofides, test_performance_christofides_increasing_both){
    int tries = 10;
    vector<double> size={};
    vector<double> time={};
    int intPoints = 2;
    for(int x = 10; x <= 100; x += 10, intPoints++) {
        int nNodes= (x + 1) * (x + 1);
        size.push_back(nNodes);
        DIST = 600 / x;
        Graph g = generateGridGraph(x, x);
        vector<int> ids = getRandomNodes(x, x, intPoints);
        vector<Point> route = {};
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < tries; i++) {
            g.Christofides(ids, route);
            for (int i = 0; i < route.size() - 1; i++) {
                Point from = route.at(i), to = route.at(i + 1);
                g.dijkstraShortestPath(from);
                vector<Point> path = g.getPath(from, to);
/*                if(!path.empty()){
                    for(vector<Point>::iterator it = path.begin(); it != path.end(); it++)
                        cout << it->getId() << " -> ";
                    cout <<endl;
                }*/
            }
        }
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
        auto average = (elapsed) / tries;
        time.push_back((double) average / 1000000);
        std::cout << "Christofides processing grid " << x << " x " << x << "("<< nNodes<< " nodes)"<< " with " <<  intPoints << " interest points "<<  "average time (micro-seconds)="
                  << average << std::endl;

    }

    plot(size, time, "plot_increasing_both.png");

}