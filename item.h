#ifndef ITEM_H_INCLUDE
#define ITEM_H_INCLUDE

#include <iostream>
#include <vector>

class Item
{
    private:
        std::string name;
        std::string status;
        std::string description;
        std::string writing;
        std::vector<std::string> turnon;
        int deleted = 0;

    public:
        std::vector<int> itemTrigger;
        Item();
        virtual ~Item();
        void setName(std::string);
        void setStatus(std::string);
        void setDescription(std::string);
        void setWriting(std::string);
        void setTurnon(std::string);
        void setItemTrigger(int);
        void setdeleted(int);

        std::string getName();
        std::string getStatus();
        std::string getDescription();
        std::string getWriting();
        std::vector<std::string> getTurnon();
        std::vector<int> getItemTrigger();
        int getdeleted();
};

#endif