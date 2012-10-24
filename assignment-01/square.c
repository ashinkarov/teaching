#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif



#define DATA_SIZE 1024

const char *KernelSource =		   "\n"
  "__kernel void square(                    \n"
  "   __global float* input,                \n"
  "   __global float* output,               \n"
  "   const unsigned int count)             \n"
  "{                                        \n"
  "   int i = get_global_id(0);             \n"
  "   if(i < count)                         \n"
  "       output[i] = input[i] * input[i];  \n"
  "}                                        \n"
  "\n";

#define die(msg, ...) do {                      \
  (void) fprintf (stderr, msg, ## __VA_ARGS__); \
  (void) fprintf (stderr, "\n");                \
  goto out;                                     \
} while (0)

int
main (int argc, char *argv[])
{
  int devType = CL_DEVICE_TYPE_GPU;

  cl_int err;			/* Error code returned from api calls.  */
  size_t global;		/* Global domain size for our calculation.  */
  size_t local;			/* Local domain size for our calculation.  */

  cl_platform_id cpPlatform;	/* openCL platform.  */
  cl_device_id device_id;	/* Compute device id.  */
  cl_context context;		/* Compute context.  */
  cl_command_queue commands;	/* Compute command queue.  */
  cl_program program;		/* Compute program.  */
  cl_kernel kernel;		/* Compute kernel.  */

  /* Create data for the run.  */
  float *data = NULL;		/* Original data set given to device.  */
  float *results = NULL;	/* Results returned from device.  */
  unsigned int correct;		/* Number of correct results returned.  */
  cl_mem input;			/* Device memory used for the input array.  */
  cl_mem output;		/* Device memory used for the output array.  */

  unsigned int count = DATA_SIZE;
  int rc = EXIT_FAILURE;

  if (argc > 1)
    {
      devType = CL_DEVICE_TYPE_CPU;
      printf ("Using: CL_DEVICE_TYPE_CPU\n");
    }
  else
    printf ("Using: CL_DEVICE_TYPE_GPU\n");

  /* Connect to a compute device.  */
  if (CL_SUCCESS != clGetPlatformIDs (1, &cpPlatform, NULL))
    die ("Error: Failed to find a platform!");

  /* Get a device of the appropriate type.  */
  if (CL_SUCCESS != clGetDeviceIDs (cpPlatform, devType, 1, &device_id, NULL))
    die ("Error: Failed to create a device group!");

  /* Create a compute context.  */
  context = clCreateContext (0, 1, &device_id, NULL, NULL, &err);
  if (!context || err != CL_SUCCESS)
    die ("Error: Failed to create a compute context!");

  /* Create a command commands.  */
  commands = clCreateCommandQueue (context, device_id, 0, &err);
  if (!commands || err != CL_SUCCESS)
    die ("Error: Failed to create a command commands!");

  /* Create the compute program from the source buffer.  */
  program = clCreateProgramWithSource (context, 1,
				       (const char **) &KernelSource,
				       NULL, &err);
  if (!program || err != CL_SUCCESS)
    die ("Error: Failed to create compute program!");

  /* Build the program executable.  */
  err = clBuildProgram (program, 0, NULL, NULL, NULL, NULL);
  if (err != CL_SUCCESS)
    {
      size_t len;
      char buffer[2048];

      clGetProgramBuildInfo (program, device_id, CL_PROGRAM_BUILD_LOG,
			     sizeof (buffer), buffer, &len);
      die ("Error: Failed to build program executable!\n%s", buffer);
    }

  /* Create the compute kernel in the program.  */
  kernel = clCreateKernel (program, "square", &err);
  if (!kernel || err != CL_SUCCESS)
    die ("Error: Failed to create compute kernel!");

  data = (float *) malloc (DATA_SIZE * sizeof (float));
  results = (float *) malloc (DATA_SIZE * sizeof (float));

  /* Fill the vector with random float values.  */
  for (unsigned i = 0; i < count; i++)
    data[i] = rand () / (float) RAND_MAX;

  /* Create the device memory vectors.  */
  input = clCreateBuffer (context, CL_MEM_READ_ONLY,
			  sizeof (float) * count, NULL, NULL);
  output = clCreateBuffer (context, CL_MEM_WRITE_ONLY,
			   sizeof (float) * count, NULL, NULL);
  if (!input || !output)
    die ("Error: Failed to allocate device memory!");

  /* Transfer the input vector into device memory.  */
  if (CL_SUCCESS
      != clEnqueueWriteBuffer (commands, input,
			       CL_TRUE, 0, sizeof (float) * count,
			       data, 0, NULL, NULL))
    die ("Error: Failed to write to source array!");

  /* Set the arguments to the compute kernel.  */
  err = 0;
  err = clSetKernelArg (kernel, 0, sizeof (cl_mem), &input);
  err |= clSetKernelArg (kernel, 1, sizeof (cl_mem), &output);
  err |= clSetKernelArg (kernel, 2, sizeof (unsigned int), &count);
  if (err != CL_SUCCESS)
    die ("Error: Failed to set kernel arguments!");

  /* Get the maximum work group size for executing the kernel on the device.  */
  if (CL_SUCCESS
      != clGetKernelWorkGroupInfo (kernel, device_id,
				   CL_KERNEL_WORK_GROUP_SIZE,
				   sizeof (local), &local, NULL))
    die ("Error: Failed to retrieve kernel work group info!");

  /* Execute the kernel over the vector using the
     maximum number of work group items for this device.  */
  global = count;
  if (CL_SUCCESS
      != clEnqueueNDRangeKernel (commands, kernel,
				 1, NULL, &global, &local, 0, NULL, NULL))
    die ("Error: Failed to execute kernel!");

  /* Wait for all commands to complete.  */
  clFinish (commands);

  /* Read back the results from the device to verify the output.  */
  if (CL_SUCCESS
      != clEnqueueReadBuffer (commands, output,
			      CL_TRUE, 0, sizeof (float) * count,
			      results, 0, NULL, NULL))
    die ("Error: Failed to read output array!");

  /* Validate our results.  */
  correct = 0;
  for (unsigned i = 0; i < count; i++)
    if (results[i] == data[i] * data[i])
      correct++;

  /* Print a brief summary detailing the results.  */
  printf ("Computed %d/%d %2.0f%% correct values\n", correct, count,
	  (float)count/correct*100.f);

  clReleaseMemObject (input);
  clReleaseMemObject (output);
  clReleaseProgram (program);
  clReleaseKernel (kernel);
  clReleaseCommandQueue (commands);
  clReleaseContext (context);

  rc = EXIT_SUCCESS;

out:
  /* Shutdown and cleanup.  */
  if (data)
    free (data);

  if (results)
    free (results);

  return rc;
}
