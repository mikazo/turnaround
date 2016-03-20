#include "VMFileCopyTask.h"

VMFileCopyTask::VMFileCopyTask( const std::string& source, const std::string& destination ) :
    m_source( source ),
    m_destination( destination )
{
}

VMFileCopyTask::~VMFileCopyTask()
{
}

bool VMFileCopyTask::executeTask()
{
    return false;
}

