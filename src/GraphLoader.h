//
// Created by pedro on 26/04/21.
//

#ifndef CAL_PROJ_GRAPHLOADER_H
#define CAL_PROJ_GRAPHLOADER_H



#include "Graph.h"

//To get sqlite3.h:
//      ~$ sudo apt-get install sqlite3
//      ~$ sudo apt-get install libsqlite3-dev
#include <sqlite3.h>

class GraphLoader {
    Graph graph;

public:
    GraphLoader(const Graph &graph) : graph(graph) {}

    void loadMap(string filename);
};


#endif //CAL_PROJ_GRAPHLOADER_H
