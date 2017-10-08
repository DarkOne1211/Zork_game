#ifndef BORDER_H_INCLUDE
#define BORDER_H_INCLUDE

#include <iostream>

class Border 
{
    private:
        // Stores the directions to move as boolean
        // 0 - North, 1 - South, 2 - East, 3 - West
        bool direction[4] = {0, 0, 0, 0};
        
        // Stores the name of the room
        std::string name;
    
    public:
        Border();
        virtual ~Border();
        void setBorder(std::string);
        void setName(std::string);
        std::string getName();
};

#endif