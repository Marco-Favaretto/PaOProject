#ifndef ITEM_H
#define ITEM_H

#include<string>
using std::string;

class Item {
    private:
        string name;
        string path;
    public:
        Item(string = "unnamed_item", string = "error");
        virtual void effect() =0;
        virtual ~Item() =0;
};

#endif // ITEM_H
