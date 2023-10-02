#include "pieces.h"

Memento::Memento(const Desk& desk) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (desk[i][j] != nullptr){
//                _desk[i][j] = new std::remove_reference<decltype(*desk[i][j])>::type();
            }
            else
                _desk[i][j] = nullptr;
        }
    }
}
Memento::~Memento(){
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete _desk[i][j];
        }
    }
}