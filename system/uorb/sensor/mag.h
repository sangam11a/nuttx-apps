/****************************************************************************
 * apps/system/uorb/sensor/mag.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __APPS_SYSTEM_UORB_SENSOR_MAG_H
#define __APPS_SYSTEM_UORB_SENSOR_MAG_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <uORB/uORB.h>


struct orb_mag_scaled_s
{
  // uint64_t timestamp;
  // float x;
  // float y;
  // float z;
  // float temperature;
  uint64_t timestamp;
  float acc_x;
  float acc_y;
  float acc_z;
  float temp;
  float gyro_x;
  float gyro_y;
  float gyro_z;
  float mag_x;
  float mag_y;
  float mag_z;
  float temperature;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

/* register this as object request broker structure */

ORB_DECLARE(sensor_mag);
ORB_DECLARE(sensor_mag_uncal);
ORB_DECLARE(orb_mag_scaled);

#endif