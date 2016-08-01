#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "HostRunTask.h"

#include <iostream>

HostRunTask::HostRunTask( const std::string& command ) :
    m_command( command )
{
}

HostRunTask::~HostRunTask()
{
}

bool HostRunTask::executeTask()
{
    bool result = false;

#ifdef _WIN32
    STARTUPINFO startupInfo = { 0 };
    PROCESS_INFORMATION processInfo = { 0 };

    startupInfo.cb = sizeof( STARTUPINFO );

    if( CreateProcess( NULL,
                       (LPSTR) m_command.c_str(),
                       NULL,                // process attributes
                       NULL,                // thread attributes
                       FALSE,               // inherit handles
                       0,                   // creation flags
                       NULL,                // environment
                       NULL,                // current directory
                       &startupInfo,
                       &processInfo ) )
    {
        std::cout << "Started process " << m_command << " and waiting for completion..." << std::endl;

        if( WAIT_OBJECT_0 == WaitForSingleObject( processInfo.hProcess, INFINITE ) )
        {
            std::cout << "Process complete." << std::endl;

            result = true;
        }
        else
        {
            std::cout << "Failed to wait for process completion." << std::endl;
        }

        (void) CloseHandle( processInfo.hProcess );
        (void) CloseHandle( processInfo.hThread );
    }
    else
    {
        std::cout << "Failed to create process: " << m_command << std::endl;
    }
#else
    if( 0 == system( m_command.c_str() ) )
    {
        result = true;
    }
#endif

    return result;
}

