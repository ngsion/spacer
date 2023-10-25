#include <iostream>
#include "PixelHelper.h"
#include "Screen.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <iterator>
#include <stdio.h>
#include <string>
#include <stdbool.h>
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;
#define TheW 24
#define TheH 4
#define TheCount 6
#define TheRow 3065
#define TheMaxNum 33
#define TheLength 12 ////取前面几个
bool LoadMatrixFileToA(const char *fileName, int column, int row, int A[TheW][TheH])
{

    ifstream fileStream;

    fileStream.open(fileName, std::ios::in);

    if (fileStream.fail())
    {
        cout << "read file failed " << fileName << endl;
        return false;
    }
    else
    {

        for (int y = 0; y < row; y++)
        {
            for (int x = 0; x < column; x++)
            {
                fileStream >> A[x][y];
                //  cout<<" hello " <<  A[x][y];
                //  cout << "a x y " << x <<  "  " << y << "  " << A[x][y] <<endl;
            }
        }
    }

    return true;
}
bool LoadMatrixFileToT(const char *fileName, int column, int row, int A[TheCount][TheRow])
{

    ifstream fileStream;

    fileStream.open(fileName, std::ios::in);

    if (fileStream.fail())
    {
        cout << "read file failed " << fileName << endl;
        return false;
    }
    else
    {

        for (int y = 0; y < row; y++)
        {
            for (int x = 0; x < column; x++)
            {
                fileStream >> A[x][y];
                //   cout<<" hello " <<  A[x][y];
            }
        }
    }

    return true;
}
int cmp(const pair<int, int> &x, const pair<int, int> &y)
{
    return x.second > y.second;
}

void sortMapByValue(map<int, int> &tMap, vector<pair<int, int>> &tVector)
{
    for (map<int, int>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
        tVector.push_back(make_pair(curr->first, curr->second));

    sort(tVector.begin(), tVector.end(), cmp);
}

int main()
{
    int A[TheW][TheH];
    char filename[64] = {0};

    int target[TheCount][TheRow];

    int intmap[TheH] = {0};
    for (int idx = 0; idx < TheH; idx++)
    {
        intmap[idx] = 0;
    }

    int testQishu = 3054;
    
    vector<int> testNumber;
    testNumber.push_back(2);
    testNumber.push_back(11);
    testNumber.push_back(14);
    testNumber.push_back(17);
    testNumber.push_back(18);
    testNumber.push_back(28);

    map<int, int> beforeCount;
    map<int, int> currentCount;
    map<int, int> afterCount;

    sprintf(filename, "targets.txt");
    if (isFileExists_fopen(filename))
    {
        LoadMatrixFileToT(filename, TheCount, TheRow, target);
    }

    vector<vector<int>> alltargets;

    filename[64] = {0};
    sprintf(filename, "numbers.txt");
    if (isFileExists_fopen(filename))
    {

        LoadMatrixFileToA(filename, TheW, TheH, A);
    }

    vector<int> sigleColumn;
    int nomatchcount = 0;

    for (int row = 0; row < TheRow; row++)
    {

        vector<int> onetarget;
        vector<int> oneColumn;

        for (int idx = 0; idx < TheCount; idx++)
        {
            onetarget.push_back(target[idx][row]);
            // cout << "is " << target[idx][row] << endl;
        }

        alltargets.push_back(onetarget);

        for (int ypos = 0; ypos < TheH; ypos++)
        {

            bool match = true;

            for (int idx = 0; idx < TheCount; idx++)
            {

                bool found = false;
                for (int xpos = 0; xpos < TheW; xpos++)
                {
                    if (A[xpos][ypos] == target[idx][row])
                    {
                        found = true;
                        break;
                    }
                    //   cout << "a x y " << xpos <<  "  " << ypos << "  " << A[xpos][ypos] <<endl;
                }
                if (!found)
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                oneColumn.push_back(ypos + 1);
                ++intmap[ypos];
            }
        }

        if (oneColumn.size() >= 1)
        {
            // sigleColumn.push_back(oneColumn.back());
            //    print_vetor(onetarget);
            //  cout << "matchs " ;
            //   print_vetor(oneColumn);
            //  cout << " " << endl;
        }
        else
        {
            //  print_vetor(onetarget);
            //  cout << " no matchs " <<endl ;
            nomatchcount++;
        }
    }

    for (int idx = 0; idx < TheH; idx++)
    {
        // cout << " " << idx + 1 << "   " << intmap[idx] << endl;
    }
    // cout << " nomatchcount " << nomatchcount << endl;
    // print_vetor(sigleColumn);

    ////////////////////////////////////////
     cout << "test alltargets.size() " << alltargets.size() << endl;
    map<int, vector<int>> allPredict;
    for (int idx = 0; idx < alltargets.size(); idx++)
    {
        vector<int> onetarget = alltargets[idx];

        if (idx == testQishu)
        {
            testNumber = onetarget;
            cout << "test qishu " << testQishu+1 << endl;
            print_vetor(onetarget);
        }
    }
    for (int idx = 0; idx < TheCount; idx++)
    {
        vector<int> onePredict;
        allPredict[testNumber[idx]] = onePredict;
    }
    map<int, int> predictCount;

    map<int, int> anotherPredict;
    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        anotherPredict[idx] = 0;
    }
    for (int number = 0; number < TheMaxNum; number++)
    {
        int findNumber = number + 1;
        for (int idx = 0; idx < TheMaxNum; idx++)
        {
            beforeCount[idx] = 0;
            currentCount[idx] = 0;
            afterCount[idx] = 0;
        }

        for (int idx = 0; idx < alltargets.size(); idx++)
        {
            vector<int> onetarget = alltargets[idx];

            for (int index = 0; index < onetarget.size(); index++)
            {
                if (onetarget[index] == findNumber)
                {
                    for (int index = 0; index < onetarget.size(); index++)
                    {
                        currentCount[onetarget[index] - 1] = currentCount[onetarget[index] - 1] + 1;
                    }

                    if (idx >= 1)
                    {
                        vector<int> beforetarget = alltargets[idx - 1];
                        for (int index = 0; index < beforetarget.size(); index++)
                        {
                            beforeCount[beforetarget[index] - 1] = beforeCount[beforetarget[index] - 1] + 1;
                        }
                    }

                    if (idx < alltargets.size() - 1)
                    {
                        vector<int> aftertarget = alltargets[idx + 1];
                        for (int index = 0; index < aftertarget.size(); index++)
                        {
                            afterCount[aftertarget[index] - 1] = afterCount[aftertarget[index] - 1] + 1;
                        }
                    }
                }
            }
            // cout << "is " << target[idx][row] << endl;
        }

        // sort(beforeCount.begin(),beforeCount.end(),cmp);
        // sort(currentCount.begin(),currentCount.end(),cmp);
        // sort(afterCount.begin(),afterCount.end(),cmp);
        vector<pair<int, int>> bVector;
        sortMapByValue(beforeCount, bVector);

        vector<pair<int, int>> cVector;
        sortMapByValue(currentCount, cVector);

        vector<pair<int, int>> aVector;
        sortMapByValue(afterCount, aVector);

        // {
        //     cout << "before" << findNumber << endl;
        //     for (int i = 0; i < bVector.size(); i++)
        //         cout << 1 + bVector[i].first << " ";
        //     cout << endl;
        //     for (int i = 0; i < bVector.size(); i++)
        //         cout << bVector[i].second << " ";

        //     //  for (auto it = beforeCount.begin(); it != beforeCount.end(); it++)
        //     // {
        //     //     cout << " " << 1+it->first << "   " << it->second<< endl;
        //     // }
        //     cout << endl;

        //     cout << "current" << findNumber << endl;

        //     //  for (auto it = currentCount.begin(); it != currentCount.end(); it++)
        //     // {
        //     //     cout << " " << 1+it->first << "   " << it->second<< endl;
        //     // }
        //     for (int i = 0; i < cVector.size(); i++)
        //         cout << 1 + cVector[i].first << " ";
        //     cout << endl;
        //     for (int i = 0; i < cVector.size(); i++)
        //         cout << cVector[i].second << " ";

        //     cout << endl;

        //     cout << "after" << findNumber << endl;
        //     //  for (auto it = afterCount.begin(); it != afterCount.end(); it++)
        //     // {
        //     //     cout << " " << 1+it->first << "   " << it->second<< endl;
        //     // }
        //     sortMapByValue(afterCount, aVector);
        //     for (int i = 0; i < aVector.size(); i++)
        //         cout << 1 + aVector[i].first << " ";
        //     cout << endl;
        //     for (int i = 0; i < aVector.size(); i++)
        //         cout << aVector[i].second << " ";

        //     cout << endl;
        //     cout << endl;
        // }

        for (int idx = 0; idx < TheCount; idx++)
        {
            if (findNumber == testNumber[idx])
            {
                // cout << " findNumber is " << findNumber << endl;
                for (int i = 0; i < TheLength; i++)
                {
                    allPredict[testNumber[idx]].push_back(aVector[i].first + 1);
                   //  allPredict[testNumber[idx]].push_back(bVector[i].first + 1);
                  //  allPredict[testNumber[idx]].push_back(cVector[i].first + 1);

                    // cout << " first " << cVector[i].first << "  sedond " << cVector[i].second << endl;
                   // anotherPredict[cVector[i].first] += cVector[i].second;
                    anotherPredict[aVector[i].first] += aVector[i].second;
                    // anotherPredict[bVector[i].first] += bVector[i].second;
                }
            }
        }

        aVector.clear();
        bVector.clear();
        cVector.clear();
    }

    for (auto it = allPredict.begin(); it != allPredict.end(); it++)
    {
        cout << " " << it->first << "   " << endl;
        print_vetor(it->second);
        for (auto itor = it->second.begin(); itor != it->second.end(); itor++)
        {
            int value = *itor;
            if (predictCount.find(value) == predictCount.end())
            {
                predictCount[value] = 0;
            }
            // cout << " value " << value << "   " << predictCount[value];
            predictCount[value] = predictCount[value] + 1;
        }
    }

    vector<pair<int, int>> dVector;
    sortMapByValue(predictCount, dVector);
    for (int i = 0; i < dVector.size(); i++)
        cout << dVector[i].first << " " << dVector[i].second << " " << endl;

    cout << "another predict " << endl;
    for (auto itor = anotherPredict.begin(); itor != anotherPredict.end(); itor++)
    {
        cout << 1 + itor->first << " " << itor->second << endl;
    }

    return 0;
}