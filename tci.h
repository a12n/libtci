
#pragma once

#ifndef __TCI_H_INCLUDED__
#define __TCI_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

int
config_set(const char* path, const char* val);

int
config_set_int(const char* path, int val);

const char*
config_value_r(const char* path, const char* def, char* buf, size_t buf_sz);

const char*
config_value(const char* path, const char* def);

int
config_int_value(const char* path, int def);

#ifdef __cplusplus
} // extern "C"
#endif  /* __cplusplus */

#endif  /* __TCI_H_INCLUDED__ */
