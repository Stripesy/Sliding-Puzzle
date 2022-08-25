class Puzzle {
    std::vector<char> currentState;
    int blankPos;
    public:
    Puzzle() {
        currentState = {'B', 'B', 'B', ' ', 'W', 'W', 'W'};
        blankPos = 2;
    }

    bool checkWin();
    std::vector<std::vector<char>> generateMoves();
};

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

std::vector<std::vector<char>> Puzzle::generateMoves() {
    std::vector<char> tempState;
    std::vector<std::vector<char>> generatedMoves;
    for(int i = 0; i < currentState.size(); i++) {
        if(abs(i-blankPos) <= 3 && i != blankPos) { //check if within 3 spaces as able to hop over one or two tiles.  
        tempState = currentState;
        tempState[blankPos] = tempState[i];
        tempState[i] = ' ';
        generatedMoves.push_back(tempState); // swap elements and pushback to generatedMoves vector.
        }
    }
    return generatedMoves;
}