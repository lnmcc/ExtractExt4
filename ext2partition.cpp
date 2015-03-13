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
        LOG("%s", "read inode error");
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
    
    if(lvol) {
        sectno = lvol->lvm_mapper((lloff_t)nsects * blocknum);
    } else {
        sectno = (lloff_t)((lloff_t)nsects * blocknum) + relative_sect;
    }

    ret = read_disk(handle, buffer, sectno, nsects, sect_size);

    return ret
}

int Ext2Partition::mount() {
    EXT2_SUPER_BLOCK sblock;
    int gSizes, gSizeb;
    char*   tmpbuf = NULL;

    read_disk(handle, &sblock, relative_sect + 2, 2, sect_size);

    if(sblock.s_magic != EXT2_SUPER_MAGIC) {
        LOG("%s", "Bad Super block");
        return -1;
    }

    if(sblock.s_feature_incompat & EXT2_FEATURE_INCOMPAT_COMPRESSION) {
        LOG("%s", "Unsupport compression file system");
        return -1;
    }

    blocksize = EXT2_BLOCK_SIZE(&sblock);
    inodes_per_group = sblock.s_inodes_per_group;
    inode_size = EXT2_INODE_SIZE(&sblock);

    totalGroups = (sblock.s_blocks_count) / EXT2_BLOCKS_PER_GROUP(&sblock);
    gSizeb = (sizeof(EXT2_GROUP_DESC) * totalGroups);
    gSizes = (gSizeb / sect_size) + 1;

    desc = (EXT2_GROUP_DESC*)calloc(totalGroups, sizeof(EXT2_GROUP_DESC));
    if(desc == NULL) {
        LOG("%s", "Not enough memory");
        exit(1);
    }
    
    if((tmpbuf = (char*)malloc(gSizes * sect_size)) == NULL) {
        LOG("%s", "Not enough memory");
        exit(1);
    }

    /* Read all Group descriptors and store in buffer */
    if((blocksize / sect_size) <= 2) {
        read_disk(handle, tmpbuf, relative_sect + ((blocksize / sect_size) + 2), gSizes, sect_size);
    } else {
        read_disk(handle, tmpbuf, relative_sect + (blocksize / sect_size), gSizes, sect_size);
    }

    memcpy(desc, tmpbuf, gSizeb);
    free(tmpbuf);
    
    return 0;
}

EXT2DIRENT*  Ext2Partition::open_dir(Ext2File* parent) {
    EXT2DIRENT*     dirent;

    if(NULL == parent) {
        return NULL;
    }

    dirent = new EXT2DIRENT();
    dirent->parent = parent;
    dirent->next = NULL;
    dirent->dirbuf = NULL;
    dirent->read_bytes = 0;
    dirent->next_block = 0;

    return dirent;
}
