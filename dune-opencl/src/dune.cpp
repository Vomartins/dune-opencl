#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <CL/cl.h>

#include <dune/common/exceptions.hh> // We use exceptions
#include <dune/istl/matrix.hh> // block vector definition 

// Other forward declarations
char* readKernelFile(const char* filename, long* _size){

    // Open the file
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("-- Error opening file %s\n", filename);
        exit(1);
    }

    // Get its size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // Read the kernel code as a string
    char* source = (char *)malloc((size+1)*sizeof(char));
    fread(source, 1, size*sizeof(char), file);
    source[size] = '\0';
    fclose(file);

    // Save the size and return the source string
    *_size = (size+1);
    return source;
}

// Print an error message to screen (only if it occurs)
void checkError(cl_int error, int line) {
    if (error != CL_SUCCESS) {
        switch (error) {
            case CL_DEVICE_NOT_FOUND:                 printf("-- Error at %d:  Device not found.\n", line); break;
            case CL_DEVICE_NOT_AVAILABLE:             printf("-- Error at %d:  Device not available\n", line); break;
            case CL_COMPILER_NOT_AVAILABLE:           printf("-- Error at %d:  Compiler not available\n", line); break;
            case CL_MEM_OBJECT_ALLOCATION_FAILURE:    printf("-- Error at %d:  Memory object allocation failure\n", line); break;
            case CL_OUT_OF_RESOURCES:                 printf("-- Error at %d:  Out of resources\n", line); break;
            case CL_OUT_OF_HOST_MEMORY:               printf("-- Error at %d:  Out of host memory\n", line); break;
            case CL_PROFILING_INFO_NOT_AVAILABLE:     printf("-- Error at %d:  Profiling information not available\n", line); break;
            case CL_MEM_COPY_OVERLAP:                 printf("-- Error at %d:  Memory copy overlap\n", line); break;
            case CL_IMAGE_FORMAT_MISMATCH:            printf("-- Error at %d:  Image format mismatch\n", line); break;
            case CL_IMAGE_FORMAT_NOT_SUPPORTED:       printf("-- Error at %d:  Image format not supported\n", line); break;
            case CL_BUILD_PROGRAM_FAILURE:            printf("-- Error at %d:  Program build failure\n", line); break;
            case CL_MAP_FAILURE:                      printf("-- Error at %d:  Map failure\n", line); break;
            case CL_INVALID_VALUE:                    printf("-- Error at %d:  Invalid value\n", line); break;
            case CL_INVALID_DEVICE_TYPE:              printf("-- Error at %d:  Invalid device type\n", line); break;
            case CL_INVALID_PLATFORM:                 printf("-- Error at %d:  Invalid platform\n", line); break;
            case CL_INVALID_DEVICE:                   printf("-- Error at %d:  Invalid device\n", line); break;
            case CL_INVALID_CONTEXT:                  printf("-- Error at %d:  Invalid context\n", line); break;
            case CL_INVALID_QUEUE_PROPERTIES:         printf("-- Error at %d:  Invalid queue properties\n", line); break;
            case CL_INVALID_COMMAND_QUEUE:            printf("-- Error at %d:  Invalid command queue\n", line); break;
            case CL_INVALID_HOST_PTR:                 printf("-- Error at %d:  Invalid host pointer\n", line); break;
            case CL_INVALID_MEM_OBJECT:               printf("-- Error at %d:  Invalid memory object\n", line); break;
            case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR:  printf("-- Error at %d:  Invalid image format descriptor\n", line); break;
            case CL_INVALID_IMAGE_SIZE:               printf("-- Error at %d:  Invalid image size\n", line); break;
            case CL_INVALID_SAMPLER:                  printf("-- Error at %d:  Invalid sampler\n", line); break;
            case CL_INVALID_BINARY:                   printf("-- Error at %d:  Invalid binary\n", line); break;
            case CL_INVALID_BUILD_OPTIONS:            printf("-- Error at %d:  Invalid build options\n", line); break;
            case CL_INVALID_PROGRAM:                  printf("-- Error at %d:  Invalid program\n", line); break;
            case CL_INVALID_PROGRAM_EXECUTABLE:       printf("-- Error at %d:  Invalid program executable\n", line); break;
            case CL_INVALID_KERNEL_NAME:              printf("-- Error at %d:  Invalid kernel name\n", line); break;
            case CL_INVALID_KERNEL_DEFINITION:        printf("-- Error at %d:  Invalid kernel definition\n", line); break;
            case CL_INVALID_KERNEL:                   printf("-- Error at %d:  Invalid kernel\n", line); break;
            case CL_INVALID_ARG_INDEX:                printf("-- Error at %d:  Invalid argument index\n", line); break;
            case CL_INVALID_ARG_VALUE:                printf("-- Error at %d:  Invalid argument value\n", line); break;
            case CL_INVALID_ARG_SIZE:                 printf("-- Error at %d:  Invalid argument size\n", line); break;
            case CL_INVALID_KERNEL_ARGS:              printf("-- Error at %d:  Invalid kernel arguments\n", line); break;
            case CL_INVALID_WORK_DIMENSION:           printf("-- Error at %d:  Invalid work dimensionsension\n", line); break;
            case CL_INVALID_WORK_GROUP_SIZE:          printf("-- Error at %d:  Invalid work group size\n", line); break;
            case CL_INVALID_WORK_ITEM_SIZE:           printf("-- Error at %d:  Invalid work item size\n", line); break;
            case CL_INVALID_GLOBAL_OFFSET:            printf("-- Error at %d:  Invalid global offset\n", line); break;
            case CL_INVALID_EVENT_WAIT_LIST:          printf("-- Error at %d:  Invalid event wait list\n", line); break;
            case CL_INVALID_EVENT:                    printf("-- Error at %d:  Invalid event\n", line); break;
            case CL_INVALID_OPERATION:                printf("-- Error at %d:  Invalid operation\n", line); break;
            case CL_INVALID_GL_OBJECT:                printf("-- Error at %d:  Invalid OpenGL object\n", line); break;
            case CL_INVALID_BUFFER_SIZE:              printf("-- Error at %d:  Invalid buffer size\n", line); break;
            case CL_INVALID_MIP_LEVEL:                printf("-- Error at %d:  Invalid mip-map level\n", line); break;
            case -1024:                               printf("-- Error at %d:  *clBLAS* Functionality is not implemented\n", line); break;
            case -1023:                               printf("-- Error at %d:  *clBLAS* Library is not initialized yet\n", line); break;
            case -1022:                               printf("-- Error at %d:  *clBLAS* Matrix A is not a valid memory object\n", line); break;
            case -1021:                               printf("-- Error at %d:  *clBLAS* Matrix B is not a valid memory object\n", line); break;
            case -1020:                               printf("-- Error at %d:  *clBLAS* Matrix C is not a valid memory object\n", line); break;
            case -1019:                               printf("-- Error at %d:  *clBLAS* Vector X is not a valid memory object\n", line); break;
            case -1018:                               printf("-- Error at %d:  *clBLAS* Vector Y is not a valid memory object\n", line); break;
            case -1017:                               printf("-- Error at %d:  *clBLAS* An input dimension (M,N,K) is invalid\n", line); break;
            case -1016:                               printf("-- Error at %d:  *clBLAS* Leading dimension A must not be less than the size of the first dimension\n", line); break;
            case -1015:                               printf("-- Error at %d:  *clBLAS* Leading dimension B must not be less than the size of the second dimension\n", line); break;
            case -1014:                               printf("-- Error at %d:  *clBLAS* Leading dimension C must not be less than the size of the third dimension\n", line); break;
            case -1013:                               printf("-- Error at %d:  *clBLAS* The increment for a vector X must not be 0\n", line); break;
            case -1012:                               printf("-- Error at %d:  *clBLAS* The increment for a vector Y must not be 0\n", line); break;
            case -1011:                               printf("-- Error at %d:  *clBLAS* The memory object for Matrix A is too small\n", line); break;
            case -1010:                               printf("-- Error at %d:  *clBLAS* The memory object for Matrix B is too small\n", line); break;
            case -1009:                               printf("-- Error at %d:  *clBLAS* The memory object for Matrix C is too small\n", line); break;
            case -1008:                               printf("-- Error at %d:  *clBLAS* The memory object for Vector X is too small\n", line); break;
            case -1007:                               printf("-- Error at %d:  *clBLAS* The memory object for Vector Y is too small\n", line); break;
            case -1001:                               printf("-- Error at %d:  Code -1001: no GPU available?\n", line); break;
            default:                                  printf("-- Error at %d:  Unknown with code %d\n", line, error);
        }
        exit(1);
    }
}

// =================================================================================================

// Repeat all kernels multiple times to get an average timing result
#define NUM_RUNS 100

// Size of the matrices - K, M, N (squared)
#define SIZE 512

// Threadblock sizes (e.g. for kernels myGEMM1 or myGEMM2)
#define TS 16

// Kernel file path
#define CL_KERNEL_FILE "/home/vinicius/Documentos/OpenCL/dune-opencl/dune-opencl/src/kernels.cl"

// Define OpenCL compiler options, such as "-cl-nv-maxrregcount=127"
#define COMPILER_OPTIONS ""

// Determine the location where to output the PTX code
#define CL_PTX_FILE "bin/myGEMM.cl.ptx"

// Select kernel
#define KERNEL 1

// OpenCL settings
#define MAX_NUM_DEVICES 16
#define MAX_DEVICE_NAME 1024
#define CURRENT_DEVICE 0

int main(){

    // Timers
    struct timeval Tvalue;
    struct timezone dummy;

    // Matrices dimentions
    const int K = SIZE;
    const int M = SIZE;
    const int N = SIZE;

    // Matrices allocation
    // Dune Matrices definition
    Dune::Matrix<float> A(M,K);
    Dune::Matrix<float> B(K,N);
    Dune::Matrix<float> C(M,N);

    // Elements initialization

    for (int i=0; i<M; i++) {
        for (int j=0; j<K; j++) {
            A[i][j] = 3.6*i+i*j+3.1;
        }
    }

    for (int i=0; i<K; i++) {
        for (int j=0; j<N; j++) {
            B[i][j] = 1.3*i+0.1*i*j+1.0;
        }
    }

    for (int i=0; i<M; i++) {
        for (int j=0; j<K; j++) {
            C[i][j] = 0.0;
        }
    }

    // **********************************************************
    //              OpenCL configuration
    // **********************************************************


    // Define OpenCL variables
    cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_device_id devices[MAX_NUM_DEVICES];
    cl_uint numDevices = 0;
    cl_context_properties props[3] = {CL_CONTEXT_PLATFORM, 0, 0};
    cl_context context = 0;
    cl_command_queue queue = 0;
    cl_event event = NULL;
    cl_program program = NULL;
    char deviceName[MAX_DEVICE_NAME];
    
    // Configure the OpenCL environment
    err = clGetPlatformIDs(1, &platform, NULL);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
    device = devices[CURRENT_DEVICE];
    props[1] = (cl_context_properties)platform;
    context = clCreateContext(props, 1, &device, NULL, NULL, &err);
    queue = clCreateCommandQueue(context, device, 0, &err);
    err = clGetDeviceInfo(device, CL_DEVICE_NAME, MAX_DEVICE_NAME, deviceName, NULL);
    checkError(err,__LINE__);
    printf("## %d devices, running on %d: '%s'\n", numDevices, CURRENT_DEVICE, deviceName);
    
    // Read the kernel file from disk
    long sizeSource;
    char* source = readKernelFile(CL_KERNEL_FILE, &sizeSource);
    long size = 2 + sizeSource;
    char* code = (char*)malloc(size*sizeof(char));
    for (int c=0; c<size; c++) { code[c] = '\0'; }
    strcat(code, source);
    const char* constCode = code;
    free(source);
    
    // Compile the kernel file
    program = clCreateProgramWithSource(context, 1, &constCode, NULL, &err);
    checkError(err,__LINE__);
    err = clBuildProgram(program, 0, NULL, COMPILER_OPTIONS, NULL, NULL);
    checkError(err,__LINE__);
    
    // Check for compilation errors
    size_t logSize;
    err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    checkError(err,__LINE__);
    char* messages = (char*)malloc((1+logSize)*sizeof(char));
    err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, messages, NULL);
    checkError(err,__LINE__);
    messages[logSize] = '\0';
    if (logSize > 10) { printf("## Compiler message: %s\n", messages); }
    free(messages);
    
    // OpenCL memory buffers
    cl_mem bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, M*K*sizeof(float), NULL, NULL);
    cl_mem bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, K*N*sizeof(float), NULL, NULL);
    cl_mem bufferC = clCreateBuffer(context, CL_MEM_READ_WRITE, M*N*sizeof(float), NULL, NULL);
    printf("OK\n");
    // Copy matrices to GPU
    clEnqueueWriteBuffer(queue, bufferA, CL_TRUE, 0, M*K*sizeof(float), &A, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufferB, CL_TRUE, 0, K*N*sizeof(float), &B, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufferC, CL_TRUE, 0, M*N*sizeof(float), &C, 0, NULL, NULL);
    printf("OK\n");
    // Configure kernel
    cl_kernel kernel = clCreateKernel(program, "naiveGEMM", &err);
    checkError(err,__LINE__);
    clSetKernelArg(kernel, 0, sizeof(int), (void *)&M);
    clSetKernelArg(kernel, 1, sizeof(int), (void *)&N);
    clSetKernelArg(kernel, 2, sizeof(int), (void *)&K);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&bufferA);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&bufferB);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&bufferC);
    

    // Loop for multiple kernel runs
    printf("***** Starting %d runs *****\n", NUM_RUNS);
    gettimeofday(&Tvalue, &dummy);
    double startTime = (double)Tvalue.tv_sec + 1.0e-6*((double)Tvalue.tv_usec);
    for (int i=0; i<NUM_RUNS; i++) {
        //Run kernel
        const size_t local[2] = {TS, TS};
        const size_t global[2] = {M, N};
        err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, global, local, 0, NULL, &event);
        checkError(err,__LINE__);
        clWaitForEvents(1, &event);
    }

    // Time spent calculation
    gettimeofday(&Tvalue, &dummy);
    double endTime = (double)Tvalue.tv_sec + 1.0e-6*((double)Tvalue.tv_usec);
    double runTime = (endTime - startTime)/(double)NUM_RUNS;
    double gflop = ((long)K*(long)M*(long)N*2)/(1000*1000*1000);
    printf(">>> Done: took %.10lf seconds per run, %.1lf GFLOPS\n", runTime, gflop/runTime);

    // Copy matrix C back to the CPU
    clEnqueueReadBuffer(queue, bufferC, CL_TRUE, 0, M*N*sizeof(float), &C, 0, NULL, NULL);

    // Free OpenCL memory objects
    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferC);

    // Free others OpenCL objects
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    clReleaseProgram(program);
    clReleaseKernel(kernel);

    // Free matrices
    //free(A);
    //free(B);
    //free(C);

    return 0;
}