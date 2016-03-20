#ifndef _HOST_RUN_TASK_H_
#define _HOST_RUN_TASK_H_

#include <string>

#include "task.h"

class HostRunTask : public Task
{
public:
    HostRunTask( const std::string& command );
    ~HostRunTask(); 

    bool executeTask();

private:
    std::string m_command;
};

#endif

