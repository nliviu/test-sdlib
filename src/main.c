/*
 * Copyright (c) 2018 Liviu Nicolescu <nliviu@gmail.com>
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mgos.h"
#include "mgos_sd.h"

struct mgos_sd* s_sd = NULL;

enum mgos_app_init_result mgos_app_init(void) {
  s_sd = mgos_sd_open(false /* spi */, "/sd", false);
  if (NULL != s_sd) {
    LOG(LL_INFO, ("SD init successfuly!"));
    struct mbuf jsmb;
    struct json_out jsout = JSON_OUT_MBUF(&jsmb);
    mbuf_init(&jsmb, 0);
    mgos_sd_print_info(&jsout);
    LOG(LL_INFO, ("%.*s", jsmb.len, jsmb.buf));
    mbuf_free(&jsmb);
    LOG(LL_INFO, ("SD size=%llu B", mgos_sd_get_fs_size(SD_FS_UNIT_BYTES)));
    LOG(LL_INFO, ("SD size=%llu kiB", mgos_sd_get_fs_size(SD_FS_UNIT_KILOBYTES)));
    LOG(LL_INFO, ("SD size=%llu MiB", mgos_sd_get_fs_size(SD_FS_UNIT_MEGABYTES)));
  } else {
    LOG(LL_INFO, ("SD init ERROR!"));
  }
  
  return MGOS_APP_INIT_SUCCESS;
}
