// // /****************************************************************************
// //  * apps/examples/hello/hello_main.c
// //  *
// //  * Licensed to the Apache Software Foundation (ASF) under one or more
// //  * contributor license agreements.  See the NOTICE file distributed with
// //  * this work for additional information regarding copyright ownership.  The
// //  * ASF licenses this file to you under the Apache License, Version 2.0 (the
// //  * "License"); you may not use this file except in compliance with the
// //  * License.  You may obtain a copy of the License at
// //  *
// //  *   http://www.apache.org/licenses/LICENSE-2.0
// //  *
// //  * Unless required by applicable law or agreed to in writing, software
// //  * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// //  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// //  * License for the specific language governing permissions and limitations
// //  * under the License.
// //  *
// //  ****************************************************************************/

// // /****************************************************************************
// //  * Included Files
// //  ****************************************************************************/

// // #include <nuttx/config.h>
// // #include <stdio.h>

// // /****************************************************************************
// //  * Public Functions
// //  ****************************************************************************/

// // /****************************************************************************
// //  * hello_main
// //  ****************************************************************************/

// // int main(int argc, FAR char *argv[])
// // {
// //   printf("Hello, World!!\n");
// //   return 0;
// // }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <nuttx/config.h>
// #include <nuttx/mm/mm.h>
// #include <fcntl.h>
// #include "gpio_def.h"

// // Define the size for the allocation test
// // #define TEST_SIZE 1024*2   // 1 MB
// uint32_t TEST_SIZE = 0;
// void check_memory(void)
// {
//   void *ptr;
//   size_t i;
//   size_t free_memory = 0;
//   size_t used_memory = 0;

//   // Check initial available memory
//   ptr = malloc(TEST_SIZE);
//   if (ptr != NULL)
//   {
//     printf("Successfully allocated %d MB of memory\n", TEST_SIZE / 1024);
//     free(ptr);
//   }
//   else
//   {
//     printf("Memory allocation failed\n");
//   }

//   // Optionally, perform a larger allocation to test limits
//   ptr = malloc(TEST_SIZE * 10);
//   if (ptr != NULL)
//   {
//     printf("Successfully allocated %d MB of memory\n", TEST_SIZE / 1024 * 10);
//     free(ptr);
//   }
//   else
//   {
//     printf("Memory allocation failed for %d MB\n", TEST_SIZE / 1024 * 10);
//   }

//   // Note: Accurate free and used memory might require more specific system-level calls.
//   // This is a basic demonstration.
// }

// int main(int argc, FAR char *argv[])
// {
//   // printf("Checking available memory.. %s.\n",argv[1]);
//   // TEST_SIZE = 1024* atoi
//   // gpio_write();
//   struct file file_p;
//   // char file_path[65];
//   char file_path[] = "/mnt/fs/sfm/mtd_mission/camera.txt";
//   // check_memory();
//   uint16_t fd;
//   gpio_write(GPIO_MUX_EN, false);
//   gpio_write(GPIO_SFM_MODE, true);
//   // gpio_write(GPIO_SFM_CS, false);
//   fd = file_open(&file_p, file_path, O_RDONLY);
//   if (fd >= 0)
//   {
//     printf("file opened\n");
//     char seek_pointer[300] = {'\0'};

//     // Seek to the end to get file size
//     int file_size = file_seek(&file_p, 0, SEEK_END);
//     printf("The file size is %d\n", file_size);

//     // Seek back to the start before reading
//     file_seek(&file_p, 0, SEEK_SET);

//     ssize_t bytes_read = file_read(&file_p, seek_pointer, sizeof(seek_pointer) - 1);
//     if (bytes_read < 0)
//     {
//       printf("Error reading file\n");
//     }
//     else
//     {
//       seek_pointer[bytes_read] = '\0'; // Null-terminate
//       printf("Data is %s\n", seek_pointer);
//     }
//   }
//   else
//   {
//     printf("file error %d\n", fd);
//   }

//   file_syncfs(&file_p);
//   file_close(&file_p);

//   gpio_write(GPIO_SFM_MODE, false);
//   gpio_write(GPIO_MUX_EN, false);
//   return 0;
// }

// //working
#include <nuttx/config.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "gpio_def.h"
#include <syslog.h>
#include <fcntl.h>
#include "gpio_def.h"

// int gpio_write(uint32_t pin, uint8_t mode)
// {

//   gpio_config_s gpio_numval;
//   int fd = open(ETX_LED_DRIVER_PATH, O_WRONLY);
//   if (fd < 0)
//   {
//     syslog(LOG_ERR, "Error opening %s for GPIO WRITE...", ETX_LED_DRIVER_PATH);
//     close(fd);
//     return -1;
//   }
//   gpio_numval.gpio_num = pin;
//   gpio_numval.gpio_val = mode;
//   if (gpio_numval.gpio_val > 1 || gpio_numval.gpio_num < 0)
//   {
//     syslog(LOG_ERR, "Undefined GPIO pin or set mode selected...\n");
//     return -2;
//   }
//   int ret = write(fd, (const void *)&gpio_numval, sizeof(gpio_config_s));
//   close(fd);
//   if (ret < 0)
//   {
//     syslog(LOG_ERR, "Unable to write to gpio pin...\n");
//   }
//   return ret;
// }

volatile sig_atomic_t running = 1;
time_t start_time; // To store the initial time
time_t last_report_time; // To track when the last report was printed

void handle_signal(int sig) {
    running = 0;
}

void print_full_date_time(void) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    
    char buffer[64]; // Buffer to hold the formatted string
    
    // Format the time: Day, Date, Month, Year, Hour:Minute:Second
    strftime(buffer, sizeof(buffer), "%A, %Y-%m-%d %H:%M:%S", tm_info);
    
    printf("Current date and time: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    // Set up signal handling for graceful termination
    if (signal(SIGINT, handle_signal) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    // Initialize the start time
    start_time = time(NULL);
    last_report_time = start_time; // Set the last report time to the start time

    // Print the initial date and time
    print_full_date_time();

    // Loop to display updated date and time every second
    while (running) {
        sleep(1); // Wait for one second

        if (running) {
            print_full_date_time(); // Print updated date and time each second

            // Calculate the elapsed time
            double elapsed = difftime(time(NULL), start_time);
            // if ((uint32_t)elapsed % 60 == 0)
            // printf("Difference in time: %.0f seconds\n", elapsed );

            // Check if 2 minutes (120 seconds) have passed since the last report
            if ((uint32_t)difftime(time(NULL), last_report_time) % 180 ==0) {
                printf("3 minute has passed.\n Global reset starting\n");
                gpio_write(GPIO_GBL_RST, true);
                last_report_time = time(NULL); // Update the last report time
            }

            // Check if 5 minutes (300 seconds) have passed
            if (elapsed >= 300) {
                printf("5 minutes have exceeded.\n");
            }

            // Check if 24 hours (86400 seconds) have passed
            if (elapsed >= 86400) {
                printf("24 hours have passed.\n");
                running = 0; // Optionally stop the program after 24 hours
            }
        }
    }

    printf("Exiting gracefully...\n");
    return 0;
}
