
#ifndef __WRITEBMP_H__
#define __WRITEBMP_H__

#include <malloc.h>
#include <string.h>
#include <fstream>
/*
BMP文件由两部分组成,

文件信息头
文件主体(图片颜色信息)

所以, 如果要用C写入BMP文件, 我们一共有4个步骤

计算文件长度, 申请内存
生成文件信息头
写入图片颜色
将整段内存空间按二进制写入文件

*/
/*
fileName  文件名字
line      图片行数
column    图片列数
BGRData   图片的颜色信息, 要求是蓝色, 绿色, 红色依次按字节排列 */




static inline void writeFile(const char* fileName,const char* toWrite,const long long unsigned int length){
	FILE* filePointer=NULL;
	filePointer=fopen(fileName,"wb");
	// fprintf(filePointer,"%s",toWrite);
	fwrite(toWrite,length,1,filePointer);
    fclose(filePointer);
}

static inline void writeBMP(const char* fileName,const unsigned line,const unsigned column,const unsigned char* BGRData){
	 /// 按照BMP格式的介绍, 每一行的字节长度必须是4的倍数, 少的要补0
    unsigned columnByteLength=column*3;
	if(columnByteLength&0b11){
		columnByteLength=((columnByteLength>>2)+1)<<2;
	}
	unsigned fileLength=56+(line*columnByteLength);
	char* toWrite=(char*)malloc(sizeof(char)*fileLength);
	memset(toWrite,0,sizeof(char)*fileLength);
	*((char*)(toWrite+0))='B';
	*((char*)(toWrite+1))='M';
	*((unsigned*)(toWrite+2))=fileLength;
	*((unsigned*)(toWrite+6))=0;
	*((unsigned*)(toWrite+10))=56;  /// BMP文件头的长度,  最少54字节
	*((unsigned*)(toWrite+14))=40; /// 文件头的长度，固定40
	*((int*)(toWrite+18))=column;
	*((int*)(toWrite+22))=-line;
	*((unsigned short*)(toWrite+26))=1;
	*((unsigned short*)(toWrite+28))=24;  /// 每个像素的颜色长度 bit
	*((unsigned*)(toWrite+30))=0;
	*((unsigned*)(toWrite+34))=0;
	*((int*)(toWrite+38))=0;
	*((int*)(toWrite+42))=0;
	*((unsigned*)(toWrite+46))=0;
	*((unsigned*)(toWrite+50))=0;
	char* BGR=toWrite+56;
	unsigned indexBGR=0;
	unsigned dataIndex=0;
	for(unsigned indexLine=0;indexLine<line;indexLine++){
		memcpy(BGR+indexBGR,BGRData+dataIndex,column*3);
		indexBGR=indexBGR+columnByteLength;
		dataIndex=dataIndex+column*3;
	}
	char* fileNameCopy=(char*)malloc(sizeof(char*)*(strlen(fileName)+8));
	memset(fileNameCopy,0,sizeof(char*)*(strlen(fileName)+8));
	strcpy(fileNameCopy,fileName);
	if(strlen(fileName)>=4){
		if(strcmp(".bmp",fileName+strlen(fileName)-4)){
			strcat(fileNameCopy,".bmp");
		}
	}

    
    /// 最后就是写文件并且释放内存.
	writeFile(fileNameCopy,toWrite,fileLength);
	free(fileNameCopy);
	free(toWrite);
}

#endif // __WRITEBMP_H__