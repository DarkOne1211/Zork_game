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
        int deleted = 0;

    public:
        
        vector<int> creatureTriggers;
        Creature();
        virtual ~Creature();
        void setName(string);
        void setStatus(string);
        void setDescription(string);
        void setVulnerability(string);
        void setAttackActions(string);
        void setCreatureTriggers(int);
        void setdeleted(int);

        string getName();
        string getStatus();
        string getDescription();
        vector<string> getVulnerability();
        vector<string> getAttackAction();
        vector<int> getCreatureTriggers();
        int getdeleted();
};

#endif