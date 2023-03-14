#include <iostream.h>
#include "PixelHelper.h"
#include "Screen.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include "iterator.h"
#include <stdio.h>
#include <string>
#include "Utility.h"

#define INVALID_VALUE -1

PixelHelper pixelHelper = PixelHelper();
vector<int> ivec(PW *PH);
 const int startPoint = PW*((PH+1)/2-1)+PH/2;
 const int startPointLeftUp = startPoint - PH + 1;
  const int startPointLeft = startPoint - PH;
  const int startPointLeftDown = startPoint - PH - 1;
    const int startPointRightUp = startPoint + PH + 1;
  const int startPointRight = startPoint + PH;
   const int startPointRightDown = startPoint + PH - 1;
  const int startPointUp = startPoint + 1;
  const int startPointDown = startPoint - 1;
  
bool Set2(int index)
{

    int row = index % PH;
    int column = index / PH;

    if (PH-1 == row)
    {
        int num = ivec[index + PH];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];

        vector<int> array = onePixel->pixelLeftArrayNoValue;
        
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

        int num = ivec[index + 1];
        int num2 = ivec[index + PH];
         Pixel *startPixel = pixelHelper.pixelArray[ivec[startPoint]];
        vector<int> array =  pixelHelper.GetFromDownLeftMapNoValue(num, num2) ;
         if (index==startPointLeftUp && startPixel->up == 1)
        {
              array =  pixelHelper.GetFromDownLeftMap(num, num2) ;
        }
        if (index==startPointLeft && (startPixel->up == 1 || startPixel->origin == 1 ))
        {
              array =  pixelHelper.GetFromDownLeftMap(num, num2) ;
        }
         if (index==startPointLeftDown && startPixel->origin == 1)
        {
              array =  pixelHelper.GetFromDownLeftMap(num, num2) ;
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

bool SetColumn(int index)
{

    int num = ivec[index - 1];
    int oldValue = ivec[index];
    Pixel *onePixel = pixelHelper.pixelArray[num];

     vector<int> array = onePixel->pixelUpArrayNoValue;
     if (index==startPointUp)
     {
           Pixel *startPixel = pixelHelper.pixelArray[ivec[startPoint]];
           if (startPixel->up == 1 || startPixel->upright == 1)
           {
               array = onePixel->pixelUpArray;
           }
     }
     
     //  cout << " old value is index " <<index << "   "<< oldValue << endl;
     // print_vetor(onePixel->pixelUpArray);

     if(array.size() == 0)
        {
            return false;
        }
        
        
    if (INVALID_VALUE == oldValue)
    {

        int targeNum = array[0];
      /*  int max = 0;
        for (int m = 0; m < onePixel->pixelUpArray.size(); m++)
        {

            int number = onePixel->pixelUpArray[m];
            Pixel *pixel = pixelHelper.pixelArray[number];

            int leftsize = pixel->pixelLeftArray.size();
            int rightsize = pixel->pixelRightArray.size();

            int temp = leftsize + rightsize;
            if (temp > max)
            {
                max = temp;
                targeNum = number;
            }
        } */
        ivec[index] = targeNum;
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

                // ivec[index] = onePixel->pixelUpArray[idx+1];
                int targeNum = array[idx + 1];
              /*  int max = 0;
                for (int m = idx + 1; m < onePixel->pixelUpArray.size(); m++)
                {

                    int number = onePixel->pixelUpArray[m];
                    Pixel *pixel = pixelHelper.pixelArray[number];

                    int leftsize = pixel->pixelLeftArray.size();
                    int rightsize = pixel->pixelRightArray.size();

                    int temp = leftsize + rightsize;
                    if (temp > max)
                    {
                        max = temp;
                        targeNum = number;
                    }
                } */
                ivec[index] = targeNum;
                return true;
            }
        }
    }
    cout << " SetColumn logic wrong " << index << endl;
    return false;
}

bool SetColumn2(int index)
{

    int num = ivec[index + 1];
    int oldValue = ivec[index];
    Pixel *onePixel = pixelHelper.pixelArray[num];


     vector<int> array = onePixel->pixelDownArrayNoValue;
     if (index==startPointDown)
     {
           Pixel *startPixel = pixelHelper.pixelArray[ivec[startPoint]];
           if (startPixel->origin == 1 || startPixel->right == 1)
           {
               array = onePixel->pixelDownArray;
           }
     }
     
     
     //    cout << " old value is 222 " << oldValue  << " num is " << num << " index is " << index << endl;
    //  print_vetor(onePixel->pixelDownArray);

     if(array.size() == 0)
        {
            return false;
        }
        
    if (INVALID_VALUE == oldValue)
    {
        //  ivec[index] = onePixel->pixelDownArray[0];
        int targeNum = array[0];
     /*   int max = 0;
        for (int m = 0; m < onePixel->pixelDownArray.size(); m++)
        {

            int number = onePixel->pixelDownArray[m];
            Pixel *pixel = pixelHelper.pixelArray[number];

            int leftsize = pixel->pixelLeftArray.size();
            int rightsize = pixel->pixelRightArray.size();

            int temp = leftsize + rightsize;
            if (temp > max)
            {
                max = temp;
                targeNum = number;
            }
        }    */
        ivec[index] = targeNum;

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
                //   ivec[index] = onePixel->pixelDownArray[idx+1];
                int targeNum = array[idx + 1];
             /*   int max = 0;
                for (int m = idx + 1; m < onePixel->pixelDownArray.size(); m++)
                {

                    int number = onePixel->pixelDownArray[m];
                    Pixel *pixel = pixelHelper.pixelArray[number];

                    int leftsize = pixel->pixelLeftArray.size();
                    int rightsize = pixel->pixelRightArray.size();

                    int temp = leftsize + rightsize;
                    if (temp > max)
                    {
                        max = temp;
                        targeNum = number;
                    }
                }  */
                ivec[index] = targeNum;

                return true;
            }
        }
    }
    cout << " Set2 logic wrong " << index << endl;
    return false;
}

bool Set(int index)
{

    int row = index % PH;
    int column = index / PH;
    
    if (0 == row)
    {
        int num = ivec[index - PH];
        int oldValue = ivec[index];
        Pixel *onePixel = pixelHelper.pixelArray[num];
          vector<int> array = onePixel->pixelRightArrayNoValue;

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
        int num2 = ivec[index - PH];
        
          Pixel *startPixel = pixelHelper.pixelArray[ivec[startPoint]];
        vector<int> array =  pixelHelper.GetFromUpRightMapNoValue(num, num2) ;
         if (index==startPointRightUp && startPixel->upright == 1)
        {
              array =  pixelHelper.GetFromUpRightMap(num, num2) ;
        }
        if (index==startPointRight && (startPixel->upright == 1 || startPixel->right == 1 ))
        {
              array =  pixelHelper.GetFromUpRightMap(num, num2) ;
        }
         if (index==startPointRightDown && startPixel->right == 1)
        {
              array =  pixelHelper.GetFromUpRightMap(num, num2) ;
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

void main()
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
    float maxratio = 0;
    int maxIndex = PW * PH;
    int start = 0;
    int offset = 0;
    int targetoffset = 0;
    int targetStart = 0;
    const   int startcolumn = startPoint / PH;
    const  int rightstartIndex =   (startcolumn + 1) * PH;
    const  int leftstartIndex =  startcolumn * PH - 1;
    int index = 0;
    bool result = true;
      int count = 500;
       
     restart:


     offset = 0;
     ++targetoffset;
       result = true;


      for (int idx = 0; idx < maxIndex; idx++)
        {
            ivec[idx] = INVALID_VALUE;
        }
        
    for ( start = 39; start < 40; start++)
    {
        Pixel *startPixel = pixelHelper.pixelArray[start];
     //  cout << "restart with " <<startPixel->value << "  " << startPixel->pixelUpArray.size() << startPixel->pixelDownArray.size() << startPixel->pixelLeftArray.size() << startPixel->pixelRightArray.size() << endl;
        if (startPixel->value == 1 && startPixel->pixelUpArray.size() > 0 && startPixel->pixelDownArray.size() > 0  && startPixel->pixelLeftArray.size() > 0  && startPixel->pixelRightArray.size() > 0)
        {
          //  cout << "restart with " <<  start << endl;
              ++offset;
             if(offset != targetoffset)
            {
                continue;
            }
        }
        else{

              continue;
           }





          cout << "startPixel upsize " << startPixel->pixelUpArray.size() << "   down size " << startPixel->pixelDownArray.size() << endl;
        //  print_vetor(startPixel->pixelDownArray);
        char filename[64] = {0};

        sprintf(filename, "result_%dX%d_start_%d.txt", PW, PH, start);
        //  if (isFileExists_fopen(filename))
        {
            //   continue;
        }

        cout << "start with " << start << endl;

        //  int start = 2;

        ivec[startPoint] = start;
        break;
     }

      if (  INVALID_VALUE ==  ivec[startPoint] )
      {
         cout << " loop finish "  <<endl;
         return 0;
      }
        

       //pixelHelper.ClearMapWithValue();
      //   pixelHelper.SetPixelVectors();





        index = startPoint + 1;


          // cout << "start with111111 " << start << "  index " << index << " startcolumn " << startcolumn << "  index/PH " << index / PH << endl;


        restartup:

        while (index < rightstartIndex)
        {

            //   cout << "good index " << index << endl;
            if (SetColumn(index))
            {
                ++index;
                continue;
            }
            else
            {
                ivec[index] = INVALID_VALUE;
                --index;
                 if (index <= startPoint)
                {
                     result = false;
                    //  cout << "good finish" << endl;
                      cout << "SetColumn back  to restart , error"  << endl;
                      goto restart;


                }
                else
                {
                    // cout << "good index set true" << index-1 << endl;
                    continue;
                }
            }
            //  cout << "good index set false " << index << endl;
        }


       /*  for (int index = startPoint; index < rightstartIndex; index++)
        {
           cout << ivec[index] << "  " ;
        }
          cout << endl;*/




        index = startPoint - 1;
        
         restartdown:
         
        //cout << "start with22222 " << start << "  index " << index << " startcolumn " << startcolumn << "  index/PH " << index / PH << endl;
        while (index > leftstartIndex )
        {

           //  cout << "good index 222 " << index << endl;
            if (SetColumn2(index))
            {
                --index;

                  continue;

            }
            else{
                 ivec[index] = INVALID_VALUE;
                ++index;
                   if (index >= startPoint)
                {
                    //  cout << "good finish" << endl;
                      cout << "SetColumn2 back  to restart , error"  << endl;
                       result = false;
                      index = rightstartIndex  - 1;
                      goto restartup;


                }
                else
                {
                    // cout << "good index set true" << index-1 << endl;
                    continue;
                }
                
            }
        }
        
       //  cout << "good first finished continue"  << endl;

     /*         for (int index = leftstartIndex + 1; index < rightstartIndex; index++)
        {
           cout << ivec[index] << "  " ;
        }
          cout << endl;*/





        index = rightstartIndex;
        
        restartright:
         
      //  cout << "start with33333 " << start << "  index " << index << " startcolumn " << startcolumn << "  index/PH " << index / PH << endl;
        while (index < maxIndex )
        {

            // cout << "good index " << index << endl;
            if ( Set(index))
            {
                ++index;
                if (index >= maxIndex)
                {
                  //  cout << "good finish gooooooooooood" << endl;
                    break;
                }
                else
                {
                   //  cout << "good index set true" << index-1 << endl;
                    continue;
                }
            }
            else{
                  ivec[index] = INVALID_VALUE;
                 --index;
                 if (index <= rightstartIndex)
                {
                    //  cout << "good finish" << endl;
                      cout << "Set back  to rightstartIndex, restart1  , error"  << endl;
                         result = false;
                       index = leftstartIndex + 1;
                      goto restartdown;


                }
                else
                {
                    // cout << "good index set true" << index-1 << endl;
                    continue;
                }

            }

        }

         //  for (int index = leftstartIndex + 1; index < maxIndex; index++)
        {
          // cout << ivec[index] << "  " ;
        }
        //  cout << endl;
          

        index = leftstartIndex;
        
        restartleft:
        
      //  cout << "start with44444 " << start << "  index " << index << " startcolumn " << startcolumn << "  index/PH " << index / PH << endl;
        while (index >= 0 )
        {

            // cout << "good index " << index << endl;
            if (Set2(index))
            {
                --index;
                if (index < 0)
                {
                  //  cout << "good finish22222222222222222222222222222222222222" << endl;
                    result = true;
                    break;
                }
                else
                {
                    //   cout << "good index set true" << index-1 << endl;
                    continue;
                }
            }
            else{
                 ivec[index] = INVALID_VALUE;
                 ++index;
                 if (index >= leftstartIndex)
                {
                    //  cout << "good finish" << endl;
                      cout << "Set2 back  to leftstartIndex , restart1, error"  << endl;
                      result = false;
                      index = maxIndex - 1;
                      goto restartright;


                }
                else
                {
                    // cout << "good index set true" << index-1 << endl;
                    continue;
                }

            }

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
                int num = ivec[i];
                Pixel *onePixel = pixelHelper.pixelArray[num];
                screen.SetPixel(column, row, onePixel);
            }

             if(screen.SameColumns())
             {
                   cout << "good get one" << endl;
                screen.PrintOut(count++);
             }

            index = 0;
            goto restartleft;


        }


    cout << "Hello World Finished! "
         << "   " << PW * PH << "  " << targetStart << " maxratio is " << maxratio << endl;
}

