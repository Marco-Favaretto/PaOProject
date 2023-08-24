#ifndef ITEM_H
#define ITEM_H

#include<string>
using std::string;

#include <qobject.h>

class Item : public QObject {
    Q_OBJECT
    private:
        string name;
        string path;
        unsigned int id;
    public:
        Item(string = "unnamed_item", string = "error");
        virtual ~Item() =0;
        string getName() const;
        string getItemPath() const;
        unsigned int getID() const;
        void setID(unsigned int);
        virtual string description() const;
    public slots:
        virtual void effect() =0;
};

#endif // ITEM_H
