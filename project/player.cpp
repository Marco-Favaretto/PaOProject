#include "player.h"
using namespace player;
using namespace player::classe;

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

std::string Player::getPath() const {
    return path;
}

void Player::setDefense(u_int _def) {
    def = _def;
    emit defChanged();
}

void Player::setAttack(u_int _atk) {
    atk = _atk;
    emit atkChanged();
}

STATUS Player::getStatus() const {
    return st;
}

std::string Player::getStatusString() const {
    switch(st) {
        case NORMAL:
            return "NORMAL";
            break;
        case POISONED:
            return "POISONED";
            break;
        case TOXIC:
            return "TOXIC";
            break;
        case DEAD:
            return "DEAD";
            break;
    }
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
    if(st != _st) st = _st;
    if(!pathCorrectness()) pathCorrect();
    emit statusChanged();
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
        case TOXIC:
            return path == TOXIC_PIC;
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
        case TOXIC:
            path = TOXIC_PIC;
            break;
        case DEAD:
            path = DEAD_PIC;
            break;
    }
}
