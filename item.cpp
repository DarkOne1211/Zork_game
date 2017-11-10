#include "item.h"

Item::Item() {}
Item::~Item() {}

void Item::setName(std::string name)
{
    this->name = name;
}

void Item::setStatus(std::string status)
{
    this->status = status;
}

void Item::setDescription(std::string description)
{
    this->description = description;
}

void Item::setWriting(std::string writing)
{
    this->writing = writing;
}

void Item::setTurnon(std::string turnon)
{
    this->turnon.push_back(turnon);
}

void Item::setItemTrigger(int trigger)
{
    this->itemTrigger.push_back(trigger);
}

void Item::setdeleted()
{
    this->deleted = 1;
}

std::string Item::getName()
{
    return this->name;
}

std::string Item::getStatus()
{
    return this->status;
}

std::string Item::getDescription()
{
    return this->description;
}

std::string Item::getWriting()
{
    return this->writing;
}

std::vector<std::string> Item::getTurnon()
{
    return this->turnon;
}

std::vector<int> Item::getItemTrigger()
{
    return this->itemTrigger;
}

int Item::getdeleted()
{
    return this->deleted;
}