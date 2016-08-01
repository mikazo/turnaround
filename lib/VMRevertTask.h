#ifndef _VM_REVERT_TASK_H_
#define _VM_REVERT_TASK_H_

#include <string>

#include "task.h"

class VMRevertTask : public Task
{
public:
    VMRevertTask( const std::string& vmxPath );
    ~VMRevertTask(); 

    bool executeTask();

private:
    std::string m_vmxPath;
};

#endif

