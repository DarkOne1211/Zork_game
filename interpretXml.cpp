// ACCEPT ELEMETS FOT CONTAINERS
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
void gameInit();
void changeRoom(string);
void listInventory();
void takeItem(string);
void openContainer(string);
void readItem(string);
void dropItem(string);
void putItem(string, string);
void turnonItem(string);
void attackCreature(string, string);
void findAction(string);
int checkTriggers(string);

vector<Room> allRooms;
vector<Item> allItems;
vector<Creature> allCreatures;
vector<Container> allContainers;
vector<Border> allBorders;
vector<Trigger> allTriggers;

// initializing the player    
Person player;

void interpretXmlString(std::string gameXml)
{
    // THIS FUNCTION INTERPRETS THE XML FILE AND CREATES THE
    // REQUIRED OBJECTS ACCORDINGLY

    // Parsing the xml string into an object named doc
    std::vector<char> xml_copy(gameXml.begin(), gameXml.end());
    xml_copy.push_back('\0');
    xml_document<> doc;
    doc.parse<0>(&xml_copy[0]);

    // Initialize player Room
    player.currentRoom = 0;

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
                        newTrigger.setCommands(commands->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setPrints(prints->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setActions(actions->value());
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
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
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

        if(container->first_node("trigger") != NULL)
        {
           xml_node<>* trigger = container->first_node("trigger");
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
                        newTrigger.setCommands(commands->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setPrints(prints->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setActions(actions->value());
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
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }
               }

               allTriggers.push_back(newTrigger);
               newContainer.setContainerTrigger(allTriggers.size() - 1);
               trigger = trigger->next_sibling("trigger");
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
                xml_node<>* actionStuff = attack->first_node();
                while(actionStuff != NULL)
                {
                    newCreature.setAttackActions(actionStuff->value());
                    actionStuff = actionStuff->next_sibling();
                }
                attack = attack->next_sibling("attack");
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
                        newTrigger.setCommands(commands->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setPrints(prints->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setActions(actions->value());
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
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
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
                        newTrigger.setCommands(commands->value());
                        commands = commands->next_sibling("command");
                   }
               }

               if(trigger->first_node("print") != NULL)
               {
                   xml_node<>* prints = trigger->first_node("print");
                   while(prints != NULL)
                   {
                        newTrigger.setPrints(prints->value());
                        prints = prints->next_sibling("print");
                   }
               }

               if(trigger->first_node("action") != NULL)
               {
                   xml_node<>* actions = trigger->first_node("action");
                   while(actions != NULL)
                   {
                        newTrigger.setActions(actions->value());
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
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("status") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("status")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("object") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("object")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
                   }

                   if(conditions->first_node("owner") != NULL)
                   {
                        newTrigger.setConditions(conditions->first_node("owner")->value());
                   }
                   else
                   {
                        newTrigger.setConditions("0");
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

    // Starting to take user input 

    for(int throughTrigger = 0; throughTrigger < allTriggers.size(); throughTrigger++)
    {
        allTriggers[throughTrigger].setCommands("");
    }
    gameInit();
    
    // TESING IF THE XML HAS BEEN READ PROPERLY(COMMENT OUT WHEN NOT TESTING)
    //printRoom(allRooms);
    //deleteObject("Delete giant");
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
            allCreatures[location].setdeleted(0);
            allRooms[addedLocation].setRoomCreatures(location);
        }
        
        if(objectType == "Container")
        {
            allContainers[location].setdeleted(0);
            allRooms[addedLocation].setRoomContainers(location);
        }
        
        if(objectType == "Item")
        {
            allItems[location].setdeleted(0);
            allRooms[addedLocation].setRoomItems(location);
        }
    }

    if(objectToAddTo == "Container")
    {
        allContainers[location].setdeleted(0);
        allContainers[addedLocation].setContainerItems(location);
    }
    
}

// Deletes Object
void deleteObject(string deleteCommand)
{
    string deleteCommandWords[4];
    int location = -1;
    string objectType;

    // Splitting the commad into words
    short counter = 0;
    
    for(short i=0;i<deleteCommand.length();i++)
    {
        if(deleteCommand[i] == ' ')
        {
            counter++;
            i++;
        }
        deleteCommandWords[counter] += deleteCommand[i];
    }
    
    // Finding the object to change delete

    if(findCreatureAddress(allCreatures, deleteCommandWords[1]) != -1)
    {
        location = findCreatureAddress(allCreatures, deleteCommandWords[1]);
        objectType = "Creature";
    }
    else if(findContainerAddress(allContainers, deleteCommandWords[1]) != -1)
    {
        location = findContainerAddress(allContainers, deleteCommandWords[1]);
        objectType = "Container";
    }
    else if(findItemAddress(allItems, deleteCommandWords[1]) != -1)
    {
        location = findItemAddress(allItems, deleteCommandWords[1]);
        objectType = "Item";
    }
    else
    {
        location = findRoomAddress(allRooms, deleteCommandWords[1]);
        objectType = "Room";
    }

    // deleting
    if(objectType == "Creature")
    {
        allCreatures[location].setdeleted(1);
    }

    if(objectType == "Container")
    {
        allContainers[location].setdeleted(1);
    }

    if(objectType == "Item")
    {
        allItems[location].setdeleted(1);
    }

    if(objectType == "Room")
    {
        allRooms[location].setdeleted(1);
    }

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
    cout << "Game Over\n";
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
void gameInit()
{
    cout << allRooms[player.currentRoom].getDescription() << "\n";
    string inputCommand;
    string inputCommandWords[4] = {"","","",""};
    short counter = 0 ;
    for(;;)
    {
        inputCommandWords[0] = "";
        inputCommandWords[1] = "";
        inputCommandWords[2] = "";
        inputCommandWords[3] = "";
        counter = 0;
        getline(cin, inputCommand);
        for(short i = 0; i < inputCommand.length(); i++)
        {
            if(inputCommand[i] == ' ')
            {
                counter++;
                i++;
            }
            inputCommandWords[counter] += inputCommand[i];
        }

        int override = 0;
        if(inputCommandWords[0] != "take" || inputCommandWords[0] != "put")
            override = checkTriggers(inputCommand);

        /*
        for(short i = 0; i < 4; i++)
        {
            cout << i << ":" << inputCommandWords[i] << " " ;
        }
        cout << "\n";
        */
        // Change Rooms

        if(inputCommandWords[0] == "n" || inputCommandWords[0] == "s" || inputCommandWords[0] == "e" || inputCommandWords[0] == "w")
        {   
            if(override != 1)
                changeRoom(inputCommandWords[0]);
        }

        // Display Inventory

        else if(inputCommandWords[0] == "i")
        {
            if(override != 1)
                listInventory();
        }

        // Take Item

        else if(inputCommandWords[0] == "take")
        {
            takeItem(inputCommandWords[1]);
            checkTriggers(inputCommand);
        }

        // Open Exit
        
        else if(inputCommandWords[0] == "open" && inputCommandWords[1] == "exit")
        {
            if(allRooms[player.currentRoom].getType() == "exit")
            {
                if(override != 1)
                gameOver();
            }
            else
                cout << "Rooms is not an exit\n";
        }
        
        // Open Container
        
        else if(inputCommandWords[0] == "open")
        {
            if(override != 1)
                openContainer(inputCommandWords[1]);
        }

        // Read Item
        else if(inputCommandWords[0] == "read")
        {
            if(override != 1)
                readItem(inputCommandWords[1]);
        }

        // Drop Item
        else if(inputCommandWords[0] == "drop")
        {
            if(override != 1)
                dropItem(inputCommandWords[1]);
        }

        // put Item
        else if(inputCommandWords[0] == "put")
        {
            putItem(inputCommandWords[1], inputCommandWords[3]);
            checkTriggers(inputCommand);
        }
        
        // Turn on Item
        else if(inputCommandWords[0] == "turn")
        {
            if(override != 1)
                turnonItem(inputCommandWords[2]);
        }
        
        // attack creature
        else if(inputCommandWords[0] == "attack")
        {
            if(override != 1)
                attackCreature(inputCommandWords[1],inputCommandWords[3]);
        }

        else
        {
            cout << "Invalid Command\n";
        }
        
    }
}

//-----------------------------------GAME COMMANDS-------------------------------

void changeRoom(string direction)
{
    int move;
    string nextRoom = "";

    if(direction == "n")
    {
        move = 0;
    }
    else if(direction == "s")
    {
        move = 1;
    }
    else if(direction == "e")
    {
        move = 2;
    }
    else if(direction == "w")
    {
        move = 3;
    }
    else
    {
        cout << "Invalid command\n";
    }

    vector<int> borderLocation = allRooms[player.currentRoom].getBorders();
    int borderVectorSize = borderLocation.size();
    for(int k = 0; k < borderVectorSize; k ++)
    {
        if(allBorders[borderLocation[k]].getBorder()[0] == direction[0])
        {
            nextRoom = allBorders[borderLocation[k]].getName();
            player.currentRoom = findRoomAddress(allRooms, nextRoom);
            cout << allRooms[player.currentRoom].getDescription() << "\n";
        }        
    }
    if(allRooms[player.currentRoom].getName() != nextRoom)
    {
        cout << "Cannot go in that direction\n";
    }
}

void listInventory()
{
    if(player.inventory.empty())
    {
        cout << "Inventory: Empty\n";
    }
    else
    {
        cout << "Inventory: ";
        for(int i = 0; i < player.inventory.size(); i++)
        {
            cout << allItems[player.inventory[i]].getName() << ", ";
        }
        cout << "\b\b" << " \n";
    }
}

void takeItem(string itemName)
{
    int itemLocation  = -1;
    itemLocation = findItemAddress(allItems, itemName);
    
    if(itemLocation == -1)
    {
        cout << itemName << " does not exist\n";
        return;
    }

    for(int counter = 0; counter < player.inventory.size(); counter++)
    {
        if(itemLocation == player.inventory[counter])
        {
            cout << "Item alread in inventory.\n";
            return;            
        }
    }

    int itemFoundinContext = 0;
    // check if item is in current room
    for(int test = 0; test < allRooms[player.currentRoom].getRoomItems().size(); test++)
    {
        if(itemLocation == allRooms[player.currentRoom].getRoomItems()[test])
        {
            itemFoundinContext = 1;
        }
    }

    vector<int> currentRoomContainers = allRooms[player.currentRoom].getRoomContainers();
    int itemFoundinContainerinContext = 0;
    for(int containerCounter = 0; containerCounter < currentRoomContainers.size(); containerCounter++)
    {
        vector<int> itemsinContainer = allContainers[currentRoomContainers[containerCounter]].getContainerItems();
        for(int itemsinContainerCounter = 0; itemsinContainerCounter < itemsinContainer.size(); itemsinContainerCounter++)
        {
            if(itemLocation == itemsinContainer[itemsinContainerCounter])
            {
                itemFoundinContainerinContext = 1;
            }
        }
    }

    if(itemFoundinContext == 0 && itemFoundinContainerinContext == 0)
    {
        cout << "Item not in this room\n";
        return;
    }

    // Removing item from Room
    for(int i = 0; i < allRooms.size(); i++)
    {
        for(int j = 0; j < allRooms[i].getRoomItems().size(); j++)
        {
            if(allRooms[i].getRoomItems()[j] == itemLocation)
            {
                allRooms[i].RoomItems.erase(allRooms[i].RoomItems.begin() + j);
            }
        }
    }   

    // Removing item from Container
    for(int i = 0; i < allContainers.size(); i++)
    {
        for(int j = 0; j < allContainers[i].getContainerItems().size(); j++)
        {
            if(allContainers[i].getContainerItems()[j] == itemLocation)
            {
                if(allContainers[i].open == 0)
                {
                    cout << "Connot take item. Container closed\n";
                    return;
                }
                allContainers[i].ContainerItems.erase(allContainers[i].ContainerItems.begin() + j);
            }
        }
    }

    player.inventory.push_back(itemLocation);
    cout << "Item " << itemName << " added to inventory\n";
}

void openContainer(string containerName)
{
    int containerLocation = -1;
    containerLocation = findContainerAddress(allContainers, containerName);
    
    if(containerLocation == -1)
    {
        cout<< "Container does not exist\n";
        return;
    }
    
    int containerFoundinContext = 0;
    for(int test = 0; test < allRooms[player.currentRoom].getRoomContainers().size(); test++)
    {
        if(containerLocation == allRooms[player.currentRoom].getRoomContainers()[test])
            containerFoundinContext = 1;
    }

    if(containerFoundinContext == 0)
    {
        cout << "Container not in the current room";
        return;
    }

    if(!allContainers[containerLocation].getAccept().empty())
    {
        int acceptElement = -1;
        vector<string> accept = allContainers[containerLocation].getAccept();
        for(int k = 0; k < accept.size(); k++)
        {
            vector<int> items = allContainers[containerLocation].getContainerItems();
            for(int m = 0; m < items.size(); m++)
            {
                if(allItems[items[m]].getName() == accept[k])
                    acceptElement = 1;        
            }
        }

        if(acceptElement == -1)
        {
            cout << "Cannot open the container\n";
            return;
        }
    }
    if(allContainers[containerLocation].getContainerItems().size() == 0)
    {
        cout << containerName << " is empty\n";
    }
    cout << containerName << " contains ";
    allContainers[containerLocation].open = 1;
    for(int i = 0; i < allContainers[containerLocation].getContainerItems().size(); i++)
    {
        if(allItems[allContainers[containerLocation].getContainerItems()[i]].getdeleted() == 0)
            cout << allItems[allContainers[containerLocation].getContainerItems()[i]].getName() << ", ";
    }
    cout << "\b\b" << " \n";
}

void readItem(string itemName)
{
    int inventoryLocation = -1;
    for(int i = 0; i < player.inventory.size(); i++)
    {
        if(allItems[player.inventory[i]].getName() == itemName)
        {
            inventoryLocation = i;
        }
    }

    if(inventoryLocation == -1)
    {
        cout << "Item not in inventory\n";
    }
    else
    {
        if(allItems[player.inventory[inventoryLocation]].getWriting() == "")
        {
            cout << "Nothing Written\n";
        }
        else
        {
            cout << allItems[player.inventory[inventoryLocation]].getWriting() << "\n";
        }
    }
}

void dropItem(string itemName)
{
    int itemLocationinInv = -1;

    for(int i = 0; i < player.inventory.size(); i++)
    {
        if(allItems[player.inventory[i]].getName() == itemName)
        {
            itemLocationinInv = i;
        }
    }

    if(itemLocationinInv == -1)
    {
        cout << "Item not in inventory\n";
    }
    else
    {
        allRooms[player.currentRoom].setRoomItems(player.inventory[itemLocationinInv]);
        (player.inventory).erase(player.inventory.begin()+itemLocationinInv);
        cout<< itemName << " dropped\n";
    }
}

void putItem(string itemName, string containerName)
{
    
    int itemLocationinInv = -1;

    for(int i = 0; i < player.inventory.size(); i++)
    {
        if(allItems[player.inventory[i]].getName() == itemName)
        {
            itemLocationinInv = i;
        }
    }

    if(itemLocationinInv == -1)
    {
        cout << "Item not in inventory\n";
    }
    else
    {
        int containerLocation = -1;
        containerLocation = findContainerAddress(allContainers, containerName);
        if(containerLocation == -1)
        {
            cout << "Container does not exist\n";
        }
        else
        {
            vector<int> currentRoomContainers = allRooms[player.currentRoom].getRoomContainers();
            int containerPresent = -1;
            for(int x = 0; x < currentRoomContainers.size(); x++)
            {
                if(allContainers[currentRoomContainers[x]].getName() == containerName)
                {
                    containerPresent = 1;
                }
            }

            if(containerPresent == -1)
            {
                cout << "Container not present in room\n";
                return;
            }
            
            if(!allContainers[containerLocation].getAccept().empty())
            {   
                int acceptElement = -1;
                vector<string> acceptItem = allContainers[containerLocation].getAccept();
                for(int k = 0; k < acceptItem.size(); k++)
                {
                    if(acceptItem[k] == itemName)
                        acceptElement = 1;
                }
                if( acceptElement == -1)
                {
                    cout << "Cannot put " << itemName << " in " << containerName << "\n";
                    return;
                }
            }
            allContainers[containerLocation].setContainerItems(player.inventory[itemLocationinInv]);
            (player.inventory).erase(player.inventory.begin()+itemLocationinInv);
            cout<< itemName << " added to " << containerName<< "\n";
        }
    }
}

void turnonItem(string itemName)
{
    int itemLocationinInv = -1;

    for(int i = 0; i < player.inventory.size(); i++)
    {
        if(allItems[player.inventory[i]].getName() == itemName)
        {
            itemLocationinInv = i;
        }
    }

    if(itemLocationinInv == -1)
    {
        cout << "Item not in inventory\n";
    }
    else
    {
        vector<string> turnon = allItems[player.inventory[itemLocationinInv]].getTurnon();
        if(turnon.empty())
        {
            cout << "This item cannot be turned on\n";
        }
        else
        {
            for(int i = 0; i < turnon.size(); i++)
            {
                findAction(turnon[i]);
            }
        }
    }
}

void attackCreature(string creatureName, string itemName)
{
    int itemLocationinInv = -1;

    for(int i = 0; i < player.inventory.size(); i++)
    {
        if(allItems[player.inventory[i]].getName() == itemName)
        {
            itemLocationinInv = i;
        }
    }

    if(itemLocationinInv == -1)
    {
        cout << "Item not in inventory\n";
    }
    else
    {
        int creatureLocation = -1;
        for(int i = 0; i < allCreatures.size(); i++)
        {
            if(allCreatures[i].getName() == creatureName)
            {
                creatureLocation = i;
            }
        }

        if(creatureLocation == -1)
        {
            cout << "Creature does not exist\n";
        }
        else
        {
            int creatureinRoom = -1;
            vector<int> currentRoomCreatures = allRooms[player.currentRoom].getRoomCreatures();
            for(int y = 0; y < currentRoomCreatures.size(); y++)
            {
                if(allCreatures[currentRoomCreatures[y]].getName() == creatureName)
                {
                    creatureinRoom = 1;
                }
            }

            if(creatureinRoom == -1)
            {
                cout << "Creature not in this room\n";
                return;
            }

            if(allCreatures[creatureLocation].getdeleted() == 1)
            {
                cout << "Error\n";
                return;
            }

            int attackDone = -1;
            vector<string> vulnerability = allCreatures[creatureLocation].getVulnerability();
            for(int i = 0; i < vulnerability.size(); i++)
            {
                if(vulnerability[i] == itemName)
                {
                    cout << "You attacked " << creatureName << " with " << itemName <<"\n";
                    attackDone = 1;
                    vector<string> attack = allCreatures[creatureLocation].getAttackAction();
                    for(int j = 0; j < attack.size(); j++)
                    {
                        findAction(attack[j]);
                    }
                }
            }

            if(attackDone == -1)
            {
                cout << creatureName << " is invulnerable to " << itemName << "\n";
            }

            if(attackDone == 1)
            {
                if(allCreatures[creatureLocation].getCreatureTriggers().empty())
                {
                    deleteObject("Delete " + creatureName);
                }
            }
        }
    }   
}

void findAction(string inputCommand)
{
    string inputCommandWords[100];

    short counter = 0 ;

    for(int j = 0;j < 100; j++)
    {
        inputCommandWords[j] = "";
    }

    for(short i = 0; i < inputCommand.length(); i++)
        {
            if(inputCommand[i] == ' ')
            {
                counter++;
                i++;
            }
            inputCommandWords[counter] += inputCommand[i];
        }

        /*
        for(short i = 0; i < 4; i++)
        {
            cout << i << ":" << inputCommandWords[i] << " " ;
        }
        cout << "\n";
        */
        // Change Rooms

        if(inputCommandWords[0] == "n" || inputCommandWords[0] == "s" || inputCommandWords[0] == "e" || inputCommandWords[0] == "w")
        {
            changeRoom(inputCommandWords[0]);
        }

        // Display Inventory

        else if(inputCommandWords[0] == "i")
        {
            listInventory();
        }

        // Take Item

        else if(inputCommandWords[0] == "take")
        {
            takeItem(inputCommandWords[1]);
        }

        // Open Exit
        
        else if(inputCommandWords[0] == "open" && inputCommandWords[1] == "exit")
        {
            if(allRooms[player.currentRoom].getType() == "exit")
                gameOver();
            else
                cout << "Rooms is not an exit\n";
        }
        
        // Open Container
        
        else if(inputCommandWords[0] == "open")
        {
            openContainer(inputCommandWords[1]);
        }

        // Read Item
        else if(inputCommandWords[0] == "read")
        {
            readItem(inputCommandWords[1]);
        }

        // Drop Item
        else if(inputCommandWords[0] == "drop")
        {
            dropItem(inputCommandWords[1]);
        }

        // put Item
        else if(inputCommandWords[0] == "put")
        {
            putItem(inputCommandWords[1], inputCommandWords[3]);
        }
        
        // Turn on Item
        else if(inputCommandWords[0] == "turn")
        {
            turnonItem(inputCommandWords[2]);
        }
        
        // attack creature
        else if(inputCommandWords[0] == "attack")
        {
            attackCreature(inputCommandWords[1],inputCommandWords[3]);
        }

        // Behind the scenes add command
        else if(inputCommandWords[0] == "Add")
        {
            add(inputCommand);
        }
        // Behind the scenes Delete command
        else if(inputCommandWords[0] == "Delete")
        {
            deleteObject(inputCommand);
        }
        // Behind the scenes Update command
        else if(inputCommandWords[0] == "Update")
        {
            update(inputCommand);
        }
        // Behind the scenes Game Over command
        else if(inputCommandWords[0] == "Game" && inputCommandWords[1] == "Over")
        {
            gameOver();
        }
        else
        {
            cout << inputCommand << "\n";
        }
}

int checkOwner(int itemLocation, string containerName)
{
    if(containerName == "inventory")
    {
        for(int i = 0; i < player.inventory.size(); i++)
        {
            if(player.inventory[i] == itemLocation)
                return 1;
        }
    }
    else
    {
        int containerLocation = findContainerAddress(allContainers, containerName);
        vector<int> containerItems = allContainers[containerLocation].getContainerItems();
        for(int j = 0; j < containerItems.size(); j++)
        {
            if(containerItems[j] == itemLocation)
                return 1;
        }
    }

    return 0;
}

int excuteTrigger(int triggerLocation)
{
    Trigger currentTrigger = allTriggers[triggerLocation];
    vector<string> conditions = currentTrigger.getConditions();

    if(conditions[0] == "no")
    {
        int itemLocation = findItemAddress(allItems, conditions[2]);
        int inOwner = checkOwner(itemLocation, conditions[3]);
        if(inOwner == 0)
        {
        
            vector<string> prints = currentTrigger.getPrints();
            for(int i = 0; i < prints.size(); i++)
            {
                findAction(prints[i]);
            }

            vector<string> actions = currentTrigger.getActions();
            for(int i = 0; i < actions.size(); i++)
            {
                findAction(actions[i]);
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }

    else if(conditions[0] == "yes")
    {
        int itemLocation = findItemAddress(allItems, conditions[2]);
        int inOwner = checkOwner(itemLocation, conditions[3]);
        if(inOwner == 1)
        {
            
            vector<string> prints = currentTrigger.getPrints();
            for(int i = 0; i < prints.size(); i++)
            {
                findAction(prints[i]);
            }

            vector<string> actions = currentTrigger.getActions();
            for(int i = 0; i < actions.size(); i++)
            {
                findAction(actions[i]);
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        int itemLocation = -1;
        int containerLocation = -1;
        int creatureLocation = -1;
        int test = -1;
        itemLocation = findItemAddress(allItems, conditions[2]);
        containerLocation = findContainerAddress(allContainers, conditions[2]);
        creatureLocation = findCreatureAddress(allCreatures, conditions[2]);
        
        if(itemLocation != -1)
        {
            if(allItems[itemLocation].getStatus() == conditions[1])
                test = 1;
        }
        else if(containerLocation != -1)
        {
            if(allContainers[containerLocation].getStatus() == conditions[1])
                test = 1;
        }
        else if(creatureLocation != -1)
        {
            if(allCreatures[creatureLocation].getStatus() == conditions[1])
                test = 1;
        }
        else
        {

        }

        if(test == 1)
        {
        
            vector<string> prints = currentTrigger.getPrints();
            for(int i = 0; i < prints.size(); i++)
            {
                findAction(prints[i]);
            }

            vector<string> actions = currentTrigger.getActions();
            for(int i = 0; i < actions.size(); i++)
            {
                findAction(actions[i]);
            }
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int checkTriggers(string inputCommand)
{
    vector<int> currentRoomItems = allRooms[player.currentRoom].getRoomItems();
    vector<int> currentRoomCreatures = allRooms[player.currentRoom].getRoomCreatures();
    vector<int> currentRoomContainers = allRooms[player.currentRoom].getRoomContainers();    
    vector<int> currentRoomTrigger;
    vector<int> currentRoomItemTrigger;
    vector<int> currentRoomCreatureTrigger;
    vector<int> currentRoomContainerTrigger;
    int setReturnValue = 0;
    // Checking Room Triggers
    if(!allRooms[player.currentRoom].getRoomTriggers().empty())
    {
        currentRoomTrigger = allRooms[player.currentRoom].getRoomTriggers();
        for(int j = 0; j < currentRoomTrigger.size(); j++)
            {
                string checkTriggerCommand;
                int execTrigger = 0;
                if(allTriggers[currentRoomTrigger[j]].getCommands()[0] != "")
                {
                    checkTriggerCommand = allTriggers[currentRoomTrigger[j]].getCommands()[0];
                }
                if(checkTriggerCommand == "")
                {
                    execTrigger = excuteTrigger(currentRoomTrigger[j]);
                }
                else
                {
                    if(checkTriggerCommand == inputCommand)
                    {
                        setReturnValue = 1;
                        execTrigger = excuteTrigger(currentRoomTrigger[j]);
                        return execTrigger;
                    }
                    else
                    {
                        setReturnValue =  0; 
                    }
                }
                setReturnValue = execTrigger && setReturnValue;
                if(allTriggers[currentRoomTrigger[j]].getType() == "single" && execTrigger)
                {
                    allRooms[player.currentRoom].RoomTriggers.erase(allRooms[player.currentRoom].RoomTriggers.begin() + j);
                }
            }
    }

    // Checking current item Triggers
    for(int i = 0; i < currentRoomItems.size(); i++)
    {
        if((allItems[currentRoomItems[i]].getdeleted() == 0))
        {
            currentRoomItemTrigger = allItems[currentRoomItems[i]].getItemTrigger();
            for(int j = 0; j < currentRoomItemTrigger.size(); j++)
            {
                string checkTriggerCommand;
                int execTrigger = 0;
                if(allTriggers[currentRoomItemTrigger[j]].getCommands()[0] != "")
                {
                    checkTriggerCommand = allTriggers[currentRoomItemTrigger[j]].getCommands()[0];
                }
                if(checkTriggerCommand == "")
                {
                    execTrigger = excuteTrigger(currentRoomItemTrigger[j]);
                }
                else
                {
                    if(checkTriggerCommand == inputCommand)
                    {
                        setReturnValue = 1;
                        execTrigger = excuteTrigger(currentRoomItemTrigger[j]);
                        return execTrigger;
                    }
                    else
                    {
                        setReturnValue = 0;
                    }
                } 
                setReturnValue = execTrigger && setReturnValue;
                if(allTriggers[allItems[currentRoomItems[i]].getItemTrigger()[j]].getType() == "single" && execTrigger)
                {
                    allItems[currentRoomItems[i]].itemTrigger.erase(allItems[currentRoomItems[i]].itemTrigger.begin() + j);
                }
            }
        }
    }

    // Checking current creature triggers
    for(int i = 0; i < currentRoomCreatures.size(); i++)
    {
        if(!allCreatures[currentRoomCreatures[i]].getCreatureTriggers().empty() && (allCreatures[currentRoomCreatures[i]].getdeleted() == 0))
        {
            currentRoomCreatureTrigger = allCreatures[currentRoomCreatures[i]].getCreatureTriggers();
            for(int j = 0; j < currentRoomCreatureTrigger.size(); j++)
            {
                string checkTriggerCommand;
                int execTrigger = 0;
                if(allTriggers[currentRoomCreatureTrigger[j]].getCommands()[0] != "")
                {
                    checkTriggerCommand = allTriggers[currentRoomCreatureTrigger[j]].getCommands()[0];
                }
                if(checkTriggerCommand == "")
                {
                    execTrigger = excuteTrigger(currentRoomCreatureTrigger[j]);
                }
                else
                {
                    if(checkTriggerCommand == inputCommand)
                    {
                        setReturnValue = 1;
                        execTrigger = excuteTrigger(currentRoomCreatureTrigger[j]);
                        return execTrigger;
                    }
                    else
                    {
                        setReturnValue = 0;
                    }
                }
                setReturnValue = execTrigger && setReturnValue;
                if(allTriggers[allCreatures[currentRoomCreatures[i]].getCreatureTriggers()[j]].getType() == "single" && execTrigger)
                {
                    allCreatures[currentRoomCreatures[i]].creatureTriggers.erase(allCreatures[currentRoomCreatures[i]].creatureTriggers.begin() + j);
                }
            }
        }
    }

    // checking current container triggers
    for(int i = 0; i < currentRoomContainers.size(); i++)
    {
        if(!allContainers[currentRoomContainers[i]].getContainerTriggers().empty() && (allContainers[currentRoomContainers[i]].getdeleted() == 0))
        {
            currentRoomContainerTrigger = allContainers[currentRoomContainers[i]].getContainerTriggers();
            for(int j = 0; j < currentRoomContainerTrigger.size(); j++)
            {
                string checkTriggerCommand;
                int execTrigger = 0;
                if(allTriggers[currentRoomContainerTrigger[j]].getCommands()[0] != "")
                {
                    checkTriggerCommand = allTriggers[currentRoomContainerTrigger[j]].getCommands()[0];
                }
                if(checkTriggerCommand == "")
                {
                    execTrigger = excuteTrigger(currentRoomContainerTrigger[j]);
                }
                else
                {
                    if(checkTriggerCommand == inputCommand)
                    {
                        setReturnValue = 1;
                        execTrigger = excuteTrigger(currentRoomContainerTrigger[j]);
                        return execTrigger;
                    }
                    else
                    {
                        setReturnValue = 0;
                    }
                }
                setReturnValue = execTrigger && setReturnValue;
                if(allTriggers[allContainers[currentRoomContainers[i]].getContainerTriggers()[j]].getType() == "single" && execTrigger)
                {
                    allContainers[currentRoomContainers[i]].ContainerTriggers.erase(allContainers[currentRoomContainers[i]].ContainerTriggers.begin() + j);
                }
            }
        }
    }
    return setReturnValue;
}