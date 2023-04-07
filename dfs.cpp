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



const int cols = SW;
const int rows = SH;
bool shu[cols];
bool pie[cols+rows-1];
bool na[cols+rows-1];
Screen screen = Screen();

static int results = 0;

void dfs(int row)
{


          

    for (int col = 0; col < cols; col++)
    {
          int pieIndex = row + col;
          int naIndex = rows - 1 - row + col;
          if (shu[col] || pie[pieIndex] || na[naIndex])
          {
             continue;
          }

             if  (rows - 1 == row)
          {

               screen.SetPixelValue(row, col, 1);
              screen.PrintOut(results);
               printf("get one result \n");

             ++results;
          }
          else
          {
            shu[col] = pie[pieIndex] = na[naIndex] = true;
            screen.SetPixelValue(row, col, 1);
            

          
          /*  int xpos = col;
            int ypos = row;
            while(ypos > 0 && xpos < cols)
            {
                --ypos;
                ++xpos;
                screen.SetPixelValue(xpos, ypos, 4);
            }*/
            dfs(row+1);
            screen.SetPixelValue(row, col, 2);
            /* xpos = col;
             ypos = row;
            while(ypos > 0 && xpos < cols)
            {
                --ypos;
                ++xpos;
                screen.SetPixelValue(xpos, ypos, 2);
            } */
            shu[col] = pie[pieIndex] = na[naIndex] = false;
          }
    }
    

}


void main()
{
   for(int index = 0; index < cols; index++)
   {
       shu[index] = false;
       for(int pos = 0; pos < rows; pos++)
       {
         screen.SetPixelValue(pos,index,2);
       }
   }
   for(int index = 0; index < cols+rows-1; index++)
   {
       pie[index] = false;
       na[index] = false;
   }
   
   time_t timer0;
   timer0 = time(NULL);
   char * pctime = ctime(&timer0);
   printf("starts at \n%s\n",pctime);
   
   dfs(0);
   

   timer0 = time(NULL);
   pctime = ctime(&timer0);
   printf("\nends at %d \n%s\n",results,pctime);
   
}
