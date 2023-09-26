#include "pieces.h"
bool turn = true;

void Rook::move(const char* step, Desk& desk){
    short int div; //check stand move
    if(desk[step[4] - '1'][step[3] - 'a'] != nullptr && desk[step[4] - '1'][step[3] - 'a']->color() == turn)
        throw except("not available piece track");
    if (step[0] == step[3]){ //по вертикали
        div = step[1] < step[4] ? 1 : -1;
        int in = step[1] + div;
        while (in != step[4]){
            if (desk[in][step[0]] != nullptr)
                throw except("not available piece track");
            in += div;
        }
    }
    else if (step[1] == step[4]){
        div = step[0] < step[3] ? 1 : -1;
        int in = step[1] + div;
        while (in != step[4]){
            if (desk[in][step[0]] != nullptr)
                throw except("not available piece track");
            in += div;
        }
    }
    else
        throw except("not available piece track");
}

void Knight::move(const char* step,  Desk& desk){
    if (std::abs(step[0] - step[3]) == 2){
        if (std::abs(step[1] - step[4]) != 1) {
            throw except("not available piece track");
        }
    }
    else if (std::abs(step[1] - step[4]) == 2) {
        if (std::abs(step[0] - step[3]) != 1) {
            throw except("not available piece track");
        }
    }
    else {
        throw except("not available piece track");
    }

    if (desk[step[4] - '1'][step[3] - 'a'] == nullptr || desk[step[4] - '1'][step[3] - 'a']->color() != turn){

    }
    else {
        throw except("not available piece track");
    }
}

void Bishop::move(const char* step,  Desk& desk)  {
    if (std::abs((step[0] - step[3])) != std::abs((step[1] - step[4])) ||
        (desk[step[4] - '1'][step[3] - 'a'] != nullptr && desk[step[4] - '1'][step[3] - 'a']->color() == turn)){
        throw except("not available piece track");
    }

    short int xdiv, ydiv;
    xdiv = step[1] < step[4] ? 1 : -1;
    ydiv = step[0] < step[3] ? 1 : -1;
    int xin, yin; xin = step[1] + xdiv; yin = step[0] + ydiv;
        while (xin != step[4] && yin != step[3]) {
            if (desk[xin - '1'][yin - 'a'] != nullptr) {
                throw except("not available piece track");
            }
            xin += xdiv; yin += ydiv;
        }
}

void Queen::move(const char* step, Desk& desk) {
    try {
        bishop.move(step, desk); //почему-то не перехватывает исключение
    }
    catch (except& ex1) {
        try {
            rook.move(step, desk);
        }
        catch (except& ex2) {
            throw except("not available piece track");
        }
    }
}

void King::move(const char* step, Desk& desk){
    if (std::abs(step[3] - step[0]) > 1 || std::abs(step[4] - step[1]) > 1) {
        throw except("not available piece track");
    }

    if (desk[step[4] - '1'][step[3] - 'a'] == nullptr || desk[step[4] - '1'][step[3] - 'a']->color() != turn){

    }
    else {
        throw except("not available piece track");
    }
}

void Pawn::move(const char* step,  Desk& desk) {
    if (!trans){
        if (turn) {
            if (step[4] - step[1] == 1) {
                if (step[3] == step[0]) {
                    if (desk[step[4] - '1'][step[3] - 'a'] == nullptr) {
                        start_move = false;

                    } else {
                        throw except("not available piece track");
                    }
                } else if (std::abs(step[3] - step[0]) == 1 && desk[step[4] - '1'][step[3] - 'a'] != nullptr &&
                           desk[step[4] - '1'][step[3] - 'a']->color() != turn) {
                    start_move = false;

                } else {
                    throw except("not available piece track");
                }
            } else if (start_move && (step[4] - step[1]) == 2 && (step[0] == step[3])) {
                if (desk[step[4] - '1'][step[3] - 'a'] == nullptr) {
                    start_move = false;
                } else {
                    throw except("not available piece track");
                }
            } else {
                throw except("not available piece track");
            }
        } else {
            if (step[4] - step[1] == -1) {
                if (step[3] == step[0]) {
                    if (desk[step[4] - '1'][step[3] - 'a'] == nullptr) {
                        start_move = false;

                    } else {
                        throw except("not available piece track");
                    }
                } else if (std::abs(step[3] - step[0]) == -1 && desk[step[4] - '1'][step[3] - 'a'] != nullptr &&
                           desk[step[4] - '1'][step[3] - 'a']->color() != turn) {
                    start_move = false;

                } else {
                    throw except("not available piece track");
                }
            } else if (start_move && (step[4] - step[1]) == -2 && (step[0] == step[3])) {
                if (desk[step[4] - '1'][step[3] - 'a'] == nullptr) {
                    start_move = false;
                } else {
                    throw except("not available piece track");
                }
            } else {
                throw except("not available piece track");
            }
        }
        int e;
        if (step[4] == '1' || step[4] == '8') {
            bool command = true;
            std::cout << "your choice is : \n Q, N, R, B ?\n";
            while (command) {
                e = std::getchar();
                if (e == 'Q') {
                    trans.reset(new Queen(turn));
                    _sign = 'Q';
                    command = false;
                } else if (e == 'N') {
                    trans.reset(new Knight(turn));
                    _sign = 'N';
                    command = false;
                } else if (e == 'R') {
                    trans.reset(new Rook(turn));
                    _sign = 'R';
                    command = false;
                } else if (e == 'B') {
                    trans.reset(new Rook(turn));
                    _sign = 'B';
                    command = false;
                } else {
                    std::cout  << "please, choose possible piece : \n R, N, B, Q" << std::endl;
                    std::getchar();
                }
            }
        }
    }
    else {
        try{
            trans->move(step, desk);
        }
        catch(const char* ex){
            throw except("not available piece track");
        }
    }
}

const char* Desk::get_king_coordinate(bool _turn){
    if (_turn)
        return white_king_coordinate;
    else
        return black_king_coordinate;
}
void Desk::set_king_coordinate(bool _turn, const char *str) {
    if (_turn){ strncpy(white_king_coordinate, str, 2); }
    else { strncpy(black_king_coordinate, str, 2); }
}
