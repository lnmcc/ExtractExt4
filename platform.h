/*************************************************************************
	> File Name: platform.h
	> Author: 
	> Mail: 
	> Created Time: Fri 13 Mar 2015 03:44:16 PM CST
 ************************************************************************/

#ifndef _PLATFORM_H
#define _PLATFORM_H

    #ifdef WIN32
        #include <windows.h>
        #include <stdint.h>
            typedef HANDLE  FileHandle;
        #ifdef _MSC_VER
            typedef unsigned char    uint8_t;
            typedef unsigned short   uint16_t;
            typedef unsigned int     uint32_t;
        #endif

        #else
            typedef int FileHandle;
    #endif

    typedef unsigned long long  lloff_t;
    typedef unsigned int        uint;
    typedef unsigned long       ulong;

    #define SECTOR_SIZE     512

    #if defined(__GNUC__)
        #define PACKED __attribute__((packed))
    #else
        #define PACKED
    #endif


    #ifndef INLINE
        #if defined(_MSC_VER)
            #define INLINE __inline
        #elif defined(__GNUC__)
            #define INLINE __inline__
        #endif
    #endif

    #ifdef __cplusplus
    extern "C" {
    #endif    

    FileHandle open_disk(const char*, int*);
    #ifdef __cplusplus
    }
    #endif

#endif
