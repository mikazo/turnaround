#ifndef _VM_REVERT_TASK_H_
#define _VM_REVERT_TASK_H_

#include <string>

#include "task.h"

class VMRevertTask : public Task
{
public:
    VMRevertTask( const std::string& name, const std::string& snapshot );
    ~VMRevertTask(); 

    bool executeTask();

private:
    std::string m_name;
    std::string m_snapshot;
};

#endif

