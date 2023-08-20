#ifndef PLAYER_H
#define PLAYER_H

#include<QObject>
#include <string>

#define u_int unsigned int

#define MAX_HEALTH 100

#define NORMAL_PIC ""
#define POISONED_PIC ""
#define DEAD_PIC ""

enum STATUS {NORMAL, POISONED, DEAD};

class Player : public QObject {
    Q_OBJECT
    private:
        u_int hp;
        u_int def;
        u_int atk;
        STATUS st;
        std::string path;
        bool pathCorrectness() const;
        void pathCorrect();
    public:
        Player(u_int = MAX_HEALTH, STATUS = NORMAL, std::string = NORMAL_PIC, u_int = 10, u_int = 10);
        u_int getHP() const;
        u_int getAtk() const;
        u_int getDef() const;
        STATUS getStatus() const;
        virtual ~Player();
    public slots:
        void changeHP(int);
        void setDefense(u_int);
        void setAttack(u_int);
        void changeStatus(STATUS);
    signals:
        void statusChanged(STATUS);
        void hpChanged();
};

#endif // PLAYER_H
