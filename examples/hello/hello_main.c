// /****************************************************************************
//  * apps/examples/hello/hello_main.c
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

// #include <nuttx/config.h>
// #include <stdio.h>

// /****************************************************************************
//  * Public Functions
//  ****************************************************************************/

// /****************************************************************************
//  * hello_main
//  ****************************************************************************/

// int main(int argc, FAR char *argv[])
// {
//   printf("Hello, World!!\n");
//   return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <nuttx/config.h>
#include <nuttx/mm/mm.h>
#include <fcntl.h>
#include "gpio_def.h"

// Define the size for the allocation test
// #define TEST_SIZE 1024*2   // 1 MB
uint32_t TEST_SIZE = 0;
void check_memory(void)
{
  void *ptr;
  size_t i;
  size_t free_memory = 0;
  size_t used_memory = 0;

  // Check initial available memory
  ptr = malloc(TEST_SIZE);
  if (ptr != NULL)
  {
    printf("Successfully allocated %d MB of memory\n", TEST_SIZE / 1024);
    free(ptr);
  }
  else
  {
    printf("Memory allocation failed\n");
  }

  // Optionally, perform a larger allocation to test limits
  ptr = malloc(TEST_SIZE * 10);
  if (ptr != NULL)
  {
    printf("Successfully allocated %d MB of memory\n", TEST_SIZE / 1024 * 10);
    free(ptr);
  }
  else
  {
    printf("Memory allocation failed for %d MB\n", TEST_SIZE / 1024 * 10);
  }

  // Note: Accurate free and used memory might require more specific system-level calls.
  // This is a basic demonstration.
}

int main(int argc, FAR char *argv[])
{
  // printf("Checking available memory.. %s.\n",argv[1]);
  // TEST_SIZE = 1024* atoi
  // gpio_write();
  struct file file_p;
  // char file_path[65];
  char file_path[] = "/mnt/fs/sfm/mtd_mission/camera.txt";
  // check_memory();
  uint16_t fd;
  gpio_write(GPIO_MUX_EN, false);
  gpio_write(GPIO_SFM_MODE, true);
  // gpio_write(GPIO_SFM_CS, false);
  fd = file_open(&file_p, file_path, O_RDONLY);
  if (fd >= 0)
  {
    printf("file opened\n");
    char seek_pointer[300] = {'\0'};

    // Seek to the end to get file size
    int file_size = file_seek(&file_p, 0, SEEK_END);
    printf("The file size is %d\n", file_size);

    // Seek back to the start before reading
    file_seek(&file_p, 0, SEEK_SET);

    ssize_t bytes_read = file_read(&file_p, seek_pointer, sizeof(seek_pointer) - 1);
    if (bytes_read < 0)
    {
      printf("Error reading file\n");
    }
    else
    {
      seek_pointer[bytes_read] = '\0'; // Null-terminate
      printf("Data is %s\n", seek_pointer);
    }
  }
  else
  {
    printf("file error %d\n", fd);
  }

  file_syncfs(&file_p);
  file_close(&file_p);

  gpio_write(GPIO_SFM_MODE, false);
  gpio_write(GPIO_MUX_EN, false);
  return 0;
}