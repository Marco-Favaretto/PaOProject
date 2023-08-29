#ifndef ITEM_H
#define ITEM_H

#include<string>
using std::string;

#include <qobject.h>

#define DEFAULTPIC ":/consumabili/images/defaultItem.png"

class Item : public QObject {
    Q_OBJECT
    private:
        string name;
        string path;
        unsigned int id;
    public:
        Item(const string& = "unnamed_item", const string& = DEFAULTPIC);
        Item(const Item&);
        virtual ~Item() =0;
        virtual Item* clone() const =0;
        string getName() const;
        string getItemPath() const;
        unsigned int getID() const;
        void setID(unsigned int);
        void setPath(const string&);
        void setName(const string&);
        virtual string description() const;
    public slots:
        virtual void effect() =0;
};

#endif // ITEM_H
