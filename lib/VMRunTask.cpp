#include "VMRunTask.h"

VMRunTask::VMRunTask( const std::string& command ) :
    m_command( command )
{
}

VMRunTask::~VMRunTask()
{
}

bool VMRunTask::executeTask()
{
    return false;
}

