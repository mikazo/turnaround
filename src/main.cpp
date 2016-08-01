#include <iostream>

#include "xml.h"
#include "task.h"

int main( int argc, char** argv )
{
    int i = 0;
    bool success = true;

    if( 2 == argc )
    {
        std::cout << "Turnaround v0.1" << std::endl;

        std::string filename( argv[ 1 ] );
        std::vector<Task*> tasks;

        if( ParseXML( filename, tasks ) )
        {
            std::cout << "Parsed XML file " << filename << std::endl;

            for( i = 0; i < tasks.size() && success; i++ )
            {
                Task* task = tasks[ i ];

                std::cout << "Executing task #" << i << std::endl;

                success = task->executeTask();

                std::cout << "Task #" << i << " complete." << std::endl;
                std::cout << "-------------------------------------" << std::endl;
            }

            if( success )
            {
                std::cout << "Finished executing all tasks successfully." << std::endl;
            }
            else
            {
                std::cout << "Task execution failed on task #" << i << std::endl;
            }
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

