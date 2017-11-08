#ifndef TRIGGER_H_INCLUDE
#define TRIGGER_H_INCLUDE

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Trigger {
    private:
        string type = "single";
        // 0 - has, 1 - status, 2 - object, 3 - owner 
        vector<string> conditions;
        vector<string> prints;
        vector<string> actions;  
        vector<string> commands; 

    public:
        Trigger();
        virtual ~Trigger();
        void setType(string);
        void setConditions(string);
        void setPrints(string);
        void setActions(string);
        void setCommands(string);
        
        string getType();
        vector <string> getConditions();
        vector <string> getPrints();
        vector <string> getActions();
        vector <string> getCommands();
};

# endif