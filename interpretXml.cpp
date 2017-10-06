#include "main.h"
#include "interpretXml.h"

using namespace std;
using namespace rapidxml;

void interpretXmlString(std::string gameXml)
{
    // THIS FUCNTION INTERPRETS THE XML FILE AND CREATES THE
    // REQUIRED OBJECTS ACCORDINGLY

    // Parsing the xml string into an object named doc
    std::vector<char> xml_copy(gameXml.begin(), gameXml.end());
    xml_copy.push_back('\0');
    xml_document<> doc;
    doc.parse<0>(&xml_copy[0]);
    
    // Declaring variables for all major objects
    xml_node<>* map = doc.first_node("map");
    xml_node<>* room = map->first_node("room");
    
    // Testing if the rooms read correctly. Update to create a new room object
    while(room != NULL)
    {
        cout<<room->first_node("name")->value() <<endl;
        room= room->next_sibling("room");
    }
}