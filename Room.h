#ifndef ROOM_H_INCLUDE
#define ROOM_H_INCLUDE

#include <iostream>
#include <vector>
#include "item.h"
#include "Creature.h"
#include "border.h"
#include "Container.h"
#include "Trigger.h"

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
        vector<int> RoomTriggers;
        int deleted = 0;
        
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
        void setRoomTriggers(int);
        void setdeleted();

        string getName();
        string getStatus();
        string getType();
        string getDescription();
        vector<int> getBorders();
        vector<int> getRoomContainers();
        vector<int> getRoomItems();
        vector<int> getRoomCreatures();
        vector<int> getRoomTriggers();
        int getdeleted();
};

#endif