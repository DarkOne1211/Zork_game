#ifndef ROOM_H_INCLUDE
#define ROOM_H_INCLUDE

#include <iostream>
#include <vector>
#include "item.h"
#include "Creature.h"
#include "border.h"
#include "Container.h"

class Room
{
    private:
        string name;
        string status;
        string type;
        string description;
        vector<Border> RoomBorders;
        vector<Container> RoomContainers;
        vector<Item> RoomItems;
        vector<Creature> RoomCreatures;
        //add triggers later
        
    public:
        Room();
        virtual ~Room();
        void setName(string);
        void setStatus(string);
        void setType(string);
        void setDescription(string);
        void setRoomBorders(Border);
        void setRoomContainers(Container);
        void setRoomItems(Item);
        void setRoomCreatures(Creature);

        string getName();
        string getStatus();
        string getType();
        string getDescription();
        vector<Border> getBorders();
        vector<Container> getRoomContainers();
        vector<Item> getRoomItems();
        vector<Creature> getRoomCreatures();
};

#endif