#ifndef _HOST_FILE_COPY_TASK_H_
#define _HOST_FILE_COPY_TASK_H_

#include <string>

#include "task.h"

class HostFileCopyTask : public Task
{
public:
    HostFileCopyTask( const std::string& source, const std::string& destination );
    ~HostFileCopyTask(); 

    bool executeTask();

private:
    std::string m_source;
    std::string m_destination;
};

#endif

