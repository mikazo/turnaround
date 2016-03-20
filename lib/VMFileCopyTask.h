#ifndef _VM_FILE_COPY_TASK_H_
#define _VM_FILE_COPY_TASK_H_

#include <string>

#include "task.h"

class VMFileCopyTask : public Task
{
public:
    VMFileCopyTask( const std::string& source, const std::string& destination );
    ~VMFileCopyTask(); 

    bool executeTask();

private:
    std::string m_source;
    std::string m_destination;
};

#endif

