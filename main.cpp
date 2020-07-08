#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

//Enumerated class to define all possible states of a cell
enum class State {kEmpty, kObstacle, kClosed};

//Function to convert cells to ascii symbol
std::string CellString(State cellState){

    std::string theCellState;
    if(cellState == State::kObstacle){ theCellState = "⛰️ ";}
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

//Function for set up of basic search
std::vector<std::vector<State>> Search (std::vector<std::vector<State>> boardGrid, int start[2], int goal[2]){

    std::cout << "No Path Found!\n";
    return std::vector<std::vector<State>> {};
}

//Function for Manhattan Distance between start and goal.
int Heuristic(int x, int y, int xi, int yi){
    return abs(xi - x), abs(yi -y);
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

