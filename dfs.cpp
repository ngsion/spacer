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

////算法1： 在某条对角线上，在大于 MinRectWidth 的边长，取最大的那个点放置柱子
#define MinRectLength 3



#define Rectw 44
#define RectH 42
#define MaxCount (Rectw * RectH - 1) /// 在 rectW x rectH 区域内，最多MaxCount个空点

int colValues[nValue]; /// 每行的colvalues值

Screen screen = Screen();

static int results = 0;

void dfs(int row)
{

  if (nValue - 1 == row)
  {
    /// 得到一个结果了, 打印出来
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
    screen.PrintOut(results);
    printf("get one result %d , pole count %d\n", results, screen.GetPoleCount());
    ++results;

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

  /// 前面几行需要特殊处理
  if (row >= 0)
  {
    int minRectWidth = MinRectLength;
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
        
      int tempMinRectWidth = -1;
      /////找出该行中可以画出最大的正方形，要求没有柱子坐落在正方形内
      for (int index = 0; index < row; index++)
      {
        if (colValues[index] != -1)
        {
          int yDiff = row - index;
          int xDiff = abs(col - colValues[index]);
          int width = max(xDiff, yDiff);
          if (-1 == tempMinRectWidth)
          {
            tempMinRectWidth = width;
          }
          else if (width < tempMinRectWidth)
          {
            tempMinRectWidth = width;
          }
        }
      }
      if (-1 == tempMinRectWidth)
      {
        tempMinRectWidth = MinRectLength;
      }

      if (tempMinRectWidth >= minRectWidth)
      {
        minRectWidth = tempMinRectWidth;
        targetCol = col;
      }
    }

    

   // printf("add one is %d, targetCol %d , row is %d\n", minRectWidth, targetCol, row);
    if (-1 != targetCol)
    {

      colValues[row] = targetCol;
      int x = (row + targetCol + 1 - SH) / 2;
      int y = (row - targetCol - 1 + SH) / 2;

      screen.SetPixelValue(x, SH - 1 - y, 1);

      found = true;
      dfs(row + 1);

      screen.SetPixelValue(x, SH - 1 - y, 2);

      colValues[row] = -1;
    }
  }
  else
  {

    flag = !flag;

    int tagetValue = flag ? nValue - 1 : 1;
    int col = flag ? 1 : nValue - 1;
    while (col != tagetValue)
    {
      flag ? ++col : --col;
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

      ////将要放柱子的列
      int shouldAddColumn = -1;

      /// 超过一定距离就不放
      int xStop = x + Rectw / 2 > SW - 1 ? SW - 1 : x + Rectw / 2;
      int xStart = xStop - Rectw + 1 > 0 ? xStop - Rectw + 1 : 0;
      int yStop = y + RectH / 2 > SH - 1 ? SH - 1 : y + RectH / 2;
      int yStart = yStop - RectH + 1 > 0 ? yStop - RectH + 1 : 0;

      //  printf("col is %d, x is %d, xStart is %d  , xStop is %d, y is %d, yStart is %d, yStop is %d \n",col,x, xStart,xStop,y,yStart,yStop);
      int count = 0;
      for (int index = xStart; index <= xStop; index++)
      {
        for (int idx = yStart; idx <= yStop; idx++)
        {
          if (1 != screen.A[index][SH - 1 - idx])
          {
            ++count;
          }
          else
          {
            break;
          }
        }
      }

      if (count > MaxCount)
      {
        shouldAddColumn = col;
      }

      if (-1 != shouldAddColumn)
      {
        // printf("add one is %d \n", shouldAddColumn);
        colValues[row] = shouldAddColumn;

        screen.SetPixelValue(x, SH - 1 - y, 1);

        found = true;
        dfs(row + 1);

        screen.SetPixelValue(x, SH - 1 - y, 2);

        colValues[row] = -1;
      }
    }
  }

  if (!found)
  {
    dfs(row + 1);
  }
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

  dfs(1);

  timer0 = time(NULL);
  pctime = ctime(&timer0);
  printf("\nends with %d results , at %s\n", results, pctime);
}
