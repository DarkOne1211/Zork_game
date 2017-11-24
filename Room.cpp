#include "Room.h"
Room::Room() {}
Room::~Room() {}
void Room::setName(string name)
{
    this->name = name;
}

void Room::setStatus(string status)
{
    this->status = status;
}

void Room::setType(string type)
{
    this->type = type;
}

void Room::setDescription(string description)
{
    this->description = description;
}

void Room::setRoomBorders(int roomBorders)
{
    this->RoomBorders.push_back(roomBorders);
}

void Room::setRoomContainers(int RoomContainers)
{
    this->RoomContainers.push_back(RoomContainers);
}

void Room::setRoomItems(int RoomItems)
{
    this->RoomItems.push_back(RoomItems);
}

void Room::setRoomCreatures(int RoomCreatures)
{
    this->RoomCreatures.push_back(RoomCreatures);
}

void Room::setRoomTriggers(int Triggers) 
{
    this->RoomTriggers.push_back(Triggers);
}

void Room::setdeleted(int number)
{
    this->deleted = number;
}

string Room::getName()
{
    return this->name;
}

string Room::getStatus()
{
    return this->status;
}

string Room::getType()
{
    return this->type;
}

string Room::getDescription()
{
    return this->description;
}

vector<int> Room::getBorders()
{
    return this->RoomBorders;
}

vector<int> Room::getRoomContainers()
{
    return this->RoomContainers;
}

vector<int> Room::getRoomItems()
{
    return this->RoomItems;
}

vector<int> Room::getRoomCreatures()
{
    return this->RoomCreatures;
}

vector<int> Room::getRoomTriggers()
{
    return this->RoomTriggers;
}

int Room::getdeleted()
{
    return this->deleted;
}
