#ifndef _VM_FILE_COPY_TASK_H_
#define _VM_FILE_COPY_TASK_H_

#include <string>

#include "task.h"

enum FileCopyType
{
    HOST_TO_VM,
    VM_TO_HOST
};

class VMFileCopyTask : public Task
{
public:
    VMFileCopyTask( const std::string& vmxPath,
                    const std::string& username,
                    const std::string& password,
                    FileCopyType fileCopyType,
                    const std::string& source,
                    const std::string& destination );
    ~VMFileCopyTask(); 

    bool executeTask();

private:
    std::string m_vmxPath;
    std::string m_username;
    std::string m_password;
    FileCopyType m_fileCopyType;
    std::string m_source;
    std::string m_destination;
};

#endif

