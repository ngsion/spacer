#ifndef _PIXELHELPER_
#define _PIXELHELPER_
#include <iostream.h>
#include "Pixel.h"
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "Utility.h"
using namespace std;


class PixelHelper
{
public:
  int State[PW][PH];
  vector<Pixel *> pixelArray;

  int bottom[PW];

  vector< vector<int> > columnPixels;
  vector< vector<int> > rowPixels;

  map<int, vector<int> > pixelDownMap;
  map<int, vector<int> > pixelLeftMap;
  map<int, vector<int> > pixelUpMap;
  map<int, vector<int> > pixelRightMap;
  map<int, map<int, vector<int> > > pixelUpRightMap;
  map<int, map<int, vector<int> > > pixelDownLeftMap;
  map<int, map<int, vector<int> > > pixelDownRightMap;

public:
  void CalculateRows();
  void CalculateColumns();
  void SetBottom(int start);
  vector<int> GetFromUpRightMap(int m, int n);
  vector<int> GetFromDownLeftMap(int m, int n);
  vector<int> GetFromDownRightMap(int m, int n);
   vector<int> GetFromUpRightMapNoValue(int m, int n);
  vector<int> GetFromDownLeftMapNoValue(int m, int n);
   vector<int> GetFromDownRightMapNoValue(int m, int n);
   vector<int> GetFromUpRightMapWithValue(int m, int n);
   vector<int> GetFromDownRightMapWithValue(int m, int n);
   
  
  void PrintOutAllPixels();
  void GetAllPossiblePixels();
  void SetMap();
  void SetMapWithoutValue();
  void ClearMapWithValue();
  void ClearPixels();
  void SetPixelVectors();

  PixelHelper();
  ~PixelHelper();

  bool PlusOneFor(int x, int y, int max);
  bool BackTraceFrom(int xpos, int ypos, int maxN, int *xout, int *yout);
};



vector<int> PixelHelper::GetFromDownLeftMap(int m, int n)
{
  map<int, map<int, vector<int> > >::iterator itor = pixelDownLeftMap.find(m);
  if ( itor != pixelDownLeftMap.end())
  {
      map<int, vector<int> >::iterator it = itor->second.find(n);
      if ( it != itor->second.end())
      {
           return it->second;
      }
  }
  vector<int> array;
   return  array;
}

vector<int> PixelHelper::GetFromDownRightMap(int m, int n)
{
  map<int, map<int, vector<int> > >::iterator itor = pixelDownRightMap.find(m);
  if ( itor != pixelDownRightMap.end())
  {
      map<int, vector<int> >::iterator it = itor->second.find(n);
      if ( it != itor->second.end())
      {
           return it->second;
      }
  }
  vector<int> array;
   return  array;
}



vector<int> PixelHelper::GetFromDownLeftMapNoValue(int m, int n)
{
  vector<int> array = GetFromDownLeftMap(m,n);
  
  if (array.size() > 0)
  {
     vector<int>::iterator itor;
       itor = array.begin();
      while (itor != array.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = array.erase(itor);

           } else{

                 ++itor;
           }
     }
  }
  
  
   return  array;
}


vector<int> PixelHelper::GetFromDownRightMapNoValue(int m, int n)
{
  vector<int> array = GetFromDownRightMap(m,n);

  if (array.size() > 0)
  {
     vector<int>::iterator itor;
       itor = array.begin();
      while (itor != array.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = array.erase(itor);

           } else{

                 ++itor;
           }
     }
  }


   return  array;
}


vector<int> PixelHelper::GetFromDownRightMapWithValue(int m, int n)
{
  vector<int> array = GetFromDownRightMap(m,n);

  if (array.size() > 0)
  {
     vector<int>::iterator itor;
       itor = array.begin();
      while (itor != array.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value <= 1)
           {
                itor = array.erase(itor);

           } else{

                 ++itor;
           }
     }
  }


   return  array;
}


vector<int> PixelHelper::GetFromUpRightMap(int m, int n)
{
  map<int, map<int, vector<int> > >::iterator itor = pixelUpRightMap.find(m);
  if ( itor != pixelUpRightMap.end())
  {
      map<int, vector<int> >::iterator it = itor->second.find(n);
      if ( it != itor->second.end())
      {
           return it->second;
      }
  }
  vector<int> array;
   return  array;
}

vector<int> PixelHelper::GetFromUpRightMapNoValue(int m, int n)
{
 vector<int> array = GetFromUpRightMap(m,n);

  if (array.size() > 0)
  {
     vector<int>::iterator itor;
       itor = array.begin();
      while (itor != array.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = array.erase(itor);

           } else{

                 ++itor;
           }
     }
  }


   return  array;
}


vector<int> PixelHelper::GetFromUpRightMapWithValue(int m, int n)
{
 vector<int> array = GetFromUpRightMap(m,n);

  if (array.size() > 0)
  {
     vector<int>::iterator itor;
       itor = array.begin();
      while (itor != array.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value <= 1)
           {
                itor = array.erase(itor);

           } else{

                 ++itor;
           }
     }
  }


   return  array;
}


void PixelHelper::CalculateColumns()
{

  int len = pixelArray.size();
  cout << "------- columnPixels  start " << len << endl;
  for (int num = 0; num < len; num++)
  {
    int start = num;

    vector<int> numarray = pixelUpMap[start];

    for (int idx = 0; idx < numarray.size(); idx++)
    {
      int second = numarray[idx];
      vector<int> numarray2 = pixelUpMap[second];

      for (int idx2 = 0; idx2 < numarray2.size(); idx2++)
      {
        int third = numarray2[idx2];
        vector<int> numarray3 = pixelUpMap[third];
        for (int idx3 = 0; idx3 < numarray3.size(); idx3++)
        {
          int fourth = numarray3[idx3];
          vector<int> numarray4 = pixelUpMap[fourth];

          for (int idx4 = 0; idx4 < numarray4.size(); idx4++)
          {
            int fifth = numarray4[idx4];
            vector<int> oneRow;
            oneRow.push_back(start);
            oneRow.push_back(second);
            oneRow.push_back(third);
            oneRow.push_back(fourth);
            oneRow.push_back(fifth);
            columnPixels.push_back(oneRow);
          }
        }
      }
    }
  }

  cout << "------- columnPixels size " << columnPixels.size() << endl;
}

void PixelHelper::CalculateRows()
{

  int len = pixelArray.size();
  cout << "------- rowpixels  start " << len << endl;
  for (int num = 0; num < len; num++)
  {
    int start = num;

    vector<int> numarray = pixelRightMap[start];

    for (int idx = 0; idx < numarray.size(); idx++)
    {
      int second = numarray[idx];
      vector<int> numarray2 = pixelRightMap[second];

      for (int idx2 = 0; idx2 < numarray2.size(); idx2++)
      {
        int third = numarray2[idx2];
        vector<int> numarray3 = pixelRightMap[third];
        for (int idx3 = 0; idx3 < numarray3.size(); idx3++)
        {
          int fourth = numarray3[idx3];
          vector<int> numarray4 = pixelRightMap[fourth];

          for (int idx4 = 0; idx4 < numarray4.size(); idx4++)
          {
            int fifth = numarray4[idx4];
            vector<int> oneRow;
            oneRow.push_back(start);
            oneRow.push_back(second);
            oneRow.push_back(third);
            oneRow.push_back(fourth);
            oneRow.push_back(fifth);
            rowPixels.push_back(oneRow);
          }
        }
      }
    }
  }

  cout << "------- rowpixels size " << rowPixels.size() << endl;
}

void PixelHelper::SetBottom(int start)
{
  bottom[0] = start;
  for (int index = 0; index < PW - 1; index++)
  {
    int num = bottom[index];
    if (pixelRightMap[num].size() > 0)
    {
      bottom[index + 1] = pixelRightMap[num][0];
    }
    else
    {
      cout << "wrong in setbottom" << endl;
    }
  }
}

void PixelHelper::ClearPixels()
{
  int len = pixelArray.size();
  vector<int> needtodelete;
  for (int xpos = 0; xpos < len; xpos++)
  {
    int downsize = pixelDownMap[xpos].size();
    int leftsize = pixelLeftMap[xpos].size();
    int upsize = pixelUpMap[xpos].size();
    int rightsize = pixelRightMap[xpos].size();
    int reference = 1;
    if ( upsize < reference || rightsize < reference || leftsize < reference || downsize < reference )
    {
      needtodelete.push_back(xpos);
     // cout << "reference " << reference << "   " << upsize << " " << rightsize << " " << downsize << " " << leftsize << " " << xpos << endl;
    }
  }
 // cout << "needtodelete  size " << needtodelete.size() << endl;
  for (int index = needtodelete.size() - 1; index >= 0; index--)
  {
    int pos = needtodelete[index];
    pixelArray.erase(pixelArray.begin() + pos);
  }
}

void PixelHelper::SetPixelVectors()
{
  int len = pixelArray.size();

  for (int xpos = 0; xpos < len; xpos++)
  {
    Pixel *onePixel = pixelArray[xpos];

      vector<int> upone;
     onePixel->pixelUpArrayNoValue = upone;
    if( pixelUpMap.count(xpos) > 0 )
    {
         onePixel->pixelUpArray = pixelUpMap[xpos];
            for (int idx = 0; idx < onePixel->pixelUpArray.size(); idx++)
              {
                  int num = onePixel->pixelUpArray[idx];
                  Pixel *targetPixel = pixelArray[num];
                if (0 == targetPixel->value)
                {
                   onePixel->pixelUpArrayNoValue.push_back(num);
                }
              }
    }
    else{

       vector<int> one;
        onePixel->pixelUpArray =  one;
    }
    
     vector<int> downone;
    onePixel->pixelDownArrayNoValue = downone;
     if( pixelDownMap.count(xpos) > 0 )
    {
       onePixel->pixelDownArray = pixelDownMap[xpos];
       
        for (int idx = 0; idx < onePixel->pixelDownArray.size(); idx++)
              {
                  int num = onePixel->pixelDownArray[idx];
                  Pixel *targetPixel = pixelArray[num];
                if (0 == targetPixel->value)
                {
                   onePixel->pixelDownArrayNoValue.push_back(num);
                }
              }
    }
    else{

        vector<int> one;
        onePixel->pixelDownArray =  one;
    }

     vector<int> leftone;
    onePixel->pixelLeftArrayNoValue = leftone;
      if( pixelLeftMap.count(xpos) > 0 )
    {
       onePixel->pixelLeftArray = pixelLeftMap[xpos];
        for (int idx = 0; idx < onePixel->pixelLeftArray.size(); idx++)
              {
                  int num = onePixel->pixelLeftArray[idx];
                  Pixel *targetPixel = pixelArray[num];
                if (0 == targetPixel->value)
                {
                   onePixel->pixelLeftArrayNoValue.push_back(num);
                }
              }
              
    }
    else{

    vector<int> one;
        onePixel->pixelLeftArray =  one;
    }

    vector<int> rightone;
     onePixel->pixelRightArrayNoValue = rightone;
       if( pixelRightMap.count(xpos) > 0 )
    {
       onePixel->pixelRightArray = pixelRightMap[xpos];
       
       for (int idx = 0; idx < onePixel->pixelRightArray.size(); idx++)
              {
                  int num = onePixel->pixelRightArray[idx];
                  Pixel *targetPixel = pixelArray[num];
                if (0 == targetPixel->value)
                {
                   onePixel->pixelRightArrayNoValue.push_back(num);
                }
              }
              
    }
    else{

    vector<int> one;
        onePixel->pixelRightArray =  one;
    }

  }
}
void PixelHelper::SetMap()
{
  pixelUpMap.clear();

  pixelRightMap.clear();
  pixelLeftMap.clear();

  pixelDownMap.clear();
  pixelUpRightMap.clear();
  pixelDownLeftMap.clear();
  pixelDownRightMap.clear();
  int len = pixelArray.size();

 // cout << "SetMap  len " << len << endl;
  for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {
      Pixel *onePixel = pixelArray[xpos];
      Pixel *anotherPixel = pixelArray[ypos];
      if (onePixel->IsConnectedV(anotherPixel))
      {

           pixelUpMap[xpos].push_back(ypos);

           pixelDownMap[ypos].push_back(xpos);

      }

      if (onePixel->IsConnectedH(anotherPixel))
      {

            pixelRightMap[xpos].push_back(ypos);

             pixelLeftMap[ypos].push_back(xpos);

      }
    }
  }

  for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {

      vector<int> array = vector_intersection(pixelUpMap[xpos], pixelRightMap[ypos]);

      if (array.size() > 0)
      {
        //   cout << "aaaaaaaaaaa"  << endl;
        pixelUpRightMap[xpos][ypos] = array;
      }
    }
  }

   for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {

      vector<int> array = vector_intersection(pixelDownMap[xpos], pixelLeftMap[ypos]);

      if (array.size() > 0)
      {
        //   cout << "aaaaaaaaaaa"  << endl;
        pixelDownLeftMap[xpos][ypos] = array;
      }
    }
  }
  
   for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {

      vector<int> array = vector_intersection(pixelDownMap[xpos], pixelRightMap[ypos]);

      if (array.size() > 0)
      {
        //   cout << "aaaaaaaaaaa"  << endl;
        pixelDownRightMap[xpos][ypos] = array;
      }
    }
  }


  map<int, vector<int> >::iterator it;
  cout << "pixelDownRightMap  size " << pixelDownRightMap.size() << endl;
cout << "pixelDownLeftMap  size " << pixelDownLeftMap.size() << endl;
  cout << "pixelUpRightMap  size " << pixelUpRightMap.size() << endl;
 /* map<int, map<int, vector<int> > >::iterator itor;
  for (itor = pixelUpRightMap.begin(); itor != pixelUpRightMap.end(); itor++)
  {

    for (it = itor->second.begin(); it != itor->second.end(); it++)
    {
      cout << itor->first << " --" << it->first << " --";
      for (int index = 0; index < it->second.size(); index++)
      {

        cout << it->second[index] << " ";
      }
      cout << endl;
    }
  }   */

  cout << "pixelUpMap  size " << pixelUpMap.size() << endl;
 /* for (it = pixelUpMap.begin(); it != pixelUpMap.end(); it++)
  {
    cout << it->first << " --";
    for (int index = 0; index < it->second.size(); index++)
    {
      cout << it->second[index] << " ";
    }
    cout << endl;
  }  */
  
   cout << "pixelDownMap  size " << pixelDownMap.size() << endl;
 /* for (it = pixelDownMap.begin(); it != pixelDownMap.end(); it++)
  {
    cout << it->first << " --";
    for (int index = 0; index < it->second.size(); index++)
    {
      cout << it->second[index] << " ";
    }
    cout << endl;
  } */


  cout << "pixelRightMap  " << pixelRightMap.size() << endl;
 // map<int, vector<int> >::iterator it2;
  /*for (it2 = pixelRightMap.begin(); it2 != pixelRightMap.end(); it2++)
  {
    cout << it2->first << " --";
    for (int index = 0; index < it2->second.size(); index++)
    {
      cout << it2->second[index] << " ";
    }
    cout << endl;
  }  */
  
   cout << "pixelLeftMap  size " << pixelLeftMap.size() << endl;
  /*for (it = pixelLeftMap.begin(); it != pixelLeftMap.end(); it++)
  {
    cout << it->first << " --";
    for (int index = 0; index < it->second.size(); index++)
    {
      cout << it->second[index] << " ";
    }
    cout << endl;
  }  */
}

void PixelHelper::ClearMapWithValue()
{
       map<int, vector<int> >::iterator it;
     vector<int>::iterator itor;
        
           it = pixelUpMap.begin();
   while (it != pixelUpMap.end())
  {
     itor = it->second.begin();
     while (itor != it->second.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = it->second.erase(itor);
                
           } else{

                 ++itor;
           }
     }

     it++ ;
  }
 //   cout << "pixelUpMap  size " << pixelUpMap.size() << endl;

   it = pixelDownMap.begin();
   while (it != pixelDownMap.end())
  {
     itor = it->second.begin();
     while (itor != it->second.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = it->second.erase(itor);

           } else{

                 ++itor;
           }
     }

     it++ ;
  }
   // cout << "pixelDownMap  size " << pixelDownMap.size() << endl;


  it = pixelRightMap.begin();
   while (it != pixelRightMap.end())
  {
     itor = it->second.begin();
     while (itor != it->second.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = it->second.erase(itor);

           } else{

                 ++itor;
           }
     }


     it++ ;
  }
  //  cout << "pixelRightMap  size " << pixelRightMap.size() << endl;

 it = pixelLeftMap.begin();
  while (it != pixelLeftMap.end())
  {
     itor = it->second.begin();
     while (itor != it->second.end())
     {
          Pixel *onePixel = pixelArray[*itor];
           if(onePixel->value >= 1)
           {
                itor = it->second.erase(itor);

           } else{

                 ++itor;
           }
     }

    /*   if(it->second.size() == 0)
       {
         pixelLeftMap.erase( it++ );
         continue;
       } */

     it++ ;
  }
 // cout << "pixelLeftMap  size " << pixelLeftMap.size() << endl;
}


void PixelHelper::SetMapWithoutValue()
{
  pixelUpMap.clear();

  pixelRightMap.clear();
  pixelLeftMap.clear();

  pixelDownMap.clear();
  pixelUpRightMap.clear();
  pixelDownLeftMap.clear();

  int len = pixelArray.size();

  //cout << "SetMapWithoutValue  len " << len << endl;
  for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {
      Pixel *onePixel = pixelArray[xpos];
      Pixel *anotherPixel = pixelArray[ypos];
      if (onePixel->IsConnectedV(anotherPixel))
      {
        if(anotherPixel->value < 1)
        {
             pixelUpMap[xpos].push_back(ypos);
        }
        if(onePixel->value < 1)
        {
        pixelDownMap[ypos].push_back(xpos);
        }
      }

      if (onePixel->IsConnectedH(anotherPixel))
      {
         if(anotherPixel->value < 1)
         {
           pixelRightMap[xpos].push_back(ypos);
        }
        if(onePixel->value < 1)
        {
          pixelLeftMap[ypos].push_back(xpos);
        }
      }
    }
  }

  for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {

      vector<int> array = vector_intersection(pixelUpMap[xpos], pixelRightMap[ypos]);

      if (array.size() > 0)
      {
        //   cout << "aaaaaaaaaaa"  << endl;
        pixelUpRightMap[xpos][ypos] = array;
      }
    }
  }

 for (int xpos = 0; xpos < len; xpos++)
  {
    for (int ypos = 0; ypos < len; ypos++)
    {

      vector<int> array = vector_intersection(pixelDownMap[xpos], pixelLeftMap[ypos]);

      if (array.size() > 0)
      {
        //   cout << "aaaaaaaaaaa"  << endl;
        pixelDownLeftMap[xpos][ypos] = array;
      }
    }
  }

  map<int, vector<int> >::iterator it;

 /* map<int, map<int, vector<int> > >::iterator itor;
  for (itor = pixelUpRightMap.begin(); itor != pixelUpRightMap.end(); itor++)
  {

    for (it = itor->second.begin(); it != itor->second.end(); it++)
    {
      cout << itor->first << " --" << it->first << " --";
      for (int index = 0; index < it->second.size(); index++)
      {

        cout << it->second[index] << " ";
      }
      cout << endl;
    }
  }   */

  cout << "pixelUpMap  size " << pixelUpMap.size() << endl;
 /* for (it = pixelUpMap.begin(); it != pixelUpMap.end(); it++)
  {
    cout << it->first << " --";
    for (int index = 0; index < it->second.size(); index++)
    {
      cout << it->second[index] << " ";
    }
    cout << endl;
  } */

   cout << "pixelDownMap  size " << pixelDownMap.size() << endl;
 /* for (it = pixelDownMap.begin(); it != pixelDownMap.end(); it++)
  {
    cout << it->first << " --";
    for (int index = 0; index < it->second.size(); index++)
    {
      cout << it->second[index] << " ";
    }
    cout << endl;
  }  */


  cout << "pixelRightMap  " << pixelRightMap.size() << endl;
 /* map<int, vector<int> >::iterator it2;
  for (it2 = pixelRightMap.begin(); it2 != pixelRightMap.end(); it2++)
  {
    cout << it2->first << " --";
    for (int index = 0; index < it2->second.size(); index++)
    {
      cout << it2->second[index] << " ";
    }
    cout << endl;
  } */

   cout << "pixelLeftMap  size " << pixelLeftMap.size() << endl;
 /* for (it = pixelLeftMap.begin(); it != pixelLeftMap.end(); it++)
  {
    cout << it->first << " --";
    for (int index = 0; index < it->second.size(); index++)
    {
      cout << it->second[index] << " ";
    }
    cout << endl;
  } */
  
}

PixelHelper::PixelHelper()
{
  for (int xpos = 0; xpos < PW; xpos++)
  {
    for (int ypos = 0; ypos < PH; ypos++)
    {
      State[xpos][ypos] = -1;
    }
  }
}

PixelHelper::~PixelHelper()
{
  for (int index = 0; index < pixelArray.size(); index++)
  {
    free(pixelArray[index]);
  }
}

bool PixelHelper::BackTraceFrom(int xpos, int ypos, int maxN, int *xout, int *yout)
{
  this->State[xpos][ypos] = 0;
  int m = xpos;
  int n = ypos - 1;
  while (n >= 0)
  {
    if (this->State[m][n] < maxN)
    {
      this->State[m][n] = this->State[m][n] + 1;
      *xout = m;
      *yout = n;
      if (0 == m && 0 == n)
        return false;
      return true;
    }
    else
    {
      this->State[m][n] = 0;
    }
    n = n - 1;
  }

  if (m > 0)
  {
    for (m = xpos - 1; m >= 0; m--)
    {
      for (n = PH; n >= 0; n--)
      {
        if (this->State[m][n] < maxN)
        {
          this->State[m][n] = this->State[m][n] + 1;
          *xout = m;
          *yout = n;
          if (0 == m && 0 == n)
            return false;
          return true;
        }
        else
        {
          this->State[m][n] = 0;
        }
      }
    }
  }

  return false;
}

bool PixelHelper::PlusOneFor(int x, int y, int max)
{
  int temp = State[x][y] + 1;
  if (temp > max)
  {
    return false;
  }
  else
  {
    for (int xpos = 0; xpos < PW; xpos++)
    {
      for (int ypos = 0; ypos < PH; ypos++)
      {
        State[xpos][ypos] = 0;
      }
    }
    State[x][y] = temp;
  }
  return true;
}

void PixelHelper::PrintOutAllPixels()
{
  for (int ypos = 0; ypos < pixelArray.size(); ypos++)
  {
    Pixel *zeropixel = pixelArray[ypos];
    cout << ypos << " ---------";
    zeropixel->PrintOut();
  }
}
void PixelHelper::GetAllPossiblePixels()
{

  int count = 0;
  for (int a = 1; a <= 5; a++)
  {
    for (int b = 1; b <= 5; b++)
    {
      for (int c = 1; c <= 5; c++)
      {
        for (int d = 1; d <= 5; d++)
        {
          Pixel *one = new Pixel(a, b, c, d);
          one->DoValue();
          if (one->IsValid2())
          {
            
            ++count;
            pixelArray.push_back(one);
            // one.PrintOut();
          }
        }
      }
    }
  }
  cout << "GetAllPossiblePixels return " << pixelArray.size() << endl;
}

#endif
