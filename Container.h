#ifndef CONTAINER_H_INCLUDE
#define CONTAINER_H_INCLUDE

#include <iostream>
#include <vector>
#include "item.h"

using namespace std;
class Container
{
    private:
        string name;
        string status;
        string description;
        vector<string> accept;
        vector<int> ContainerItems;
        // add trigger later
    public:
        Container();
        virtual ~Container();
        void setName(string);
        void setStatus(string);
        void setDescription(string);
        void setAccept(string);
        void setContainerItems(int);
        
        string getName();
        string getStatus();
        string getDescription();
        vector<string> getAccept();
        vector<int> getContainerItems();
};

#endif