#include <iostream>

#include "xml.h"
#include "task.h"

int main( int argc, char** argv )
{
    if( 2 == argc )
    {
        std::cout << "Turnaround v0.1" << std::endl;

        std::string filename( argv[ 1 ] );
        std::vector<Task*> tasks;

        if( ParseXML( filename, tasks ) )
        {
            std::cout << "Parsed XML file " << filename << std::endl;

            // TODO: Execute tasks.
        }
        else
        {
            std::cout << "Failed to parse XML file " << filename << std::endl;
        }
    }
    else
    {
        std::cout << "Please specify a Turnaround XML filename." << std::endl;
    }

    return 0;
}

