#ifndef _VM_RUN_TASK_H_
#define _VM_RUN_TASK_H_

#include <string>

#include "task.h"

class VMRunTask : public Task
{
public:
    VMRunTask( const std::string& command );
    ~VMRunTask(); 

    bool executeTask();

private:
    std::string m_command;
};

#endif

