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
         cout <<   " Set logic wrong "<< index << endl;
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
         cout << " Set logic wrong  2222" << index <<endl;
        return false;

    }
    else
    {

        int num = ivec[index - 1];
        int num2 = ivec[index - PH];
        vector<int> array = pixelHelper.GetFromUpRightMap(num,num2);
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
        cout << " Set logic wrong 3333" << index <<endl;
        return false;
    }
      cout << " Set logic wrong 4444" << index <<endl;
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
                    ivec[index] = onePixel->pixelUpArray[idx+1];
                    return index;
                }
            }
        }

        cout << "logic encounter errors" << endl;
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
                    ivec[index] = onePixel->pixelRightArray[idx+1];
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
        vector<int> array = pixelHelper.GetFromUpRightMap(num,num2);
        int oldValue = ivec[index];
         ivec[index] = INVALID_VALUE;

        //    cout << " old value is f454 " << oldValue <<  " num is "  << num<<  " num2 " << num2 <<endl;
       // print_vetor(array);


        if (0 == array.size())
        {
            cout << "logic encounter errors  33333" << endl;
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

void main()
{

    pixelHelper.GetAllPossiblePixels();

    pixelHelper.SetMap();
     pixelHelper.ClearPixels();

    pixelHelper.PrintOutAllPixels();
     pixelHelper.SetMap();

    pixelHelper.SetPixelVectors();



    cout << "calculate  " << PW << " X " << PH <<endl;
    // pixelHelper.CalculateRows();


    // pixelHelper.CalculateColumns();

    int len = pixelHelper.pixelArray.size();
      float maxratio = 0;
    int maxIndex = PW * PH;
    int lessImperfect = maxIndex;
    int targetStart = 0;
     for(int start = 35; start < 37; start++)

    {

      for (int index = 0; index < maxIndex; index++)
        {
            ivec[index] = INVALID_VALUE;
         }
            int index = 1;
       char filename[64] = {0};
        
           sprintf(filename, "result_%dX%d_start_%d.txt", PW, PH, start);
    if (isFileExists_fopen(filename))
    {
          continue;
    }
    
    

    
       int oldPixelH = 5;
       int oldPixelW = 5;
        sprintf(filename, "result_%dX%d_start_%d.txt", oldPixelH, oldPixelW, start);
    if (!isFileExists_fopen(filename))
    {
          continue;
    }
        else{

          bool hasError = false;
           Screen screen = Screen();
           hasError =  !screen.LoadMatrixFileToA(filename,oldPixelH+1,oldPixelW+1);
             if (hasError)
            {
                ///遇到错误从头计算
                 cout<< "encounter errors , please check 1111" <<endl;
            }
            for (int i = 0; i < oldPixelH; i++)
            {
                Pixel pixel = screen.GetPixelFromA(0,i);
                pixel.PrintOut();
                bool found = false;
                for(int num = 0; num < len; num ++)
                {
                    Pixel *onePixel = pixelHelper.pixelArray[num];
                  //  onePixel->PrintOut();
                    if (pixel.IsEqual(onePixel))
                    {
                        found = true;
                         ivec[i] = num;
                        break;
                    }
                }
                if (!found)
                {
                     cout<< "encounter errors , please check 2222" <<endl;
                    hasError = true;

                    break;
                }
            }
            
            if (hasError)
            {
                ///遇到错误从头计算
                 cout<< "encounter errors , please check" <<endl;
                 index = 1;
                 ivec[1] = INVALID_VALUE;
            }
            else{

               index = oldPixelH;
            }
            
            
         }






        int imperfectCount = 0;

      //  int start = 2;
       cout << "start with " << start << endl;
        ivec[0] = start;
        bool result = true;


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
               //  cout << "good BackTraceFrom INVALID_VALUE" << index << endl;
                result = false;
                break;
            }
           //   cout << "good BackTraceFrom newstart" << newindex << endl;
            index = newindex+1;
        }

        /*
          for (int index = 1; index < PW * PH; index++)
          {

              int row = index % PH;
              int column = index / PH;

              if (0 == column)
              {
                  int num = ivec[index - 1];
                  Pixel *onePixel = pixelHelper.pixelArray[num];

                  int max = 0;
                  int targeNum = 0;

                  for (int m = 0; m < onePixel->pixelUpArray.size(); m++)
                  {
                      int number = onePixel->pixelUpArray[m];
                      Pixel *pixel = pixelHelper.pixelArray[number];
                      if (pixel->pixelRightArray.size() > max && pixel->isgood)
                      {
                          max = pixel->pixelRightArray.size();
                          targeNum = number;
                      }
                  }

                  ivec[index] = targeNum;
                  //  cout <<  num  << " abbbbb "<< ivec[index] << endl;
              }
              else if (0 == row)
              {
                  int num = ivec[index - PH];
                  Pixel *onePixel = pixelHelper.pixelArray[num];

                  int max = 0;
                  int targeNum = 0;

                  for (int m = 0; m < onePixel->pixelRightArray.size(); m++)
                  {
                      int number = onePixel->pixelRightArray[m];
                      Pixel *pixel = pixelHelper.pixelArray[number];

                      if (pixel->pixelUpArray.size() > max && pixel->isgood)
                      {
                          max = pixel->pixelUpArray.size();
                          targeNum = number;
                      }
                  }

                  ivec[index] = targeNum;
                  //  cout << num  << "  cdddddd "<< ivec[index] <<endl;
              }
              else
              {

                  int num = ivec[index - 1];
                  Pixel *onePixel = pixelHelper.pixelArray[num];

                  int num2 = ivec[index - PH];
                  Pixel *onePixel2 = pixelHelper.pixelArray[num2];

                  vector<int> array = vector_intersection(onePixel->pixelUpArray, onePixel2->pixelRightArray);
                  // print_vetor(array);
                  int max = 0;
                  int targeNum = -1;
                  if (array.size() > 0)
                  {

                      for (int m = 0; m < array.size(); m++)
                      {

                          int number = array[m];
                          Pixel *pixel = pixelHelper.pixelArray[number];

                          int upsize = pixel->pixelUpArray.size();
                          int rightsize = pixel->pixelRightArray.size();

                          int temp = upsize + rightsize;
                          if (temp > max && pixel->isgood)
                          {
                              max = temp;
                              targeNum = number;
                          }
                      }
                  }
                  else
                  {

                      ++imperfectCount;
                      max = 0;
                      targeNum = 0;
                      bool selectgood = false;

                      for (int m = 0; m < onePixel->pixelUpArray.size(); m++)
                      {
                          int number = onePixel->pixelUpArray[m];
                          Pixel *pixel = pixelHelper.pixelArray[number];

                          if (pixel->isgood)
                          {
                              targeNum = number;
                              selectgood = true;
                              break;
                          }

                          if (pixel->pixelRightArray.size() > max)
                          {
                              max = pixel->pixelRightArray.size();
                              targeNum = number;
                          }
                      }

                      //  cout <<"imperfect " << index << " selectgood " << selectgood <<endl;
                  }

                  if (-1 != targeNum)
                  {

                      ivec[index] = targeNum;
                  }

                  //  cout << num  << "  fdsfdsfdsfdsfds   "<<num2  << "  fdsfdsfdsfdsfds "<<ivec[index] <<endl;
              }

              if (-1 == ivec[index])
              {
                  cout << "can not find result " << start << endl;
                  result = false;
                  break;
              }
          }
           */

        if (result)
        {

            if (lessImperfect > imperfectCount)
            {
                lessImperfect = imperfectCount;

            }
            cout << "-------------------------"
                 << "imperfectCount " << imperfectCount << endl;
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

            screen.PrintOut(start);
            float ratio = screen.GetPoleRatio();
            if ( ratio > maxratio )
            {
                 targetStart = start;
                maxratio = ratio;
            }
            cout << " ratio is " << ratio  << endl;
        }
    }

    /*  vector< vector < vector<int> > > dp(PW,vector< vector<int> >(PH,vector<int>(len)));
      for (int z = 0; z < len; z++)
      {
          for (int x = 0;  x < PW; x++)
          {
              for (int y = 0; y < PH; y++)
              {
                  dp[x][y][z] = 1;
              }
          }
      }



       for (int x = 0;  x < PW; x++)
          {
              for (int y = 0; y < PH; y++)
              {
                   for (int z = 0; z < len; z++)
                   {
                     dp[x][y][z] = pixelHelper.pixelArray[z]->value;
                   }
              }
          }  */

    /*  int len = pixelArray.size();

      Screen screen = Screen();
      int resultCount = 0;
      float maxRatio = 0;
      cout << "calculate screen " << PW << " X " << PH <<endl;
     while(true)
     {
         int start = pixelHelper.State[0][0];
         cout << "start with " << start <<endl;
          screen.SetPixel(0,0,pixelArray[start]);
          bool result = false;


          int x = 0;
          int y = 0;
          while (x < PW)
          {
             bool isAllSet = 0;
             while (y < PH)
             {

                 bool found = false;
                 if  (0==x && 0==y) found = true;


                 if (!found)
                 {
                     for (int index = pixelHelper.State[x][y]; index < len; index++)
                     {
                         Pixel * pixel = pixelArray[index];
                         if ( screen.TrySetOnePixel(x,y,pixel))
                         {
                             screen.SetPixel(x,y,pixel);
                             found = true;
                             pixelHelper.State[x][y] = index;
                             break;
                         }
                     }
                 }

                 if ( !found )
                 {
                     break;
                 }
                 else
                 {

                     if (y + 1 == PH)
                     {
                         isAllSet = true;
                         break;
                     }
                     y = y + 1;
                 }
             }


                 if (isAllSet)
                 {
                      if (x + 1 == PW)
                      {
                         result = true;
                         break;
                      }
                      y = 0;
                      x = x + 1;
                 }
                 else
                 {
                      int newx = 0;
                      int newy = 0;
                      if ( ! pixelHelper.BackTraceFrom(x,y,len-1,&newx,&newy))
                      {
                           // cout << "can not find result " << x << " " << y << " back to " << newx << "  " << newy << endl;
                         break;
                      }
                      else
                         {

                           //   cout << "can not find result " << x << " " << y << " back to " << newx << "  " << newy << "   " << pixelHelper.State[newx][newy] <<endl;
                             x = newx;
                             y = newy;
                      }
                 }
              }


             if (result)
             {
                  ++resultCount;
                  float ratio = screen.GetPoleRatio();


                  cout << "find a solution " << resultCount << " ratio: "<< ratio << endl;

                  if (ratio > maxRatio)
                  {
                    maxRatio = ratio;
                    screen.PrintOut(start);

                  }



             }else
                  {
                    cout << "can not find a solution for " << start <<endl;
             }





          pixelHelper.State[0][0] = start;
          if ( !pixelHelper.PlusOneFor(0,0,len-1))
          {
             break;
          }
     }

        */

    cout << "Hello World Finished! " << lessImperfect << "   " << PW * PH << "  " << targetStart << " maxratio is " <<maxratio  << endl;
}
