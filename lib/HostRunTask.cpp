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
    return false;
}

