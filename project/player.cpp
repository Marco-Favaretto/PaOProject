#include "player.h"

Player::Player(u_int base, STATUS status, std::string _path) : hp(base), st(status), path(_path) {
    if(!pathCorrectness()) pathCorrect();
}

Player::~Player() {}

u_int Player::getHP() const {
    return hp;
}

STATUS Player::getStatus() const {
    return st;
}

// modifica hp del player, se hp tocca lo 0, player muore
void Player::changeHP(int _hp) {
    hp += _hp;
    if(hp <= 0) changeStatus(DEAD);
}

// cambia lo status del player per situazioni di avvelenamento, cura e morte
void Player::changeStatus(STATUS _st) {
    st = _st;
    emit statusChange(_st);
    if(!pathCorrectness()) pathCorrect();
}

// controlla che l'immagine assegnata sia corretta
bool Player::pathCorrectness() const {
    switch(st) {
        case NORMAL:
            return path == NORMAL_PIC;
            break;
        case POISONED:
            return path == POISONED_PIC;
            break;
        case DEAD:
            return path == DEAD_PIC;
            break;
    }
}

// corregge errori di assegnazione dell'immagine
void Player::pathCorrect() {
    switch(st) {
        case NORMAL:
            path = NORMAL_PIC;
            break;
        case POISONED:
            path = POISONED_PIC;
            break;
        case DEAD:
            path = DEAD_PIC;
            break;
    }
}
