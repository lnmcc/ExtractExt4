/*************************************************************************
	> File Name: ext2partition.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 13 Mar 2015 11:57:22 AM CST
 ************************************************************************/

#include<iostream>
#include "utils.h"
#include "ext2fs.h"

using namespace std;

Ext2Partition::Ext2Partition(lloff_t size, lloff_t offset, int ssize, FileHandle phandle, LogicalVolume *vol) {
    int ret = -1;
    total_sectors = size;
    relative_sect = offset;
    handle = phandle;
    sect_size = ssize;
    onview = false;
    inode_buffer= NULL;
    lvol = vol;

    ret = mount();
    if(ret < 0) {
        is_valid = false;
        return;
    }

    root = read_inode(EXT2_ROOT_INO);
    if(!root) {
        is_valid = false;
        LOG(__FILE__, __LINE__, "read inode error");
        return;
    }

    root->file_name = linux_name;
    root->file_type = 0x02;
    is_valid = true;
}

Ext2Partition::~Ext2Partition() {
    free(desc);
}

void Ext2Partition::set_linux_name(const char* name, int disk, int partition) {
    char dchar = 'a' + disk;
    char pchar = '1' + partition;

    linux_name = name;
    linux_name.append(1, dchar);
    linux_name.append(1, pchar);
}

string& Ext2Partition::get_linux_name() {
    return linux_name;
}

int Ext2Partition::ext2_readblock(lloff_t blocknum, void* buffer) {
    int     nsects = blocksize / sect_size;
    int ret = -1;
    lloff_t sectno;


}
