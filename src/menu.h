//
// Created by ritaramada on 16/05/21.
//

#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include <string>
#include <iomanip>
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

void showMapOptions();

void displayMap(int map);

void chooseStart(Graph &graph, GraphViewer &gv);


#endif //UNTITLED_MENU_H