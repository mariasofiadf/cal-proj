//
// Created by pedro on 25/04/21.
//

#ifndef CAL_PROJ_GRAPHVIEWERLOADER_H
#define CAL_PROJ_GRAPHVIEWERLOADER_H

//#include "Graph.h"
#include "graphviewer.h"
#include "Graph.h"

class GraphViewerLoader {
    GraphViewer* gv;

public:
    GraphViewerLoader(GraphViewer* gv);

    void loadGraph(Graph graph, int scale = 1, int thickness = 5.0, int nodeSize = 10.0);


    void colorPath(Graph graph, Point start, Point end);
};


#endif //CAL_PROJ_GRAPHVIEWERLOADER_H
