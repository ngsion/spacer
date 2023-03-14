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
 #include <iostream.h>
#include <fstream>
#include <stdio.h>

 bool LoadMatrixFileToA(const char * fileName, int row, int column, int A[SW][SH])
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
            fileStream >> A[x][22-y];
           //  cout << " A[x][y] " <<  A[x][y]<<  "  X= "<<x << " y="<<y <<endl;
        }
      }

    }

   return   true;
}

 bool LoadMatrixFileToAAAAr(const char * fileName, int row, int column, int A[SW][SH])
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
            fileStream >> A[x+11][11-y];
        }
      }

    }

   return   true;
}

int main()
{
      pixelHelper.GetAllPossiblePixels();
    pixelHelper.PrintOutAllPixels();
   // pixelHelper.SetMapWithoutValue();
     //pixelHelper.ClearPixels();


    pixelHelper.SetMap();
     pixelHelper.SetPixelVectors();


     int len = pixelHelper.pixelArray.size();

    map<int, vector< vector <int> > > columnsMap;
    map<int, vector< vector <int> > > rowsMap;

       cout << "start with " << len << endl;
    for(int start = 0; start < 100000; start++)
    {

        for(int start2 = 0; start2 < 100000; start2++)
      {

     //  int start = 1;


         cout << "start with " << start << "start2 "<< start2 << endl;

        int A[SW][SH];
         for (int xpos = 0; xpos < SW; xpos++)
      {
         for(int ypos = 0; ypos < SH; ypos++)
         {
            A[xpos][ypos] = 0;
         }
      }
        char filename[64] = {0};

       sprintf(filename, "1111/result_%dX%d_start_%d.txt", 11, 11, start);
       if (isFileExists_fopen(filename))
       {
          LoadMatrixFileToA(filename,12, 12,A);
       }
       else
       {
        continue;
       }
         sprintf(filename, "1111/result_%dX%d_start_r_%d.txt", 11, 11, start2);
       if (isFileExists_fopen(filename))
       {
          LoadMatrixFileToAAAAr(filename,12, 12,A);
       }else
       {
        continue;
       }
       
       bool found = true;
       
       for (int y = 11; y < SH; y++)
       {
        for (int x = 11; x < SW; x++)
        {

           if( 0 == A[x][y])
           {
               // cout<<"A[x][y]  "<<x << "  y " <<y<<endl;
               //    cout<<"A[x-1][y]  "<<A[x-1][y] <<" A[x-1][y-1]  "<<A[x-1][y-1]<<endl;
               bool isok = false;
               for (int pos = 0; pos < len; pos++)
                 {

                   Pixel *pixel = pixelHelper.pixelArray[pos];

                   if( pixel->origin == A[x-1][y] &&  pixel->up == A[x-1][y-1]  &&  pixel->upright == A[x][y-1] )
                   {
                     if ( 1 == pixel->right) continue;

                       A[x][y] = pixel->right;
                       isok = true;
                       break;
                   }
                }
                
                if(!isok)
                {
                    found = false;
                    goto test;
                }

           }
         }
        }

        test:
           if(found)
           {
            cout  << " find a result  ";
                    // return ;
           ofstream outFile;
          //  char filename[64] = {0};
           sprintf(filename, "2222/result_%dX%d_start_%d.txt", PW, PH, start);
             outFile.open(filename);
           for (int y = 0; y < SH; y++)
            {
                 for (int x = 0; x < SW; x++)
             {
               // cout << A[x][y] << "   ";
                 outFile << A[x][y] << "   ";
              }
            // cout << endl;
                outFile << endl;
             }

             outFile.close();
              cout<<"finish result  "<<endl;
           }
    }


}

       
       
       


    /*  for (int xpos = 0; xpos < SW; xpos++)
      {
         vector<int> oneColumn;
         for(int ypos = 0; ypos < SH; ypos++)
         {
           oneColumn.push_back(A[xpos][ypos]);
           //  cout << "a x y " << xpos <<  "  " << ypos << "  " << A[xpos][ypos] <<endl;
         }

         columnsMap[start].push_back(oneColumn);
       //  print_vetor(oneColumn);
      }

       for (int ypos = 0; ypos < SH; ypos++)
      {
         vector<int> oneRow;
         for(int xpos = 0; xpos < SW; xpos++)
         {
            oneRow.push_back(A[xpos][ypos]);
           //  cout << "a x y " << xpos <<  "  " << ypos << "  " << A[xpos][ypos] <<endl;
         }

          rowsMap[start].push_back(oneRow);
      }

    }

      cout << "rowsMap size  " << rowsMap.size() << "  columnsMap size " << columnsMap.size() << endl;

      map<int, vector< vector <int> > >::iterator rowitor;
    for(rowitor = rowsMap.begin(); rowitor != rowsMap.end(); rowitor++)
    {
    /////////////////////////////////////////////////

     int startIndex = rowitor->first;
      cout << "rowsMap start with " << startIndex << endl;
      int targetHeight = 790;
       vector< vector<int> > targetRows;
     vector<int> lastVector =  rowsMap[startIndex][1];
     targetRows.push_back(lastVector);

     for (int index = 0; index < targetHeight; index++)
     {

           bool found = false;
          //   int num = rand()%5;
          map<int,  vector< vector<int> > >::iterator  itor =  rowsMap.begin();
          while(itor != rowsMap.end())
          {
             vector< vector<int> > vectors = itor->second;


             for(int idx = 0; idx < vectors.size()-1; idx++)
             {

                if (lastVector == vectors[idx])
                {
                    lastVector = vectors[idx+1];
                   targetRows.push_back(lastVector);
                   found = true;
                   break;
                }
             }
             if (found) break;
             itor++;
          }

           if (!found)
           {
            cout<<"can not find"<<endl;
            break;
           }
     }



    // return ;
    ofstream outFile;
    char filename[64] = {0};
    sprintf(filename, "result_%dX%d_start_%d_%d.txt", PW, targetHeight, startIndex,1);
    outFile.open(filename);
    for (int y = targetHeight; y >= 0; y--)
    {
        for (int x = 0; x < SW; x++)
        {
            // cout << A[x][y] << "   ";
            outFile << targetRows[y][x] << "   ";
        }
       // cout << endl;
        outFile << endl;
    }

    outFile.close();
       cout<<"finish result  "<<targetRows.size()<<endl;
    /////////////////////////////////////////////////
    }


      map<int, vector< vector <int> > >::iterator colitor;
    for(colitor = columnsMap.begin(); colitor != columnsMap.end(); colitor++)
    {

       int  startIndex = colitor->first;
          cout << "columnsMap start with " << startIndex << endl;
      int targetWidth = 1050;
       vector< vector<int> > targetColumns;
     vector<int> lastVector =  columnsMap[startIndex][1];
     targetColumns.push_back(lastVector);

     for (int index = 0; index < targetWidth; index++)
     {


           bool found = false;
             int num = rand()%5;
          map<int,  vector< vector<int> > >::iterator  itor =  columnsMap.begin();
          while(itor != columnsMap.end())
          {
             vector< vector<int> > vectors = itor->second;

               if (--num>0)
               {
                itor++;
                continue;
               }
             for(int idx = 0; idx < vectors.size()-1; idx++)
             {

                if (lastVector == vectors[idx])
                {
                    lastVector = vectors[idx+1];
                   targetColumns.push_back(lastVector);
                   found = true;
                   break;
                }
             }
             if (found) break;
             itor++;
          }

           if (!found)
           {
             cout<<"can not find "<<index<<endl;
             break;
           }
     }


    // return ;
    ofstream outFile;
    char filename[64] = {0};
    sprintf(filename, "result_%dX%d_start_%d_%d.txt", targetWidth, PH, startIndex,1);
    outFile.open(filename);
    for (int y = 0; y < SH; y++)
    {
        for (int x = 0; x <= targetWidth; x++)
        {
            // cout << A[x][y] << "   ";
            outFile << targetColumns[x][y] << "   ";
        }
       // cout << endl;
        outFile << endl;
    }

    outFile.close();
        cout<<"finish result  "<<targetColumns.size()<<endl;
    }
   /*  cout << "columns count is " << columns.size();
     for(int index = 0; index < columns.size(); index ++)
     {
        bool found = false;
         for(int idx = 0; idx < columns2.size(); idx ++)
       {
           if  (idx != index && columns[index] == columns2[idx])
           {
                //  print_vetor(columns2[idx]);
                     found = true;
                     break;
           }
       }

        if (found == false)
        {
         print_vetor(columns[index]);

        }
     }



       cout << "rows count is " << rows.size();
     for(int index = 0; index < rows.size(); index ++)
     {
        bool found = false;
         for(int idx = 0; idx < rows2.size(); idx ++)
       {
           if  (idx != index && rows[index] == rows2[idx])
           {
                //  print_vetor(columns2[idx]);
                     found = true;
                     break;
           }
       }

        if (found == false)
         {

            print_vetor(rows[index]);
         }
     }  */

    return 0;
}
