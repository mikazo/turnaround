#include "VMRunTask.h"

#include "vix.h"

#include <iostream>
#include <sstream>

VMRunTask::VMRunTask( const std::string& vmxPath, const std::string& command ) :
    m_vmxPath( vmxPath ),
    m_command( command )
{
}

VMRunTask::~VMRunTask()
{
}

bool VMRunTask::executeTask()
{
    bool        result          = false;
    VixError    err             = 0;
    VixHandle   jobHandle       = VIX_INVALID_HANDLE;
    VixHandle   hostHandle      = VIX_INVALID_HANDLE;
    VixHandle   vmHandle        = VIX_INVALID_HANDLE;

    jobHandle = VixHost_Connect( VIX_API_VERSION,
                                 VIX_SERVICEPROVIDER_VMWARE_WORKSTATION,
                                 "",                    // Host name
                                 0,                     // Host port
                                 "",                    // Username
                                 "",                    // Password
                                 0,                     // Options
                                 VIX_INVALID_HANDLE,    // propertyListHandle
                                 NULL,                  // Callback
                                 NULL );                // Client data

    std::cout << "Connecting to VMware Workstation..." << std::endl;

    err = VixJob_Wait( jobHandle,
                       VIX_PROPERTY_JOB_RESULT_HANDLE,
                       &hostHandle,
                       VIX_PROPERTY_NONE );

    Vix_ReleaseHandle( jobHandle );

    if( !VIX_FAILED( err ) )
    {
        std::cout << "Successfully connected to VMware Workstation." << std::endl;

        jobHandle = VixVM_Open( hostHandle, 
                                m_vmxPath.c_str(),
                                NULL,       // VixEventProc callback
                                NULL );     // Client data

        std::cout << "Opening virtual machine..." << std::endl;

        err = VixJob_Wait( jobHandle,
                           VIX_PROPERTY_JOB_RESULT_HANDLE,
                           &vmHandle,
                           VIX_PROPERTY_NONE );

        Vix_ReleaseHandle( jobHandle );

        if( !VIX_FAILED( err ) )
        {
            std::cout << "Successfully opened virtual machine." << std::endl;

            jobHandle = VixVM_WaitForToolsInGuest( vmHandle,
                                                   30,      // seconds to timeout
                                                   NULL,    // callback
                                                   NULL );  // client data

            std::cout << "Waiting for VMware Tools..." << std::endl;

            err = VixJob_Wait( jobHandle, VIX_PROPERTY_NONE );

            Vix_ReleaseHandle( jobHandle );

            if( !VIX_FAILED( err ) )
            {
                std::cout << "VMware Tools ready." << std::endl;

                std::stringstream commandLine( m_command );
                std::string program;

                std::getline( commandLine, program, ' ' );

                std::string arguments( commandLine.str() );

                jobHandle = VixVM_RunProgramInGuest( vmHandle,
                                                     program.c_str(),
                                                     arguments.c_str(),
                                                     0,                     // options
                                                     VIX_INVALID_HANDLE,    // prop handle
                                                     NULL,                  // callback
                                                     NULL );                // client data

                std::cout << "Running program: " << m_command << std::endl;

                err = VixJob_Wait( jobHandle, VIX_PROPERTY_NONE );

                Vix_ReleaseHandle( jobHandle );

                if( !VIX_FAILED( err ) )
                {
                    result = true;
                }
                else
                {
                    std::cout << "Failed to run program." << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to wait for VMware Tools." << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to open specified virtual machine." << std::endl;
        }

        VixHost_Disconnect( hostHandle );
    }
    else
    {
        std::cout << "Failed to connect to VMware Workstation." << std::endl;
    }

    return result;
}

