#include "VMFileCopyTask.h"

VMFileCopyTask::VMFileCopyTask( FileCopyType fileCopyType, const std::string& source, const std::string& destination ) :
    m_fileCopyType( fileCopyType ),
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

