#include "Trigger.h"

Trigger::Trigger(){}
Trigger::~Trigger(){}

void Trigger::setType(string type)
{
    this->type = type;
}

void Trigger::setConditions(string condition)
{
    this->conditions.push_back(condition);
}

void Trigger::setPrints(string statement)
{
    this->prints.push_back(statement);
}

void Trigger::setActions(string action)
{
    this->actions.push_back(action);
}

void Trigger::setCommands(string Commands)
{
    this->commands.push_back(Commands);
}

string Trigger::getType()
{
    return this->type;
}

vector<string> Trigger::getConditions()
{
    return this->conditions; 
}

vector<string> Trigger::getPrints()
{
    return this->prints; 
}

vector<string> Trigger::getActions()
{
    return this->actions; 
}

vector<string> Trigger::getCommands()
{
    return this->commands; 
}