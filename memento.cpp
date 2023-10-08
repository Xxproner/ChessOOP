
/*
 * #include "pieces.h"
Memento::Memento(const std::array<std::array<Piece*, 8>, 8>& desk) {
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

//CareTaker
void CareTaker::back_up(){
    _memento = _desk->save();
}
void CareTaker::Undo() {
    if (!_memento){
        return;
    }
    try{
        _desk->restore(_memento);
    }
    catch(...){
        Undo();
    }
}*/
