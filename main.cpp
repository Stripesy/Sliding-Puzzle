#include<iostream>
#include<vector>
#include<set>

#include "puzzle.h"

Puzzle aStar(Puzzle puzzle);
void printPath(Puzzle *puzzle);

int main() {
    Puzzle puzzle({'B', 'B', 'B', ' ', 'W', 'W', 'W'});
    puzzle = aStar(puzzle);

}

void printPath(Puzzle *puzzle) {
    if(puzzle->parent == NULL) {
        return;
    }
    else {
        printPath(puzzle->parent);
        puzzle->printBoard();

    }    
}

Puzzle aStar(Puzzle puzzle) {
    std::set<Puzzle> openSet, closedSet;
    Puzzle current = puzzle;
    openSet.insert(current);
    
    while(!openSet.empty()) {
        current = *openSet.begin();
        openSet.erase(openSet.begin()); 

        if(current.checkWin()) {
            std::cout << "Solution found in : " << current.depth;
            return puzzle;
        }

        Puzzle temp(current);

        std::vector<Puzzle> generatedMoves = puzzle.generateMoves();

        for(int i = 0; i < generatedMoves.size(); i++) {
            if((openSet.find(temp) != openSet.end()) || (openSet.find(temp) != openSet.end() && (openSet.find(temp)->fscore < temp.fscore))) { 
                // check if temp is in open set or better fscore
                continue;
            }
            else if((closedSet.find(temp) != closedSet.end()) || (closedSet.find(temp) != closedSet.end() && (closedSet.find(temp)->fscore < temp.fscore))) { 
                // check if in closed set or better fscore
                continue;
            }
            else {
                temp.parent = new Puzzle(current);
                openSet.insert(temp);
            }
            closedSet.insert(current);
        }
    }
    return puzzle; // search failed.
}