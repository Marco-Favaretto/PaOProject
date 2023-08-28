#ifndef PLAYER_H
#define PLAYER_H

#include<QObject>
#include <string>

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#define u_int unsigned int

namespace player {

    #define NORMAL_PIC ":player/images/playerN.png"
    #define NORMAL_PIC_2 ":player/images/player30hp.png"
    #define NORMAL_PIC_FULL ":player/images/playerHpFull.png"
    #define POISONED_PIC ":player/images/playerV.png"
    #define POISONED_PIC_2 ":player/images/player30hpV.png"
    #define TOXIC_PLAYER_PIC ":player/images/playerT.png"
    #define TOXIC_PLAYER_PIC_2 ":player/images/player30hpT.png"
    #define DEAD_PIC ":player/images/playerD.png"
    #define MAX_HEALTH 100

    enum STATUS {NORMAL, POISONED, TOXIC, DEAD};
    namespace classe {
        class Player : public QObject {
            Q_OBJECT
        private:
            int hp;
            u_int def;
            u_int atk;
            STATUS st;
            std::string path;
            bool pathCorrectness() const;
            void pathCorrect();
            void death();
        public:
            Player(int = MAX_HEALTH, STATUS = NORMAL, u_int = 10, u_int = 10, std::string = NORMAL_PIC_FULL);
            Player(const Player&);
            int getHP() const;
            u_int getAtk() const;
            u_int getDef() const;
            std::string getPath() const;
            STATUS getStatus() const;
            static STATUS intToStatus(int);
            std::string getStatusString() const;
            virtual ~Player();
            static Player fromJson(const QJsonObject &json);
            QJsonObject toJson() const;
        public slots:
            void changeHP(int);
            void changeStatus(player::STATUS);
            void setDefense(u_int);
            void setAttack(u_int);
        signals:
            void statusChanged();
            void hpChanged();
            void defChanged();
            void atkChanged();
            void dead();
        };
    }
}

#endif // PLAYER_H
