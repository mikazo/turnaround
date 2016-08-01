# Turnaround
A tool to reduce the turnaround time between code changes and feedback. Turnaround executes a list of defined tasks in sequence. Task types and parameters are defined in XML.

# Requirements
Xerces-C++ XML Parser  
Scons

# Supported Tasks
Run a program
Change the current working directory
Copy a file into a VMware virtual machine
Revert a VMware virtual machine
Run a program inside a VMware virtual machine

# Example Workflow
1. Compile code (command line task)
2. Revert VM snapshot to clean state
3. Copy executable file into VM
4. Copy symbol file into VM
5. Execute debugger inside VM, with arguments for copied executable and its symbols

The result is that the developer makes a code change, executes Turnaround, and within moments is presented with a debugger inside a VM, stopped at the exact breakpoint needed to examine the effects of the code changes.
