#ifndef _VERSION_H
#define _VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#define LIB_MAJOR_VERSION       0
#define LIB_MINOR_VERSION       1
#define LIB_PATH_VERSION        7

/* define macro */
#define TOSTR(x) #x
#define STRING(x) TOSTR(x)

#define LIB_VERSION STRING(LIB_MAJOR_VERSION) "." STRING(LIB_MINOR_VERSION) "." STRING(LIB_PATH_VERSION)

#ifdef __cplusplus
}
#endif                          /* __cplusplus */

#endif                          /* _VERSION_H */
