#ifndef CREATURE_H_INCLUDE
#define CREATURE_H_INCLUDE

#include <iostream>
#include <vector>
#include "Container.h"

using namespace std;
class Creature
{
    private:
        string name;
        string status;
        string description;
        vector<string> vulnerability;
        vector<string> attackActions;
        // Add trigger later
    public:
        Creature();
        virtual ~Creature();
        void setName(string);
        void setStatus(string);
        void setDescription(string);
        void setVulnerability(string);
        void setAttackActions(string);

        string getName();
        string getStatus();
        string getDescription();
        vector<string> getVulnerability();
        vector<string> getAttackAction();
};

#endif