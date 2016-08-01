#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>

#include "HostFileCopyTask.h"

HostFileCopyTask::HostFileCopyTask( const std::string& source, const std::string& destination ) :
    m_source( source ),
    m_destination( destination )
{
}

HostFileCopyTask::~HostFileCopyTask()
{
}

bool HostFileCopyTask::executeTask()
{
    bool result = false;

#ifdef _WIN32
    std::cout << "Copying file " << m_source << " to " << m_destination << std::endl;

    if( CopyFileA( m_source.c_str(),
                   m_destination.c_str(),
                   FALSE ) )
    {
        std::cout << "File copy success." << std::endl;

        result = true;
    }
    else
    {
        std::cout << "File copy failed." << std::endl;
    }
#else
    // TODO
#endif

    return result;
}

