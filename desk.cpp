#include "pieces.h"

Desk::Desk() : prev_desk_state(nullptr), move_turn(true), _result(false) {
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
    desk[7][3] = new Queen(false);
    desk[7][4] = new King(false);

    for (int i = 0; i < 8; i++){
        desk[1][i] = new Pawn(true);
        desk[6][i] = new Pawn(false);
    }
    //for returning back state of desk;
    shapshot(); //copy constructor and operator
}

void Desk::shapshot(){
    if(prev_desk_state){
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                delete prev_desk_state->operator[](i)[j];
                if (desk[i][j])
                    prev_desk_state->operator[](i)[j] = desk[i][j]->clone();
                else
                    prev_desk_state->operator[](i)[j] = nullptr;
            }
        }
    }
    else
        prev_desk_state = new Desk(*this);
}

Desk::Desk(const Desk& _desk) : prev_desk_state(nullptr){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (_desk[i][j])
                this->desk[i][j] = _desk[i][j]->clone();
            else
                this->desk[i][j] = nullptr;
        }
    }
}
/*

Desk& Desk::operator=(const Desk& _desk){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (_desk[i][j])
                this->prev_desk_state->operator[](i)[j] = _desk[i][j]->clone();
            else
                this->prev_desk_state->operator[](i)[j] = _desk[i][j]->clone();
        }

    }
    return *this;
}

 Desk& Desk::operator=(Desk&& _desk){ };
 Desk::Desk(Desk&& _desk) noexcept {};
*/


void Desk::print_desk() const {

    if (!move_turn){
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

const char* Desk::get_king_coordinate(bool _turn) const{
    if (_turn)
        return white_king_coordinate;
    else
        return black_king_coordinate;
}
void Desk::set_king_coordinate(bool _turn, const char *str) {
    if (_turn){ strncpy(white_king_coordinate, str, 2); }
    else { strncpy(black_king_coordinate, str, 2); }
}


Desk::~Desk(){
    for (auto& elem1 : desk){
        for(auto& elem2 : elem1){
            delete elem2;
        }
    }
    delete prev_desk_state;
}
