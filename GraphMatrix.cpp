#include "GraphMatrix.hpp"

GraphMatrix::GraphMatrix(int numV, GType type) 
    // TODO
     : Graph(numV, 0, type)          // pass numV, 0 edges, and type to base class
{
    // Allocate the 2D dynamic array
    adjMatrix = new bool*[v];
    for (int i = 0; i < v; ++i) {
        adjMatrix[i] = new bool[v];
        // Initialize all entries to false (no edges)
        for (int j = 0; j < v; ++j) {
            adjMatrix[i][j] = false;
        }
    }
}

GraphMatrix::~GraphMatrix() {
    // TODO
    if (adjMatrix != nullptr) {
        for (int i = 0; i < v; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
        adjMatrix = nullptr;
    }
}

bool GraphMatrix::isEdge(int i, int j) const {
    // TODO
   if (i < 0 || i >= v || j < 0 || j >= v) {
        return false;
    }
    return adjMatrix[i][j];  
}

ostream& GraphMatrix::print(ostream& os) const {
    os << "    ";
    for (int i = 0; i < v; i++) {
        os << i << ' ';
    }
    os << endl;

    os << "---";
    for (int i = 0; i < v; i++) {
        os << "--";
    }
    os << endl;

    for (int i = 0; i < v; i++) {
        os << i << " | ";
        for (int j = 0; j < v; j++) {
            os << adjMatrix[i][j] << ' ';
        }
        os << endl;
    }

    return os;
}

void GraphMatrix::toggleEdge(int i, int j) {
    // TODO
    if (i < 0 || i >= v || j < 0 || j >= v) {
        return; // invalid vertices, do nothing
    }

    if (graphType == UNDIRECTED) {
        // Undirected graph: matrix is symmetric
        bool currentlyEdge = adjMatrix[i][j];   // same as adjMatrix[j][i]

        if (currentlyEdge) {
            // Remove edge
            adjMatrix[i][j] = false;
            adjMatrix[j][i] = false;
            e--;    // one undirected edge removed
        } else {
            // Add edge
            adjMatrix[i][j] = true;
            adjMatrix[j][i] = true;
            e++;    // one undirected edge added
        }
    }
    else { // DIRECTED
        bool currentlyEdge = adjMatrix[i][j];

        if (currentlyEdge) {
            // Remove directed edge i -> j
            adjMatrix[i][j] = false;
            e--;    // one directed edge removed
        } else {
            // Add directed edge i -> j
            adjMatrix[i][j] = true;
            e++;    // one directed edge added
        }
    }
}
