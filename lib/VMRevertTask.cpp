#include "VMRevertTask.h"

VMRevertTask::VMRevertTask( const std::string& name, const std::string& snapshot ) :
    m_name( name ),
    m_snapshot( snapshot )
{
}

VMRevertTask::~VMRevertTask()
{
}

bool VMRevertTask::executeTask()
{
    return false;
}

