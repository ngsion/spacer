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
#define Rectw 6
#define RectH 6
#define MaxCount 36 ///在 rectW x rectH 区域内，最多MaxCount个空点

int colValues[nValue]; /// 每行的colvalues值

Screen screen = Screen();

static int results = 0;


void dfs(int row)
{

  if (nValue - 1 == row)
  {
    /// 得到一个结果了
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
    printf("get one result %d\n", results);
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
  flag = !flag;
  bool found = false;
  int tagetValue = flag ? nValue - 1 : 1;
  int col =   flag ? 1 : nValue - 1;
  while ( col != tagetValue)
  {
     flag ? ++col : --col;
     

    int x = (row + col + 1 - SH) / 2;
    int y = (row - col - 1 + SH) / 2;

    /// x,y为screen中坐标
    if ((row + col + 1 - SH) % 2 != 0 || (row - col - 1 + SH) % 2 != 0)
    {
      ////这里有接近1/2的点不见了
      // printf("something is wrong pls check %d , %d\n",(row+col+1-SH),(row-col-1+SH));
      continue;
    }

    if (x < 0 || x >= SW || y < 0 || y >= SH)
    {
      continue;
    }

    ////将要放柱子的列
    int shouldAddColumn = -1;

    /// 超过一定距离就不放
    int xStart = floor(x - Rectw/2.0 > 0) ? floor(x - Rectw/2.0) : 0;
    int xStop = ceil(x + Rectw/2.0) > SW -1 ? SW -1 : ceil(x + Rectw/2.0);
    int yStart = floor(y - Rectw/2.0) > 0 ? floor(y - Rectw/2.0) : 0; 
    int yStop = ceil(y + Rectw/2.0) > SH -1 ? SH -1 : ceil(y + Rectw/2.0);
  //  printf("col is %d, x is %d, xStart is %d  , xStop is %d, y is %d, yStart is %d, yStop is %d \n",col,x, xStart,xStop,y,yStart,yStop);
    int count = 0;
    for (int index = xStart; index < xStop; index++)
    {
      for (int idx = yStart; idx < yStop; idx++)
      {
        if ( 1 != screen.A[index][SH - 1 - idx] ) 
        {
          ++count;  
        } 
      }
    }

    if ( count >= MaxCount)
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
