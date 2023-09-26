#ifndef CHESS_PIECES_H
#define CHESS_PIECES_H

#include <array>
#include <iostream>
#include <memory>
#include <cstring>

struct Piece;

class Desk {
private:
    std::array<std::array<Piece*, 8>, 8> desk;
    char white_king_coordinate[3] = "e1";
    char black_king_coordinate[3] = "e8";
public:

    Desk();

    void print_desk(bool _turn) const;

    const char* get_king_coordinate(bool);
    void set_king_coordinate(bool, const char*);

    std::array<Piece*, 8>& operator[](int i){ return desk[i]; };

    ~Desk();
};

class except : public std::exception{
public:
    explicit except(const char* exception) : _exception(exception) {}

    const char* what() const noexcept override {
        return _exception;
    }
    ~except() override = default;
private:
    const char* _exception;
};

    struct Piece{
        explicit Piece(bool color) : _color(color){ };
        bool color() const { return _color; };
        virtual void move(const char* step, Desk& desk) = 0;
        virtual char sign(){ return 'o'; };
        virtual ~Piece() = default;

    protected:
        bool _color;
    };

    struct Rook : public Piece{
        explicit  Rook(bool color) : Piece(color) { };
        void move(const char* step, Desk& desk) override;
        char sign() override { return 'R'; };
        ~Rook() override = default;


    };

    struct Knight : public Piece{
        explicit Knight(bool color) : Piece(color) { };

        void move(const char* step,  Desk& desk) override;
        char sign() override { return 'N'; };
        ~Knight() override = default;

    };

    struct Bishop : public Piece{
        explicit Bishop(bool color) : Piece(color) { };

        void move(const char* step,  Desk& desk) override;
        char sign() override { return 'B'; };
        ~Bishop() override = default;


    };

    struct Queen : public Piece{
    private:
        Bishop bishop;
        Rook rook;
    public:
        explicit Queen(bool color) : Piece(color), bishop(Bishop(color)), rook(Rook(color)) { };
        void move(const char* step, Desk& desk) override;
        char sign() override { return 'Q'; };
        ~Queen() override = default;

    };

    struct Pawn : public Piece{
        explicit Pawn(bool color) : Piece(color){ };
        void move(const char* step,  Desk& desk) override;
        char sign() override { return _sign; };
        ~Pawn() override = default; //можно добавить сюда delete trans

    private:
        char _sign = 'e';
        std::unique_ptr<Piece> trans; //но я хочу умный указатель
        bool start_move = true;
    };

    struct King : public Piece{
        explicit King(bool color) : Piece(color) { };
        void move(const char* step,  Desk& desk) override ;
        char sign() override { return 'K'; };
        ~King() override = default;

    };

#endif //CHESS_PIECES_H
