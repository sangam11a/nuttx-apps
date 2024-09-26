// /****************************************************************************
//  * apps/system/uorb/sensor/sensor_combined.c
//  *
//  * Licensed to the Apache Software Foundation (ASF) under one or more
//  * contributor license agreements.  See the NOTICE file distributed with
//  * this work for additional information regarding copyright ownership.  The
//  * ASF licenses this file to you under the Apache License, Version 2.0 (the
//  * "License"); you may not use this file except in compliance with the
//  * License.  You may obtain a copy of the License at
//  *
//  *   http://www.apache.org/licenses/LICENSE-2.0
//  *
//  * Unless required by applicable law or agreed to in writing, software
//  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
//  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
//  * License for the specific language governing permissions and limitations
//  * under the License.
//  *
//  ****************************************************************************/

// /****************************************************************************
//  * Included Files
//  ****************************************************************************/

// #include <sensor/sensor_combined.h>

// /****************************************************************************
//  * Private Functions
//  ****************************************************************************/

// #ifdef CONFIG_DEBUG_UORB
// static void print_sensor_gyro_message(FAR const struct orb_metadata *meta,
//                                       FAR const void *buffer)
// {
//   FAR const struct sensor_gyro *message = buffer;
//   const orb_abstime now = orb_absolute_time();

//   uorbinfo_raw("%s:\ttimestamp: %" PRIu64 " (%" PRIu64 " us ago) "
//                "temperature: %.2f x: %.2f y: %.2f z: %.2f",
//                meta->o_name, message->timestamp, now - message->timestamp,
//                message->temperature, message->x, message->y, message->z);
// }
// static void print_sensor_mag_message(FAR const struct orb_metadata *meta,
//                                      FAR const void *buffer)
// {FAR const struct sensor_gyro *message = buffer;
//   const orb_abstime now = orb_absolute_time();

//   uorbinfo_raw("%s:\ttimestamp: %" PRIu64 " (%" PRIu64 " us ago) "
//                "temperature: %.2f x: %.2f y: %.2f z: %.2f",
//                meta->o_name, message->timestamp, now - message->timestamp,
//                message->temperature, message->x, message->y, message->z);
//   FAR const struct sensor_mag *message = buffer;
//   const orb_abstime now = orb_absolute_time();
//   FAR const struct sensor_accel *message = buffer;
//   const orb_abstime now = orb_absolute_time();

//   uorbinfo_raw("%s:\ttimestamp: %" PRIu64 " (%" PRIu64 " us ago) "
//                "temperature: %.2f x: %.2f y: %.2f z: %.2f",
//                meta->o_name, message->timestamp, now - message->timestamp,
//                message->temperature, message->x, message->y, message->z);

//   uorbinfo_raw("%s:\ttimestamp: %" PRIu64 " (%" PRIu64 " us ago) "
//                "temperature: %.2f x: %.2f y: %.2f z: %.2f",
//                meta->o_name, message->timestamp, now - message->timestamp,
//                message->temperature, message->x, message->y, message->z);
// }static void print_sensor_accel_message(FAR const struct orb_metadata *meta,
//                                        FAR const void *buffer)
// {
//   }
// #endif

// /****************************************************************************
//  * Public Data
//  ****************************************************************************/

// ORB_DEFINE(ads7953_raw_msg, struct ads7953_raw_msg, print_sensor_adc_raw_message);
// ORB_DEFINE(sat_temp_msg, struct sat_temp_msg, print_sat_temperature_message);
// ORB_DEFINE(sat_volts_msg, struct sat_volts_msg, print_sat_voltage_message);
// ORB_DEFINE(sat_int_adc_msg, struct sat_int_adc_msg, print_sat_int_adc_message);