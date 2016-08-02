#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>

#include "HostCreateDirTask.h"

HostCreateDirTask::HostCreateDirTask( const std::string& directory ) :
    m_directory( directory )
{
}

HostCreateDirTask::~HostCreateDirTask()
{
}

bool HostCreateDirTask::executeTask()
{
    bool result = false;

#ifdef _WIN32
    if( CreateDirectory( m_directory.c_str(), NULL ) )
    {
        std::cout << "Created directory " << m_directory << std::endl;

        result = true;
    }
    else
    {
        std::cout << "Failed to create directory." << std::endl;
    }
#else
    // TODO
#endif

    return result;
}

