#include <CL/cl.h>
#include "device_test.h"
#include <stdio.h>
#include <string.h>

JNIEXPORT jint JNICALL Java_com_ee_cldevicetest_CLDeviceTestActivity_updateBuffer
  (JNIEnv *env, jobject obj, jobject buffer) {

    cl_platform_id platform;
    cl_device_id device;
    char name_data[48], vendor[64], version[64], ext_data[512];
    unsigned int image_support = 0, max_frequency = 0, work_group_size = 0;
    unsigned int max_compute_units = 0, max_image_height = 0, max_image_width = 0;
    unsigned long max_global_size = 0, max_local_size = 0;
    jint ret = 0, pos = 0;

	void *buff = (*env)->GetDirectBufferAddress(env, buffer);
    clGetPlatformIDs(1, &platform, NULL);
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);

    // Read device name
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name_data), name_data, &ret);
    memcpy(buff, name_data, ret);
    pos = ret;
    sprintf(buff + pos++, ",");

    // Read device vendor
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendor), vendor, &ret);
    memcpy(buff + pos, vendor, ret);
    pos += ret;
    sprintf(buff + pos++, ",");

    // Read supported version
    clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(version), version, &ret);
    memcpy(buff + pos, version, ret);
    pos += ret;
    sprintf(buff + pos++, ",");

    // Find maximum frequency
    clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_frequency), &max_frequency, NULL);
    pos += sprintf(buff + pos, "%u MHz,", max_frequency);

    // Find the maximum number of compute units
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_compute_units), &max_compute_units, NULL);
    pos += sprintf(buff + pos, "%u,", max_compute_units);

    // Find the maximum work-group size
    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(work_group_size), &work_group_size, NULL);
    pos += sprintf(buff + pos, "%u work-items per group,", work_group_size);

    // Find the maximum size of global memory
    clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(max_global_size), &max_global_size, NULL);
    pos += sprintf(buff + pos, "%lu bytes,", max_global_size);

    // Find the maximum size of global memory
    clGetDeviceInfo(device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(max_local_size), &max_local_size, NULL);
    pos += sprintf(buff + pos, "%lu bytes,", max_local_size);

    // Find out if device supports images
    clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, sizeof(image_support), &image_support, NULL);
    pos += sprintf(buff + pos, (image_support)? "true," : "false,");

    // Find maximum image width
    clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_WIDTH, sizeof(max_image_width), &max_image_width, NULL);
    pos += sprintf(buff + pos, "%u pixels,", max_image_width);

    // Find maximum image height
    clGetDeviceInfo(device, CL_DEVICE_IMAGE2D_MAX_HEIGHT, sizeof(max_image_height), &max_image_height, NULL);
    pos += sprintf(buff + pos, "%u pixels,", max_image_height);

    // Read device extensions
    clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, sizeof(ext_data), ext_data, &ret);
    memcpy(buff + pos, ext_data, ret);
    pos += ret;
    sprintf(buff + pos++, ",");

    return pos;
}
