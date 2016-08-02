#ifdef _WIN32
#include <Windows.h>
#include <Shellapi.h>
#include <Shlwapi.h>
#endif

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "HostDeleteTask.h"

HostDeleteTask::HostDeleteTask( const std::string& path ) :
    m_path( path )
{
}

HostDeleteTask::~HostDeleteTask()
{
}

bool HostDeleteTask::executeTask()
{
    bool result = false;

#ifdef _WIN32
    DWORD attr = GetFileAttributesA( m_path.c_str() );
    SHFILEOPSTRUCT operation = { 0 };
    char*   pathDouble = NULL;
    int retCode = 0;
    bool removeDirectory = false;

    // Only operate on absolute paths.
    if( FALSE == PathIsRelative( m_path.c_str() ) )
    {
        // Need to make a double null terminated string for the SHFileOperation API.
        // Also leaving room to add "\*" if needed.
        
        pathDouble = (char*) malloc( m_path.length() + 4 );
        if( pathDouble )
        {
            memset( pathDouble, 0, m_path.length() + 4 );
            memcpy( pathDouble, m_path.c_str(), m_path.length() );

            operation.wFunc = FO_DELETE;
            operation.pFrom = pathDouble;
            operation.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT;

            if( FILE_ATTRIBUTE_DIRECTORY & attr )
            {
                std::cout << "Deleting directory " << m_path << std::endl;
                strcat( pathDouble, "\\*" );
                removeDirectory = true;
            }
            else
            {
                std::cout << "Deleting file " << m_path << std::endl;
            }

            retCode = SHFileOperation( &operation );
            if( 0 == retCode )
            {
                result = true;

                if( removeDirectory )
                {
                    result = false;

                    if( RemoveDirectory( m_path.c_str() ) )
                    {
                        result = true;
                    }
                }

                if( result )
                {
                    std::cout << "Delete successful." << std::endl;
                }
            }
            else
            {
                std::cout << "Delete failed with error " << retCode << std::endl;
            }

            free( pathDouble );
        }
    }
    else
    {
        std::cout << "Specified path is relative. Please specify an absolute path." << std::endl;
    }

#else
    // TODO
#endif

    return result;
}

