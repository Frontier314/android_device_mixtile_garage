/*
 *
 * Copyright 2012 Samsung Electronics S.LSI Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * @file    fimc_m2m.h
 * @brief   header file for GSC HAL
 */

#ifndef FIMC_M2M_CSC_H_
#define FIMC_M2M_CSC_H_

#define FIMC_M2M_ErrorNone                0
#define FIMC_M2M_Error                   -1
#define FIMC_M2M_ErrorNotInit            -2
#define FIMC_M2M_ErrorInvalidAddress     -3
#define FIMC_M2M_ErrorUnsupportFormat    -4
#define FIMC_M2M_ErrorNotImplemented     -5

typedef enum _FIMC_M2M_CACHE {
    FIMC_M2M_NON_CACHEABLE = 0,
    FIMC_M2M_CACHEABLE
} FIMC_M2M_CACHE;

void *fimc_m2m_open(
    unsigned int dev_num);

void fimc_m2m_close(
    void *handle);

int fimc_m2m_set_src_format(
    void *handle,
    unsigned int width,
    unsigned int height,
    unsigned int crop_left,
    unsigned int crop_top,
    unsigned int crop_width,
    unsigned int crop_height,
    unsigned int colorformat,
    unsigned int cacheable);

int fimc_m2m_set_dst_format(
    void *handle,
    unsigned int width,
    unsigned int height,
    unsigned int crop_left,
    unsigned int crop_top,
    unsigned int crop_width,
    unsigned int crop_height,
    unsigned int colorformat,
    unsigned int cacheable);

int fimc_m2m_set_src_addr(
    void *handle,
    void **addr);

int fimc_m2m_set_dst_addr(
    void *handle,
    void **addr);

int fimc_m2m_convert(
    void *handle);

#endif /*FIMC_M2M_CSC_H_*/

