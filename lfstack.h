/*
*
* BSD 2-Clause License
*
* Copyright (c) 2018, Taymindis Woon
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
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

#ifndef LFQUEUE_H
#define LFQUEUE_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lfstack_cas_node_s lfstack_cas_node_t;

#if defined __GNUC__ || defined __CYGWIN__ || defined __MINGW32__ || defined __APPLE__
#define lfs_bool_t int
#else
#ifdef _WIN64
#define lfs_bool_t int64_t
#else
#define lfs_bool_t int
#endif
#endif

typedef struct {
	lfstack_cas_node_t *head, *root_free, *move_free;
	volatile size_t size;
	volatile lfs_bool_t in_free_mode;
} lfstack_t;

extern int   lfstack_init(lfstack_t *lfstack);
extern int   lfstack_push(lfstack_t *lfstack, void *value);
extern void* lfstack_pop(lfstack_t *lfstack);
extern void* lfstack_single_pop(lfstack_t *lfstack);
/*** lfstack_flush to flush all the inacitve element ***/
extern void lfstack_flush(lfstack_t *lfstack);
extern void lfstack_destroy(lfstack_t *lfstack);
extern size_t lfstack_size(lfstack_t *lfstack);
extern void lfstack_sleep(unsigned int milisec);


#ifdef __cplusplus
}
#endif

#endif

