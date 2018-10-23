# TEEShift

A small proof of concept for shifting function into a TEE using the Asylo Library.

See the paper for general ideas (https://dl.acm.org/citation.cfm?doid=3268935.3268938)

### Implementation Details

#### Python Part :

TEEShift.py  takes the target binary as argument and generate the C/C++ code to generate the Library which use the Asylo Framework
When generating the code, you have to precise which function to hook.

####  asylo_lib_bin

This directory contains every file developped for the Asylo Library.
You can follow the Asylo tutorial for the creation of a new project with Bazel and compile it.

### TODO :
Implement the "Dereference Mechanism" to replace every dereference inside the enclave.
Update to rely on the last version of asylo (Modifications on GRPC System)
