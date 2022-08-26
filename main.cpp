#include <iostream>
#include <vector>
#include <set>
#include <algorithm> 

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

        std::vector<Puzzle> generatedMoves = current.generateMoves();

        for(int i = 0; i < generatedMoves.size(); i++) {

            Puzzle temp(generatedMoves[i]);

            std::set<Puzzle>::iterator it;

            // check for matching state
            it = std::find_if(std::begin(openSet), std::end(openSet), [&] (Puzzle const& p) {return p.currentState == temp.currentState;});

            if(it != openSet.end() && (it->fscore <= temp.fscore)) { 
                // check if temp is in open set or better fscore
                continue;
            }
            // check for matching state
            it = std::find_if(std::begin(closedSet), std::end(closedSet), [&] (Puzzle const& p) {return p.currentState == temp.currentState;});
            if(it != closedSet.end() && (it->fscore <= temp.fscore)) {
                // check if in closed set or better fscore
                continue;
            }
            else {
                temp.parent = new Puzzle(current);
                openSet.insert(temp);
            }
        }
        closedSet.insert(current);
    }
    return puzzle; // search failed.
}