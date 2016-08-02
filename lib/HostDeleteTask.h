#ifndef _HOST_DELETE_TASK_H_
#define _HOST_DELETE_TASK_H_

#include <string>

#include "task.h"

class HostDeleteTask : public Task
{
public:
    HostDeleteTask( const std::string& path );
    ~HostDeleteTask(); 

    bool executeTask();

private:
    std::string m_path;
};

#endif

