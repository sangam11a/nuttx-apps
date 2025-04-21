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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <nuttx/config.h>
#include <nuttx/mm/mm.h>
#include <fcntl.h>
#include "gpio_def.h"


#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "/home/sumina/nuttxspace/nuttx_cubus/APN_BOARDS/cubus_em/src/cubus_mtd.h"

// Define the size for the allocation test
// #define TEST_SIZE 1024*2   // 1 MB
static int        g_nerrors          = 0;

static void show_statfs(const char *path)
{
  struct statfs buf;
  int ret;

  /* Try stat() against a file or directory.  It should fail with
   * expectederror
   */

  printf("show_statfs: Try statfs(%s)\n", path);
  ret = statfs(path, &buf);
  if (ret == 0)
    {
      printf("show_statfs: statfs(%s) succeeded\n", path);
      printf("\tFS Type           : %0" PRIx32 "\n", buf.f_type);
      printf("\tBlock size        : %zd\n", buf.f_bsize);
      printf("\tNumber of blocks  : %jd\n", (intmax_t)buf.f_blocks);
      printf("\tFree blocks       : %jd\n", (intmax_t)buf.f_bfree);
      printf("\tFree user blocks  : %jd\n", (intmax_t)buf.f_bavail);
      printf("\tNumber file nodes : %jd\n", (intmax_t)buf.f_files);
      printf("\tFree file nodes   : %jd\n", (intmax_t)buf.f_ffree);
      printf("\tFile name length  : %zd\n", buf.f_namelen);
    }
  else
    {
      printf("show_statfs: ERROR statfs(%s) failed with errno=%d\n",
             path, errno);
      g_nerrors++;
    }
}

int main(int argc, FAR char *argv[])
// int main()
{
  if(strcmp(argv[1],"1") ==0 ){
  cubus_mtd_unmount(board_mfm_get_manifest(), "/mnt/fs/mfm/mtd_mainstorage");
  }

   else if(strcmp(argv[1],"2") ==0 ){
  cubus_mtd_unmount(board_mfm_get_manifest(),"/mnt/fs/mfm/mtd_mission");
  }
  else if(strcmp(argv[1],"3") ==0){
    show_statfs("/mnt/fs/mfm/mtd_mainstorage");
  }
  
  else{
    printf("wrong arg\n\n");
    cubus_mft_configure(board_mfm_get_manifest(), 0);
    // cubus_mft_configure(board_sfm_get_manifest(), 2);
    

  }
  // cubus_unmount(board_mfm_get_manifest());
  return 0;
}