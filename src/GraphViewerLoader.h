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

    void loadGraph(Graph graph);
};


#endif //CAL_PROJ_GRAPHVIEWERLOADER_H
