/* zutil.c -- target dependent utility functions for the compression library
 * Copyright (C) 1995-2017 Jean-loup Gailly
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* @(#) $Id$ */

#include "zutil.h"
#ifndef Z_SOLO
#  include "gzguts.h"
#endif

const char * const z_errmsg[10] = {
    (const char *)"need dictionary",     /* Z_NEED_DICT       2  */
    (const char *)"stream end",          /* Z_STREAM_END      1  */
    (const char *)"",                    /* Z_OK              0  */
    (const char *)"file error",          /* Z_ERRNO         (-1) */
    (const char *)"stream error",        /* Z_STREAM_ERROR  (-2) */
    (const char *)"data error",          /* Z_DATA_ERROR    (-3) */
    (const char *)"insufficient memory", /* Z_MEM_ERROR     (-4) */
    (const char *)"buffer error",        /* Z_BUF_ERROR     (-5) */
    (const char *)"incompatible version",/* Z_VERSION_ERROR (-6) */
    (const char *)""
};


const char * zlibVersion()
{
    return ZLIB_VERSION;
}

unsigned long zlibCompileFlags()
{
    unsigned long flags;

    flags = 0;
    switch ((int)(sizeof(unsigned))) {
    case 2:     break;
    case 4:     flags += 1;     break;
    case 8:     flags += 2;     break;
    default:    flags += 3;
    }
    switch ((int)(sizeof(unsigned long))) {
    case 2:     break;
    case 4:     flags += 1 << 2;        break;
    case 8:     flags += 2 << 2;        break;
    default:    flags += 3 << 2;
    }
    switch ((int)(sizeof(void*))) {
    case 2:     break;
    case 4:     flags += 1 << 4;        break;
    case 8:     flags += 2 << 4;        break;
    default:    flags += 3 << 4;
    }
    switch ((int)(sizeof(z_off_t))) {
    case 2:     break;
    case 4:     flags += 1 << 6;        break;
    case 8:     flags += 2 << 6;        break;
    default:    flags += 3 << 6;
    }
#ifdef ZLIB_DEBUG
    flags += 1 << 8;
#endif
#if defined(ASMV) || defined(ASMINF)
    flags += 1 << 9;
#endif
#ifdef BUILDFIXED
    flags += 1 << 12;
#endif
#ifdef DYNAMIC_CRC_TABLE
    flags += 1 << 13;
#endif
#ifdef NO_GZCOMPRESS
    flags += 1L << 16;
#endif
#ifdef NO_GZIP
    flags += 1L << 17;
#endif
#ifdef PKZIP_BUG_WORKAROUND
    flags += 1L << 20;
#endif
#ifdef FASTEST
    flags += 1L << 21;
#endif
#    ifdef HAS_snprintf_void
    flags += 1L << 26;
#    endif
    return flags;
}

#ifdef ZLIB_DEBUG
#include <stdlib.h>
int z_verbose = 0;

void z_error (
    char *m)
{
    fprintf(stderr, "%s\n", m);
    exit(1);
}
#endif

/* exported to allow conversion of error code to string for compress() and
 * uncompress()
 */
const char * zError(
    int err)
{
    return ERR_MSG(err);
}

void* zcalloc (void* opaque, unsigned items, unsigned size)
{
    (void)opaque;
    return sizeof(unsigned) > 2 ? (void*)malloc(items * size) :
                              (void*)calloc(items, size);
}

void zcfree(void* opaque, void* ptr)
{
    (void)opaque;
    free(ptr);
}