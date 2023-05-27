
#ifndef __Screeen_
#define __Screeen_
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Pixel.h"
#include "Point.h"

using namespace std;
#define SW (PW + 1)
#define SH (PH + 1)




class Screen
{
public:
    int A[SW][SH];
    Pixel cells[PW][PH];

public:
    Screen();
    void SetPixel(int x, int y, Pixel *pixel);
    void SetPixelValue(int x, int y, int value);
    int GetPixelValue(int x, int y);
    bool TrySetOnePixel(int xpos, int ypos, Pixel *pixel);
    void PrintOut(int flag,int flag2,int flag3);
    float GetPoleRatio();
    int GetPoleCount();
    Pixel GetPixelFromA(int x,int y);
    bool LoadMatrixFileToA(const char * fileName, int row, int column);
    
    bool SameColumns(); ///��ߺ��ұ��Ƿ�һ��
    bool SameRows(); ///�����͵ײ��Ƿ�һ��
};

Screen::Screen()
{
    for (int x = 0; x < SW; x++)
    {
        for (int y = 0; y < SH; y++)
        {
            A[x][y] = -1;
        }
    }
}


 bool Screen::SameColumns() ///��ߺ��ұ��Ƿ�һ��
 {
        vector<int> colLeft;
        vector<int> colRight;
        for (int idx = 0; idx < SH; idx++)
        {
               colLeft.push_back(A[0][idx]);
               colRight.push_back(A[SW-1][idx]);
        }

        return colLeft == colRight;
}
    bool Screen::SameRows() ///�����͵ײ��Ƿ�һ��
    {
         vector<int> rowTop;
        vector<int> rowBottom;

           for (int idx = 0; idx < SW; idx++)
        {
               rowTop.push_back(A[idx][SH-1]);
               rowBottom.push_back(A[idx][0]);
        }
        
          return rowTop == rowBottom;
        }

void Screen::PrintOut(int flag,int flag2 = -1,int flag3 = -1)
{
    // return ;
    ofstream outFile; 
    char filename[64] = {0};
    if ( flag2 == -1 )
    {
        sprintf(filename, "dfs/result_%dX%d_start_%d.txt", PW, PH, flag);

    }else  if ( flag3 == -1 )
    {
         sprintf(filename, "dfs/result_%dX%d_start_%d_%d.txt", PW, PH, flag,flag2);
    }
    else
    {
         sprintf(filename, "dfs/result_%dX%d_start_%d_%d_%d.txt", PW, PH, flag,flag2,flag3);
    }
    outFile.open(filename); 
    for (int y = SH - 1; y >= 0; y--)
    {
        for (int x = 0; x < SW; x++)
        {
            // cout << A[x][y] << "   ";
            outFile << A[x][y] << " ";
        }
       // cout << endl;
        outFile << endl;
    }

    outFile.close(); 
}

void Screen::SetPixel(int x, int y, Pixel *pixel)
{
    if (!pixel->IsValid())
    {
        cout << "*******invalid pixel" << endl;
    }
    // cout << "SetPixel " << x << " " << y <<endl;
    // pixel->PrintOut();
    cells[x][y] = *pixel;
    Point point = Point(x, y);
    Point up = point.Up();
    Point right = point.Right();
    Point upright = point.UpRight();
    A[x][y] = pixel->origin;
    A[up.x][up.y] = pixel->up;
    A[upright.x][upright.y] = pixel->upright;
    A[right.x][right.y] = pixel->right;
}

void Screen::SetPixelValue(int x, int y, int value)
{
    A[x][y] = value;
}

int Screen::GetPixelValue(int x, int y)
{
   return A[x][y];
}
bool Screen::LoadMatrixFileToA(const char * fileName, int row, int column)
{

   ifstream  fileStream;

    fileStream.open(fileName,std::ios::in);

    if (fileStream.fail())
    {
        cout << "read file failed " << fileName<<endl;
        return false;
    }
    else
    {

       for (int y = column - 1; y >= 0; y--)
      {
        for (int x = 0; x < row; x++)
        {
            fileStream >> A[x][y];
        }
      }
    
    }

   return   true;
}

Pixel Screen::GetPixelFromA(int x,int y)
{
    Pixel pixel;
   Point point = Point(x, y);
    Point up = point.Up();
    Point right = point.Right();
    Point upright = point.UpRight();
    
    pixel.origin = A[x][y];
    pixel.up = A[up.x][up.y];
    pixel.upright = A[upright.x][upright.y];
    pixel.right = A[right.x][right.y];
    return pixel;
}

float Screen::GetPoleRatio()
{
    int count = 0;
    for (int x = 0; x < SW; x++)
    {
        for (int y = 0; y < SH; y++)
        {
            if (1 == this->A[x][y])
            {
                ++count;
            }
        }
    }
    return count / (SW * SH * 1.0);
}

int Screen::GetPoleCount()
{
    int count = 0;
    for (int x = 0; x < SW; x++)
    {
        for (int y = 0; y < SH; y++)
        {
            if (1 == this->A[x][y])
            {
                ++count;
            }
        }
    }
    return count;
}

bool Screen::TrySetOnePixel(int xpos, int ypos, Pixel *pixel)
{
    int x = xpos;
    int y = ypos - 1;
    if (0 == ypos)
    {
        y = 0;
        x = xpos - 1;
    }

    Pixel *referencePixel = &this->cells[x][y];
    if (0 == x)
    {
        if (referencePixel->IsConnectedV(pixel))
        {
            return true;
        }
    }
    else if (0 == y)
    {
        if (referencePixel->IsConnectedH(pixel))
        {
            return true;
        }
    }
    else
    {
        Pixel *leftPixel = &this->cells[x - 1][y];
        if (referencePixel->IsConnectedV(pixel) && leftPixel->IsConnectedH(pixel))
        {
            return true;
        }
    }
}

#endif
