#ifndef _HOST_SET_DIR_TASK_H_
#define _HOST_SET_DIR_TASK_H_

#include <string>

#include "task.h"

class HostSetDirTask : public Task
{
public:
    HostSetDirTask( const std::string& directory );
    ~HostSetDirTask(); 

    bool executeTask();

private:
    std::string m_directory;
};

#endif

