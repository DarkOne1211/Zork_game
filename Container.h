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
        int deleted = 0;

    public:
        vector<int> ContainerTriggers;
        vector<int> ContainerItems;
        int open = 0;
        Container();
        virtual ~Container();
        void setName(string);
        void setStatus(string);
        void setDescription(string);
        void setAccept(string);
        void setContainerItems(int);
        void setContainerTrigger(int);
        void setdeleted(int);

        string getName();
        string getStatus();
        string getDescription();
        vector<string> getAccept();
        vector<int> getContainerItems();
        vector<int> getContainerTriggers();
        int getdeleted();
};

#endif