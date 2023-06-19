#include "player.h"

Player::Player(u_int base, STATUS status, std::string _path) : hp(base), st(status), path(_path) {
    if(!pathCorrectness()) pathCorrect();
}

u_int Player::getHP() const {
    return hp;
}

STATUS Player::getStatus() const {
    return st;
}

void Player::changeHP(int _hp) {
    hp += _hp;
    if(hp <= 0) changeStatus(DEAD);
}

void Player::changeStatus(STATUS _st) {
    st = _st;
    if(!pathCorrectness()) pathCorrect();
}

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
