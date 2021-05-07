
/* 
* This file is part of VL53L1 Platform 
* 
* Copyright (c) 2016, STMicroelectronics - All Rights Reserved 
* 
* License terms: BSD 3-clause "New" or "Revised" License. 
* 
* Redistribution and use in source and binary forms, with or without 
* modification, are permitted provided that the following conditions are met: 
* 
* 1. Redistributions of source code must retain the above copyright notice, this 
* list of conditions and the following disclaimer. 
* 
* 2. Redistributions in binary form must reproduce the above copyright notice, 
* this list of conditions and the following disclaimer in the documentation 
* and/or other materials provided with the distribution. 
* 
* 3. Neither the name of the copyright holder nor the names of its contributors 
* may be used to endorse or promote products derived from this software 
* without specific prior written permission. 
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
* 
*/

#include "vl53l1_platform.h"
#include "vl53l1_error_codes.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <pigpiod_if2.h>
#include <stdio.h>
#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1

/* when not customized by application define dummy one */
#ifndef VL53L1_GetI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L1_GetI2cBus(...) (void)0
#endif

#ifndef VL53L1_PutI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L1_PutI2cBus(...) (void)0
#endif

uint8_t _I2CBuffer[256];
int pigpiodaemonid = -1;
int currentDev = -1;
int leftDeviceHandle = -1;
int rightDeviceHandle = -1;
int left_bus = 1, right_bus = 0;
int address = -1;

void Init_Pigpiod(int daemon_id, int leftBus, int rightBus, int devAddr){
    pigpiodaemonid = daemon_id;
    left_bus = leftBus;
    right_bus = rightBus;
    address = devAddr;
}

void Close_Pigpiod(){
    i2c_close(pigpiodaemonid, leftDeviceHandle);
    i2c_close(pigpiodaemonid, rightDeviceHandle);
}

int _I2CWrite(uint16_t Dev, uint8_t *pdata, uint32_t count) {
  //  printf("\ti2c_write_device beginning: \n");
  //  fflush(stdout);
    if(pigpiodaemonid < 0){
        printf("\tpigpiod daemon is less than 0 \n");
	fflush(stdout);
        return -1;
    }
    //    printf("\ti2c_write_device beginning 2: \n");
    //fflush(stdout);
    int deviceId = (Dev == left_bus) ? leftDeviceHandle : rightDeviceHandle;
    int ir_bus_value = (Dev == left_bus) ? left_bus : right_bus;
    if(deviceId < 0){
        printf("\tattempting to open i2c channel write: \n");
        printf("\tdaemonID: %i, ir_bus_value: %i, address: %i\n", pigpiodaemonid, ir_bus_value, address);	
        deviceId = i2c_open(pigpiodaemonid, ir_bus_value, address, 0);
        printf("\tattempting to open i2c channel device in write, id: %i\n", deviceId);
	fflush(stdout);
        if(deviceId < 0){
            switch(deviceId){
                case PI_BAD_I2C_BUS:
                    break;
                case PI_BAD_I2C_ADDR:
                    break;
                case PI_I2C_OPEN_FAILED:
                    break;
                default:
                    break;
            }
            return VL53L1_ERROR_INVALID_PARAMS;
        }
	else{
	  if(Dev == left_bus){
	        leftDeviceHandle = deviceId;
	  } else {
	        rightDeviceHandle = deviceId;
	  }
	}
    }
    int status = 0;
    //    for(uint32_t i = 0; i < count; i++){
    char buffer[count];
    for(int i = 0; i < count; i++){
      buffer[i] = pdata[i];
    }
    status = i2c_write_device(pigpiodaemonid, deviceId, &buffer, count);
    if (status < 0) {
        printf("\ti2c_write_device failed status: %i\n", status);
        fflush(stdout);
        status = VL53L1_ERROR_UNDEFINED;
        return status;
    }
    return VL53L1_ERROR_NONE;
}

int _I2CRead(uint16_t Dev, uint8_t *pdata, uint32_t count) {
  //printf("\ti2c_read_device beginning: \n");
  //fflush(stdout);
    if(pigpiodaemonid < 0){
        return -1;
    }
    //printf("\ti2c_read_device beginning 2: \n");
    //fflush(stdout);
    int deviceId = (Dev == left_bus) ? leftDeviceHandle : rightDeviceHandle;
    int ir_bus_value = (Dev == left_bus) ? left_bus : right_bus;
    if(deviceId < 0){
        printf("\tattempting to open i2c channel write: \n");
        deviceId = i2c_open(pigpiodaemonid, ir_bus_value, address, 0);
        printf("\tattempting to open i2c channel device in read, id: %i\n", deviceId);
	fflush(stdout);
        if(deviceId < 0){
            switch(deviceId){
                case PI_BAD_I2C_BUS:
                    break;
                case PI_BAD_I2C_ADDR:
                    break;
                case PI_I2C_OPEN_FAILED:
                    break;
                default:
                    break;
            }
            return VL53L1_ERROR_INVALID_PARAMS;
        }
	else{
	    if(Dev == left_bus){
	        leftDeviceHandle = deviceId;
	    } else {
	        rightDeviceHandle = deviceId;
	    }
	}
    }
    char * ptr = pdata;
    int status = 0;
    //    for(uint32_t i = 0; i < count; i++){
    status = i2c_read_device(pigpiodaemonid, deviceId, ptr, count);
    //printf("\ti2c_read_device status: %i\n", status);
    //fflush(stdout);
    if (status < 0) {
      printf("\ti2c_write_device failed status: %i\n", status);
      fflush(stdout);
      status = VL53L1_ERROR_UNDEFINED;
      return status;
    }
    return VL53L1_ERROR_NONE;
}

VL53L1_Error VL53L1_WriteMulti(uint16_t Dev, uint16_t index, uint8_t *pdata, uint32_t count) {
    int status_int;
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    if (count > sizeof(_I2CBuffer) - 1) {
        return VL53L1_ERROR_INVALID_PARAMS;
    }
    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    memcpy(&_I2CBuffer[2], pdata, count);
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, count + 2);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
    }
    VL53L1_PutI2cBus();
    return Status;
}

VL53L1_Error VL53L1_ReadMulti(uint16_t Dev, uint16_t index, uint8_t *pdata, uint32_t count) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 2);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, pdata, count);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
    }
done:
    VL53L1_PutI2cBus();
    return Status;
}

VL53L1_Error VL53L1_WrByte(uint16_t Dev, uint16_t index, uint8_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    _I2CBuffer[2] = data;

    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 3);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
    }
    VL53L1_PutI2cBus();
    return Status;
}

VL53L1_Error VL53L1_WrWord(uint16_t Dev, uint16_t index, uint16_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    _I2CBuffer[2] = data >> 8;
    _I2CBuffer[3] = data & 0x00FF;

    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 4);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
    }
    VL53L1_PutI2cBus();
    return Status;
}

VL53L1_Error VL53L1_WrDWord(uint16_t Dev, uint16_t index, uint32_t data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;
    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    _I2CBuffer[2] = (data >> 24) & 0xFF;
    _I2CBuffer[3] = (data >> 16) & 0xFF;
    _I2CBuffer[4] = (data >> 8)  & 0xFF;
    _I2CBuffer[5] = (data >> 0 ) & 0xFF;
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 6);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
    }
    VL53L1_PutI2cBus();
    return Status;
}


VL53L1_Error VL53L1_RdByte(uint16_t Dev, uint16_t index, uint8_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 2);
    if( status_int ){
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, data, 1);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
    }
done:
    VL53L1_PutI2cBus();
    return Status;
}


VL53L1_Error VL53L1_RdWord(uint16_t Dev, uint16_t index, uint16_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[0] = index>>8;
    _I2CBuffer[1] = index&0xFF;
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 2);

    if( status_int ){
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, _I2CBuffer, 2);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
        goto done;
    }

    *data = ((uint16_t)_I2CBuffer[0]<<8) + (uint16_t)_I2CBuffer[1];
done:
    VL53L1_PutI2cBus();
    return Status;
}


VL53L1_Error VL53L1_RdDWord(uint16_t Dev, uint16_t index, uint32_t *data) {
    VL53L1_Error Status = VL53L1_ERROR_NONE;
    int32_t status_int;

    _I2CBuffer[1] = index>>8;
    _I2CBuffer[0] = index&0xFF;
    VL53L1_GetI2cBus();
    status_int = _I2CWrite(Dev, _I2CBuffer, 2);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
        goto done;
    }
    status_int = _I2CRead(Dev, _I2CBuffer, 4);
    if (status_int != 0) {
        Status = VL53L1_ERROR_CONTROL_INTERFACE;
        goto done;
    }

    *data = ((uint32_t)_I2CBuffer[0]<<24) + ((uint32_t)_I2CBuffer[1]<<16) + ((uint32_t)_I2CBuffer[2]<<8) + (uint32_t)_I2CBuffer[3];

done:
    VL53L1_PutI2cBus();
    return Status;
}

VL53L1_Error VL53L1_WaitMs(uint16_t dev, int32_t wait_ms){
    (void)dev;
    struct timespec ts = { wait_ms / 1000, (wait_ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
    return VL53L1_ERROR_NONE;
}
