// NOTE - TRIGGER OBJECTS NOT ADDED AND INTERPRETED (REMOVE COMMENT ONCE ADDED)
#include "main.h"
#include "interpretXml.h"
#include "Room.h"

using namespace std;
using namespace rapidxml;
int findItemAddress(vector<Item>, string);
int findContainerAddress(vector<Container>, string);
int findCreatureAddress(vector<Creature>, string);
int findRoomAddress(vector<Room>, string);
void printRoom(vector<Room>);
void add(string);
void deleteObject(string);
void update(string);
void gameOver();

vector<Room> allRooms;
vector<Item> allItems;
vector<Creature> allCreatures;
vector<Container> allContainers;
vector<Border> allBorders;
vector<Trigger> allTriggers;

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
        
        if(item->first_node("trigger") != NULL)
        {
           xml_node<>* trigger = item->first_node("trigger");
           while(trigger != NULL)
           {
               Trigger newTrigger;
               if(trigger->first_node("type") != NULL)
               {
                   newTrigger.setType(trigger->first_node("type")->value());
               }

               if(trigger->first_node("command") != NULL)
               {
                   xml_node<>* commands = trigger->first_node("command");
                   while(commands != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("command")->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("print")->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("action")->value());
                        actions = actions->next_sibling("action");
                   }
               }

               if(trigger->first_node("condition") != NULL)
               {
                   xml_node<>* conditions = trigger->first_node("condition");
                   if(conditions->first_node("has") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("has")->value());
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
               }

               allTriggers.push_back(newTrigger);
               newItem.setItemTrigger(allTriggers.size() - 1);
               trigger = trigger->next_sibling("trigger");
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
                int newContainerItem = findItemAddress(allItems, ContainerItems->value());
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

        if(creature->first_node("trigger") != NULL)
        {
           xml_node<>* trigger = creature->first_node("trigger");
           while(trigger != NULL)
           {
               Trigger newTrigger;
               if(trigger->first_node("type") != NULL)
               {
                   newTrigger.setType(trigger->first_node("type")->value());
               }

               if(trigger->first_node("command") != NULL)
               {
                   xml_node<>* commands = trigger->first_node("command");
                   while(commands != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("command")->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("print")->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("action")->value());
                        actions = actions->next_sibling("action");
                   }
               }

               if(trigger->first_node("condition") != NULL)
               {
                   xml_node<>* conditions = trigger->first_node("condition");
                   if(conditions->first_node("has") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("has")->value());
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
               }

               allTriggers.push_back(newTrigger);
               newCreature.setCreatureTriggers(allTriggers.size() - 1);
               trigger = trigger->next_sibling("trigger");
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
                newRoom.setRoomBorders(allBorders.size() - 1);
            }
        }

        if(room->first_node("container") != NULL)
        {
            xml_node<>* RoomContainer = room->first_node("container");
            while(RoomContainer != NULL)
            {
                int newRoomContainer = findContainerAddress(allContainers, RoomContainer->value());
                newRoom.setRoomContainers(newRoomContainer);
                RoomContainer = RoomContainer->next_sibling("container");
            }  
        }

        if(room->first_node("item") != NULL)
        {
            xml_node<>* RoomItems = room->first_node("item");
            while(RoomItems != NULL)
            {
                int newRoomItem = findItemAddress(allItems, RoomItems->value());
                newRoom.setRoomItems(newRoomItem);
                RoomItems = RoomItems->next_sibling("item");
            }  
        }

        if(room->first_node("creature") != NULL)
        {
            xml_node<>* RoomCreatures = room->first_node("creature");
            while(RoomCreatures != NULL)
            {
                int newRoomCreature = findCreatureAddress(allCreatures, RoomCreatures->value());
                newRoom.setRoomCreatures(newRoomCreature);
                RoomCreatures = RoomCreatures->next_sibling("creature");
            }  
        }

        if(room->first_node("trigger") != NULL)
        {
           xml_node<>* trigger = room->first_node("trigger");
           while(trigger != NULL)
           {
               Trigger newTrigger;
               if(trigger->first_node("type") != NULL)
               {
                   newTrigger.setType(trigger->first_node("type")->value());
               }

               if(trigger->first_node("command") != NULL)
               {
                   xml_node<>* commands = trigger->first_node("command");
                   while(commands != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("command")->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("print")->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setCommands(trigger->first_node("action")->value());
                        actions = actions->next_sibling("action");
                   }
               }

               if(trigger->first_node("condition") != NULL)
               {
                   xml_node<>* conditions = trigger->first_node("condition");
                   if(conditions->first_node("has") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("has")->value());
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
               }

               allTriggers.push_back(newTrigger);
               newRoom.setRoomTriggers(allTriggers.size() - 1);
               trigger = trigger->next_sibling("trigger");
           } 
        }

        allRooms.push_back(newRoom);
        room = room->next_sibling("room");
    }

    // TESING IF THE XML HAS BEEN READ PROPERLY(COMMENT OUT WHEN NOT TESTING)
    //printRoom(allRooms);
    //add("Add giant to Main");
    //update("Update giant to idgaf");
}

// Finds the container address using the name
int findItemAddress(vector<Item> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return counter;
        }
    }
    return -1;
}

// Finds the container address using the name
int findContainerAddress(vector<Container> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return counter;
        }
    }
    return -1;
}

// Finds the creature address using the name
int findCreatureAddress(vector<Creature> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return counter;
        }
    }
    return -1;
}

int findRoomAddress(vector<Room> ReadItems, string name)
{
    int size = ReadItems.size();
    for(int counter = 0; counter < size; counter++)
    {
        if(ReadItems[counter].getName() == name)
        {
            return counter;
        }
    }
    return -1;   
}

//--------------------------------BEHIND THE SCENES COMMANDS--------------------------------

// Adds object to (Room/Container)
void add(string addCommand)
{
    string addCommandWords[4];
    int location = -1;
    int addedLocation = -1;
    string objectType;
    string objectToAddTo;

    // Splitting the commad into words
    short counter = 0;
    
    for(short i=0;i<addCommand.length();i++)
    {
        if(addCommand[i] == ' ')
        {
            counter++;
            i++;
        }
        addCommandWords[counter] += addCommand[i];
    }

    // Finding the kind of object being added
    
    if(findCreatureAddress(allCreatures, addCommandWords[1]) != -1)
    {
        location = findCreatureAddress(allCreatures, addCommandWords[1]);
        objectType = "Creature";
    }
    else if(findContainerAddress(allContainers, addCommandWords[1]) != -1)
    {
        location = findContainerAddress(allContainers, addCommandWords[1]);
        objectType = "Container";
    }
    else
    {
        location = findItemAddress(allItems, addCommandWords[1]);
        objectType = "Item";
    }

    // Finding the object to be added to
    if(findContainerAddress(allContainers, addCommandWords[1]) != -1)
    {
        addedLocation = findContainerAddress(allContainers, addCommandWords[1]);
        objectToAddTo = "Container";
    }
    else
    {
        addedLocation = findRoomAddress(allRooms, addCommandWords[3]);
        objectToAddTo = "Room";
    }

    // Adding the object
    
    if(objectToAddTo == "Room")
    {
        if(objectType == "Creature")
        {
            allRooms[addedLocation].setRoomCreatures(location);
        }
        
        if(objectType == "Container")
        {
            allRooms[addedLocation].setRoomContainers(location);
        }
        
        if(objectType == "Item")
        {
            allRooms[addedLocation].setRoomItems(location);
        }
    }

    if(objectToAddTo == "Container")
    {
        allContainers[addedLocation].setContainerItems(location);
    }
    
}

// Deletes Object
void deleteObject(string deleteCommand)
{

}

void update(string updateCommand)
{
    string updateCommandWords[4];
    int location = -1;
    string objectType;

    // Splitting the commad into words
    short counter = 0;
    
    for(short i=0;i<updateCommand.length();i++)
    {
        if(updateCommand[i] == ' ')
        {
            counter++;
            i++;
        }
        updateCommandWords[counter] += updateCommand[i];
    }

    // Finding the object to change status

    if(findCreatureAddress(allCreatures, updateCommandWords[1]) != -1)
    {
        location = findCreatureAddress(allCreatures, updateCommandWords[1]);
        objectType = "Creature";
    }
    else if(findContainerAddress(allContainers, updateCommandWords[1]) != -1)
    {
        location = findContainerAddress(allContainers, updateCommandWords[1]);
        objectType = "Container";
    }
    else if(findItemAddress(allItems, updateCommandWords[1]) != -1)
    {
        location = findItemAddress(allItems, updateCommandWords[1]);
        objectType = "Item";
    }
    else
    {
        location = findRoomAddress(allRooms, updateCommandWords[1]);
        objectType = "Room";
    }

    // Changing Status

    if(objectType == "Creature")
    {
        allCreatures[location].setStatus(updateCommandWords[3]);
    }

    if(objectType == "Container")
    {
        allContainers[location].setStatus(updateCommandWords[3]);
    }

    if(objectType == "Item")
    {
        allItems[location].setStatus(updateCommandWords[3]);
    }

    if(objectType == "Room")
    {
        allRooms[location].setStatus(updateCommandWords[3]);
    }

}

void gameOver()
{
    exit(EXIT_SUCCESS);
}
//------------------------------------------------------------------------------------------

//-----------------------------------TEST FUNCTIONS-----------------------------------------

void printItems(vector<int> positions)
{
    int size = positions.size();
    for (int i = 0; i < size; i++)
    {
        cout << allItems[positions[i]].getName() << endl;
        cout << allItems[positions[i]].getStatus() << endl;
        cout << allItems[positions[i]].getDescription() << endl;
        cout << allItems[positions[i]].getWriting() << endl;
        for (int j = 0; j < allItems[positions[i]].getTurnon().size(); j++)
        {
            cout << allItems[positions[i]].getTurnon()[j] << endl;
        }   
    }
}

void printCreatures(vector<int> positions)
{
    int size = positions.size();
    for(int i = 0; i < size; i++)
    {
        cout << allCreatures[positions[i]].getName() << endl;
        cout << allCreatures[positions[i]].getStatus() << endl;
        cout << allCreatures[positions[i]].getDescription() << endl;
        for (int j = 0; j < allCreatures[positions[i]].getVulnerability().size(); j++)
        {
            cout << allCreatures[positions[i]].getVulnerability()[j] << endl;
        }
        for (int j = 0; j < allCreatures[positions[i]].getAttackAction().size(); j++)
        {
            cout << allCreatures[positions[i]].getAttackAction()[j] << endl;
        }
    }
}

void printContainer(vector<int> positions)
{
    int size = positions.size();
    for (int i = 0; i < size; i++)
    {
        cout << allContainers[positions[i]].getName() << endl;
        cout << allContainers[positions[i]].getStatus() << endl;
        cout << allContainers[positions[i]].getDescription() << endl;
        for (int j = 0; j < allContainers[positions[i]].getAccept().size(); j++)
        {
            cout << allContainers[positions[i]].getAccept()[j] << endl;
        }
        printItems(allContainers[positions[i]].getContainerItems());
    }    
}

void printRoom(vector<Room> Rooms)
{
    int Roomsize = Rooms.size();
    for(int i = 0; i < Roomsize; i++)
    {
        cout<< Rooms[i].getName() << endl;
        cout<< Rooms[i].getStatus() << endl;
        cout<< Rooms[i].getType() << endl;
        cout<< Rooms[i].getDescription() << endl;

        for(int j = 0; j < Rooms[i].getBorders().size(); j++)
        {
            cout<< allBorders[Rooms[i].getBorders()[j]].getName() << endl;
            cout<< allBorders[Rooms[i].getBorders()[j]].getBorder() << endl;
        }

        printContainer(Rooms[i].getRoomContainers());
        printCreatures(Rooms[i].getRoomCreatures());
        printItems(Rooms[i].getRoomItems());
    } 
}
//------------------------------------------------------------------------------------------