#include "pieces.h"
#include <exception>
#include <map>

bool check_impossible_move(const Desk& desk);

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
    Piece *temp;
    switch (step[0]) {
        case 'R':
//        case 'r':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == desk.turn()
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'R') {  }
            else {
                throw except("not suitable piece in here");
            }
            break;
//        case 'n':
        case 'N':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == desk.turn()
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'N') {  }
            else {
                throw except("not suitable piece in here");
            }
            break;
//        case 'b':
        case 'B':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == desk.turn()
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'B') { }
            else {
                throw except("not suitable piece in here");
            }
            break;
//        case 'q':
        case 'Q':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == desk.turn()
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'Q'){  }
            else {
                throw except("not suitable piece in here");
            }
            break;
        case 'a': case 'b' : case 'c' : case 'd' : case 'e' : case 'f' : case 'g' : case 'h' :
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == desk.turn()
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'e') {  }
            else {
                throw except("not suitable piece in here");
            }
            break;
        case 'K':
//        case 'k':
            if (desk[step[2] - '1'][step[1] - 'a'] != nullptr
                && desk[step[2] - '1'][step[1] - 'a']->color() == desk.turn()
                && desk[step[2] - '1'][step[1] - 'a']->sign() == 'K') { }
            else {
                throw except("not suitable piece in here");
            }
            break;
        default :
            throw except("available piece is R, N, B, Q, K, e");
    }

    try{ //check piece track
        desk[step[2] - '1'][step[1] - 'a']->move(step + 1, desk, desk.turn());
    }
    catch(const except& ex){
        throw ex;
    }

    temp = desk[step[5] - '1'][step[4] - 'a'];
    desk[step[5] - '1'][step[4] - 'a'] = desk[step[2] - '1'][step[1] - 'a'];
    desk[step[2] - '1'][step[1] - 'a'] = nullptr;

    if (desk[step[5] - '1'][step[4] - 'a']->sign() == 'e'){
        if (step[5] == '1' || step[5] == '8') {
            bool command = true;
            std::cout << "your choice is : \n Q, N, R, B ?\n";
            while (command) {
                char e = std::getchar();
                if (e == 'Q') {
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->reset_trans(new Queen(desk.turn()));
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->set_sign('Q');
                    command = false;
                } else if (e == 'N') {
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->reset_trans(new Knight(desk.turn()));
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->set_sign('N');
                    command = false;
                } else if (e == 'R') {
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->reset_trans(new Rook(desk.turn()));
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->set_sign('R');
                    command = false;
                } else if (e == 'B') {
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->reset_trans(new Rook(desk.turn()));
                    static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->set_sign('B');
                    command = false;
                } else {
                    std::cout  << "please, choose possible piece : \n R, N, B, Q" << std::endl;
                    std::getchar();
                }
            }
        }
    }
    else if (desk[step[5] - '1'][step[4] - 'a']->sign() == 'K'){
        desk.set_king_coordinate(desk.turn(), step + 4);
    }
    desk.turn_move_turn();


    if (!check_impossible_move(desk)){ //back to last position
        desk[step[2] - '1'][step[1] - 'a'] = desk[step[5] - '1'][step[4] - 'a'];
        desk[step[5] - '1'][step[4] - 'a'] = temp;
        try{
            dynamic_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->reset_trans(nullptr);
            static_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->set_sign('e');
        }
        catch(const std::exception& ex){
            std::cout << ex.what() << std::endl;
        }
        catch(...){
            std::cout << "Unknown exception is thrown by dynamic_cast" << std::endl;
        }
        desk.turn_move_turn();
        throw except("impossible move");
    }

    delete temp;

}

bool check_impossible_move(const Desk& desk) {
    char ctemp[6];
    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((desk[i][j] != nullptr) && (desk[i][j]->color() == desk.turn())) { // step was done
                auto lambda = [&ctemp](int i, int j, const char *coordinate) -> char * {
                    std::map<int, char> map = {{1, '1'}, {2, '2'}, {3, '3'},
                                               {4, '4'}, {5, '5'}, {6, '6'},
                                               {7, '7'}, {8, '8'}};
                    ctemp[0] = static_cast<char>(i + 97);
                    ctemp[1] = map[j + 1];
                    ctemp[2] = '-';
                    std::copy(coordinate, coordinate + 2, &ctemp[3]);
                    ctemp[5] = '\0';
                    return ctemp;
                };
                try {
                    desk[i][j]->move(lambda(j, i, desk.get_king_coordinate(desk.turn()^true)), desk, desk.turn());
                    return false;
                }
                catch (const except &ex) {
                    //nothing
                }
            }
        }
    }
    return true;
}
int main(int argc, char* argv[]){
    Desk desk;
    std::cout << "LET'S START IT,\n\tGOOD LUCK FOR EVERYONE\n";
    desk.print_desk();
    /*char ctemp[6];
    auto lambda = [&ctemp](int i, int j, const char *coordinate) -> char * {
        std::map<int, char> map = {{1, '1'}, {2, '2'}, {3, '3'},
                                   {4, '4'}, {5, '5'}, {6, '6'},
                                   {7, '7'}, {8, '8'}};
        ctemp[0] = static_cast<char>(i + 97);
        ctemp[1] = map[j + 1];
        ctemp[2] = '-';
        std::copy(coordinate, coordinate + 2, &ctemp[3]);
        ctemp[5] = '\0';
        return ctemp;
    };
    for (int i = 0; i < 8 ; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((desk[i][j] != nullptr) && (desk[i][j]->color() != turn)) {
                try {
                    desk[i][j]->move(lambda(j, i, "e1"), desk, turn^true);
                    std::cerr << "impossible move";
                    return -1;
//                    throw except("impossible move"); //проблема в перехватывании исключения, оно перехватывается catch (const except& ex)
                }
                catch (const except &ex) {
                    //nothing
                }
            }
            std::cout << lambda(j, i, "e1") << '\t';
        }
        std::cout << std::endl;

    }*/
    char move_piece[7];
    while(!desk.is_mate()){
        std::cin.get(move_piece, 7);
        //std::cin.ignore(INT_MAX);
        //std::cin.clear(); std::fflush(stdin)
        try{
            check_break_frame(move_piece);
            try {
                step(move_piece, desk);

            }
            catch(except& ex){
                std::cout << ex.what() << std::endl;
            }
        }
        catch(except& ex){ //why warning
            std::cout << ex.what() << std::endl;
        }
        desk.print_desk();
        std::getchar();
    }
    return 0;
}