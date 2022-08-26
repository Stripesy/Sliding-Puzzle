struct Puzzle {
    std::vector<char> currentState;
    int blankPos;
    int fscore, depth, heuristic;
    Puzzle *parent = NULL; //used to record the previous state.

    Puzzle(std::vector<char> startState) {
        currentState = startState;
        blankPos = 2;
    }
    Puzzle(const Puzzle &puzzle) {
        currentState = puzzle.currentState;
        blankPos = puzzle.blankPos;
        fscore = puzzle.fscore;
        depth = puzzle.depth;
        heuristic = puzzle.heuristic;
        parent = puzzle.parent;
    }
    bool operator<(const Puzzle& rhs) const;
    bool checkWin();
    std::vector<Puzzle> generateMoves();
    void printBoard();
};

bool Puzzle::operator<(const Puzzle& rhs) const {
    if(this->fscore != rhs.fscore)
        return !(this->fscore < rhs.fscore);
    else return !(this->currentState < rhs.currentState);
}

void Puzzle::printBoard() {
    for(int i = 0; i < currentState.size(); i++) {
        if(i == 0) {
            std::cout << "-----------------------------\n";
            std::cout << "| ";
        }
        std::cout <<currentState[i] << " | ";
        if(i == currentState.size()-1) {
            std::cout << "\n-----------------------------\n\n";
        }
    }
}

bool Puzzle::checkWin() {
    int wCount;
    for(int i = 0; i < currentState.size(); i++) {
        if(currentState[i] == 'W') {
            wCount++;
        }
        if(currentState[i] == 'B') {
            return false;
        }
        if(wCount == 3) {
        return true;
        }
    }
    return false;
}

std::vector<Puzzle> Puzzle::generateMoves() {
    std::vector<char> tempState;
    std::vector<Puzzle> generatedMoves;
    for(int i = 0; i < currentState.size(); i++) {
        if(abs(i-blankPos) <= 3 && i != blankPos) { //check if within 3 spaces as able to hop over one or two tiles.  
        tempState = currentState;
        tempState[blankPos] = tempState[i];
        tempState[i] = ' ';
        Puzzle temp(tempState);
        generatedMoves.push_back(temp); // swap elements and pushback to generatedMoves vector.
        }
    }
    return generatedMoves;
}