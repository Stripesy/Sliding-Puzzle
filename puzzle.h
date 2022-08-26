struct Puzzle {
    std::vector<char> currentState;
    int blankPos;
    int fscore, depth, heuristic;
    Puzzle *parent = NULL; //used to record the previous state.

    Puzzle(std::vector<char> startState) {
        currentState = startState;
        blankPos = 3;
        heuristic = heuristicFunction();
        depth = 0;
        fscore = depth + heuristic;
    }
    Puzzle(const Puzzle &puzzle) {
        currentState = puzzle.currentState;
        blankPos = puzzle.blankPos;
        depth = puzzle.depth;
        heuristic = heuristicFunction();
        fscore = depth + heuristic;
        parent = puzzle.parent;
    }
    bool operator<(const Puzzle& rhs) const;
    bool checkWin();
    std::vector<Puzzle> generateMoves(int depth);
    void printBoard();
    int heuristicFunction();
    void calcF();
};

void Puzzle::calcF() {
    heuristic = heuristicFunction();
    fscore = depth + heuristic;
}

bool Puzzle::operator<(const Puzzle& rhs) const {
    if(this->fscore != rhs.fscore)
        return (this->fscore < rhs.fscore);
    else return (this->currentState < rhs.currentState);
}

int Puzzle::heuristicFunction() { // improve this function? Does random moves until it finally gets a move that crosses a B tile.
    bool isB = false;
    int wCount = 0;
    //h(n): the number of White tiles on which they have at least one Black tile on their left side.
    for(int i = 0; i < currentState.size(); i++) {
        if(currentState[i] == 'B') {
            isB = true; // sets isB to true, meaning we have found a Black tile
        }
        else if(currentState[i] == 'W') {
            if(isB) {
                wCount++; // if there is a black tile before this white tile, increase count
            }
        }
    }
    return wCount;
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
    int wCount = 0;
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

std::vector<Puzzle> Puzzle::generateMoves(int depth) {
    std::vector<char> tempState;
    std::vector<Puzzle> generatedMoves;
    for(int i = 0; i < currentState.size(); i++) {
        if(abs(i-blankPos) <= 3 && i != blankPos) { //check if within 3 spaces as able to hop over one or two tiles.  
        tempState = currentState;
        tempState[blankPos] = tempState[i];
        tempState[i] = ' ';
        Puzzle temp(tempState);
        temp.depth = 1 + depth;
        temp.calcF();
        temp.blankPos = i;
        generatedMoves.push_back(temp); // swap elements and pushback to generatedMoves vector.
        }
    }
    return generatedMoves;
}