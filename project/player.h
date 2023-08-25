#ifndef PLAYER_H
#define PLAYER_H

#include<QObject>
#include <string>

#define u_int unsigned int


#define NORMAL_PIC ""
#define POISONED_PIC ""
#define TOXIC_PIC ""
#define DEAD_PIC ""

namespace player {

    #define MAX_HEALTH 100

    enum STATUS {NORMAL, POISONED, TOXIC, DEAD};
    namespace classe {
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
            std::string getPath() const;
            STATUS getStatus() const;
            std::string getStatusString() const;
            virtual ~Player();
        public slots:
            void changeHP(int);
            void changeStatus(STATUS);
            void setDefense(u_int);
            void setAttack(u_int);
        signals:
            void statusChanged();
            void hpChanged();
            void defChanged();
            void atkChanged();
        };
    }
}

#endif // PLAYER_H