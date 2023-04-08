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

#define nVlaue (SW * SH - PW * PH)

bool shu[nVlaue];
bool pie[nVlaue + nVlaue - 1];
bool na[nVlaue + nVlaue - 1];
Screen screen = Screen();

static int results = 0;


void dfs(int row)
{

  for (int col = 0; col < nVlaue; col++)
  {
    int pieIndex = row + col;
    int naIndex = nVlaue - 1 - row + col;

    

    /// x,y为screen中坐标
    if ((row + col + 1 - SH) % 2 != 0 || (row - col - 1 + SH) % 2 != 0)
    {
      // printf("something is wrong pls check %d , %d\n",(row+col+1-SH),(row-col-1+SH));
      continue;
    }
    int x = (row + col + 1 - SH) / 2;
    int y = (row - col - 1 + SH) / 2;
    if (x < 0 || x >= SW || y < 0 || y >= SH)
    {
      continue;
    }
   
    if (x < 2 || x > nVlaue - 3 || y < 2 || y > nVlaue -3)
    {
      if(x == 0 && y == 0) continue;
      if(x == SW-1 && y == SH-1) continue;
      if (shu[col])
      {
        continue;
      }
    }
    else if (shu[col] || pie[pieIndex] || na[naIndex])
    {
      continue;
    }


    if (nVlaue - 1 == row)
    {

       screen.SetPixelValue(x, SH-1-y, 1);

      /* for (int xpos = 0; xpos < cols; xpos++)
       {
         for (int ypos = 0; ypos < rows; ypos++)
         {

         }
       }*/

      screen.PrintOut(results);
      printf("get one result \n");
      ++results;

       screen.SetPixelValue(x, SH-1-y, 2);
    }
    else
    {
         if (x < 2 || x > nVlaue - 3 || y < 2 || y > nVlaue -3)
         {
             shu[col] = true;
         }
         else
         {
             shu[col] = pie[pieIndex] = na[naIndex] = true;
         }

        screen.SetPixelValue(x, SH-1-y, 1);
           printf("set  one result %d, %d\n",x,y);
      /*  int xpos = col;
        int ypos = row;
        while(ypos > 0 && xpos < cols)
        {
            --ypos;
            ++xpos;
            screen.SetPixelValue(xpos, ypos, 4);
        }*/

      dfs(row + 1);
       screen.SetPixelValue(x, SH-1-y, 2);

      shu[col] = pie[pieIndex] = na[naIndex] = false;
    }
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

  for (int index = 0; index < nVlaue; index++)
  {
    shu[index] = false;
  }

  for (int index = 0; index < nVlaue + nVlaue - 1; index++)
  {
    pie[index] = false;
    na[index] = false;
  }

  time_t timer0;
  timer0 = time(NULL);
  char *pctime = ctime(&timer0);
  printf("starts at \n%s\n", pctime);

  dfs(0);

  timer0 = time(NULL);
  pctime = ctime(&timer0);
  printf("\nends with %d results , at \n%s\n", results, pctime);
}
