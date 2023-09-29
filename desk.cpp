#include "pieces.h"

Desk::Desk() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            desk[i][j] = nullptr;
        }
    }
    //white
    desk[0][0] = new Rook(true);
    desk[0][7] = new Rook(true);
    desk[0][1] = new Knight(true);
    desk[0][6] = new Knight(true);
    desk[0][2] = new Bishop(true);
    desk[0][5] = new Bishop(true);
    desk[0][3] = new Queen(true);
    desk[0][4] = new King(true);
    //black
    desk[7][0] = new Rook(false);
    desk[7][7] = new Rook(false);
    desk[7][1] = new Knight(false);
    desk[7][6] = new Knight(false);
    desk[7][2] = new Bishop(false);
    desk[7][5] = new Bishop(false);
    desk[3][3] = new Queen(false);
    desk[7][4] = new King(false);

    for (int i = 0; i < 8; i++){
        desk[1][i] = new Pawn(true);
        desk[6][i] = new Pawn(false);
    }
}

void Desk::print_desk(bool _turn) const {

    if (!_turn){
        int y = 1;
        for (int i = 0; i < 8; i++) {
            std::cout << y << ' ' <<'|';
            y++;
            for (int j = 7; j > -1; j--) {
                if (desk[i][j] != nullptr)
                    std::cout << desk[i][j]->color() << desk[i][j]->sign() << '|';
                else
                    std::cout << ' ' << ' ' << '|';
            }
            std::cout << '\n';
        }
        std::cout << "    ";
        for (char i = 'h'; i > static_cast<char>(96); i--)
            std::cout << i << "  ";
        std::cout << std::endl;
    }
    else{
        int y = 8;
        for (int i = 7; i > -1; i--) {
            std::cout << y << ' ' << '|';
            y--;
            for (int j = 0; j < 8; j++) {
                if (desk[i][j] != nullptr)
                    std::cout << desk[i][j]->color() << desk[i][j]->sign() << '|';
                else
                    std::cout << ' ' << ' ' << '|';
            }
            std::cout << '\n';
        }
        std::cout << "    ";
        for (char i = 'a'; i < 'i'; i++)
            std::cout << i << "  ";
    }
    std::cout << std::endl;
}

Desk::~Desk(){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete desk[i][j];
        }
    }
}

