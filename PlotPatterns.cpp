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

#define PatternWidth 2
#define PatterHeight 2
#define AllBlockWidth 32
#define AllBlockHeight 32
#define CopyBlockWidth 8
#define CopyBlockHeight 8

#define PositionCountInOnePixel 4
#define ElementCountInOnePattern 4

#define UPLEFT 0b1000
#define UPRIGHT 0b0100
#define DOWNRIGHT 0b0010
#define DOWNLEFT 0b0001

static std::vector<int> allPatterns;

static std::vector<int> CPatterns;
static std::vector<int> MPatterns;
static std::vector<int> YPatterns;

static int patternsForScreen[PW][PH]; ////每个像素的模式值

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

void generatePatterns(int pattern, int depth) {
  if (depth == 4) {
    // 如果已经生成了4个元素的模式，打印结果
    /// print_binary(pattern);
    allPatterns.push_back(pattern);
    return;
  }

  // 每个元素可以处于1到4的位置，使用二进制表示
  for (int i = 0; i < 4; i++) {
    // 生成位置值 (1, 2, 4, 8)
    int positionValue = 1 << i;
    // 更新当前位置的值，并递归处理下一个位置
    int newPattern = pattern | (positionValue << (depth * 4));
    generatePatterns(newPattern, depth + 1);
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

    for (int ypos = height - 1; ypos >= 0; ypos--) {

      char pattern = *((char *)patterns + xpos * height + ypos);

      int yy = 2 * (height - ypos - 1);

      int upleft = yy * lengthInLine + xx * 3;
      int upright = yy * lengthInLine + (xx + 1) * 3;
      int downright = (yy + 1) * lengthInLine + (xx + 1) * 3;
      int downleft = (yy + 1) * lengthInLine + xx * 3;

      if (pattern & UPLEFT) {
        *((unsigned char *)(RGBData + upleft)) = 0;
        *((unsigned char *)(RGBData + upleft + 1)) = 0;
        *((unsigned char *)(RGBData + upleft + 2)) = 0;
      } else if (pattern & UPRIGHT) {
        *((unsigned char *)(RGBData + upright)) = 0;
        *((unsigned char *)(RGBData + upright + 1)) = 0;
        *((unsigned char *)(RGBData + upright + 2)) = 0;
      } else if (pattern & DOWNRIGHT) {
        *((unsigned char *)(RGBData + downright)) = 0;
        *((unsigned char *)(RGBData + downright + 1)) = 0;
        *((unsigned char *)(RGBData + downright + 2)) = 0;
      } else if (pattern & DOWNLEFT) {
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
      patterns[column][row] = 0;
    }
  }

  for (int column = 0; column < width; column += 2) {
    for (int row = 0; row < height; row += 2) {

      int columnIndex = column / 64;
      int rowIndex = row / 64;

      int patternIndex = rowIndex * width / 2 + columnIndex;

      //  if (patternIndex >= CPatterns.size())
      //    break;

      int pattern = CPatterns[patternIndex];

      patterns[column][row] = patternToElement(pattern, 0);
      patterns[column + 1][row] = patternToElement(pattern, 1);
      patterns[column + 1][row + 1] = patternToElement(pattern, 2);
      patterns[column][row + 1] = patternToElement(pattern, 3);
    }
  }

  return plotBmpWithPatterns(*patterns, width, height, "plotCPatterns");
}

int plotMPatterns() {

  int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = 0;
    }
  }

  for (int column = 0; column < width; column += 2) {
    for (int row = 0; row < height; row += 2) {

      int columnIndex = column / 64;
      int rowIndex = row / 64;

      int patternIndex = rowIndex * width / 2 + columnIndex;

      //  if (patternIndex >= MPatterns.size())
      //   break;

      int pattern = MPatterns[patternIndex];

      patterns[column][row] = patternToElement(pattern, 0);
      patterns[column + 1][row] = patternToElement(pattern, 1);
      patterns[column + 1][row + 1] = patternToElement(pattern, 2);
      patterns[column][row + 1] = patternToElement(pattern, 3);
    }
  }

  return plotBmpWithPatterns(*patterns, width, height, "plotMPatterns");
}

int plotYPatterns() {

  int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = 0;
    }
  }

  for (int column = 0; column < width; column += 2) {
    for (int row = 0; row < height; row += 2) {

      int columnIndex = column / 64;
      int rowIndex = row / 64;

      int patternIndex = rowIndex * width / 2 + columnIndex;

      // if (patternIndex >= YPatterns.size())
      //   break;

      int pattern = YPatterns[patternIndex];

      patterns[column][row] = patternToElement(pattern, 0);
      patterns[column + 1][row] = patternToElement(pattern, 1);
      patterns[column + 1][row + 1] = patternToElement(pattern, 2);
      patterns[column][row + 1] = patternToElement(pattern, 3);
    }
  }

  return plotBmpWithPatterns(*patterns, width, height, "plotYPatterns");
}

int plotCopyForAllPatterns() {

  int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = 0;
    }
  }

  for (int column = 0; column < width; column += 2) {
    for (int row = 0; row < height; row += 2) {

      int columnIndex = column / 8;
      int rowIndex = row / 8;

      int patternIndex = rowIndex * 16 + columnIndex;

      int pattern = allPatterns[patternIndex];

      patterns[column][row] = patternToElement(pattern, 0);
      patterns[column + 1][row] = patternToElement(pattern, 1);
      patterns[column + 1][row + 1] = patternToElement(pattern, 2);
      patterns[column][row + 1] = patternToElement(pattern, 3);
    }
  }

  return plotBmpWithPatterns(*patterns, width, height,
                             "plotCopyForAllPatterns");
}

int plotAllPatternsIn32x32() {

  int width = PW;
  int height = PH;

  char patterns[width][height];
  for (int column = 0; column < width; column++) {
    for (int row = 0; row < height; row++) {
      patterns[column][row] = 0;
    }
  }

  for (int column = 0; column < width; column += 2) {
    for (int row = 0; row < height; row += 2) {

      int columnIndex = column % 32;
      int rowIndex = row % 32;

      int patternColumnIndex = columnIndex / 2;
      int patternRowIndex = rowIndex / 2;

      if (column <= width / 2 && row <= height / 2)
        continue;
      if (column >= width / 2 && row >= height / 2)
        continue;

      int patternIndex = patternRowIndex * 16 + patternColumnIndex;

      int pattern = allPatterns[patternIndex];

      patterns[column][row] = patternToElement(pattern, 0);
      patterns[column + 1][row] = patternToElement(pattern, 1);
      patterns[column + 1][row + 1] = patternToElement(pattern, 2);
      patterns[column][row + 1] = patternToElement(pattern, 3);
    }
  }

  return plotBmpWithPatterns(*patterns, width, height,
                             "plotAllPatternsIn32x32");
}

void calCMYPatterns() {

  int count = allPatterns.size();
  for (int cpos = 0; cpos < count; cpos++) {
    for (int mpos = 0; mpos < count; mpos++) {
      for (int ypos = 0; ypos < count; ypos++) {
        int cp = allPatterns[cpos];
        int mp = allPatterns[mpos];
        int yp = allPatterns[ypos];
        if ((cp & mp) == 0 && (yp & mp) == 0 && (cp & yp) == 0) {

          if (cp == (int)0b0010000110000100) {
            //   if (mp == (int)0b1000010000100001) {
            CPatterns.push_back(cp);
            MPatterns.push_back(mp);
            YPatterns.push_back(yp);
            //   }
          }
        }
      }
    }
  }
}

int main() {
  int pattern = 0; // 初始模式为0
  generatePatterns(pattern, 0);

  cout << allPatterns.size() << endl;

  plotAllPatternsIn32x32();

  plotCopyForAllPatterns();

  calCMYPatterns();
  // print_binary_vector(CPatterns);

  //  print_binary(MPatterns.back());
  // print_binary(YPatterns.back());
  cout << YPatterns.size() << endl;
  print_binary(YPatterns.back());
  char upleft = patternToElement(YPatterns.back(), 0);
  print_binary(upleft);
  cout << MPatterns.size() << endl;
  //  print_binary_vector(YPatterns);
  cout << YPatterns.size() << endl;

  plotCPatterns();
  plotMPatterns();
  plotYPatterns();

  return 0;
}
