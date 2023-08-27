#ifndef SHIELD_H
#define SHIELD_H

#include "weapon.h"

/* -- Per lettura/scrittura file JSON -- */
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class Shield : public Weapon {
private:
    u_int def;
public:
    Shield(u_int = 10, string = "unnamed_item", string = "error");
    Shield(const Shield&);
    Shield* clone() const override;
    virtual string description() const;
    u_int getDEF() const;
    static Shield fromJson(const QJsonObject&);
    QJsonObject toJson() const;
};

#endif // SHIELD_H
