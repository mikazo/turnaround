#include "VMRunTask.h"

#include "vix.h"

#include <iostream>
#include <sstream>

VMRunTask::VMRunTask( const std::string& vmxPath,
                      const std::string& username,
                      const std::string& password,
                      const std::string& command,
                      bool waitForCompletion ) :
    m_vmxPath( vmxPath ),
    m_username( username ),
    m_password( password ),
    m_command( command ),
    m_waitForCompletion( waitForCompletion )
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

                jobHandle = VixVM_LoginInGuest( vmHandle,
                                                m_username.c_str(),
                                                m_password.c_str(),
                                                0,          // options
                                                NULL,       // callback
                                                NULL );     // client data

                std::cout << "Logging in to VM..." << std::endl;

                err = VixJob_Wait( jobHandle, VIX_PROPERTY_NONE );

                Vix_ReleaseHandle( jobHandle );

                if( !VIX_FAILED( err ) )
                {
                    std::cout << "Logged in to VM." << std::endl;

                    std::string program;
                    std::string arguments( "" );

                    if( std::string::npos != m_command.find( " " ) )
                    {
                        // The command line has arguments, so parse them out.

                        std::stringstream commandLine( m_command );

                        std::getline( commandLine, program, ' ' );

                        arguments = commandLine.str();
                    }
                    else
                    {
                        // The command line does not have arguments.

                        program = m_command;
                    }

                    jobHandle = VixVM_RunProgramInGuest( vmHandle,
                                                         program.c_str(),
                                                         arguments.c_str(),
                                                         VIX_LOGIN_IN_GUEST_REQUIRE_INTERACTIVE_ENVIRONMENT,
                                                         VIX_INVALID_HANDLE,    // prop handle
                                                         NULL,                  // callback
                                                         NULL );                // client data

                    std::cout << "Running program: " << program << " " << arguments << std::endl;

                    if( m_waitForCompletion )
                    {
                        std::cout << "Waiting for completion..." << std::endl;

                        err = VixJob_Wait( jobHandle, VIX_PROPERTY_NONE );

                        if( !VIX_FAILED( err ) )
                        {
                            std::cout << "Program completed." << std::endl;

                            result = true;
                        }
                        else
                        {
                            std::cout << "Failed to run program." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "Not waiting for completion." << std::endl;

                        result = true;
                    }

                    Vix_ReleaseHandle( jobHandle );
                }
                else
                {
                    std::cout << "Failed to log in to VM." << std::endl;
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

