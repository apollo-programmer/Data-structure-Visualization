#ifndef SHORTESTPATHCODE_H
#define SHORTESTPATHCODE_H

#include <string>

const std::string DijkstraCode = {
    "Node cur = graph[startNode]\n"
    "cur.cost = 0\n"
    "while (cur != null)\n"
    "   for (Node adj : cur.adjs)\n"
    "       if (cur.cost + edgeWeight < adj.cost)\n"
    "           adj.cost = cur.cost + edgeWeight\n"
    "   cur.visited = true\n"
    "   cur = getMinCostNode()\n"
};

#endif