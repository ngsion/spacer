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
    if (PW-1 == column)
    {

        int num = ivec[index + 1];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];

        //   cout << " old value is 222 " << oldValue << endl;
        //  print_vetor(onePixel->pixelUpArray);

        if (INVALID_VALUE == oldValue)
        {
            ivec[index] = onePixel->pixelDownArray[0];
            return true;
        }
        else if (oldValue == onePixel->pixelDownArray.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < onePixel->pixelDownArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelDownArray[idx])
                {
                    ivec[index] = onePixel->pixelDownArray[idx + 1];
                    return true;
                }
            }
        }

        cout << " Set2 logic wrong " << index << endl;
        return false;
    }
    else if (0 == row)
    {
        int num = ivec[index + PH];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];

        // cout << " old value is 33333 " << oldValue <<  " num is "  << num<< endl;
        //  print_vetor(onePixel->pixelRightArray);

        if (INVALID_VALUE == oldValue)
        {
            ivec[index] = onePixel->pixelLeftArray[0];
            return true;
        }
        else if (oldValue == onePixel->pixelLeftArray.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < onePixel->pixelLeftArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelLeftArray[idx])
                {
                    ivec[index] = onePixel->pixelLeftArray[idx + 1];
                    return true;
                }
            }
        }
        cout << "Set2 logic wrong  2222" << index << endl;
        return false;
    }
    else
    {

        int num = ivec[index + 1];
        int num2 = ivec[index + PH];
        vector<int> array = pixelHelper.GetFromDownLeftMap(num, num2);
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
    if (0 == column)
    {

        int num = ivec[index - 1];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];

        //   cout << " old value is 222 " << oldValue << endl;
        //  print_vetor(onePixel->pixelUpArray);

        if (INVALID_VALUE == oldValue)
        {
            ivec[index] = onePixel->pixelUpArray[0];
            return true;
        }
        else if (oldValue == onePixel->pixelUpArray.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < onePixel->pixelUpArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelUpArray[idx])
                {
                    ivec[index] = onePixel->pixelUpArray[idx + 1];
                    return true;
                }
            }
        }
        cout << " Set logic wrong " << index << endl;
        return false;
    }
    else if (0 == row)
    {
        int num = ivec[index - PH];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];

        // cout << " old value is 33333 " << oldValue <<  " num is "  << num<< endl;
        //  print_vetor(onePixel->pixelRightArray);

        if (INVALID_VALUE == oldValue)
        {
            ivec[index] = onePixel->pixelRightArray[0];
            return true;
        }
        else if (oldValue == onePixel->pixelRightArray.back())
        {
            return false;
        }
        else
        {
            for (int idx = 0; idx < onePixel->pixelRightArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelRightArray[idx])
                {
                    ivec[index] = onePixel->pixelRightArray[idx + 1];
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
        int num2 = ivec[index - PH];
        vector<int> array = pixelHelper.GetFromUpRightMap(num, num2);
        int oldValue = ivec[index];

        //   cout << " old value is f454 " << oldValue <<  " num is "  << num<<  " num2 " << num2 <<endl;
        //  print_vetor(array);

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
        cout << " Set logic wrong 3333" << index << endl;
        return false;
    }
    cout << " Set logic wrong 4444" << index << endl;
    return false;
}

int BackTraceFrom(int current)
{
    if (1 >= current)
    {

        return INVALID_VALUE;
    }
    ivec[current] = INVALID_VALUE;

    int index = current - 1;

    int row = index % PH;
    int column = index / PH;
    if (0 == column)
    {
        int num = ivec[index - 1];
        int oldValue = ivec[index];
        ivec[index] = INVALID_VALUE;
        Pixel *onePixel = pixelHelper.pixelArray[num];

        //    cout << " old value is 222 " << oldValue << "  index: "<< index << endl;
        //  print_vetor(onePixel->pixelUpArray);

        if (oldValue == onePixel->pixelUpArray.back())
        {
            return BackTraceFrom(index - 1);
        }
        else
        {
            for (int idx = 0; idx < onePixel->pixelUpArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelUpArray[idx])
                {
                    ivec[index] = onePixel->pixelUpArray[idx + 1];
                    return index;
                }
            }
        }

        cout << "logic encounter errors BackTraceFrom" << endl;
        return INVALID_VALUE;
        //  cout <<  num  << " abbbbb "<< ivec[index] << endl;
    }
    else if (0 == row)
    {
        int num = ivec[index - PH];
        int oldValue = ivec[index];
        ivec[index] = INVALID_VALUE;
        Pixel *onePixel = pixelHelper.pixelArray[num];

        //   cout << " old value is 33333 " << oldValue <<  " num is "  << num<< endl;
        //  print_vetor(onePixel->pixelRightArray);

        if (oldValue == onePixel->pixelRightArray.back())
        {
            return BackTraceFrom(index - 1);
        }
        else
        {

            for (int idx = 0; idx < onePixel->pixelRightArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelRightArray[idx])
                {
                    ivec[index] = onePixel->pixelRightArray[idx + 1];
                    return index;
                }
            }
        }
        cout << "logic encounter errors   22222" << endl;
        return INVALID_VALUE;
        //  cout << num  << "  cdddddd "<< ivec[index] <<endl;
    }
    else
    {
        int num = ivec[index - 1];
        int num2 = ivec[index - PH];
        vector<int> array = pixelHelper.GetFromUpRightMap(num, num2);
        int oldValue = ivec[index];
        ivec[index] = INVALID_VALUE;

        //    cout << " old value is f454 " << oldValue <<  " num is "  << num<<  " num2 " << num2 <<endl;
        // print_vetor(array);

        if (0 == array.size())
        {
            cout << "logic encounter errors  33333"
                 << " index " << index << endl;
            return INVALID_VALUE;
        }

        if (oldValue == array.back())
        {
            return BackTraceFrom(index - 1);
        }
        else
        {

            for (int idx = 0; idx < array.size() - 1; idx++)
            {
                if (oldValue == array[idx])
                {
                    ivec[index] = array[idx + 1];
                    return index;
                }
            }
        }
    }

    cout << "logic encounter errors  4444" << endl;
    return INVALID_VALUE;
}


int BackTraceFrom2(int current)
{
    if (PW*PH-2 <= current)
    {
        return INVALID_VALUE;
    }
    ivec[current] = INVALID_VALUE;

    int index = current + 1;

    int row = index % PH;
    int column = index / PH;
    if (PW-1 == column)
    {
        int num = ivec[index + 1];
        int oldValue = ivec[index];
        ivec[index] = INVALID_VALUE;
        Pixel *onePixel = pixelHelper.pixelArray[num];

        //    cout << " old value is 222 " << oldValue << "  index: "<< index << endl;
        //  print_vetor(onePixel->pixelUpArray);

        if (oldValue == onePixel->pixelDownArray.back())
        {
            return BackTraceFrom2(index + 1);
        }
        else
        {
            for (int idx = 0; idx < onePixel->pixelDownArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelDownArray[idx])
                {
                    ivec[index] = onePixel->pixelDownArray[idx + 1];
                    return index;
                }
            }
        }

        cout << "logic22 encounter errors" << endl;
        return INVALID_VALUE;
        //  cout <<  num  << " abbbbb "<< ivec[index] << endl;
    }
    else if (0 == row)
    {
        int num = ivec[index + PH];
        int oldValue = ivec[index];
        ivec[index] = INVALID_VALUE;
        Pixel *onePixel = pixelHelper.pixelArray[num];

        //   cout << " old value is 33333 " << oldValue <<  " num is "  << num<< endl;
        //  print_vetor(onePixel->pixelRightArray);

        if (oldValue == onePixel->pixelLeftArray.back())
        {
            return BackTraceFrom2(index + 1);
        }
        else
        {

            for (int idx = 0; idx < onePixel->pixelLeftArray.size() - 1; idx++)
            {
                if (oldValue == onePixel->pixelLeftArray[idx])
                {
                    ivec[index] = onePixel->pixelLeftArray[idx + 1];
                    return index;
                }
            }
        }
        cout << "logic22 encounter errors   22222" << endl;
        return INVALID_VALUE;
        //  cout << num  << "  cdddddd "<< ivec[index] <<endl;
    }
    else
    {
        int num = ivec[index + 1];
        int num2 = ivec[index + PH];
        vector<int> array = pixelHelper.GetFromDownLeftMap(num, num2);
        int oldValue = ivec[index];
        ivec[index] = INVALID_VALUE;

        //    cout << " old value is f454 " << oldValue <<  " num is "  << num<<  " num2 " << num2 <<endl;
        // print_vetor(array);

        if (0 == array.size())
        {
            cout << "logic2 encounter errors  33333" << endl;
            return INVALID_VALUE;
        }

        if (oldValue == array.back())
        {
            return BackTraceFrom2(index + 1);
        }
        else
        {

            for (int idx = 0; idx < array.size() - 1; idx++)
            {
                if (oldValue == array[idx])
                {
                    ivec[index] = array[idx + 1];
                    return index;
                }
            }
        }
    }

    cout << "logic22 encounter errors  4444" << endl;
    return INVALID_VALUE;
}

int main()
{

    pixelHelper.GetAllPossiblePixels();

    pixelHelper.SetMapWithoutValue();
   pixelHelper.ClearPixels();

   pixelHelper.PrintOutAllPixels();
   pixelHelper.SetMapWithoutValue();

    pixelHelper.SetPixelVectors();

    cout << "calculate  " << PW << " X " << PH << endl;


   int len = pixelHelper.pixelArray.size();


/*
    int maxIndex = PW * PH;
     int count = 0;
    for (int start = 0; start < len; start++)
    {

        Pixel *startPixel = pixelHelper.pixelArray[start];
        if (startPixel->value != 1)
        {
            continue;
        }
        for (int index = 0; index < maxIndex; index++)
        {
            ivec[index] = INVALID_VALUE;
        }

        char filename[64] = {0};

      //  sprintf(filename, "result_%dX%d_start_%d.txt", PW, PH, start);
        //  if (isFileExists_fopen(filename))
        {
            //   continue;
        }

        cout << "start with " << start << endl;

        //  int start = 2;

        ivec[maxIndex-1] = start;
        bool result = true;


          again:
          int index = maxIndex-2;

         newone:
        while (index >= 0)
        {

           // cout << "good index " << index << endl;
            if (Set2(index))
            {
                --index;
                if (index == -1)
                {
                    cout << "good finish" << endl;
                    break;
                }
                else
                {
                 //   cout << "good index set true" << index-1 << endl;
                    continue;
                }
            }
            //  cout << "good index set false " << index << endl;
            int newindex = BackTraceFrom2(index);
            if (INVALID_VALUE == newindex)
            {
                 goto again;
               //  cout << "good BackTraceFrom INVALID_VALUE" << index << endl;
                result = false;
                break;
            }
           //   cout << "good BackTraceFrom newstart" << newindex << endl;
            index = newindex-1;
        }



        if (result)
        {


            cout << "-------------------------"<< endl;
            for (int i = 0; i < ivec.size(); i++)
            {
                  cout << ivec[i] << " ";
            }
            cout << " ------------------------------------" << endl;


            Screen screen = Screen();

            for (int i = 0; i < maxIndex; i++)
            {
                int row = i % PH;
                int column = i / PH;
                int num = ivec[i];
                Pixel *onePixel = pixelHelper.pixelArray[num];
                screen.SetPixel(column, row, onePixel);
            }

            screen.PrintOut(count++);
            index = 1;
            goto newone;
        }
    }
     */


      int maxIndex = PW * PH;
      int count = 0;
      for (int start = 0; start < len; start++)
     {

        Pixel *startPixel = pixelHelper.pixelArray[start];
        if (startPixel->value != 1)
        {
            continue;
        }
        for (int index = 0; index < maxIndex; index++)
        {
            ivec[index] = INVALID_VALUE;
        }

        char filename[64] = {0};

      //  sprintf(filename, "result_%dX%d_start_%d.txt", PW, PH, start);
        //  if (isFileExists_fopen(filename))
        {
            //   continue;
        }

        cout << "start with " << start << endl;

        //  int start = 2;

        ivec[0] = start;
        bool result = true;

           again:
          int index = 1;

        newone:
        while (index < maxIndex)
        {

           // cout << "good index " << index << endl;
            if (Set(index))
            {
                ++index;
                if (index == maxIndex)
                {
                    cout << "good finish" << endl;
                    break;
                }
                else
                {
                 //   cout << "good index set true" << index-1 << endl;
                    continue;
                }
            }
            //  cout << "good index set false " << index << endl;
            int newindex = BackTraceFrom(index);
            if (INVALID_VALUE == newindex)
            {
                goto again;
               //  cout << "good BackTraceFrom INVALID_VALUE" << index << endl;
                result = false;
                break;
            }
           //   cout << "good BackTraceFrom newstart" << newindex << endl;
            index = newindex+1;
        }



        if (result)
        {


            cout << "-------------------------"<< endl;
            for (int i = 0; i < ivec.size(); i++)
            {
                  cout << ivec[i] << " ";
            }
            cout << " ------------------------------------" << endl;


            Screen screen = Screen();

            for (int i = 0; i < maxIndex; i++)
            {
                int row = i % PH;
                int column = i / PH;
                int num = ivec[i];
                Pixel *onePixel = pixelHelper.pixelArray[num];
                screen.SetPixel(column, row, onePixel);
            }

            screen.PrintOut(count++);
             index = maxIndex-2;
            goto newone;
        }
    }

    cout << "Hello World Finished! "
         << "   " << PW * PH << "  " << endl;
         
         return 0;
}
