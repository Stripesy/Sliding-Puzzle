struct Puzzle {
    std::vector<char> currentState;
    int blankPos;
    int fscore, depth, heuristic;
    int cost;
    Puzzle *parent = NULL; //used to record the previous state.

    Puzzle(std::vector<char> startState) {
        currentState = startState;
        blankPos = 3;
        heuristic = heuristicFunction();
        depth = 0;
        cost = 0;
        fscore = cost + heuristic;
    }
    Puzzle(const Puzzle &puzzle) {
        currentState = puzzle.currentState;
        blankPos = puzzle.blankPos;
        depth = puzzle.depth;
        heuristic = puzzle.heuristic;
        cost = puzzle.cost;
        fscore = puzzle.fscore;
        parent = puzzle.parent;
    }
    bool operator<(const Puzzle& rhs) const;
    bool checkWin();
    std::vector<Puzzle> generateMoves();
    void printBoard();
    int heuristicFunction();
    void calcF();
};

void Puzzle::calcF() {
    heuristic = heuristicFunction();
    fscore = cost + heuristic;
}

bool Puzzle::operator<(const Puzzle& rhs) const {
    if(this->fscore != rhs.fscore)
        return (this->fscore < rhs.fscore);
    else return (this->currentState < rhs.currentState);
}

int Puzzle::heuristicFunction() { // improve this function? Does random moves until it finally gets a move that crosses a B tile.
    int wCount = 0;
    int withLeft = 0;
    //h(n): the number of White tiles on which they have at least one Black tile on their left side.
    for(int i = currentState.size()-1; i >= 0; i--) {
        if(currentState[i] == 'B') {
            withLeft += wCount;
            wCount = 0;
        }
        else if(currentState[i] == 'W') {
                wCount++; // if there is a black tile before this white tile, increase count
        }
    }
    return withLeft;
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

std::vector<Puzzle> Puzzle::generateMoves() {
    std::vector<char> tempState;
    std::vector<Puzzle> generatedMoves;
    int tempCost = 0;
    for(int i = 0; i < currentState.size(); i++) {
        if(abs(i-blankPos) <= 3 && i != blankPos) { //check if within 3 spaces as able to hop over one or two tiles.  
        if(abs(i-blankPos) == 1) {
            tempCost = 1;
        }
        else {
        tempCost = abs(i-blankPos)-1;
        }
        tempState = currentState;
        tempState[blankPos] = tempState[i];
        tempState[i] = ' ';
        Puzzle temp(tempState);
        temp.depth = 1 + depth;
        temp.blankPos = i;
        temp.cost += tempCost + cost;
        temp.calcF();
        generatedMoves.push_back(temp); // swap elements and pushback to generatedMoves vector.
        }
    }
    return generatedMoves;
}