/*
 * @Description: Arduino_DriveBus.cpp
 * @version: V1.0.0
 * @Author: Xk_w
 * @Date: 2023-11-16 15:53:46
 * @LastEditors: Xk_w
 * @LastEditTime: 2023-12-22 14:20:40
 * @License: GPL 3.0
 */
#include "Arduino_DriveBus.h"

Arduino_IIC_DriveBus::Arduino_IIC_DriveBus() {}

bool Arduino_IIC_DriveBus::WriteC8D8(uint8_t c, uint8_t d)
{
    if (Write(c) == false)
    {
        log_e("->Write(c) fail");
        return false;
    }
    if (Write(d) == false)
    {
        log_e("->Write(d) fail");
        return false;
    }
    return true;
}

bool Arduino_IIC_DriveBus::BufferOperation(uint8_t device_address, const uint8_t *operations, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        switch (operations[i])
        {
        case Arduino_DriveBus_BufferOperation::BO_BEGIN_TRANSMISSION:
            BeginTransmission(device_address);
            break;
        case Arduino_DriveBus_BufferOperation::BO_WRITE:
            i++;
            if (Write(operations[i]) == false)
            {
                log_e("->Write(operations[i]) fail");
                return false;
            }
            break;
        case Arduino_DriveBus_BufferOperation::BO_WRITE_C8_D8:
            i++;
            if (Write(operations[i]) == false)
            {
                log_e("->Write(operations[i]) fail");
                return false;
            }
            i++;
            if (Write(operations[i]) == false)
            {
                log_e("->Write(operations[i]) fail");
                return false;
            }
            break;
        case Arduino_DriveBus_BufferOperation::BO_END_TRANSMISSION:
            if (EndTransmission() == false)
            {
                log_e("->EndTransmission() fail");
                return false;
            }
            break;
        case Arduino_DriveBus_BufferOperation::BO_DELAY:
            i++;
            delay(operations[i]);
            break;
        default:
            return false;
            break;
        }
    }

    return true;
}

bool Arduino_IIC_DriveBus::IIC_WriteC8D8(uint8_t device_address, uint8_t c, uint8_t d)
{
    BeginTransmission(device_address);
    if (WriteC8D8(c, d) == false)
    {
        log_e("->WriteC8D8(c, d) fail");
        return false;
    }
    if (EndTransmission() == false)
    {
        log_e("->EndTransmission() fail");
        return false;
    }
    return true;
}

bool Arduino_IIC_DriveBus::IIC_ReadC8D8(uint8_t device_address, uint8_t c, uint8_t *d)
{
    BeginTransmission(device_address);
    if (Write(c) == false)
    {
        log_e("->Write(c) fail");
        return false;
    }
    if (EndTransmission() == false)
    {
        log_e("->EndTransmission() fail");
        return false;
    }
    if (RequestFrom(device_address, 1) == false)
    {
        log_e("->RequestFrom(device_address, 1) fail");
        return false;
    }
    *d = Read();

    return true;
}

Arduino_IIS_DriveBus::Arduino_IIS_DriveBus() {}

bool Arduino_IIS_DriveBus::IIS_Read(char *data, size_t length)
{
    size_t temp_buf = Read(data, length);

    if (temp_buf != length)
    {
        log_e("->Read(data, length) fail");
        return false;
    }
    return true;
}

bool Arduino_IIS_DriveBus::IIS_Write(char *data, size_t length)
{
    size_t temp_buf = Write(data, length);

    if (temp_buf != length)
    {
        log_e("->Write(data, length) fail");
        return false;
    }
    return true;
}