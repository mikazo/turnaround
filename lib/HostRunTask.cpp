#include <stdlib.h>

#include "HostRunTask.h"

HostRunTask::HostRunTask( const std::string& command ) :
    m_command( command )
{
}

HostRunTask::~HostRunTask()
{
}

bool HostRunTask::executeTask()
{
    bool result = false;

    if( 0 == system( m_command.c_str() ) )
    {
        result = true;
    }

    return result;
}

