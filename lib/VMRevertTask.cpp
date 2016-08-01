#include "VMRevertTask.h"

#include "vix.h"

#include <iostream>

VMRevertTask::VMRevertTask( const std::string& vmxPath ) :
    m_vmxPath( vmxPath )
{
}

VMRevertTask::~VMRevertTask()
{
}

bool VMRevertTask::executeTask()
{
    bool        result          = false;
    VixError    err             = 0;
    VixHandle   jobHandle       = VIX_INVALID_HANDLE;
    VixHandle   hostHandle      = VIX_INVALID_HANDLE;
    VixHandle   vmHandle        = VIX_INVALID_HANDLE;
    VixHandle   snapshotHandle  = VIX_INVALID_HANDLE;
    int         numSnapshots    = 0;

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

            err = VixVM_GetNumRootSnapshots( vmHandle, &numSnapshots );

            if( !VIX_FAILED( err ) )
            {
                if( numSnapshots >= 1 )
                {
                    // Revert to the newest snapshot.
                    err = VixVM_GetRootSnapshot( vmHandle, numSnapshots - 1, &snapshotHandle );

                    if( !VIX_FAILED( err ) )
                    {
                        jobHandle = VixVM_RevertToSnapshot( vmHandle,
                                                            snapshotHandle,
                                                            0, 
                                                            VIX_INVALID_HANDLE,
                                                            NULL,       // Callback
                                                            NULL );     // Client data

                        std::cout << "Reverting virtual machine to latest snapshot..." << std::endl;

                        err = VixJob_Wait( jobHandle, VIX_PROPERTY_NONE );

                        Vix_ReleaseHandle( jobHandle );

                        if( !VIX_FAILED( err ) )
                        {
                            std::cout << "Successfully reverted virtual machine to latest snapshot." << std::endl;

                            result = true;
                        }
                        else
                        {
                            std::cout << "Failed to revert to latest snapshot." << std::endl;
                        }

                        Vix_ReleaseHandle( snapshotHandle );
                    }
                    else
                    {
                        std::cout << "Failed to open latest snapshot." << std::endl;
                    }
                }
                else
                {
                    std::cout << "No snapshots exist for the specified virtual machine." << std::endl;
                }
            }
            else
            {
                std::cout << "Failed to determine number of snapshots for virtual machine." << std::endl;
            }

            Vix_ReleaseHandle( vmHandle );
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

