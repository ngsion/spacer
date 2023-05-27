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
    pixelHelper.PrintOutAllPixels();
   // pixelHelper.SetMapWithoutValue();
     //pixelHelper.ClearPixels();


    pixelHelper.SetMap();
     pixelHelper.SetPixelVectors();


   //  int len = pixelHelper.pixelArray.size();
   int len = 585304;

    map<int, vector< vector <int> > > columnsMap;
    map<int, vector< vector <int> > > rowsMap;


     
    cout << "start with " << len << endl;
    for(int start = 0; start < len; start++)
    {


     //  int start = 1;


       //  cout << "start with " << start << endl;

        int A[SW][SH];
        char filename[64] = {0};
        
        vector<int> rowTop;
        vector<int> rowBottom;
        vector<int> colLeft;
        vector<int> colRight;

       sprintf(filename, "new9/result_%dX%d_start_%d.txt", PW, PH, start);
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

         columnsMap[start].push_back(oneColumn);
         if (0 == xpos) colLeft = oneColumn;
          if (xpos == SW-1) colRight = oneColumn;
      }

       for (int ypos = 0; ypos < SH; ypos++)
      {
         vector<int> oneRow;
         for(int xpos = 0; xpos < SW; xpos++)
         {
            oneRow.push_back(A[xpos][ypos]);
           //  cout << "a x y " << xpos <<  "  " << ypos << "  " << A[xpos][ypos] <<endl;
         }
      //  if (start == 12)   print_vetor(oneRow);
          rowsMap[start].push_back(oneRow);
           if (0 == ypos) rowTop = oneRow;
          if (ypos == SH-1) rowBottom = oneRow;
      }
    //  print_vetor(rowBottom);
      if (rowTop == rowBottom)
      {
          cout << "hey get a row start  " << start << endl;
      }

    }

      cout << "rowsMap size  " << rowsMap.size() << "  columnsMap size " << columnsMap.size() << endl;

      //////////////////////////////
      /////////////////////////////////
   

    int targetHeight = 769;
      map<int, vector< vector <int> > >::iterator rowitor;
    for(rowitor = rowsMap.begin(); rowitor != rowsMap.end(); rowitor++)
    {
    /////////////////////////////////////////////////

      int startIndex = rowitor->first;
    //  cout << "rowsMap start with " << startIndex << endl;
     
       vector< vector<int> > targetRows;
    
      for ( int idx = 0; idx < rowsMap[startIndex].size(); idx++ )
     {
         if (targetRows.size() < targetHeight) targetRows.push_back(rowsMap[startIndex][idx]);
     }
     vector<int> lastVector =  rowsMap[startIndex].back();

     while (targetRows.size() < targetHeight)
     {

           bool found = false;
            
          map<int,  vector< vector<int> > >::iterator  itor =  rowsMap.begin();
          while(itor != rowsMap.end())
          {
             vector< vector<int> > vectors = itor->second;
             int  startIdx = itor->first;
          

                if (lastVector == vectors[0])
                {
                  //   cout << "rowsMap ends conbines with " << startIdx << endl;
                     
                        print_vetor(lastVector);
                         print_vetor(vectors[0]);
                      for ( int idx = 1; idx < rowsMap[startIdx].size(); idx++ )
                      {
                        if (targetRows.size() < targetHeight) targetRows.push_back(rowsMap[startIdx][idx]);
                      }
                   lastVector =  rowsMap[startIdx].back();
                   found = true;
                   break;
                }
             
             itor++;
          }

           if (!found)
           {
            cout<<"can not find failture  "<< startIndex << endl;
            break;
           }
     }
   //   cout << "targetRows start with size " << targetRows.size() << endl;

       if (targetRows.size() < targetHeight)
     {
        continue;
     }

    // return ;
    ofstream outFile;
    char filename[64] = {0};
    sprintf(filename, "result_%dX%d_start_%d.txt", PW, targetHeight-1, startIndex);
    outFile.open(filename);
    for (int y = targetHeight-1; y >= 0; y--)
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
    
    
      cout<<"finish result  fsfsdfsfsfdsfdsfsfd" <<endl;
    
    }


 /////////////////////////////////////////////////
/////////////////////////////////////////////////

   /*  int targetWidth = 1025;
     map<int, vector< vector <int> > >::iterator colitor;
    for(colitor = columnsMap.begin(); colitor != columnsMap.end(); colitor++)
    {


       int  startIndex = colitor->first;

      vector< vector<int> > targetColumns;


     for ( int idx = 0; idx < columnsMap[startIndex].size(); idx++ )
     {
         if (targetColumns.size() < targetWidth) targetColumns.push_back(columnsMap[startIndex][idx]);
     }
     vector<int> lastVector =  columnsMap[startIndex].back();

          cout << "columnsMap start with " << startIndex  << "  targetColumns size " << targetColumns.size()<< endl;

     while (targetColumns.size() < targetWidth)
     {

         //  print_vetor(lastVector);
           bool found = false;
          map<int,  vector< vector<int> > >::iterator  itor =  columnsMap.begin();
          while(itor != columnsMap.end())
          {
             vector< vector<int> > vectors = itor->second;
               int  startIdx = itor->first;


                if (lastVector == vectors[0])
                {
                    for ( int idx = 1; idx < columnsMap[startIdx].size(); idx++ )
                   {
                       if (targetColumns.size() < targetWidth) targetColumns.push_back(columnsMap[startIdx][idx]);
                   }
                   lastVector =  columnsMap[startIdx].back();
                   found = true;
                   break;
                }
                itor++;
          }

           if (!found)
           {
             cout<<"can not find result, failed "<<startIndex<<endl;
             break;
           }
     }

     cout << "columnsMap start with size " << targetColumns.size() << endl;
     
      if (targetColumns.size() < targetWidth)
     {
        continue;
     }
    // return ;
    ofstream outFile;
    char filename[64] = {0};
    sprintf(filename, "result_%dX%d_start_%d.txt", targetWidth-1, PH, startIndex);
    outFile.open(filename);
    for (int y = SH-1; y >=0; y--)
    {
        for (int x = 0; x < targetWidth; x++)
        {
           //  cout << targetColumns[x][y] << "   ";
            outFile << targetColumns[x][y] << "   ";
        }
      //  cout << endl;
        outFile << endl;
    }
    


    outFile.close();
    

    
        cout<<"finish result  gooooood "<< endl;
    }
       */

    return 0;
}
