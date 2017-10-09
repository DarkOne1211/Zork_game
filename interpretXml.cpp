// NOTE - TRIGGER OBJECTS NOT ADDED AND INTERPRETED (REMOVE COMMENT ONCE ADDED)
#include "main.h"
#include "interpretXml.h"
#include "Room.h"

using namespace std;
using namespace rapidxml;
Item* findItemAddress(vector<Item>, string);
Container* findContainerAddress(vector<Container>, string);
Creature* findCreatureAddress(vector<Creature>, string);
void printRoom(vector<Room>);

void interpretXmlString(std::string gameXml)
{
    // THIS FUNCTION INTERPRETS THE XML FILE AND CREATES THE
    // REQUIRED OBJECTS ACCORDINGLY

    // Parsing the xml string into an object named doc
    std::vector<char> xml_copy(gameXml.begin(), gameXml.end());
    xml_copy.push_back('\0');
    xml_document<> doc;
    doc.parse<0>(&xml_copy[0]);
    
    // Declaring variables for all major objects
    xml_node<>* map = doc.first_node("map");
    xml_node<>* room = map->first_node("room");
    xml_node<>* item = map->first_node("item");
    xml_node<>* creature = map->first_node("creature");
    xml_node<>* container = map->first_node("container");

    // Stores the items, creatures, containers and rooms
    vector<Room> allRooms;
    vector<Item> allItems;
    vector<Creature> allCreatures;
    vector<Container> allContainers;
    vector<Border> allBorders;

    // Reading the xml file and creating item object
    while(item != NULL)
    {
        Item newItem;
        newItem.setName(item->first_node("name")->value());
        
        if (item->first_node("status") != NULL)
            newItem.setStatus(item->first_node("status")->value());
        
        if(item->first_node("description") != NULL)
            newItem.setDescription(item->first_node("description")->value());
        
        if(item->first_node("writing") != NULL)
            newItem.setWriting(item->first_node("writing")->value());
        
        if(item->first_node("turnon") != NULL)
        {
            xml_node<>* turnon = item->first_node("turnon");
            while(turnon != NULL)
            {
                newItem.setTurnon(turnon->first_node()->value());
                turnon = turnon->first_node()->next_sibling();
            }
        }

        allItems.push_back(newItem);
        item = item->next_sibling("item");
    }

    // Reading the xml file and creating the container object
    while(container != NULL)
    {
        Container newContainer;
        newContainer.setName(container->first_node("name")->value());
        
        if(container->first_node("status") != NULL)
            newContainer.setStatus(container->first_node("status")->value());
    
        if(container->first_node("description") != NULL)
            newContainer.setDescription(container->first_node("description")->value());

        if(container->first_node("accept") != NULL)
        {
            xml_node<>* accept = container->first_node("accept");
            while(accept != NULL)
            {
                newContainer.setAccept(accept->first_node()->value());
                accept = accept->first_node()->next_sibling();
            }
        }
        
        if(container->first_node("item") != NULL)
        {
            xml_node<>* ContainerItems = container->first_node("item");
            while(ContainerItems != NULL)
            {
                Item* newContainerItem = findItemAddress(allItems, ContainerItems->value());
                newContainer.setContainerItems(newContainerItem);
                ContainerItems = ContainerItems->next_sibling("item");
            }
        }

        allContainers.push_back(newContainer);
        container = container->next_sibling("container");
    }

    // Read the xml file and creating the creature objects
    while(creature != NULL)
    {
        Creature newCreature;
        newCreature.setName(creature->first_node("name")->value());

        if(creature->first_node("status") != NULL)
            newCreature.setStatus(creature->first_node("status")->value());

        if(creature->first_node("description") != NULL)
            newCreature.setDescription(creature->first_node("description")->value());
                    
        if(creature->first_node("vulnerability") != NULL)
        {
            xml_node<>* vulnerability = creature->first_node("vulnerability");
            while(vulnerability != NULL)
            {
                newCreature.setVulnerability(vulnerability->first_node()->value());
                vulnerability = vulnerability->next_sibling("vulnerability");
            }
        }

        if(creature->first_node("attack") != NULL)
        {
            xml_node<>* attack = creature->first_node("attack");
            while(attack != NULL)
            {
                newCreature.setAttackActions(attack->first_node()->value());
                attack = attack->first_node()->next_sibling();
            }
        }

        allCreatures.push_back(newCreature);
        creature = creature->next_sibling("creature");
    }

    // Reading the xml file and creating the Room object
    while(room != NULL)
    {
        Room newRoom;
        newRoom.setName(room->first_node("name")->value());

        if(room->first_node("status") != NULL)
            newRoom.setStatus(room->first_node("status")->value());
        
        if(room->first_node("type") != NULL)
            newRoom.setType(room->first_node("type")->value());
        
        if(room->first_node("description") != NULL)
            newRoom.setDescription(room->first_node("description")->value());
        
        if(room->first_node("border") != NULL)
        {
            xml_node<>* borders = room->first_node("border");
            while(borders != NULL)
            {
                Border newBorder;
                newBorder.setBorder(borders->first_node("direction")->value());
                newBorder.setName(borders->first_node("name")->value());
                borders = borders->next_sibling("border");
                allBorders.push_back(newBorder);
                newRoom.setRoomBorders(&(allBorders.back()));
            }
        }

        if(room->first_node("container") != NULL)
        {
            xml_node<>* RoomContainer = room->first_node("container");
            while(RoomContainer != NULL)
            {
                Container* newRoomContainer = findContainerAddress(allContainers, RoomContainer->value());
                newRoom.setRoomContainers(newRoomContainer);
                RoomContainer = RoomContainer->next_sibling("container");
            }  
        }

        if(room->first_node("item") != NULL)
        {
            xml_node<>* RoomItems = room->first_node("item");
            while(RoomItems != NULL)
            {
                Item* newRoomItem = findItemAddress(allItems, RoomItems->value());
                newRoom.setRoomItems(newRoomItem);
                RoomItems = RoomItems->next_sibling("item");
            }  
        }

        if(room->first_node("creature") != NULL)
        {
            xml_node<>* RoomCreatures = room->first_node("creature");
            while(RoomCreatures != NULL)
            {
                Creature* newRoomCreature = findCreatureAddress(allCreatures, RoomCreatures->value());
                newRoom.setRoomCreatures(newRoomCreature);
                RoomCreatures = RoomCreatures->next_sibling("creature");
            }  
        }

        allRooms.push_back(newRoom);
        room = room->next_sibling("room");
    }

    // TESING IF THE XML HAS BEEN READ PROPERLY(COMMENT OUT WHEN NOT TESTING)
    printRoom(allRooms);
}

// Finds the container address using the name
Item* findItemAddress(vector<Item> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return &(ReadItems[counter]);
        }
    }
    return &(ReadItems[0]);
}

// Finds the container address using the name
Container* findContainerAddress(vector<Container> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return &(ReadItems[counter]);
        }
    }
    return &(ReadItems[0]);
}

// Finds the creature address using the name
Creature* findCreatureAddress(vector<Creature> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return &(ReadItems[counter]);
        }
    }
    return &(ReadItems[0]);
}


//-----------------------------------TEST FUNCTIONS-----------------------------------------

void printItems(Item* item)
{
    int counter;
    cout<<item->getName()<<endl;
    cout<<item->getStatus()<<endl;
    cout<<item->getDescription()<<endl;
    cout<<item->getWriting()<<endl;
    vector<string> tempTurnon = item->getTurnon();
    for(counter = 0; counter < tempTurnon.size(); counter++)
    {
        cout<<tempTurnon[counter]<<endl;
    }
}

void printContainers(Container* container)
{
    int counter;
    cout<<container->getName()<<endl;
    cout<<container->getStatus()<<endl;
    cout<<container->getDescription()<<endl;
    vector<string> tempAccept = container->getAccept();
    for(counter = 0; counter < tempAccept.size(); counter++)
    {
        cout<<tempAccept[counter]<<endl;
    }
    vector<Item*> tempItems = container->getContainerItems();
    for(counter = 0; counter < tempItems.size(); counter++)
    {
        printItems(tempItems[counter]);
    }
}

void printCreatures(Creature* creature)
{
    int counter;
    cout<<creature->getName()<<endl;
    cout<<creature->getStatus()<<endl;
    cout<<creature->getDescription()<<endl;    
    vector<string> tempVulnerability = creature->getVulnerability();
    for(counter = 0; counter < tempVulnerability.size(); counter++)
    {
        cout<<tempVulnerability[counter]<<endl;
    }
    vector<string> tempAttackAction = creature->getAttackAction();
    for(counter = 0; counter < tempAttackAction.size(); counter++)
    {
        cout<<tempAttackAction[counter]<<endl;
    }
}

void printBorders(Border* border)
{
    cout<<border->getName()<<endl;
    cout<<border->getBorder()<<endl;
}

void printRoom(vector<Room> allRooms)
{
    int counter;
    int innerCounter;
    for(counter = 0; counter < allRooms.size(); counter++)
    {
        cout<<allRooms[counter].getName()<<endl;
        cout<<allRooms[counter].getStatus()<<endl;
        cout<<allRooms[counter].getType()<<endl;
        cout<<allRooms[counter].getDescription()<<endl;
        vector<Border*> RoomBorders = allRooms[counter].getBorders();
        vector<Container*> RoomContainers = allRooms[counter].getRoomContainers();
        vector<Item*> RoomItems = allRooms[counter].getRoomItems();
        vector<Creature*> RoomCreatures = allRooms[counter].getRoomCreatures();
        
        for(innerCounter = 0; innerCounter < RoomBorders.size(); innerCounter++)
        {
            printBorders(RoomBorders[innerCounter]);
        }

        for(innerCounter = 0; innerCounter < RoomContainers.size(); innerCounter++)
        {
            printContainers(RoomContainers[innerCounter]);
        }

        for(innerCounter = 0; innerCounter < RoomItems.size(); innerCounter++)
        {
            printItems(RoomItems[innerCounter]);
        }

        for(innerCounter = 0; innerCounter < RoomCreatures.size(); innerCounter++)
        {
            printCreatures(RoomCreatures[innerCounter]);
        }
    }
}

//------------------------------------------------------------------------------------------