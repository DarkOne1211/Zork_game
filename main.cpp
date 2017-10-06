#include "main.h"

void interpretXmlString(std::string);
using namespace std;

int main(int argc, char** argv)
{
    // THIS FUNCTION READS THE .XML FILE, STORES THE CONTENT INTO A STRING 
    // AND PASS THE STRING INTO THE interpretXml FUNCTION

    // Checks if arguements were passed correctly
    if(argc !=2)
    {
        cout << "Enter one .xml document as an arguement"<< endl;
        return EXIT_FAILURE;
    }
    // Opening the xml file
    std::ifstream ifs(argv[1]);
    
    // Checks if the file was read properly
    if(!ifs.is_open())
    {
        cout << "The file was not read correctly" << endl;
        return EXIT_FAILURE;
    }

    // Storing the content of the file as as string
    std::string contentXml;
    
    // Copying the content of the file into the contentXml variable
    contentXml.assign( (std::istreambuf_iterator<char>(ifs) ),
    (std::istreambuf_iterator<char>()    ) );

    // Interpret the xml document and create the game
    interpretXmlString(contentXml);

    return EXIT_SUCCESS;
}