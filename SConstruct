env = Environment( MSVC_USE_SCRIPT = "f:\\Program Files (x86)\\Microsoft Visual Studio 14.0\\VC\\bin\\vcvars32.bat")

env.Program('bin/turnaround',
            ['lib/xml.cpp',
             'lib/task.cpp',
             'lib/HostRunTask.cpp',
             'lib/HostSetDirTask.cpp',
             'lib/VMFileCopyTask.cpp',
             'lib/VMRevertTask.cpp',
             'lib/VMRunTask.cpp',
             'src/main.cpp'],
             CPPPATH=['lib', 'src', 'inc'],
             LIBPATH=['prebuilt'],
             LIBS=['xerces-c_3', 'VixAllProductsDyn'])
