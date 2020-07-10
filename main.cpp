#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

//Enumerated class to define all possible states of a cell
enum class State {kEmpty, kObstacle, kClosed, kPath};

//Function to convert cells to ascii symbol
std::string CellString(State cellState){

    std::string theCellState;
    if(cellState == State::kObstacle){ theCellState = "⛰️ ";}
    else if(cellState == State::kPath){ theCellState = "🚗   ";}
    else {theCellState = "0 ";}

    return theCellState;
}

//Function to parse each row of the read in txt board into a vector
//returns a vector for each row read in
std::vector<State> ParseLine(std::string lineToParse){

    std::vector<State> lineParsed;
    std::istringstream theStream(lineToParse);

    int x;
    char y;
    while(theStream >> x >> y){
        if(x == 0){ lineParsed.push_back(State::kEmpty);}
        else {lineParsed.push_back(State::kObstacle);}
    }

    return lineParsed;
}

//Function to read the board from the txt file,
//passes to ParseLine before returning a 2d vector
std::vector<std::vector<State> > ReadBoard(std::string boardPath){

    std::vector<std::vector<State>> theBoard {};
    std::string line;
    std::ifstream boardRow(boardPath);

    while(getline(boardRow, line)){
        std::vector<State> row = ParseLine(line);
        theBoard.push_back(row);
    }
    return theBoard;
}

//Function to Print the converted board
void PrintBoard(std::vector<std::vector<State>> printMe){

    for(int i = 0; i < printMe.size(); i++){
        for(int j = 0; j < printMe[i].size(); j++){
            std::cout << CellString(printMe[i][j]);
        }
    std::cout << "\n";
    }
}

//Function for Manhattan Distance between start and goal.
int Heuristic(int x, int y, int xi, int yi){
    return abs(xi - x), abs(yi - y);
}


void AddToOpen(int x, int y, int g, int h, std::vector<std::vector<int>> &openNodes,
                                           std::vector<std::vector<State>> &gridState){

    std::vector<int> node = {x, y, g, h};
    openNodes.push_back(node);
    gridState[x][y] = State::kClosed;

}

// Calculates the "F" value for each cell. (f=g+h)
bool CompareNodes (std::vector<int> nodeOne, std::vector<int> nodeTwo){
    if ((nodeOne[2] + nodeOne[3]) > (nodeTwo[2] + nodeTwo[3])){
        return true;
    }else{
        return false;
    }
}

//Sorts the open nodes vector
void CellSort(std::vector<std::vector<int>> *openNodes){
    std::sort(openNodes->begin(), openNodes->end(), CompareNodes);
}

//Checking if the cell is valid, not kClosed or kObstacle
bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &boardGrid){
    if(x >= 0 && x <= boardGrid[x].size()){
        if (y >= 0 && y <= boardGrid[y].size()){
            if (boardGrid[x][y] == State::kEmpty){
                return true;
            }
        }
    }else{ return false;}

    return true;
}

//Function for set up of basic A* search
std::vector<std::vector<State>> Search (std::vector<std::vector<State>> boardGrid, int start[2], int goal[2]){

    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, goal[1], goal[2]);
    std::vector<std::vector<int>> openNodes {};
    AddToOpen(x, y, g ,h, openNodes, boardGrid);

    while(!openNodes.empty()){
        CellSort(&openNodes);
        std::vector<int> currentNode = openNodes.back();
        int currentX = currentNode[0];
        int currentY = currentNode[1];
        currentNode.pop_back();
        boardGrid[currentX][currentY] = State::kPath;
        if (currentX == goal[0] && currentY == goal[1]){
            return boardGrid;
        }
    }
    std::cout << "No Path Found!\n";
    return std::vector<std::vector<State>> {};
}

int main(){
    int start[] = {0,0};
    int goal[] = {4,5};
    //Read board from board.txt
    auto board = ReadBoard("board.txt");
    //Function to search board here
    auto solution = Search(board, start, goal);
    //Prints the board
    PrintBoard(solution);
}

