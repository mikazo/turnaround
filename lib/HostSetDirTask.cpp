#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>

#include "HostSetDirTask.h"

HostSetDirTask::HostSetDirTask( const std::string& directory ) :
    m_directory( directory )
{
}

HostSetDirTask::~HostSetDirTask()
{
}

bool HostSetDirTask::executeTask()
{
    bool result = false;

#ifdef _WIN32
    if( SetCurrentDirectory( m_directory.c_str() ) )
    {
        std::cout << "Set current directory to " << m_directory << std::endl;

        result = true;
    }
    else
    {
        std::cout << "Failed to set current directory." << std::endl;
    }
#else
    if( 0 == chdir( m_directory.c_str() ) )
    {
        result = true;
    }
#endif

    return result;
}

