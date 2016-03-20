#ifndef _TASK_H_
#define _TASK_H_

class Task
{
public:
    Task();
    virtual ~Task(); 

    virtual bool executeTask() = 0;
};

#endif

