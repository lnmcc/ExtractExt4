/*************************************************************************
	> File Name: ext2fs.h
	> Author: 
	> Mail: 
	> Created Time: Fri 13 Mar 2015 11:10:52 AM CST
 ************************************************************************/

#ifndef _EXT2FS_H
#define _EXT2FS_H

#include "utils.h"
#include "string"

using namespace std;

class Ext2Partition;

class Ext2File {
public:
    uint32_t    inode_num;
    uint8_t     file_type;
    string      file_name;
    lloff_t     file_size;
    
    EXT2_INODE  inode;
    Ext2Partition *partition;
    bool    onview;
};

typedef struct ext2dirent {
    EXT2_DIR_ENTRY  *next;
    EXT2_DIR_ENTRY  *dirbuf;
    Ext2File    *parent;
    lloff_t     read_bytes;
    lloff_t     next_block;
} EXT2DIRENT;

class Ext2Partition {
private:
    FileHandle  handle;
    int     sect_size;
    lloff_t     total_sectors;
    lloff_t     relative_sect;
    string      linux_name;

    int     inodes_per_group;
    int     inode_size;
    int     blocksize;
    uint32_t    totalGroups;
    EXT2_GROUP_DESC     *desc;
    char*   inode_buffer;
    lloff_t     last_block;
    Ext2File    *root;

    LogicalVolume   *lvol;
private:
    int     ext2_readblock(lloff_t blocknum, void* buffer);
    uint32_t    fileblock_to_logical(EXT2_INODE* ino, uint32_t lbn);
    lloff_t     extent_to_logical(EXT2_INODE *ino, lloff_t lbn);
    lloff_t     extent_binarysearch(EXT4_EXTENT_HEADER *header, lloff_t lbn, bool isallocated);
    int mount();

public:
    bool onview;
    bool is_valid;

public:
    Ext2Partition(lloff_t, lloff_t, int ssize, FileHandle, LogicalVolume* vol);
    ~Ext2Partition();

    void set_linux_name(const char*, int, int);

    void set_image_name(const char* name) {
        linux_name.assign(name); 
    }

    string& get_linux_name();

    Ext2File* get_root() {
        return root;
    }

    int get_blocksize() {
        return blocksize;
    }

    Ext2File* read_inode(uint32_t inum);
    int read_data_block(EXT2_INODE *ino, lloff_t lbn, void* buf);
    EXT2DIRENT* open_dir(Ext2File *parent);
    Ext2File* read_dir(EXT2DIRENT*);
    void close_dir(EXT2DIRENT*);
};

class Ext2Read {
private:
    int ndiskl
    list<Ext2Partition *> nparts;
    int scan_ebr(FileHandle, lloff_t, int, int);
    int scan_partitions(char* path, int);
    void clear_partitions();

public:
    list<VolumeGroup*> groups;

public:
    Ext2Read();
    ~Ext2Read();

    void scan_system();
    int add_loopback(const char* file);
    list<Ext2Partition*> get_partitions();

    list<VolumeGroup*>& get_volgroups() {
        return groups;
    }

    void add_partition(Ext2Partition *part) {
        nparts.push_back(part);
    }
}

#endif
