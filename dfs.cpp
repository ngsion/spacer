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


#define nValue (SW * SH - PW * PH)


int shu[nValue];
int pie[nValue + nValue - 1];
int na[nValue + nValue - 1];

const int difference = 5;

Screen screen = Screen();


static int results = 0;
static bool flag = false;

void dfs(int row)
{

  int base = nValue/2;
  srand((unsigned)time(NULL));
  int offset = rand()%(base/2);
  int number = flag ? base + offset : base - offset;
  flag = !flag;
  bool normal = (number > nValue / 2) ? false : true;

  int col = normal ? number - 1 : number + 1;
  int target = normal ? nValue - 2 : 1;
 // for(int col = 0; col < nValue; col++)
  while (col != target)
  {
     normal ? ++col : --col;

    int pieIndex = row + col;
    int naIndex = nValue - 1 - row + col;

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

    /* if (x < 2 || x > nValue - 3 || y < 2 || y > nValue -3)
     {
       if(x == 0 && y == 0) continue;
       if(x == SW-1 && y == SH-1) continue;
       if (shu[col])
       {
         continue;
       }
     }
     else
    if (shu[col] || pie[pieIndex] || na[naIndex])
    {
      continue;
    }*/
    if (shu[col] && row - shu[col] < difference)
    {
      continue;
    }
    if (pie[pieIndex] && row - pie[pieIndex] < difference)
    {
      continue;
    }
   

    if (nValue - 1 == row)
    {

      // if ((row + col + 1 - SH) % 2 == 0 && (row - col - 1 + SH) % 2 == 0)
      {
        // if (x > 0 && x <= SW && y > 0 && y <= SH)
        {
          screen.SetPixelValue(x, SH - 1 - y, 1);
        }
      }

      /* for (int xpos = 0; xpos < cols; xpos++)
       {
         for (int ypos = 0; ypos < rows; ypos++)
         {

         }
       }*/

      for(int xpos = 0; xpos < SW; xpos++)
      {
        for(int ypos = 0; ypos < SH; ypos++)
        {
          if ( 1 == screen.A[xpos][ypos])
          {
                for(int xx = xpos+1,yy = ypos+1; xx < SW,yy < SH; xx++,yy++)
                {
                   screen.A[xx][yy] = 4;
                }
          }
        }
      }
      screen.PrintOut(results);
      printf("get one result %d\n", results);
      ++results;

      // if ((row + col + 1 - SH) % 2 == 0 && (row - col - 1 + SH) % 2 == 0)
      {
        //  if (x > 0 && x <= SW && y > 0 && y <= SH)
        {
          screen.SetPixelValue(x, SH - 1 - y, 2);
           for(int xpos = 0; xpos < SW; xpos++)
      {
        for(int ypos = 0; ypos < SH; ypos++)
        {
          if ( 1 == screen.A[xpos][ypos])
          {
                for(int xx = xpos+1,yy = ypos+1; xx < SW,yy < SH; xx++,yy++)
                {
                   screen.A[xx][yy] = 2;
                }
          }
        }
      }
        }
      }
    }
    else
    {
      /*if (x < 2 || x > nValue - 3 || y < 2 || y > nValue -3)
      {
          shu[col] = true;
      }
      else*/
      {
        shu[col] = row;
        pie[pieIndex] = row;
        na[naIndex] = row;
        // shu[col] = pie[pieIndex] = na[naIndex] = true;
      }

      // if ((row + col + 1 - SH) % 2 == 0 && (row - col - 1 + SH) % 2 == 0)
      {
        // if (x > 0 && x <= SW && y > 0 && y <= SH)
        {
          screen.SetPixelValue(x, SH - 1 - y, 1);
        }
      }

      // screen.SetPixelValue(x, SH-1-y, 1);
      //    printf("set  one result %d, %d\n",x,y);
      /*  int xpos = col;
        int ypos = row;
        while(ypos > 0 && xpos < cols)
        {
            --ypos;
            ++xpos;
            screen.SetPixelValue(xpos, ypos, 4);
        }*/

      dfs(row + 1);
      // screen.SetPixelValue(x, SH-1-y, 2);

      // if ((row + col + 1 - SH) % 2 == 0 && (row - col - 1 + SH) % 2 == 0)
      {
        // if (x > 0 && x <= SW && y > 0 && y <= SH)
        {
          screen.SetPixelValue(x, SH - 1 - y, 2);
        }
      }
      shu[col] = 0;
      pie[pieIndex] = 0;
      na[naIndex] = 0;
      // shu[col] = pie[pieIndex] = na[naIndex] = false;
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

  for (int index = 0; index < nValue; index++)
  {
    shu[index] = 0;
  }

  for (int index = 0; index < nValue + nValue - 1; index++)
  {
    pie[index] = 0;
    na[index] = 0;
  }

  printf("nvalue is %d \n", nValue);
  time_t timer0;
  timer0 = time(NULL);
  char *pctime = ctime(&timer0);
  printf("starts at \n%s\n", pctime);

  dfs(0);

  timer0 = time(NULL);
  pctime = ctime(&timer0);
  printf("\nends with %d results , at %s\n", results, pctime);
}
