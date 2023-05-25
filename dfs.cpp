#include <iostream.h>

#include "Screen.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include "iterator.h"
#include <stdio.h>
#include <string>
#include "Utility.h"
#include <time.h>

static bool flag = false;

#define nValue (SW * SH - PW * PH)
#define nStart (nValue / 2)

////算法1： 在某条对角线上，每一点都计算，以该点为圆心的，圆内没有柱子的半径， 然后去最大半径的那个点来放柱子
int MinDistance = 10;

int colValues[nValue]; /// 每行的colvalues值

Screen screen = Screen();

static int results = 0;

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

    int maxDistance = 0;
    for (int a = 0; a < nValue; a++)
    {
      int dis = 0;
      for (int b = 0; b < nValue; b++)
      {
        if (a != b)
        {
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
      }
      if (0 == maxDistance)
          {
            maxDistance = dis;
          }
          else if (maxDistance < dis)
          {
            maxDistance = dis;
          }
    }

    screen.PrintOut(maxDistance);
    printf("get one result %d , pole count %d, ratio is %f\n", results, screen.GetPoleCount(), screen.GetPoleRatio());
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

  bool found = false;

  /// 方法1

  int mDistance = MinDistance * MinDistance;
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

    if (x <= MinDistance || y <= MinDistance || (SW - x) <= MinDistance || (SH - y) <= MinDistance)
    {
      continue;
    }

    int tempDiff = 0;
    /////找出该行中可以画出最大的正方形，要求没有柱子坐落在正方形内
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

  int mDistance = MinDistance * MinDistance;
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

    if (x <= MinDistance || y <= MinDistance || (SW - x) <= MinDistance || (SH - y) <= MinDistance)
    {
      continue;
    }

    int tempDiff = 0;
    /////找出该行中可以画出最大的正方形，要求没有柱子坐落在正方形内
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

void main()
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
  dfss(nStart);
  // int temp = MinRectLength;
  // for (int offset = 0; offset < 30; offset++)
  // {
  //   MinRectLength = temp + offset;
  //   dfss(nStart);
  // }

  timer0 = time(NULL);
  pctime = ctime(&timer0);
  printf("\nends with %d results , at %s\n", results, pctime);
}
