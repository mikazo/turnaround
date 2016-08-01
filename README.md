# Turnaround
A tool to reduce the turnaround time between code changes and feedback. Turnaround executes a list of defined tasks in sequence. Task types and parameters are defined in XML.

# Requirements
Xerces-C++ XML Parser  
VMware VIX API  
Scons

# Supported Tasks
Run a program  
Change the current working directory  
Copy a file into or out of a VMware virtual machine  
Revert a VMware virtual machine  
Run a program inside a VMware virtual machine

# Example Workflows
1. Compile code (command line task)
2. Revert VM snapshot to clean state
3. Copy executable file into VM
4. Copy symbol file into VM
5. Execute debugger inside VM, with arguments for copied executable and its symbols

The result is that the developer makes a code change, executes Turnaround, and within moments is presented with a debugger inside a VM, stopped at the exact breakpoint needed to examine the effects of the code changes.

1. Compile code inside a build VM
2. Copy resulting binary out of VM onto host
3. Package the binary on the host
4. Copy the package into the VM
5. Run the package in the VM
