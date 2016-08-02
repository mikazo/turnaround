#ifndef _HOST_CREATE_DIR_TASK_H_
#define _HOST_CREATE_DIR_TASK_H_

#include <string>

#include "task.h"

class HostCreateDirTask : public Task
{
public:
    HostCreateDirTask( const std::string& directory );
    ~HostCreateDirTask(); 

    bool executeTask();

private:
    std::string m_directory;
};

#endif

