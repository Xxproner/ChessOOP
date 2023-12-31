#include "pieces.h"

void Rook::move(const char* step, const Desk& desk, bool _turn) const{
    short int div; //check stand move
    if((desk[step[4] - '1'][step[3] - 'a'] != nullptr) && (desk[step[4] - '1'][step[3] - 'a']->color() == _turn))
        throw except("not available piece track");
    if (step[0] == step[3]){ //vertical
        div = step[1] < step[4] ? 1 : -1;
        int in = step[1] + div;
        while (in != step[4]){
            if (desk[in - '1'][step[0] - 'a'] != nullptr)
                throw except("not available piece track");
            in += div;
        }

    }
    else if (step[1] == step[4]){ //gorizontal
        div = step[0] < step[3] ? 1 : -1;
        int in = step[0] + div;
        while (in != step[3]){
            if (desk[step[1] - '1'][in - 'a'] != nullptr)
                throw except("not available piece track");
            in += div;
        }
    }
    else
        throw except("not available piece track");

}
Piece* Rook::clone() const {
    Piece *rook = new Rook(this->color());
    return rook;
}
void Knight::move(const char* step,  const Desk& desk, bool _turn) const{
    if((desk[step[4] - '1'][step[3] - 'a'] != nullptr) && (desk[step[4] - '1'][step[3] - 'a']->color() == _turn))
        throw except("not available piece track");

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
}

Piece* Knight::clone() const{
    Piece* knight = new Knight(this->color());
    return knight;
}

void Bishop::move(const char* step,  const Desk& desk, bool _turn)  const{
    if((desk[step[4] - '1'][step[3] - 'a'] != nullptr) && (desk[step[4] - '1'][step[3] - 'a']->color() == _turn) ||
            (std::abs((step[0] - step[3])) != std::abs(step[1] - step[4])))
        throw except("not available piece track");

    short int xdiv, ydiv;
    xdiv = step[1] < step[4] ? 1 : -1;
    ydiv = step[0] < step[3] ? 1 : -1;
    int xin, yin; xin = step[1] + xdiv; yin = step[0] + ydiv;
    while (xin != step[4]) {
        if (desk[xin - '1'][yin - 'a'] != nullptr) {
            throw except("not available piece track");
        }
        xin += xdiv; yin += ydiv;
    }
}
Piece* Bishop::clone() const{
    Piece* bishop = new Bishop(this->color());
    return bishop;
}

void Queen::move(const char* step, const Desk& desk, bool _turn) const{
    try {
        bishop.move(step, desk, _turn); //почему-то не перехватывает исключение
    }
    catch (except& ex1) {
        try {
            rook.move(step, desk, _turn);
        }
        catch (except& ex2) {
            throw except("not available piece track");
        }
    }
}
Piece* Queen::clone() const{
    Piece* queen = new Queen(this->color());
    return queen;
}

void King::move(const char* step, const Desk& desk, bool _turn) const{
    if((desk[step[4] - '1'][step[3] - 'a'] != nullptr) && (desk[step[4] - '1'][step[3] - 'a']->color() == _turn))
        throw except("not available piece track");

    if (std::abs(step[3] - step[0]) > 1 || std::abs(step[4] - step[1]) > 1) {
        throw except("not available piece track");
    }

}
Piece* King::clone() const {
    Piece* king = new King(this->color());
    return king;
}

void Pawn::move(const char* step, const Desk& desk, bool _turn) const{
    if((desk[step[4] - '1'][step[3] - 'a'] != nullptr) && (desk[step[4] - '1'][step[3] - 'a']->color() == _turn))
        throw except("not available piece track");
    if (!_trans){
        if (_turn) {
            if (step[4] - step[1] == 1) {
                if (step[3] == step[0]) {
                    if (desk[step[4] - '1'][step[3] - 'a'] != nullptr) {
                        throw except("not available piece track");
                    }
                } else if (std::abs(step[3] - step[0]) == 1 && desk[step[4] - '1'][step[3] - 'a'] != nullptr &&
                           desk[step[4] - '1'][step[3] - 'a']->color() != desk.turn()) {

                } else {
                    throw except("not available piece track");
                }
            } else if (start_move && (step[4] - step[1]) == 2 && (step[0] == step[3])) {
                if (desk[step[4] - '1'][step[3] - 'a'] != nullptr) {
                    throw except("not available piece track");
                }
            } else {
                throw except("not available piece track");
            }
        } else {
            if (step[4] - step[1] == -1) {
                if (step[3] == step[0]) {
                    if (desk[step[4] - '1'][step[3] - 'a'] != nullptr) {
                        throw except("not available piece track");
                    }
                } else if (std::abs(step[3] - step[0]) == 1 && desk[step[4] - '1'][step[3] - 'a'] != nullptr &&
                           desk[step[4] - '1'][step[3] - 'a']->color() != desk.turn()) {

                } else {
                    throw except("not available piece track");
                }
            } else if (start_move && (step[4] - step[1]) == -2 && (step[0] == step[3])) {
                if (desk[step[4] - '1'][step[3] - 'a'] != nullptr) {
                    throw except("not available piece track");
                }
            } else {
                throw except("not available piece track");
            }
        }
    } else {
        try{
            _trans->move(step, desk, _turn);
        }
        catch(const char* ex){
            throw except("not available piece track");
        }
    }
}
Piece* Pawn::clone() const {
    Pawn* pawn = new Pawn(this->color());
    pawn->set_sign(this->sign());
    if (this->get_trans())
        pawn->reset_trans(this->get_trans()->clone());
    else
        pawn->reset_trans(nullptr);
    return pawn;
}
