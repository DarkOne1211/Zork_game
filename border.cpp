#include "border.h"

Border::Border()
{

}
Border::~Border(){}

void Border::setBorder(std::string direction)
{
    if(direction == "north")
        this->direction[0] = 1;
    else if(direction == "south")
        this->direction[1] = 1;
    else if(direction == "east")
        this->direction[2] = 1;
    else if(direction == "west")
        this->direction[3] = 1;
}

void Border::setName(std::string roomName)
{
    this->name = roomName;
}

std::string Border::getName()
{
    return this->name;
}

std::string Border::getBorder()
{
    if(this->direction[0] == 1)
        return "north";
    if(this->direction[1] == 1)
        return "south";
    if(this->direction[2] == 1)
        return "east";
    if(this->direction[3] == 1)
        return "west";

    return NULL;
}