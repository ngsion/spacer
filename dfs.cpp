#include <iostream>
#include "Screen.h"
#include <algorithm>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <iterator>
#include <stdio.h>
#include <string>
#include "Utility.h"
#include <time.h>

////算法思路： 在某条对角线上，每一点都进行计算，以该点为圆心作圆，圆内要求没有柱子， 然后取能作最大半径圆那个点来放柱子

/// 参考n皇后的做法，在以nValue为边长的正方形内进行计算
#define nValue (SW * SH - PW * PH)

////从中心开始向两边展开来放柱子
#define nStart (nValue / 2)

////两套坐标系的利率
#define Ratio 1.414

/// @brief 可变参数，标记两个柱子的最小距离要求
int MinDistance = 3;

////定义边缘最少空行
int EdgeOffset = 1;

/// 记录每行的colvalues值，index值即为row值
int colValues[nValue];

Screen screen = Screen();

static int results = 0;

/// @brief 检查x，y的值是否处于边缘
/// @param x
/// @param y
/// @return
bool checkXY(int x, int y)
{
  if (x <= EdgeOffset || y <= EdgeOffset || (SW - x) <= EdgeOffset || (SH - y) <= EdgeOffset)
  {
    return true;
  }
  return false;

  if (MinDistance <= x && x <= SW - MinDistance && (y <= MinDistance || (SH - y) <= MinDistance))
  {
    return true;
  }

  if (MinDistance <= y && y <= SH - MinDistance && (x <= MinDistance || (SW - x) <= MinDistance))
  {
    return true;
  }

  if (x < MinDistance)
  {
    if (y < MinDistance && x * x + y * y < MinDistance * MinDistance * Ratio)
    {
      return true;
      ;
    }

    if ((SH - y) < MinDistance && x * x + (SH - y) * (SH - y) < MinDistance * MinDistance * Ratio)
    {
      return true;
    }
  }

  if (x > SW - MinDistance)
  {
    if (y < MinDistance && (SW - x) * (SW - x) + y * y < MinDistance * MinDistance * Ratio)
    {
      return true;
    }

    if ((SH - y) < MinDistance && (SW - x) * (SW - x) + (SH - y) * (SH - y) < MinDistance * MinDistance * Ratio)
    {
      return true;
    }
  }

  return false;
}

void dfs(int row)
{

  if (nValue - 1 == row)
  {
    /// 得到一个结果了, 打印出来
    ////将柱子右上方的全部置为4
    for (int xpos = 0; xpos < SW; xpos++)
    {
      for (int ypos = 0; ypos < SH; ypos++)
      {
        if (1 == screen.A[xpos][ypos])
        {
          for (int xx = xpos + 1, yy = ypos + 1; xx < SW, yy < SH; xx++, yy++)
          {
            screen.A[xx][yy] = 4;
          }
        }
      }
    }

    ofstream outFile;
    char filename[64] = {0};

    sprintf(filename, "dfs/result_%dX%d_distance_%d_%d.csv", PW, PH, EdgeOffset, MinDistance);

    outFile.open(filename);

    int maxDistance = 0;
    for (int a = 0; a < nValue; a++)
    {
      if (-1 == colValues[a])
        continue;

      ////找出离a点柱子最近的柱子的距离
      int dis = 0;
      for (int b = 0; b < nValue; b++)
      {
        if (-1 == colValues[b])
          continue;
        if (a == b)
          continue;

        int y = abs(a - b);
        int x = abs(colValues[a] - colValues[b]);
        int tempdis = x * x + y * y;
        if (0 == dis)
        {
          dis = tempdis;
        }
        else if (tempdis < dis)
        {
          dis = tempdis;
        }
      }

      int xpos = (a + colValues[a] + 1 - SH) / 2;
      int ypos = (a - colValues[a] - 1 + SH) / 2;

      // return ;

      outFile << xpos << "," << ypos << "," << sqrt((dis * 1.0) / Ratio) << endl;

      if (0 == maxDistance)
      {
        maxDistance = dis;
      }
      else if (maxDistance < dis)
      {
        maxDistance = dis;
      }
    }

    outFile.close();

    printf("get one result %d , pole count %d, ratio is %f, maxdis %f\n", results, screen.GetPoleCount(), screen.GetPoleRatio(), sqrt((maxDistance * 1.0) / Ratio));

    screen.PrintOut(EdgeOffset, MinDistance, maxDistance);
    ++results;

    ////打印完了，恢复，用于下一次计算
    for (int xpos = 0; xpos < SW; xpos++)
    {
      for (int ypos = 0; ypos < SH; ypos++)
      {
        if (1 == screen.A[xpos][ypos])
        {
          for (int xx = xpos + 1, yy = ypos + 1; xx < SW, yy < SH; xx++, yy++)
          {
            screen.A[xx][yy] = 2;
          }
        }
      }
    }
    return;
  }

  /// 在当前对角线上是否找到了结果标识
  bool found = false;

  int mDistance = MinDistance * MinDistance * Ratio;

  int targetCol = -1;
  for (int col = 0; col < nValue; col++)
  {

    /// x,y为screen中坐标
    if ((row + col + 1 - SH) % 2 != 0 || (row - col - 1 + SH) % 2 != 0)
    {
      ////这里有接近1/2的点不见了
      // printf("something is wrong pls check %d , %d\n",(row+col+1-SH),(row-col-1+SH));
      continue;
    }

    int x = (row + col + 1 - SH) / 2;
    int y = (row - col - 1 + SH) / 2;

    if (x < 0 || x >= SW || y < 0 || y >= SH)
    {
      continue;
    }

    if (checkXY(x, y))
    {
      continue;
    }

    int tempDiff = 0;
    /////找出以 row ，col 为圆心能画出的最大圆的半径
    for (int index = 0; index < row; index++)
    {
      if (colValues[index] != -1)
      {
        int yDiff = abs(row - index);
        int xDiff = abs(col - colValues[index]);
        int difference = xDiff * xDiff + yDiff * yDiff;
        if (0 == tempDiff)
        {
          tempDiff = difference;
        }
        else if (difference < tempDiff)
        {
          tempDiff = difference;
        }

        // printf("col is %d, row is %d, index is %d, colValues[index] is %d tempDiff is %d\n",col,row,index,colValues[index],tempDiff);
      }
    }

    ////找到最需要放柱子的地方
    if (tempDiff >= mDistance)
    {
      mDistance = tempDiff;
      targetCol = col;
    }
  }

  // printf("add one is %d, targetCol %d , row is %d\n", minRectWidth, targetCol, row);
  if (-1 != targetCol)
  {
    // printf("set col for row , row is %d, col is %d, mDistance is %d\n", row, targetCol, mDistance);

    colValues[row] = targetCol;
    int x = (row + targetCol + 1 - SH) / 2;
    int y = (row - targetCol - 1 + SH) / 2;

    screen.SetPixelValue(x, SH - 1 - y, 1);

    found = true;
    dfs(row + 1);

    screen.SetPixelValue(x, SH - 1 - y, 2);

    colValues[row] = -1;
  }

  if (!found)
  {
    dfs(row + 1);
  }
}

void dfsr(int row)
{

  if (0 == row)
  {
    dfs(nStart + 1);
    return;
  }

  bool found = false;

  int mDistance = MinDistance * MinDistance * Ratio;
  int targetCol = -1;

  for (int col = 0; col < nValue; col++)
  {

    /// x,y为screen中坐标
    if ((row + col + 1 - SH) % 2 != 0 || (row - col - 1 + SH) % 2 != 0)
    {
      ////这里有接近1/2的点不见了
      // printf("something is wrong pls check %d , %d\n",(row+col+1-SH),(row-col-1+SH));
      continue;
    }
    int x = (row + col + 1 - SH) / 2;
    int y = (row - col - 1 + SH) / 2;

    if (x < 0 || x >= SW || y < 0 || y >= SH)
    {
      continue;
    }

    if (checkXY(x, y))
    {
      continue;
    }

    int tempDiff = 0;
    /////////找出以 row ，col 为圆心能画出的最大圆的半径
    for (int index = nStart; index > row; index--)
    {
      if (colValues[index] != -1)
      {
        int yDiff = abs(row - index);
        int xDiff = abs(col - colValues[index]);
        int difference = xDiff * xDiff + yDiff * yDiff;
        if (0 == tempDiff)
        {
          tempDiff = difference;
        }
        else if (difference < tempDiff)
        {
          tempDiff = difference;
        }
      }
    }

    /// 在最需要的地方放置柱子
    if (tempDiff >= mDistance)
    {
      mDistance = tempDiff;
      targetCol = col;
    }
  }

  // printf("add one is %d, targetCol %d , row is %d\n", minRectWidth, targetCol, row);
  if (-1 != targetCol)
  {
    //  printf("set col for row , row is %d, col is %d, mDistance is %d\n", row, targetCol, mDistance);

    colValues[row] = targetCol;
    int x = (row + targetCol + 1 - SH) / 2;
    int y = (row - targetCol - 1 + SH) / 2;

    screen.SetPixelValue(x, SH - 1 - y, 1);

    found = true;
    dfsr(row - 1);

    screen.SetPixelValue(x, SH - 1 - y, 2);

    colValues[row] = -1;
  }

  if (!found)
  {
    dfsr(row - 1);
  }
}

void dfss(int row)
{

  int targetCol = -1;

  /// 尽量从中间开始
  for (int col = nValue / 2 - 2; col < nValue / 2 + 2; col++)
  {

    /// x,y为screen中坐标
    if ((row + col + 1 - SH) % 2 != 0 || (row - col - 1 + SH) % 2 != 0)
    {
      ////这里有接近1/2的点不见了
      // printf("something is wrong pls check %d , %d\n",(row+col+1-SH),(row-col-1+SH));
      continue;
    }

    int x = (row + col + 1 - SH) / 2;
    int y = (row - col - 1 + SH) / 2;

    if (x < 0 || x >= SW || y < 0 || y >= SH)
    {
      continue;
    }

    targetCol = col;
    break;
  }

  colValues[row] = targetCol;
  int x = (row + targetCol + 1 - SH) / 2;
  int y = (row - targetCol - 1 + SH) / 2;
  printf("first x is %d , dy is %d, targetCol %d\n", x, SH - 1 - y, targetCol);
  screen.SetPixelValue(x, SH - 1 - y, 1);

  dfsr(row - 1);

  screen.SetPixelValue(x, SH - 1 - y, 2);
}

int main()
{

  for (int x = 0; x < SW; x++)
  {
    for (int y = 0; y < SH; y++)
    {
      screen.SetPixelValue(x, y, 2);
    }
  }

  for (int index = 0; index < nValue; index++)
  {
    colValues[index] = -1;
  }

  printf("nvalue is %d \n", nValue);
  time_t timer0;
  timer0 = time(NULL);
  char *pctime = ctime(&timer0);
  printf("starts at \n%s\n", pctime);
  // dfss(nStart);
  int tempEdge = EdgeOffset;
  int initDiss = MinDistance;
  for (int diff = 0; diff < 10; diff++)
  {
    EdgeOffset = tempEdge + diff;
    int temp = initDiss;
    for (int offset = 0; offset < 35; offset++)
    {
      MinDistance = temp + offset;
      dfss(nStart);
    }
  }

  timer0 = time(NULL);
  pctime = ctime(&timer0);
  printf("\nends with %d results , at %s\n", results, pctime);
  return 0;
}
