#include "player.h"

Player::Player(u_int base, STATUS status, std::string _path, u_int _def, u_int _atk)
    : hp(base), def(_def), atk(_atk), st(status), path(_path) {
    if(!pathCorrectness()) pathCorrect();
}

Player::~Player() {}

u_int Player::getHP() const {
    return hp;
}

unsigned int Player::getAtk() const {
    return atk;
}

unsigned int Player::getDef() const {
    return def;
}

void Player::setDefense(u_int _def) {
    def = _def;
}

void Player::setAttack(u_int _atk) {
    atk = _atk;
}

STATUS Player::getStatus() const {
    return st;
}

// modifica hp del player, se hp tocca lo 0, player muore
void Player::changeHP(int _hp) {
    if(hp + _hp > 0 && hp + _hp < MAX_HEALTH) hp += _hp;
    else if(hp + _hp < 0) hp = 0;
    else hp = MAX_HEALTH;

    emit hpChanged();
    if(hp <= 0) changeStatus(DEAD);
}

// cambia lo status del player per situazioni di avvelenamento, cura e morte
void Player::changeStatus(STATUS _st) {
    st = _st;
    if(!pathCorrectness()) pathCorrect();
    emit statusChanged(_st);
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
