#include "VMFileCopyTask.h"

#include "vix.h"

#include <iostream>

VMFileCopyTask::VMFileCopyTask( const std::string& vmxPath,
                                FileCopyType fileCopyType,
                                const std::string& source,
                                const std::string& destination ) :
    m_vmxPath( vmxPath ),
    m_fileCopyType( fileCopyType ),
    m_source( source ),
    m_destination( destination )
{
}

VMFileCopyTask::~VMFileCopyTask()
{
}

bool VMFileCopyTask::executeTask()
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

                if( HOST_TO_VM == m_fileCopyType )
                {
                    std::cout << "Copying host file " << m_source << " to destination VM file " << m_destination << std::endl;

                    jobHandle = VixVM_CopyFileFromHostToGuest( vmHandle,
                                                               m_source.c_str(),
                                                               m_destination.c_str(),
                                                               0,                   // options
                                                               VIX_INVALID_HANDLE,  // prop list
                                                               NULL,                // callback
                                                               NULL );              // client data
                }
                else if( VM_TO_HOST == m_fileCopyType )
                {
                    std::cout << "Copying VM file " << m_source << " to destination host file " << m_destination << std::endl;

                    jobHandle = VixVM_CopyFileFromGuestToHost( vmHandle,
                                                               m_source.c_str(),
                                                               m_destination.c_str(),
                                                               0,                   // options
                                                               VIX_INVALID_HANDLE,  // prop list
                                                               NULL,                // callback
                                                               NULL );              // client data
                }

                err = VixJob_Wait( jobHandle, VIX_PROPERTY_NONE );

                Vix_ReleaseHandle( jobHandle );

                if( !VIX_FAILED( err ) )
                {
                    std::cout << "File copy complete." << std::endl;

                    result = true;
                }
                else
                {
                    std::cout << "Failed to copy file." << std::endl;
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

