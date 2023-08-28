#ifndef REGULAR_H
#define REGULAR_H

#include "weapon.h"

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class Regular : public Weapon {
public:
    Regular(u_int = 10, string = "unnamed_item", string = "error");
    Regular(const Regular&);
    Regular* clone() const override;
    virtual string description() const;
    u_int getATK() const;
    static Regular fromJson(const QJsonObject&);
    QJsonObject toJson() const;
};

#endif // REGULAR_H
