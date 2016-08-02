#ifndef _VM_RUN_TASK_H_
#define _VM_RUN_TASK_H_

#include <string>

#include "task.h"

class VMRunTask : public Task
{
public:
    VMRunTask( const std::string& vmxPath,
               const std::string& username,
               const std::string& password,
               const std::string& command,
               bool waitForCompletion );
    ~VMRunTask(); 

    bool executeTask();

private:
    std::string m_vmxPath;
    std::string m_username;
    std::string m_password;
    std::string m_command;
    bool m_waitForCompletion;
};

#endif

