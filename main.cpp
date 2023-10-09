#include "pieces.h"
#include <exception>

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
            if (!strcmp(step, "0-0")) {
                if (desk.short_castling())
                    break;
            }
            else if (!strcmp(step, "0-0-0")) {
                if (desk.long_castling())
                    break;
            }
            throw except("available piece is R, N, B, Q, K, e or available castling");
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
        static_cast<Pawn*>(desk[step[5] - '1'][step[4] - 'a'])->fmove();
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
        static_cast<King*>(desk[step[5] - '1'][step[4] - 'a'])->fmove();
    }
    else if (desk[step[5] - '1'][step[4] - 'a']->sign() == 'R'){
        static_cast<King*>(desk[step[5] - '1'][step[4] - 'a'])->fmove();
    }
    desk.turn_move_turn();

    if (desk.check_influenced_square(desk.get_king_coordinate(desk.turn()^true), desk.turn())){ //back to last position
        desk[step[2] - '1'][step[1] - 'a'] = desk[step[5] - '1'][step[4] - 'a'];
        desk[step[5] - '1'][step[4] - 'a'] = temp;
        desk.turn_move_turn();

        if (dynamic_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])) {
            static_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->reset_trans(nullptr);
            static_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->set_sign('e');
            static_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->fmove();
        } else if(desk[step[2] - '1'][step[1] - 'a']->sign() == 'K') {
            desk.set_king_coordinate(desk.turn(), step);
            static_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->fmove();
        } else if (desk[step[2] - '1'][step[1] - 'a']->sign() == 'R'){
            static_cast<Pawn*>(desk[step[2] - '1'][step[1] - 'a'])->fmove();
        }

        throw except("impossible move");
    }
    delete temp;
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
            if (!(!strcmp(move_piece, "0-0") || !strcmp(move_piece, "0-0-0")))
                check_break_frame(move_piece);
            try {
                step(move_piece, desk);
                //check does this desk state define checkmate or not

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