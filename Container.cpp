#include "Container.h"

Container::Container() {}
Container::~Container() {}
void Container::setName(string name)
{
    this->name = name;
}
void Container::setStatus(string status)
{
    this->status = status;
}
void Container::setDescription(string description)
{
    this->description = description;
}
void Container::setAccept(string accept)
{
    this->accept.push_back(accept);
}
void Container::setContainerItems(int ContainerItems)
{
    this->ContainerItems.push_back(ContainerItems);
}
void Container::setContainerTrigger(int trigger)
{
    this->ContainerTriggers.push_back(trigger);
}
void Container::setdeleted(int number)
{
    this->deleted = number;
}

string Container::getName()
{
    return this->name;
}
string Container::getStatus()
{
    return this->status;
}
string Container::getDescription()
{
    return this->description;
}
vector<string> Container::getAccept()
{
    return this->accept;
}
vector<int> Container::getContainerItems()
{
    return this->ContainerItems;
}
vector<int> Container::getContainerTriggers()
{
    return this->ContainerTriggers;
}
int Container::getdeleted()
{
    return this->deleted;
}
