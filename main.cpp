#include "pieces.h"
#include <exception>
#include <map>

bool _result = false;
extern bool turn;

void check_impossible_move(const char *step, Desk &desk);

//const char* operator+ (char*) - white operator char* + char*
inline void check_break_frame(const char* step){
    if (step[1] > 'h' || step[1] < 'a' ||
        step[4] > 'h' || step[4] < 'a' ||
        step[2] < '1' || step[2] > '8' ||
        step[5] < '1' || step[5] > '8') {
            throw except("violation of the desk frame");
    }
}

void step(const char* step, Desk& desk) {
    switch (step[0]) {
        case 'R':
//        case 'r':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == turn
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'R') {  }
            else {
                throw except("not suitable piece in here");
            }
            break;
//        case 'n':
        case 'N':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == turn
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'N') {  }
            else {
                throw except("not suitable piece in here");
            }
            break;
//        case 'b':
        case 'B':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == turn
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'B') { }
            else {
                throw except("not suitable piece in here");
            }
            break;
//        case 'q':
        case 'Q':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == turn
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'Q'){  }
            else {
                throw except("not suitable piece in here");
            }
            break;
            case 'a': case 'b' : case 'c' : case 'd' : case 'e' : case 'f' : case 'g' : case 'h' :
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == turn
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'e') {  }
            else {
                throw except("not suitable piece in here");
            }
            break;
        case 'K':
//        case 'k':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == turn
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'K') { }
            else {
                throw except("not suitable piece in here");
            }
            break;
        default :
            throw except("available piece is R, N, B, Q, K, e");
        }
        try{
            desk[step[2] - '1'][step[1] - 'a']->move(step + 1, desk);
            check_impossible_move(step, desk);
            //проверка на невозможный ход, если ты открыл короля или
            //не убрал короля из-под шаха
        }
        catch(except& ex){
            throw ex;
        }
}

void check_impossible_move(const char *step, Desk& desk) {
    int check_count = 0;
    char ctemp[6];
    Piece* temp = desk[step[5] - '1'][step[4] - 'a'];
    desk[step[5] - '1'][step[4] - 'a'] = desk[step[2] - '1'][step[1] - 'a'];
    desk[step[2] - '1'][step[1] - 'a'] = nullptr;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (desk[i][j] != nullptr && desk[i][j]->color() != turn) {
                auto lambda = [&ctemp](int j, int i, const char *coordinate) -> const char * {
                    std::map<int, char> map = {{1, '1'}, {2, '2'}, {3, '3'},
                                               {4, '4'}, {5, '5'}, {6, '6'},
                                               {7, '7'}, {8, '8'}};
                    ctemp[0] = static_cast<char>(j + 97);
                    ctemp[1] = map[i + 1];
                    ctemp[2] = '-';
                    std::copy(coordinate, coordinate + 2, &ctemp[3]);
                    ctemp[5] = '\0';
                    return ctemp;
                };
                try {
                    desk[i][j]->move(lambda(j, i, desk.get_king_coordinate(turn)), desk);
                    check_count++;
                }
                catch (except &ex) {
                    //nothing
                }
            }
        }
    }
    if (check_count){
        desk[step[2] - '1'][step[1] - 'a'] = desk[step[5] - '1'][step[4] - 'a'];
        desk[step[5] - '1'][step[4] - 'a'] = temp;
        throw except("impossible move");
    }
    delete temp;

}
int main(int argc, char* argv[]){
    Desk desk;
    std::cout << "LET'S START IT,\n\tGOOD LUCK FOR EVERYONE\n";
    desk.print_desk(turn);
    char move_piece[7];
    while(!_result){
        std::cin.get(move_piece, 7);
        //std::cin.ignore(INT_MAX);
        //std::cin.clear(); std::fflush(stdin)
        try{
            check_break_frame(move_piece);
            try {
                step(move_piece, desk);
                turn ^= true;

            }
            catch(except& ex){
                std::cout << ex.what() << std::endl;
            }
        }
        catch(except& ex){ //why warning
            std::cout << ex.what() << std::endl;
        }
        desk.print_desk(turn);
        std::getchar();
    }
    return 0;
}