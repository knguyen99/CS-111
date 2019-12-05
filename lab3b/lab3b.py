#Khoi Nguyen
#knguyen99.g.ucla.edu
#804993073

import sys
import csv

exitCode = 0

inodeErr = "{} {} {} IN INODE {} AT OFFSET {}"
duplicate = "DUPLICATE {} {} IN INODE {} AT OFFSET {}"
allocated = "{} {} {}{} ON FREELIST"
inodeLink = "INODE {} HAS {} LINKS BUT LINKCOUNT IS {}"
dirInode = "DIRECTORY INODE {} NAME {} {} {}"
dirLink = "DIRECTORY INODE {} NAME {} LINK TO INODE {} SHOULD BE {}"

class superblock():
	def __init__(self,line):
		self.numBlocks = int(line[1])
                self.numInodes = int(line[2])
                self.blockSize = int(line[3])
                self.inodeSize = int(line[4])
                self.firstInode = int(line[7])
class group():
	def __init__(self,Audit,line):
		self.blocksInGroup = int(line[2])
                self.inodesInGroup = int(line[3])
                self.firstBlock = int(line[8]) + Audit.superblock.inodeSize * self.inodesInGroup/ Audit.superblock.blockSize

class Audit():
	def __init__(self, file):
		self.freeBlocks = []
		self.freeInodes = []
		self.inodes = []
		self.dirs = []
		self.indirs = []
		for line in file:
			if line[0] == "SUPERBLOCK":
				self.superblock = superblock(line)
			if line[0] == "GROUP":
				self.group = group(self,line)
			if line[0] == "BFREE":
				self.freeBlocks.append(int(line[1]))
			if line[0] == "IFREE":
				self.freeInodes.append(int(line[1]))
			if line[0] == "INODE":
				self.inodes.append(line)
			if line[0] == "DIRENT":
				self.dirs.append(line)
			if line[0] == "INDIRECT":
				self.indirs.append(line)

	def getOffset(self, i):
		if i == 24:
			return 12, "INDIRECT BLOCK"
		elif i == 25:
			return 268, "DOUBLE INDIRECT BLOCK"
		elif i == 26: 
			return 65804, "TRIPLE INDIRECT BLOCK"
		else:
			 return 0, "BLOCK"

	def blockAudit(self):
		refBlocks = {}
		for line in self.inodes:
			inodeNum = int(line[1])
			if self.inodes[2] == 's' and self.inodes[10] == '0':
				continue
			i = 0
			for b in range(12,27):
				bNum = int(line[b])
				offset,label = self.getOffset(b)
				if bNum != 0:
					if bNum not in refBlocks:
						if bNum not in self.freeBlocks:
							if not bNum in range(0,self.superblock.numBlocks):
								exitCode = 2
								print(inodeErr.format("INVALID",label,bNum,inodeNum,offset))
							elif bNum in range (0,self.group.firstBlock):
								exitCode = 2
								print(inodeErr.format("RESERVED",label,bNum,inodeNum,offset)) 
							else:
								refBlocks[bNum] = [(label,inodeNum,offset)]								
						else:
							refBlocks[bNum] = [(label,inodeNum,offset)]
					else:
						refBlocks[bNum].append((label,inodeNum,offset))
				i = i+1
		for line in self.indirs:
			level = int(line[2])
			offset,label = self.getOffset(23+level) 
			bNum = int(line[5])
			inodeNum = int(line[1])
			if bNum != 0:
				if bNum not in refBlocks:
					if bNum not in self.freeBlocks:
						if not bNum in range(0,self.superblock.numBlocks):
							exitCode = 2
							print(invalid.format(label,bNum,inodeNum, offset)) 
						elif bNum in range(0,self.group.firstBlock):
							exitCode = 2
							print(reserved.format(label,bNum,inodeNum,offset))
						else:
							refBlocks[bNum] = [(label,inodeNum,offset)]
					else:
						refBlocks[bNum] = [(label,inodeNum,offset)]
				else:
					refBlocks[bNum].append((label,inodeNum,offset))
		for i in range(self.group.firstBlock, self.superblock.numBlocks):
			if i not in self.freeBlocks and i not in refBlocks:
				exitCode = 2
				print("UNREFERENCED BLOCK {}".format(i))
			elif i in refBlocks and len(refBlocks[i])>1:
				for j in range(len(refBlocks[i])):
					exitCode = 2
					print(duplicate.format(refBlocks[i][j][0],i,refBlocks[i][j][1],refBlocks[i][j][2]))
			elif i in refBlocks and i in self.freeBlocks:
				exitCode = 2
				print(allocated.format("ALLOCATED","BLOCK",i, ""))

	def inodeAudit(self):
		for line in self.inodes:
			inodeNum = int(line[1])
			if inodeNum in self.freeInodes:
				exitCode = 2
				print(allocated.format("ALLOCATED","INODE",inodeNum,""))
		for i in range(self.superblock.firstInode, self.group.inodesInGroup):
			if i not in self.freeInodes:
				flag = False
				for j in self.inodes:
					if i == int(j[1]):
						flag = True
				if not flag:
					exitCode = 2
					print(allocated.format("UNALLOCATED","INODE", i, " NOT")) 
	def dirAudit(self):
		links =	{}
		parents = {}
                for i in self.inodes:
                        links[int(i[1])] = (0)
		for line in self.dirs:
			inodeNum = int(line[3])
			flag = False
                        for j in self.inodes:
                        	if inodeNum == int(j[1]):
                	                flag = True
                        if not flag and inodeNum in self.freeInodes:
				exitCode = 2
				print(dirInode.format(line[1],line[6],"UNALLOCATED INODE", inodeNum))
			elif not inodeNum in range(1,self.superblock.numInodes):
                                exitCode = 2
                                print(dirInode.format(line[1],line[6],"INVALID INODE", inodeNum))
			else:
				links[inodeNum] = (links[inodeNum]+1)
				name = line[6]
				if inodeNum not in parents:
					parents[inodeNum] = int(line[1])

		for i in self.inodes:
			if links[int(i[1])] != int(i[6]):
				exitCode = 2
				print(inodeLink.format(i[1],links[int(i[1])],i[6])) 

		for line in self.dirs:
			name = line[6]
			parentInode = int(line[1])
			currInode = int(line[3])
			if name == "'.'" and parentInode != currInode:
				exitCode = 2
				print(dirLink.format(parentInode,"'.'",currInode,parentInode))
			if name == "'..'" and parents[parentInode] != currInode:
				exitCode = 2
				print(dirLink.format(parentInode,"'..'",currInode,parentInode))				
def main():
	if (len(sys.argv) != 2):
		sys.stderr.write("Error incorrect arguments\n")
		exit(1)

	try:
		fd = open(sys.argv[1],'r')
	except IOError:
		sys.stderr.write("Unable to open file\n")
		exit(1)

	file = csv.reader(fd)

	f = Audit(file)
	f.blockAudit()
	f.inodeAudit()
	f.dirAudit()
	fd.close()
	exit(exitCode)

if __name__ == "__main__":
    main()
