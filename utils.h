/*************************************************************************
	> File Name: ext2fs.h
	> Author: 
	> Mail: 
	> Created Time: Thu 12 Mar 2015 10:18:37 AM CST
 ************************************************************************/

#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>

#define EXT2_DEFAULT_PREALLOC_BLOCK 8

/* Special Inode Numbers */
#define EXT2_BAD_INO            1
#define EXT2_ROOT_INO           2
#define EXT2_ACL_IDX_INO        3
#define EXT2_ACL_DATA_INO       4
#define EXT2_BOOT_LOADER_INO    5
#define EXT2_UNDEL_DIR_INO      6
#define EXT2_GOOD_OLD_FIRST_INO 11
#define EXT2_SUPER_MAGIC        0xEF53 // EXT2 FS Magic Number
#define EXT2_LINK_MAX           3200 // Max count of links to the file

/* Block Size Management */
#define EXT2_MIN_BLOCK_SIZE     1024
#define EXT2_MAX_BLOCK_SIZE     4096
#define EXT2_MIN_BLOCK_LOG_SIZE 10

/* EXT2 Fragment Sizes */
#define EXT2_MIN_FRAG_SIZE      1024
#define EXT2_MAX_FRAG_SIZE      4096
#define EXT2_MIN_FRAG_LOG_SIZE  10

#define EXT2_FRAG_SIZE(s)   (EXT2_MIN_BLOCK_SIZE << (s)->s_log_frag_size)
#define EXT2_FRAGS_PER_BLOCK(s)    (EXT2_BLOCK_SIZE(2)/ EXT2_FRAG_SIZE(2)) 

/* Block Group Macro */
#define EXT2_BLOCKS_PER_GROUP(s)    ((s)->s_blocks_per_group)
#define EXT2_DESC_PER_BLOCK(s)      ((EXT2_BLOCK_SIZE(s) / sizeof(EXT2_GROUP_DESC)))
#define EXT2_INODES_PER_GROUP(s)    ((s)->s_inodes_per_group)      
#define EXT2_INODES_PER_BLOCK(s)    (EXT2_BLOCK_SIZE(s) / sizeof(EXT2_INODE))
#define EXT2_BLOCK_SIZE_BITS(s)     ((s)->s_log_block_size + 10);

/* Constants relative to the data blocks */
#define EXT2_NDIR_BLOCKS        12
#define EXT2_IND_BLOCK          EXT2_NDIR_BLOCKS
#define EXT2_DIND_BLOCK         (EXT2_IND_BLOCK + 1)
#define EXT2_TIND_BLOCK         (EXT2_DIND_BLOCK + 1)
#define EXT2_N_BLOCKS           (EXT2_TIND_BLOCK + 1)

/* Superblock Flags */
#define EXT2_FEATURE_INCOMPAT_COMPRESSION   0x0001 // disk/file compression is used
/* Inode flags */
#define EXT2_SECRM_FL           0x00000001 // Secure deletion
#define EXT2_UNRM_FL            0x00000002 // Undelete
#define EXT2_COMPR_FL           0x00000004 // Compress File
#define EXT2_SYNC_FL            0x00000008 // Sync updates
#define EXT2_IMMUTABLE_FL       0x00000010 // Imutable File
#define EXT2_APPEND_FL          0x00000020 // writes to file may only append
#define EXT2_NODUMP_FL          0x00000040
#define EXT2_NOATIME_FL         0x00000080 
#define EXT2_DIRTY_FL           0x00000100 
#define EXT2_COMPRBLK_FL        0x00000200
#define EXT2_NOCOMP_FL          0x00000400
#define EXT2_ECOMPR_FL          0x00000800
#define EXT2_BIREE_FL           0x00001000
#define EXT2_IMAGIC_FL          0x00002000
#define EXT2_JOURNAL_DATA_FL    0x00004000 
#define EXT2_NOTAIL_FL          0x00008000
#define EXT2_DIRSYNC_FL         0x00010000
#define EXT2_TOPDIR_FL          0x00020000
#define EXT2_HUGE_FILE_FL       0x00040000
#define EXT2_EXTENTS_FL         0x00080000
#define EXT2_RESERVED_FL        0x80000000
#define EXT2_INLINEDATA_FL      0x10000000 // Inode has inline data (EXT4_INLINE_DATA_FL).

#define EXT2_FL_USER_VISIBLE    0x00001FFF
#define EXT2_FL_USER_MODIFIABLE 0x000000FF

/* Codes for operating systems */
#define EXT2_OS_LINUX           0
#define EXT2_OS_HURD            1
#define EXT2_OS_MASIX           2
#define EXT2_OS_FREEBSD         3
#define EXT2_OS_LITES           4

/* Revision levels */
#define EXT2_GOOD_OLD_REV       0
#define EXT2_DYNAMIC_REV        1

#define EXT2_CURRENT_REV        EXT2_GOOD_OLD_REV
#define EXT2_MAX_SUPP_REV       EXT2_DYNAMIC_REV

#define EXT2_GOOD_OLD_INODE_SIZE    128

/* Default values for user and/or group using reserved blocks */
#define EXT2_DEF_RESUID         0
#define EXT2_DEF_RESGIS         0

/* Structure of a dir entry */
#define EXT2_NAME_LEN           255

#define EXT2_BLOCK_SIZE(s)  (EXT2_MIN_BLOCK_SIZE << (s)->s_log_block_size)
#define EXT2_ACLE_PER_BLOCKS(s)     (EXT2_BLOCK_SIZE(s) / sizeof(struct ext2_acl_entry))
#define EXT2_ADDR_PER_BLOCKS(s)     (EXT2_BLOCK_SIZE(s) / sizeof(uint16_t))

#define EXT2_INODE_SIZE(s)          (((s)->s_rev_level == EXT2_GOOD_OLD_REV) ? \
                                        EXT2_GOOD_OLD_INODE_SIZE : (s)->s_inode_size)
#define EXT2_FIRST_INO(s)           (((s)->rev_level == EXT2_GOOD_OLD_REV) ? \
                                        EXT2_GOOD_OLD_FIRST_INO : (s)->s_first_ino)

/* The Supper Block comes first in the block group */
typedef struct tagEXT2_SUPER_BLOCK {
    uint32_t    s_inodes_count;
    uint32_t    s_blocks_count;
    uint32_t    s_r_block_count;
    uint32_t    s_free_blocks_count;
    uint32_t    s_free_inodes_count;
    uint32_t    s_first_data_block;
    uint32_t    s_log_block_size;
    uint32_t    s_blocks_per_group;
    uint32_t    s_frags_per_group;
    uint32_t    s_inodes_per_group;
    uint32_t    s_mtime;
    uint32_t    s_wtime;
    uint16_t    s_mnt_count;
    uint16_t    s_max_mnt_count;
    uint16_t    s_magic;
    uint16_t    s_state;
    uint16_t    s_pad;
    uint16_t    s_minor_rev_level;
    uint16_t    s_lastcheck;
    uint16_t    s_creator_os;
    uint16_t    s_rev_level;
    uint16_t    s_def_resuid;
    uint16_t    s_def_regid;

    /* for EXT2_DYNAMIC_REV Superblock only */
    uint32_t    s_first_ino;
    uint16_t    s_inode_size;
    uint16_t    s_block_group_nr;
    uint32_t    s_feature_compat;
    uint32_t    s_feature_incompat;
    uint32_t    s_feature_ro_compat;
    uint8_t     s_uuid[16];
    char        s_volume_name[16];
    char        s_last_mounted[64];
    uint32_t    s_algorithm_usage_bitmap;
    uint8_t     s_prealloc_blocks;
    uint8_t     s_prealloc_dir_blocks;
    uint16_t    s_padding1;
    uint32_t    s_reserved[204];
} __atttibute__ ((__packed__)) EXT2_SUPER_BLOCK;

/* The Group Descriptions follow the Superblock */
typedef struct tagEXT2_GROUP_DESC {
    uint32_t    bg_block_bitmap; 
    uint32_t    bg_inode_bitmap;
    uint32_t    bg_inode_table;
    uint16_t    bg_free_blocks_count;
    uint16_t    bg_free_inode_count;
    uint16_t    bg_used_dirs_count;
    uint16_t    bg_pad;
    uint32_t    bg_reserved[3];
} __atttibute__ ((__packed__)) EXT2_GROUP_DESC;

/* Structure of inode on the disk */
typedef struct tagEXT2_INODE {
    uint16_t    i_mode;
    uint16_t    i_uid;
    uint32_t    i_size;
    uint32_t    i_atime;
    uint32_t    i_ctime;
    uint32_t    i_mtime;
    uint32_t    i_dtime;
    uint16_t    i_gid;
    uint16_t    i_links_count;
    uint32_t    i_blocks_lo;
    uint32_t    i_flags;

    union {
        struct {
            uint32_t    l_i_reserved1;
        } linux1;

        struct {
            uint32_t    h_i_translator;
        } hurd1;

        struct {
            uint32_t    m_i_reserved1;
        } masix1;
    } osd1;

    uint32_t    i_block[EXT2_N_BLOCKS];
    uint32_t    i_generation;
    uint32_t    i_file_acl;
    uint32_t    i_size_high;
    uint32_t    i_faddr;

    union {
        struct {
            uint8_t     l_i_frag;
            uint8_t     l_i_fsize;
            uint16_t    i_pad1;
            uint16_t    l_i_uid_high;
            uint16_t    l_i_gid_high;
            uint32_t    l_i_reserved2;
        } linux2;

        struct {
            uint8_t     h_i_frag;
            uint8_t     h_i_fsize;
            uint16_t    h_i_mode_high; 
            uint16_t    h_i_uid_high;
            uint16_t    h_i_gid_high;
            uint16_t    h_i_author;
        } hurd1;

        struct {
            uint8_t     m_i_frag;
            uint8_t     m_i_fsize;
            uint16_t    m_pad1;
            uint32_t    m_i_reserved2[2];
        } masix2;
    } osd2;
} __atttibute__ ((__packed__)) EXT2_INODE;

/* EXT2 dir Structure */
typedef struct tagEXT2_DIR_ENTRY {
    uint32_t    inode;
    uint16_t    rec_len;
    uint8_t     name_len;
    uint8_t     filetype;
    char        name[EXT2_NAME_LEN];
} __atttibute__ ((__packed__)) EXT2_DIR_ENTRY;

typedef struct ext4_extent {
    uint32_t    ee_block;
    uint16_t    ee_len;
    uint16_t    ee_start_hi;
    uint32_t    ee_start_lo;
} __atttibute__  ((__packed__)) EXT4_EXTENT;

typedef struct ext4_extent_idx {
    uint32_t    ei_block;
    uint32_t    ei_leaf_lo;
    uint16_t    ei_leaf_hi;
    uint16_t    ei_unused;
} __atttibute__ ((__packed__)) EXT4_EXTENT_IDX;

typedef struct ext4_extent_header {
    uint16_t    eh_magic;
    uint16_t    eh_entries;
    uint16_t    eh_max;
    uint16_t    eh_depth;
    uint32_t    eh_generation;
} __atttibute__ ((__packed__)) EXT4_EXTENT_HEADER;

#define EXT4_EXT_MAGIC  0xf30a
#define get_ext4_header(i)      ((struct ext4_extent_header*)(i)->i_block)

#define EXT_FIRST_EXTENT(__hdr__) \
        ((struct ext4_extent*)(((char*)(__hdr__)) + \
                              sizeof(struct ext4_extent_header)))

#define EXT4_FIRST_INDEX(__hdr__) \
        ((struct ext4_extent_idx*)(((char*)(__hdr__)) + \
                                  sizeof(struct ext4_extent_header)))

#define INODE_HAS_EXTENT(i)     ((i)->i_flags & EXT2_EXTENTS_FL)

static inline uint64_t idx_to_block(EXT4_EXTENT_IDX *idx) {
    uint64_t block;

    block = (uint64_t)idx->ei_leaf_lo;
    block |= ((uint64_t)idx->ei_leaf_hi << 31) << 1;

    return block;
}

#define MAX_CACHE_SIZE      500
#define INVALID_TABLE       3
#define FILE_TYPE_PARTITION     0x7E
#define FILE_TYPE_DIR           2

/* Identifies the type of file by using i_mode of inode */
#define EXT2_S_ISDIR(mode)      ((mode & 0x0f000) == 0x04000)
#define EXT2_S_ISLINK(mode)     ((mode & 0x0f000) == 0x0a000)
#define EXT2_S_ISBLK(mode)      ((mode & 0x0f000) == 0x06000)
#define EXT2_S_ISSOCK(mode)     ((mode & 0x0f000) == 0x0c000)
#define EXT2_S_ISREG(mode)      ((mode & 0x0f000) == 0x08000)
#define EXT2_S_ISCHAR(mode)     ((mode & 0x0f000) == 0x02000)
#define EXT2_S_ISFIFO(mode)     ((mode & 0x0f000) == 0x01000)
 
/* Identifies the type of file by using file_type of dir structure */
#define EXT2_FT_ISDIR(mode)     (mode == 0x2)
#define EXT2_FT_ISLINK(mode)    (mode == 0x7)
#define EXT2_FT_ISBLK(mode)     (mode == 0x4)
#define EXT2_FT_ISSOCK(mode)    (mode == 0x6)
#define EXT2_FT_ISREG(mode)     (mode == 0x1)
#define EXT2_FT_ISCHAR(mode)    (mode == 0x3)
#define EXT2_FT_ISFIFO(mode)    (mode == 0x5) 

#define IS_PART(mode)           (mode == FILE_TYPE_PARTITION)

/* Mask values for access rights */
/* User*/
#define EXT2_S_IRUSR        0x0100
#define EXT2_S_IWUSR        0x0080
#define EXT2_S_IXUSR        0x0040
/* Group */
#define EXT2_S_IRGRP        0x0020
#define EXT2_S_IWGRP        0x0010
#define EXT2_S_IXGRP        0x0008
/* Other */
#define EXT2_S_IROTH        0x0004
#define EXT2_s_IWOTH        0x0002
#define EXT2_S_IXOTH        0x0001

#define IS_BUFFER_END(p, q, bsize)      (((char*)(p)) >= ((char*)(q) + bsize))

static inline const char* get_type_string(int type) {
    switch(type) {
        case 0x1:   return "Regular File";
        case 0x2:   return "Directory";
        case 0x3:   return "Character Device";
        case 0x4:   return "Block Device";
        case 0x5:   return "Fifo File";
        case 0x6:   return "Socket File";
        case 0x7:   return "Symbolic Link";
    }
    return "Unknown Type";
}

static inline char* get_access(unsigned long mode) {
    static char acc[10];

    acc[0] = (mode & EXT2_S_IRUSR) ? 'r' : '-';
    acc[1] = (mode & EXT2_S_IWUSR) ? 'w' : '-';
    acc[2] = (mode & EXT2_S_IXUSR) ? 'x' : '-';

    acc[3] = (mode & EXT2_S_IRGRP) ? 'r' : '-';
    acc[4] = (mode & EXT2_S_IWGRP) ? 'w' : '-';
    acc[5] = (mode & EXT2_S_IXGRP) ? 'x' : '-';

    acc[6] = (mode & EXT2_S_IROTH) ? 'r' : '-';
    acc[7] = (mode & EXT2_S_IWOTH) ? 'w' : '-';
    acc[8] = (mode & EXT2_S_IXOTH) ? 'x' : '-';
    
    acc[9] = '\0';
    
    return acc;
}

#define LOG(file, line, msg) printf("%s:%d : %s", file, line, smg);

#endif
