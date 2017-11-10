#include "Creature.h"
Creature::Creature() {}
Creature::~Creature() {}

void Creature::setName(string name)
{
    this->name = name;
}

void Creature::setStatus(string status)
{
    this->status = status;
}

void Creature::setDescription(string description)
{
    this->description = description;
}

void Creature::setVulnerability(string vulnerability)
{
    this->vulnerability.push_back(vulnerability);
}

void Creature::setAttackActions(string attackActions)
{
    this->attackActions.push_back(attackActions);
}

void Creature::setCreatureTriggers(int trigger)
{
    this->creatureTriggers.push_back(trigger);
}

void Creature::setdeleted(int number)
{
    this->deleted = number;
}

string Creature::getName()
{
    return this->name;
}

string Creature::getStatus()
{
    return this->status;
}

string Creature::getDescription()
{
    return this->description;
}

vector<string> Creature::getVulnerability()
{
    return this->vulnerability;
}

vector<string> Creature::getAttackAction()
{
    return this->attackActions;
}

vector<int> Creature::getCreatureTriggers()
{
    return this->creatureTriggers;
}

int Creature::getdeleted()
{
    return this->deleted;
}