/*************************************************************************
	> File Name: partition.h
	> Author: 
	> Mail: 
	> Created Time: Fri 13 Mar 2015 04:58:09 PM CST
    > Ref: http://en.wikipedia.org/wiki/Master_boot_record
 ************************************************************************/

#ifndef _PARTITION_H
#define _PARTITION_H

#include "platform.h"

struct MBRPartition {
    uint8_t     active;     //0x80: active
    uint8_t     head;
    uint8_t     sector;
    uint8_t     cylinder;
    uint8_t     type;
    uint8_t     end_head;
    uint8_t     end_cylinder;
    uint8_t     start

}


#endif
