#include "writeBMP.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

#define PW 128
#define PH 128

#define SW (PW + 1)
#define SH (PH + 1)

#define BigRadi 60
#define SmallRadi 15

#define CenterX 64
#define CenterY 64


#define UPLEFT 0b1000
#define UPRIGHT 0b0100
#define DOWNRIGHT 0b0010
#define DOWNLEFT 0b0001


static char CPatterns[PW][PH] ;
static char MPatterns[PW][PH] ;
static char YPatterns[PW][PH] ;


void print_binary(int num) {
  char binary_str[33];
  itoa(num, binary_str, 2);
  printf("%016s\n", binary_str); // 打印二进制字符串
}

void print_vector(vector<int> vec) {
  for (int index = 0; index < vec.size(); index++) {
    cout << vec[index] << ",";
  }
}

void print_binary_vector(vector<int> vec) {
  for (int index = 0; index < vec.size(); index++) {
    char binary_str[33];
    itoa(vec[index], binary_str, 2);
    printf("%016s,", binary_str); // 打印二进制字符串
  }
}

char patternToElement(int pattern, int index) {

  switch (index) {
  case 0:
    /// upleft
    return (pattern & 0xF000) >> 12;
  case 1:
    /// upright
    return (pattern & 0x0F00) >> 8;
  case 2:
    /// downright
    return (pattern & 0x00F0) >> 4;
    ;
  default:
    /// downleft
    return (pattern & 0x000F);
  }

  return 0;
}

int plotBmpWithPatterns(char *patterns, int width, int height, char *filename) {

  // Calculate size of image data
  ////X4 的原因在于一个像素里面有四个落点
  int data_size = width * height * 3 * 4;
  unsigned char *RGBData =
      (unsigned char *)malloc(sizeof(unsigned char) * data_size);
  memset(RGBData, 255, sizeof(unsigned char) * data_size);

  int lengthInLine = width * 3 * 2;

  for (int xpos = 0; xpos < width; xpos++) {

    int xx = 2 * xpos;

    for (int ypos = 0; ypos < height; ypos++) {

      char pattern = *((char *)patterns + xpos * height + ypos);

      int yy = 2 * ypos;

      int upleft = yy * lengthInLine + xx * 3;
      int upright = yy * lengthInLine + (xx + 1) * 3;
      int downright = (yy + 1) * lengthInLine + (xx + 1) * 3;
      int downleft = (yy + 1) * lengthInLine + xx * 3;

      if (pattern & UPLEFT) {
        *((unsigned char *)(RGBData + upleft)) = 0;
        *((unsigned char *)(RGBData + upleft + 1)) = 0;
        *((unsigned char *)(RGBData + upleft + 2)) = 0;
      }
      if (pattern & UPRIGHT) {
        *((unsigned char *)(RGBData + upright)) = 0;
        *((unsigned char *)(RGBData + upright + 1)) = 0;
        *((unsigned char *)(RGBData + upright + 2)) = 0;
      }
      if (pattern & DOWNRIGHT) {
        *((unsigned char *)(RGBData + downright)) = 0;
        *((unsigned char *)(RGBData + downright + 1)) = 0;
        *((unsigned char *)(RGBData + downright + 2)) = 0;
      }
      if (pattern & DOWNLEFT) {
        *((unsigned char *)(RGBData + downleft)) = 0;
        *((unsigned char *)(RGBData + downleft + 1)) = 0;
        *((unsigned char *)(RGBData + downleft + 2)) = 0;
      }
    }
  }

  char bmpFileName[128];
  memset(bmpFileName, 0, 128);
  sprintf(bmpFileName, "image_%s.bmp", filename);
  writeBMP(bmpFileName, height * 2, width * 2, RGBData);
  // Draw point
  free(RGBData);

  cout << "finish" << endl;

  return 0;
}



int plotCPatterns() {
 
  int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = CPatterns[column][row];
    }
  }

  return plotBmpWithPatterns(*patterns, width, height, "plotCirclePatternsForC");
}

int plotMPatterns() {

   int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = MPatterns[column][row];
    }
  }

  return plotBmpWithPatterns(*patterns, width, height, "plotCirclePatternsForM");
}

int plotYPatterns() {

    int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = YPatterns[column][row];
    }
  }

  return plotBmpWithPatterns(*patterns, width, height, "plotCirclePatternsForY");
}


int doCMYPatterns() {
  /////要打印的是银浆
  int pattern = UPRIGHT;

 int width = PW;
  int height = PH;

 for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      
        CPatterns[column][row] = 0;
        MPatterns[column][row] = 0;
        YPatterns[column][row] = 0;

     double distance = sqrt(pow(column - CenterX, 2) + pow(row - CenterY, 2));

       // 计算斜率角的弧度值
    double angle = atan2(row - CenterY, column - CenterX);

    // 将弧度值转换为角度
    angle = angle * 180 / M_PI;
 
      if(distance <= SmallRadi) 
      {
        CPatterns[column][row] = pattern;
        MPatterns[column][row] = pattern;
        YPatterns[column][row] = pattern;
      }

      if (distance <= BigRadi)
      {
         if (column > CenterX)
         {
           YPatterns[column][row] = pattern;
         }

         if (angle >= 30  && angle <= 180
         || angle <= -150)
         {
             CPatterns[column][row] = pattern;
         }

          if (angle >= -180 && angle <= -30
          || angle >= 150)
         {
             MPatterns[column][row] = pattern;
         }
      }


    }
  }

}

int main() {

    printf("start  \n");

doCMYPatterns();

  plotCPatterns();
  plotMPatterns();
  plotYPatterns();

    printf("end  \n");

  return 0;
}
