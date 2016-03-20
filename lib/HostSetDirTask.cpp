#ifdef _WIN32
#include <Windows.h>
#endif

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
        result = true;
    }
#else
    if( 0 == chdir( m_directory.c_str() ) )
    {
        result = true;
    }
#endif

    return result;
}

