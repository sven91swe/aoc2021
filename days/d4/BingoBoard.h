#include <string>
#include <vector>

struct location {
    unsigned int value;
    bool checked;
};

class BingoBoard {
   public:
    BingoBoard(std::vector<std::vector<int>> input);
    BingoBoard(const BingoBoard& in);
    void checkNumber(unsigned int n);
    bool hasWon();
    unsigned int score();
    void printBoard();

   private:
    std::vector<std::vector<location>> boardState;
};

BingoBoard::BingoBoard(std::vector<std::vector<int>> input) {
    for (auto row : input) {
        std::vector<location> boardStateRow;
        for (int place : row) {
            location p;
            p.value = place;
            p.checked = false;
            boardStateRow.emplace_back(p);
        }
        boardState.emplace_back(boardStateRow);
    }
}

BingoBoard::BingoBoard(const BingoBoard& in) { boardState = in.boardState; }

void BingoBoard::checkNumber(unsigned int n) {
    for (auto& row : boardState) {
        for (auto& place : row) {
            place.checked |= place.value == n;
        }
    }
}

bool BingoBoard::hasWon() {
    // Check row
    for (auto& row : boardState) {
        bool allChecked = true;
        for (auto& place : row) {
            allChecked &= place.checked;
        }
        if (allChecked) {
            return true;
        }
    }
    // Check column
    for (size_t j = 0; j < boardState.at(0).size(); j++) {
        bool allChecked = true;
        for (size_t i = 0; i < boardState.size(); i++) {
            allChecked &= boardState.at(i).at(j).checked;
        }
        if (allChecked) {
            return true;
        }
    }
    return false;
}

unsigned int BingoBoard::score() {
    unsigned int score = 0;
    for (auto row : boardState) {
        for (auto place : row) {
            if (!place.checked) {
                score += place.value;
            }
        }
    }
    return score;
}

void BingoBoard::printBoard() {
    for (auto row : boardState) {
        for (auto place : row) {
            std::cout << place.value << " ";
        }
        std::cout << std::endl;
    }
}