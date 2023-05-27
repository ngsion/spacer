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
 #include <iostream>
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
            fileStream >> A[x][y];
        }
      }

    }

   return   true;
}

int main()
{
    PixelHelper pixelHelper = PixelHelper();
    
       pixelHelper.GetAllPossiblePixels();

    pixelHelper.SetMap();
     pixelHelper.ClearPixels();

    pixelHelper.PrintOutAllPixels();
     pixelHelper.SetMap();

    pixelHelper.SetPixelVectors();
    
    
     int len = pixelHelper.pixelArray.size();

    map<int, vector< vector <int> > > columnsMap;
    map<int, vector< vector <int> > > rowsMap;
     vector< vector<int> > columns;
     vector< vector<int> > rows;
       cout << "start with " << len << endl;
    for(int start = 0; start < len; start++)
    {


     //  int start = 1;
        
        
         cout << "start with " << start << endl;
         
        int A[SW][SH];
        char filename[64] = {0};

       sprintf(filename, "result_%dX%d_start_%d.txt", PW, PH, start);
       if (isFileExists_fopen(filename))
       {
          LoadMatrixFileToA(filename,SW, SH,A);
       }
       else
       {
          continue;
       }
      
      for (int xpos = 0; xpos < SW; xpos++)
      {
         vector<int> oneColumn;
         for(int ypos = 0; ypos < SH; ypos++)
         {
           oneColumn.push_back(A[xpos][ypos]);
           //  cout << "a x y " << xpos <<  "  " << ypos << "  " << A[xpos][ypos] <<endl;
         }
         columns.push_back(oneColumn);
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
         rows.push_back(oneRow);
          rowsMap[start].push_back(oneRow);
      }
      
    }
       cout << "columns size  " << columns.size() << "  rows size " << rows.size() << endl;


      cout << "rowsMap size  " << rowsMap.size() << "  columnsMap size " << columnsMap.size() << endl;

      map<int, vector< vector <int> > >::iterator rowitor;
    for(rowitor = rowsMap.begin(); rowitor != rowsMap.end(); rowitor++)
    {
    /////////////////////////////////////////////////

     int startIndex = rowitor->first;
      cout << "rowsMap start with " << startIndex << endl;
      int targetHeight = 768;
       vector< vector<int> > targetRows;
     vector<int> lastVector =  rowsMap[startIndex][0];
     targetRows.push_back(lastVector);

     for (int index = 0; index < targetHeight; index++)
     {

           bool found = false;
          //   int num = rand()%5;
          map<int,  vector< vector<int> > >::iterator  itor =  rowsMap.begin();
          while(itor != rowsMap.end())
          {
             vector< vector<int> > vectors = itor->second;

            /*   if (--num>0)
               {
                itor++;
                continue;
               }  */
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
    sprintf(filename, "result_%dX%d_start_%d_%d.txt", PW, targetHeight, startIndex,0);
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
      int targetWidth = 1024;
       vector< vector<int> > targetColumns;
     vector<int> lastVector =  columnsMap[startIndex][0];
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
    sprintf(filename, "result_%dX%d_start_%d_%d.txt", targetWidth, PH, startIndex,0);
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
