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
        vector<int> RoomBorders;
        vector<int> RoomContainers;
        vector<int> RoomItems;
        vector<int> RoomCreatures;
        //add triggers later
        
    public:
        Room();
        virtual ~Room();
        void setName(string);
        void setStatus(string);
        void setType(string);
        void setDescription(string);
        void setRoomBorders(int);
        void setRoomContainers(int);
        void setRoomItems(int);
        void setRoomCreatures(int);

        string getName();
        string getStatus();
        string getType();
        string getDescription();
        vector<int> getBorders();
        vector<int> getRoomContainers();
        vector<int> getRoomItems();
        vector<int> getRoomCreatures();
};

#endif