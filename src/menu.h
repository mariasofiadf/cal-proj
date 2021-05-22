//
// Created by ritaramada on 16/05/21.
//

#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include <string>
#include <vector>
#include "GraphViewerLoader.h"
#include <graphviewer.h>
#include "GraphLoader.h"
#include "utils.h"

#define WIDTH 1920
#define HEIGHT 1080
/*enum Map{
    quatro,
    oito,
    Maia,
    Porto
};*/
void initialMenu();

void displayMap(int map);

void choosePoints(Graph  * graph, GraphViewer &gv, GraphViewerLoader &gvl);

int chooseOptimization(Graph * graph, Point * destiny);

void chooseTasks(Graph * graph);

#endif //UNTITLED_MENU_H
