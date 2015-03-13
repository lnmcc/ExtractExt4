/*************************************************************************
	> File Name: ext2read.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 13 Mar 2015 04:32:38 PM CST
 ************************************************************************/

#include <iostream>
#include "utils.h"
#include "ext2fs.h"

using namespace std;

Ext2Read::Ext2Read() {
    scan_system();
}

Ext2Read::~Ext2Read() {

}

void Ext2Read::scan_system() {
    char pathname[128];
    int ret = -1;

}

int Ext2Read::scan_partitions(char* path) {
    uint8_t sector[SECTOR_SIZE];
    struct MBRPartition*    mbr;
    Ext2Partition*  partion;
    FileHandle  handle;
    int sector_size;
    int ret = -1;

    handle = open_disk(path, &sector_size);
    if(handle < 0)
        return -1;

    ret = read_disk(handle, sector, 0, 1, sector_size);
    if(ret < 0)
        return ret;

    if(ret < sector_size) {
        LOG("Error Reading the MBR on %s", path);
        return -1;
    }

    if(!valid_part_table_flag(sector)) {
        LOG("Partition Table Error on %s", path);
        return -1;
    }

    /* Scan primary Partitions */
    for(int i = 0; i < 4; i++) {
       mbr = pt_offset(setor, i);  
    }
    
}
