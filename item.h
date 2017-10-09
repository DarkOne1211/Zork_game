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
        // add trigger later
    public:
        Item();
        virtual ~Item();
        void setName(std::string);
        void setStatus(std::string);
        void setDescription(std::string);
        void setWriting(std::string);
        void setTurnon(std::string);
        
        std::string getName();
        std::string getStatus();
        std::string getDescription();
        std::string getWriting();
        std::vector<std::string> getTurnon();
};

#endif