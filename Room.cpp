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

void Room::setRoomBorders(Border roomBorders)
{
    this->RoomBorders.push_back(roomBorders);
}

void Room::setRoomContainers(Container RoomContainers)
{
    this->RoomContainers.push_back(RoomContainers);
}

void Room::setRoomItems(Item RoomItems)
{
    this->RoomItems.push_back(RoomItems);
}

void Room::setRoomCreatures(Creature RoomCreatures)
{
    this->RoomCreatures.push_back(RoomCreatures);
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

vector<Border> Room::getBorders()
{
    return this->RoomBorders;
}

vector<Container> Room::getRoomContainers()
{
    return this->RoomContainers;
}

vector<Item> Room::getRoomItems()
{
    return this->RoomItems;
}

vector<Creature> Room::getRoomCreatures()
{
    return this->RoomCreatures;
}