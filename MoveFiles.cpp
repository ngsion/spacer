  #include <iostream>
  #include <fstream>
  #include <windows.h>
    #include "Utility.h"
    
  int main()
  {
    std::cout << "hello "<<endl;


    for (int start = 1300000; start < 1500000; start++)
    {


      char filename[64] = {0};
       char filename2[64] = {0};
       sprintf(filename, "result_%dX%d_start_%d.txt", 11, 11, start);
        sprintf(filename2, "1111/result_%dX%d_start_%d.txt", 11, 11, start);
       if (isFileExists_fopen(filename))
       {
          int ret = MoveFile(filename, filename2);
           std::cout << "hello  finish"<<endl;
       }
       else
       {
          continue;
           std::cout << "hello  222"<<endl;
       }
    }
    std::cout << "hello  finish"<<endl;
  }
