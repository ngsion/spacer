#include <iostream>
#include "PixelHelper.h"
#include "Screen.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <iterator>
#include <stdio.h>
#include <string>
#include "Utility.h"

#define INVALID_VALUE -1

PixelHelper pixelHelper = PixelHelper();
vector<int> ivec(PW *PH);


bool Set2(int index)
{

    int row = index % PH;
    int column = index / PH;

    if (0 == row)
    {
        int num = ivec[index - 1];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];

        vector<int> array = onePixel->pixelRightArrayNoValue;

        // cout << " old value is 33333 " << oldValue <<  " num is "  << num<< endl;
        //  print_vetor(onePixel->pixelRightArray);

        if(array.size() == 0 )
        {
            return false;
        }

           if (INVALID_VALUE == oldValue)
            {
               ivec[index] = array[0];
               return true;
            }
            else if (oldValue == array.back())
            {
               return false;
            }
            else
            {
              for (int idx = 0; idx < array.size() - 1; idx++)
              {
                if (oldValue == array[idx])
                {
                    ivec[index] = array[idx + 1];
                    return true;
                }
              }
           }


        cout << "Set2 logic wrong  2222" << index << endl;
        return false;
    }
    else
    {

        int num = ivec[index - 1];
        int num2 = ivec[index - 2*row -1];

        vector<int> array =  pixelHelper.GetFromDownRightMapNoValue(num, num2) ;
          if (column % 11 == 0 && row % 11 == 0)
        {
              array =  pixelHelper.GetFromDownRightMapWithValue(num, num2) ;
        }

     //   vector<int> array = (index == startPointLeft) ? pixelHelper.GetFromDownLeftMap(num, num2) :  pixelHelper.GetFromDownLeftMapNoValue(num, num2) ;
        int oldValue = ivec[index];

        //   cout << " old value is f454 " << oldValue <<  " num is "  << num<<  " num2 " << num2 <<endl;
        //  print_vetor(array);

        if (0 == array.size())
        {
            return false;
        }

        if (INVALID_VALUE == oldValue)
        {
            /*    if ( flag )
               {
                   for (int idx = 0; idx < array.size(); idx++)
                  {
                   int number = array[idx];
                   if (1 == pixelHelper.pixelArray[number].value)
                   {
                       ivec[index] = number;
                       return true;
                    }
                  }
                  return false;
               }  */

            ivec[index] = array[0];
            return true;
        }
        else if (oldValue == array.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < array.size() - 1; idx++)
            {
                if (oldValue == array[idx])
                {

                    ivec[index] = array[idx + 1];
                    return true;
                }
            }
        }

        cout << " Set2 logic wrong 3333" << index << endl;
        return false;
    }
    cout << " Set2 logic wrong 4444" << index << endl;
    return false;
}

bool Set(int index)
{

    int row = index % PH;
    int column = index / PH;

    if (column % 2 == 1)
    {
        return Set2(index);
    }


    if (0 == column || row == 0)
    {
        int num = ivec[index - 1];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];
        
        vector<int> array = onePixel->pixelRightArrayNoValue;
        if( 0 == column )    array = onePixel->pixelUpArrayNoValue;
        
         if(array.size() == 0)
        {
            return false;
        }

        // cout << " old value is 33333 " << oldValue <<  " num is "  << num<< endl;
        //  print_vetor(onePixel->pixelRightArray);

        if (INVALID_VALUE == oldValue)
        {
            ivec[index] = array[0];
            return true;
        }
        else if (oldValue == array.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < array.size() - 1; idx++)
            {
                if (oldValue == array[idx])
                {
                    ivec[index] = array[idx + 1];
                    return true;
                }
            }
        }
        cout << " Set logic wrong  2222" << index << endl;
        return false;
    }
    else
    {

        int num = ivec[index - 1];
        int num2 = ivec[index - 2 * row - 1];

        vector<int> array =  pixelHelper.GetFromUpRightMapNoValue(num, num2) ;
         if (column % 11 == 0 && row % 11 == 0)
        {
              array =  pixelHelper.GetFromUpRightMapWithValue(num, num2) ;
        }



        //  vector<int> array =  pixelHelper.GetFromUpRightMap(num, num2) ;

        int oldValue = ivec[index];

      //  if( 265 == index)
        {
       //   cout << " old value is f454 " << oldValue <<  " num is "  << num<<  " num2 " << num2 <<endl;
      //   print_vetor(array);
        }

        if (0 == array.size())
        {
            return false;
        }

        if (INVALID_VALUE == oldValue)
        {
            ivec[index] = array[0];
            return true;
        }
        else if (oldValue == array.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < array.size() - 1; idx++)
            {
                if (oldValue == array[idx])
                {
                    ivec[index] = array[idx + 1];
                    return true;
                }
            }
        }
        cout << " Set logic wrong 3333 " << index << endl;
        return false;
    }
    cout << " Set logic wrong 4444 " << index << endl;
    return false;
}

int main()
{



    pixelHelper.GetAllPossiblePixels();
    pixelHelper.PrintOutAllPixels();
   // pixelHelper.SetMapWithoutValue();
     //pixelHelper.ClearPixels();


    pixelHelper.SetMap();
    pixelHelper.SetPixelVectors();

    cout << "calculate  " << PW << " X " << PH << endl;
    // pixelHelper.CalculateRows();

    // pixelHelper.CalculateColumns();

    int len = pixelHelper.pixelArray.size();

    int maxIndex = PW * PH;
    int start = 0;


    bool result = true;




    for ( start = 0; start < len; start++)
    {
        Pixel *startPixel = pixelHelper.pixelArray[start];
     //  cout << "restart with " <<startPixel->value << "  " << startPixel->pixelUpArray.size() << startPixel->pixelDownArray.size() << startPixel->pixelLeftArray.size() << startPixel->pixelRightArray.size() << endl;
        if (startPixel->value == 0 && startPixel->pixelUpArray.size() > 0 && startPixel->pixelRightArray.size() > 0)
        {
          //  cout << "restart with " <<  start << endl;

        }
        else
        {
           continue;
        }



        cout << "startPixel upsize " << startPixel->pixelUpArray.size() << "   right size " << startPixel->pixelRightArray.size() << endl;
        //  print_vetor(startPixel->pixelDownArray);
        char filename[64] = {0};

        sprintf(filename, "result_%dX%d_start_%d.txt", PW, PH, start);
        //  if (isFileExists_fopen(filename))
        {
            //   continue;
        }

        cout << "start with " << start << endl;

        //  int start = 2;
         for (int idx = 0; idx < maxIndex; idx++)
        {
            ivec[idx] = INVALID_VALUE;
        }
         int index = 0;
        ivec[index] = start;
         ++index;



          // cout << "start with111111 " << start << "  index " << index << " startcolumn " << startcolumn << "  index/PH " << index / PH << endl;


        while (index < maxIndex)
        {

            //   cout << "good index " << index << endl;
            if (Set(index))
            {
                ++index;
                continue;
            }
            else
            {
                ivec[index] = INVALID_VALUE;
                --index;
                 if (index <= 1)
                {
                     result = false;
                    //  cout << "good finish" << endl;
                      cout << "SetColumn back  to restart , error"  << endl;
                     break;


                }
                else
                {
                    // cout << "good index set true" << index-1 << endl;
                    continue;
                }
            }
            //  cout << "good index set false " << index << endl;
        }




        if (result)
        {


         /*   cout << "-------------------------"
                 << endl;
            for (int i = 0; i < ivec.size(); i++)
            {
               //  cout << ivec[i] << " ";
            }
            cout << " ------------------------------------" << endl; */

            Screen screen = Screen();


            for (int i = 0; i < maxIndex; i++)
            {
                int row = i % PH;
                int column = i / PH;
                ///������
                if (column % 2 == 1)
                {
                    row = PH - row;
                }
                int num = ivec[i];
                Pixel *onePixel = pixelHelper.pixelArray[num];
                screen.SetPixel(column, row, onePixel);
            }

          //   if(screen.SameColumns())
             {
                   cout << "good get one" << endl;
                  screen.PrintOut(start);
             }

        }
    }

    cout << "Hello World Finished! " << endl;
    return 0;
}

