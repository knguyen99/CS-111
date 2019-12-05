//Khoi Nguyen
//knguyen99.g.ucla.edu
//804993073

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "ext2_fs.h"
#include <stdint.h>
#include <time.h>

int file;
int offset = 1024;
int blocksize;
unsigned int numGroups;
unsigned int numBlocksInGroup;
unsigned int numInodesInGroup;

struct ext2_super_block superblock;
struct ext2_group_desc group;
struct ext2_inode inode;

void groupSummary();									//print group summary
void fbSummary(int groupNum);								//print free blocks
void fiSummary(int groupNum);	 							//print free inode summary
void inodeSummary(int inodeNum);							//print inode summary
void dirSummary(int blockNum, int inodeNum); 						//print directory summary
void indirSummary(int blockNum, int inodeNum, int l, int offset, char fileType);	//print indirect reference summary
	
void sbSummary()
{
	if((pread(file,&superblock,sizeof(struct ext2_super_block), offset)) == -1)
	{
		fprintf(stderr, "Error in reading image: superblock\n");
		exit(2);
	}
	blocksize = 1024 << superblock.s_log_block_size;
	printf("SUPERBLOCK,%u,%u,%u,%u,%u,%u,%u\n", 
		superblock.s_blocks_count, 	//total number of blocks (decimal)
		superblock.s_inodes_count, 	//total number of i-nodes (decimal)
		blocksize, 			//block size (in bytes, decimal)
		superblock.s_inode_size, 	//i-node size (in bytes, decimal)
		superblock.s_blocks_per_group, 	//blocks per group (decimal)
		superblock.s_inodes_per_group, 	//i-nodes per group (decimal)
		superblock.s_first_ino 		//first non-reserved i-node (decimal)
		);
}

void groupSummary()
{
	for(__uint32_t i = 0; i < numGroups; i++)
	{
		if((pread(file,&group, sizeof(struct ext2_group_desc), offset + i*sizeof(struct ext2_group_desc) + blocksize)) == -1)
		{
			fprintf(stderr, "Error in reading image: group");
			exit(2);
		}
		numBlocksInGroup = superblock.s_blocks_per_group;
		numInodesInGroup = superblock.s_inodes_per_group;

		//all cylinder groups but the last have the same number of blocks and I-nodes; 
		//the last has the residue (e.g., blocks/fs modulo blocks/group).
		if(i == numGroups-1)
		{
			int bfrag = superblock.s_blocks_count%superblock.s_blocks_per_group; 
			int ifrag =  superblock.s_inodes_count&superblock.s_inodes_per_group;
			if(bfrag)
				numBlocksInGroup = bfrag;
			if(ifrag)
				numInodesInGroup = ifrag;
		} 
		
		printf("GROUP,%u,%u,%u,%u,%u,%u,%u,%u\n",
			i,				//group number (decimal, starting from zero)
			numBlocksInGroup,		//total number of blocks in this group (decimal)
			numInodesInGroup,		//total number of i-nodes in this group (decimal)
			group.bg_free_blocks_count,	//number of free blocks (decimal)
			group.bg_free_inodes_count,	//number of free i-nodes (decimal)
			group.bg_block_bitmap,		//block number of free block bitmap for this group (decimal)
			group.bg_inode_bitmap,		//block number of free i-node bitmap for this group (decimal)	
			group.bg_inode_table		//block number of first block of i-nodes in this group (decimal)
		);
		fbSummary(i);	
		fiSummary(i);
	}
}

void fbSummary(int groupNum)
{
	char* block = malloc(blocksize);
	if((pread(file,block, blocksize, groupNum+group.bg_block_bitmap*blocksize)) == -1)
	{
		fprintf(stderr, "Error in reading free blocks");
		exit(2);
	}

	int flag = 0;
	for(__uint32_t i = 0; i < numBlocksInGroup/8; i++)
	{
		for(int j = 0; j < 8; j++)
		{	
			if((block[i] & (1<<j)) == 0)
			{
				int blockNum = groupNum*superblock.s_blocks_per_group + i*8 + j + 1;
				if(blockNum > (int) superblock.s_blocks_per_group)
				{
					flag = 1;
					break;
				}
				printf("BFREE,%i\n", blockNum);
			}
		}
		if(flag)
			break;
	}
	free(block);
}

void fiSummary(int groupNum)
{
	char* block = malloc(blocksize);
	if((pread(file,block, blocksize, groupNum+group.bg_inode_bitmap*blocksize)) == -1)
        {
                fprintf(stderr, "Error in reading free inodes");
                exit(2);
        }
	
	int flag = 0;
        for(__uint32_t i = 0; i < numInodesInGroup/8; i++)
        {
                for(int j = 0; j < 8; j++)
                {
			int inodeNum = groupNum*superblock.s_blocks_per_group + i*8 + j + 1;
                        if((block[i] & (1<<j)) == 0)
                        {
                                if(inodeNum > (int) superblock.s_blocks_per_group)
                                {
                                        flag = 1;
                                        break;
                                }
                                printf("IFREE,%i\n", inodeNum);
                        }
			else
			{
				inodeSummary(inodeNum);
			}
                }
                if(flag)
                        break;
        }
	free(block);

}

void inodeSummary(int inodeNum)
{
	if((pread(file, &inode, superblock.s_inode_size, group.bg_inode_table*blocksize + (inodeNum-1)*superblock.s_inode_size)) == -1)
	{
		fprintf(stderr, "Error in reading allocated inode");
		exit(2);
	}	

	if(inode.i_mode == 0 || inode.i_links_count == 0)
		return;

	char fileType;
	if((inode.i_mode & 0x8000) == 0x8000) 
		fileType = 'f';
	else if((inode.i_mode & 0x4000) == 0x4000)
		fileType = 'd';
	else if((inode.i_mode & 0xA000) == 0xA000)
		fileType = 's';
	else
		fileType = '?';

	char cTime[18], mTime[18], aTime[18];

	time_t time = inode.i_ctime;
	struct tm* tm = gmtime(&time);
	strftime(cTime,18,"%m/%d/%y %H:%M:%S",tm);
	
	time = inode.i_mtime;
	tm = gmtime(&time);
	strftime(mTime,18,"%m/%d/%y %H:%M:%S",tm);

	time = inode.i_atime;
	tm = gmtime(&time);
	strftime(aTime,18,"%m/%d/%y %H:%M:%S",tm);

	printf("INODE,%i,%c,%o,%u,%u,%u,%s,%s,%s,%u,%u",
		inodeNum,	 	//inode number (decimal)
		fileType,		//file type ('f' for file, 'd' for directory, 's' for symbolic link, '?" for anything else)
		inode.i_mode & 0xFFF,	//mode (low order 12-bits, octal ... suggested format "%o")
		inode.i_uid,		//owner (decimal)
		inode.i_gid,		//group (decimal)
		inode.i_links_count,	//link count (decimal)
		cTime,			//time of last I-node change (mm/dd/yy hh:mm:ss, GMT)
		mTime,			//modification time (mm/dd/yy hh:mm:ss, GMT)
		aTime,			//time of last access (mm/dd/yy hh:mm:ss, GMT)
		inode.i_size,		//file size (decimal)
		inode.i_blocks);	//number of (512 byte) blocks of disk space (decimal) taken up by this file

	if(fileType == 'f' || fileType == 'd' || (fileType == 's' && inode.i_size > 60))
	{
		for(int i = 0; i < EXT2_N_BLOCKS; i++)
			printf(",%u", inode.i_block[i]);
	}
	printf("\n");

	for(int i = 0; i < EXT2_N_BLOCKS-3; i++)
	{
		if(fileType == 'd' && inode.i_block[i] != 0)
			dirSummary(inode.i_block[i],inodeNum);				
	}

	if(fileType == 'f' || fileType == 'd')
	{
		if(inode.i_block[EXT2_IND_BLOCK] != 0)
			indirSummary(inode.i_block[EXT2_IND_BLOCK],inodeNum,1,12,fileType);
		if(inode.i_block[EXT2_DIND_BLOCK] != 0)
	                indirSummary(inode.i_block[EXT2_DIND_BLOCK],inodeNum,2,268,fileType);
		if(inode.i_block[EXT2_TIND_BLOCK] != 0)
	                indirSummary(inode.i_block[EXT2_TIND_BLOCK],inodeNum,3,65804,fileType);
	}

}

void dirSummary(int blockNum, int inodeNum)
{
	struct ext2_dir_entry directory;
	for(int i = 0; i < blocksize; i+= directory.rec_len)
	{
		if((pread(file,&directory, sizeof(struct ext2_dir_entry),blockNum*blocksize+i)) == -1)
		{
			fprintf(stderr, "Error in reading directory");
			exit(2);
		}


		if((int)directory.inode != 0)
		{
			printf("DIRENT,%i,%i,%u,%u,%u,\'%s\'\n",
				inodeNum,		//parent inode number (decimal) ... the I-node number of the directory that contains this entry
				i,			//logical byte offset (decimal) of this entry within the directory
				directory.inode,	//inode number of the referenced file (decimal)
				directory.rec_len,	//entry length (decimal)
				directory.name_len,	//name length (decimal)
				directory.name);	//name (string, surrounded by single-quotes).
		}
	}
}

void indirSummary(int blockNum, int inodeNum, int l, int offset, char fileType)
{
	if(blockNum == 0)
		return;
	int* block = malloc(blocksize);
	if((pread(file, block, blocksize, blockNum*blocksize)) == -1)
	{
		fprintf(stderr, "Error in reading indirect");
		exit(2);
	} 
	for(int i = 0; i < blocksize/4; i++)
	{
		if(block[i])
		{
			int logicalOffset;
			switch(l)
			{
				case 3:
					logicalOffset = offset + i*65536;
					break;
				case 2:
					logicalOffset = offset + i*256;
					break;
				case 1:
					logicalOffset = offset + i;
					break; 
			}	
			if(fileType == 'd')
			{
				dirSummary(block[i],inodeNum);
			}
			printf("INDIRECT,%i,%i,%i,%i,%u\n",
                        	inodeNum,	//I-node number of the owning file (decimal)
                              	l,              //(decimal) level of indirection for the block being scanned
                              	logicalOffset,  //logical block offset (decimal) represented by the referenced block.
                              	blockNum,	//block number of the (1, 2, 3) indirect block being scanned
                              	block[i]);	//block number of the referenced block (decimal)
			if(l>1)
				indirSummary(block[i],inodeNum, l-1, logicalOffset, fileType);
		}
	}
	
	free(block);

}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Incorrect number of arguments");
		exit(1);
	}
	file = open(argv[1], O_RDONLY);

	if(file == -1)
	{
		fprintf(stderr, "Error in opening file");
		exit(1);		
	}
	
	sbSummary();
	numGroups = superblock.s_blocks_count/superblock.s_blocks_per_group + 1;
	groupSummary();
	
	close(file);	
	exit(0);
}
