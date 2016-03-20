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
    return false;
}

