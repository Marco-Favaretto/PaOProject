#include "player.h"
using namespace player;
using namespace player::classe;

Player::Player(int base, STATUS status, u_int _def, u_int _atk, const std::string& _path)
    : hp(base), def(_def), atk(_atk), st(status), path(_path) {
    if(!pathCorrectness()) pathCorrect();
}

Player::Player(const Player & pl) : hp(pl.getHP()), def(pl.getDef()), atk(pl.getAtk()), st(pl.getStatus()), path(pl.getPath()) {}

Player::~Player() {}

Player Player::fromJson(const QJsonObject &json)
{
    Player pl;
    if (const QJsonValue v = json["hp"]; v.isDouble())
        pl.hp = v.toInt();

    if (const QJsonValue v = json["status"]; v.isDouble())
        pl.st = Player::intToStatus(v.toInt());

    if (const QJsonValue v = json["def"]; v.isDouble())
        pl.atk = v.toInt();

    if (const QJsonValue v = json["atk"]; v.isDouble())
        pl.def = v.toInt();

    if(!pl.pathCorrectness()) pl.pathCorrect();

    return pl;
}

QJsonObject Player::toJson() const
{
    QJsonObject jsonobj;

    jsonobj.insert("hp", hp);
    jsonobj.insert("status", st);
    jsonobj.insert("def", static_cast<int>(getDef()));
    jsonobj.insert("atk", static_cast<int>(getAtk()));

    return jsonobj;
}

int Player::getHP() const {
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

void Player::death() {
    hp = 0;
    st = DEAD;
    if(!pathCorrectness()) pathCorrect();
    emit dead();
}

STATUS Player::getStatus() const {
    return st;
}

STATUS Player::intToStatus(int i) {
    player::STATUS _st = NORMAL;
    switch(i) {
    case 0:
        _st = NORMAL;
        break;
    case 1:
        _st = POISONED;
        break;
    case 2:
        _st = TOXIC;
        break;
    case 3:
        _st = DEAD;
        break;
    }
    return _st;
}

std::string Player::getStatusString() const {
    std::string stat = ""; 
    switch(st) {
        case NORMAL:
            stat = "NORMAL";
            break;
        case POISONED:
            stat = "POISONED";
            break;
        case TOXIC:
            stat = "TOXIC";
            break;
        case DEAD:
            stat = "DEAD";
            break;
    }
    return stat;
}

// modifica hp del player, se hp tocca lo 0, player muore
void Player::changeHP(int _hp) {
    if( (hp + _hp < MAX_HEALTH) && (hp + _hp > 0) ) {
        hp += _hp;
        if(!pathCorrectness()) pathCorrect();
        emit hpChanged();
    }
    else if ( hp + _hp >= MAX_HEALTH ) {
        hp = MAX_HEALTH;
        if(!pathCorrectness()) pathCorrect();
        emit hpChanged();
    }
    else if(hp + _hp <= 0) death();
}

// cambia lo status del player per situazioni di avvelenamento, cura e morte
void Player::changeStatus(STATUS _st) {
    if(st != _st) st = _st;
    if(!pathCorrectness()) pathCorrect();
    emit statusChanged();
}

// controlla che l'immagine assegnata sia corretta
bool Player::pathCorrectness() const {
    bool ok = false;
    switch(st) {
        case NORMAL:
            if(hp == MAX_HEALTH) ok = path == NORMAL_PIC_FULL;
            else if(hp <= MAX_HEALTH/3) ok = path == NORMAL_PIC_2;
            else ok = path == NORMAL_PIC;
            break;
        case POISONED:
            if(hp <= MAX_HEALTH/3) ok = path == POISONED_PIC_2;
            else ok = path == POISONED_PIC;
            break;
        case TOXIC:
            if(hp <= MAX_HEALTH/3) ok = path == TOXIC_PLAYER_PIC_2;
            else ok = path == TOXIC_PLAYER_PIC;
            break;
        case DEAD:
            ok = path == DEAD_PIC;
            break;
    }
    return ok;
}

// corregge errori di assegnazione dell'immagine
void Player::pathCorrect() {
    switch(st) {
        case NORMAL:
            if(hp == MAX_HEALTH) path = NORMAL_PIC_FULL;
            else if(hp <= MAX_HEALTH/3) path = NORMAL_PIC_2;
            else path = NORMAL_PIC;
            break;
        case POISONED:
            if(hp <= MAX_HEALTH/3) path = POISONED_PIC_2;
            else path = POISONED_PIC;
            break;
        case TOXIC:
            if(hp <= MAX_HEALTH/3) path = TOXIC_PLAYER_PIC_2;
            else path = TOXIC_PLAYER_PIC;
            break;
        case DEAD:
            path = DEAD_PIC;
            break;
    }
}
