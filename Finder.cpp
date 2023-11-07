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
#define TheRow 3072
#define TheMaxNum 33
#define TheLength 12 ////取前面几个
#define TheRelatedCount 12
#define TheTestInCount 24 /// 判断下一期是否在当前数字的Related序列中,此值小于等于 33

static int target[TheCount][TheRow];
static vector<vector<int>> alltargets;
/// @brief 获取所有历史
void getAllTargets();

/// @brief 加载序列文件
void testNumbers(vector<int> testqi);

static map<int, vector<pair<int, int>>> relatedClosePredict;
/// @brief 计算单个数字后面出现的序列 TheRelatedCount
void calculateRelatedNumbers(vector<int> testqi);

// 判断qishu+1期是否在当前qishu的数字的Related序列中
void testRelatedByQishu(int qishu);
void testRelatedByQishuNext(int qishu);

/// @brief 计算前两期的冷热码
void calculateHotCold(int qishu);

/// @brief 另一种计算方式，单个数字后面的一期6个数字
void calculateAfterByQishu(vector<int> testqi);

/// @brief 获取当期序列
/// @return
vector<int> getVectorByQiShu(int qishu);

int main()
{

    int testQishu = 3071;

    getAllTargets();

    vector<int> testqi = getVectorByQiShu(3071);
    print_vetor(testqi);

    // calculateAfterByQishu(testqi);

    calculateRelatedNumbers(testqi);

    for (int index = 3040; index < testQishu; index++)
    {

        calculateHotCold(index+1);
         testRelatedByQishu(index);
        //  if(index+1 < testQishu)
        // testRelatedByQishuNext(index);
    }
    // testNumbers(testqi);
    return 0;
}

bool LoadMatrixFileToA(const char *fileName, int column, int row, int A[TheW][TheH]);

bool LoadMatrixFileToT(const char *fileName, int column, int row, int A[TheCount][TheRow]);

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

vector<int> getVectorByQiShu(int qishu)
{
    vector<int> onetarget;
    cout << "getVectorByQiShu qishu " << qishu + 1 << endl;

    if (qishu >= 0 && qishu < alltargets.size())
    {
        print_vetor(alltargets[qishu]);
        return alltargets[qishu];
    }

    return onetarget;
}

void getAllTargets()
{
    char filename[64] = {0};
    sprintf(filename, "targets.txt");
    if (isFileExists_fopen(filename))
    {
        LoadMatrixFileToT(filename, TheCount, TheRow, target);
    }

    for (int row = 0; row < TheRow; row++)
    {

        vector<int> onetarget;

        for (int idx = 0; idx < TheCount; idx++)
        {
            onetarget.push_back(target[idx][row]);
            // cout << "is " << target[idx][row] << endl;
        }

        alltargets.push_back(onetarget);
    }
    print_vetor(alltargets.back());
}

void testNumbers(vector<int> testqi)
{
    cout << "testnumbers start" << endl;
    print_vetor(testqi);
    int A[TheW][TheH];
    char filename[64] = {0};

    int intmap[TheH] = {0};
    for (int idx = 0; idx < TheH; idx++)
    {
        intmap[idx] = 0;
    }

    filename[64] = {0};
    sprintf(filename, "numbers.txt");
    if (isFileExists_fopen(filename))
    {

        LoadMatrixFileToA(filename, TheW, TheH, A);
    }

    for (int count = 0; count < TheH; count++)
    {
        bool foundall = true;

        for (int index = 0; index < testqi.size(); index++)
        {
            bool found = false;
            for (int idx = 0; idx < TheW; idx++)
            {
                if (testqi[index] == A[idx][count])
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                foundall = false;
                break;
            }
        }

        if (foundall)
        {
            cout << "find in index " << count << endl;
        }
        else
        {
            cout << "can not find in index " << count << endl;
        }
    }
}

void testRelatedByQishu(int qishu)
{
    cout << "testRelatedByQishu" << endl;
    vector<int> currentQi = getVectorByQiShu(qishu);
    vector<int> nextQi = getVectorByQiShu(qishu + 1);
    for (int index = 0; index < TheCount; index++)
    {
        int number = currentQi[index];
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        //    cout << "testRelatedByQishu " << number<<endl;
        //      for (int i = 0; i < dVector.size(); i++)
        //     {
        //         cout << dVector[i].first << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < dVector.size(); i++)
        //     {
        //         cout << dVector[i].second << " ";
        //     }

        int foundCount = 0;

        for (int count = 0; count < TheCount; count++)
        {
            int findNumber = nextQi[count];

            // cout << " findNumber " << findNumber <<endl;
            // for (int i = 0; i < dVector.size(); i++)
            // {
            //     cout <<  dVector[i].first << " ";
            // }
            //  cout << " findNumber end" << findNumber <<endl;

            for (int i = 0; i < TheTestInCount; i++)
            {
                //  cout << " findNumber  " << findNumber << " i " << i <<  " dVector[i].first  " << dVector[i].first <<endl;
                if (findNumber == dVector[i].first)
                {
                    ++foundCount;
                    break;
                }
            }
        }

        if (foundCount == TheCount)
        {
            cout << " test qishu " << qishu << "  foundAll 1 "
                 << " at " << index << " number is " << number << " foundCount is " << foundCount << " TheTestInCount is " << TheTestInCount << endl;
            // break;
        }
        else
        {
            cout << " test qishu " << qishu << "  foundAll 0 "
                 << " at " << index << " number is " << number << " foundCount is " << foundCount << " TheTestInCount is " << TheTestInCount << endl;
        }
    }
}

void testRelatedByQishuNext(int qishu)
{
    cout << "testRelatedByQishuNext" << endl;
    vector<int> currentQi = getVectorByQiShu(qishu);
    vector<int> nextQi = getVectorByQiShu(qishu + 2);
    for (int index = 0; index < TheCount; index++)
    {
        int number = currentQi[index];
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        //    cout << "testRelatedByQishu " << number<<endl;
        //      for (int i = 0; i < dVector.size(); i++)
        //     {
        //         cout << dVector[i].first << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < dVector.size(); i++)
        //     {
        //         cout << dVector[i].second << " ";
        //     }

        int foundCount = 0;

        for (int count = 0; count < TheCount; count++)
        {
            int findNumber = nextQi[count];

            // cout << " findNumber " << findNumber <<endl;
            // for (int i = 0; i < dVector.size(); i++)
            // {
            //     cout <<  dVector[i].first << " ";
            // }
            //  cout << " findNumber end" << findNumber <<endl;

            for (int i = 0; i < TheTestInCount; i++)
            {
                //  cout << " findNumber  " << findNumber << " i " << i <<  " dVector[i].first  " << dVector[i].first <<endl;
                if (findNumber == dVector[i].first)
                {
                    ++foundCount;
                    break;
                }
            }
        }

        if (foundCount == TheCount)
        {
            cout << " test qishu " << qishu << "  foundAll 1 "
                 << " at " << index << " number is " << number << " foundCount is " << foundCount << " TheTestInCount is " << TheTestInCount << endl;
            // break;
        }
        else
        {
            cout << " test qishu " << qishu << "  foundAll 0 "
                 << " at " << index << " number is " << number << " foundCount is " << foundCount << " TheTestInCount is " << TheTestInCount << endl;
        }
    }
}

void calculateHotCold(int qishu)
{
    cout << "----------calculateHotCold " << qishu << endl;
    vector<int> oldQi = getVectorByQiShu(qishu - 2);
    vector<int> lastQi = getVectorByQiShu(qishu - 1);
    
    vector<int> hotresult;

    int number = lastQi[0];
    vector<pair<int, int>> dVector = relatedClosePredict[number];
    for (int index = 0; index < 24; index++)
    {
        int testNumber = dVector[index].first;
        bool found = true;
        for (int idx = 1; idx < TheCount; idx++)
        {
            int number2 = lastQi[idx];
            vector<pair<int, int>> dVector2 = relatedClosePredict[number2];
            bool isIn = false;
            for (int i = 0; i < 24; i++)
            {
                //  cout << " findNumber  " << findNumber << " i " << i <<  " dVector[i].first  " << dVector[i].first <<endl;
                if (testNumber == dVector2[i].first)
                {
                    isIn = true;
                    break;
                }
            }
            if (!isIn)
            {
                found = false;
                break;
            }
        }

        if (found)
        {

            for (int idx = 0; idx < TheCount; idx++)
            {
                int number2 = oldQi[idx];
                vector<pair<int, int>> dVector2 = relatedClosePredict[number2];
                bool isIn = false;
                for (int i = 0; i < 24; i++)
                {
                    //  cout << " findNumber  " << findNumber << " i " << i <<  " dVector[i].first  " << dVector[i].first <<endl;
                    if (testNumber == dVector2[i].first)
                    {
                        isIn = true;
                        break;
                    }
                }
                if (!isIn)
                {
                    found = false;
                    break;
                }
            }
        }
        if (found)
        {
            hotresult.push_back(testNumber);
        }
    }
 cout << "HotCode:  ";
    print_vetor(hotresult);

    vector<int> coldresult;

     number = lastQi[0];
    dVector = relatedClosePredict[number];
    for (int index = 9; index < 33; index++)
    {
        int testNumber = dVector[index].first;
        bool found = true;
        for (int idx = 1; idx < TheCount; idx++)
        {
            int number2 = lastQi[idx];
            vector<pair<int, int>> dVector2 = relatedClosePredict[number2];
            bool isIn = false;
            for (int i = 9; i < 33; i++)
            {
                //  cout << " findNumber  " << findNumber << " i " << i <<  " dVector[i].first  " << dVector[i].first <<endl;
                if (testNumber == dVector2[i].first)
                {
                    isIn = true;
                    break;
                }
            }
            if (!isIn)
            {
                found = false;
                break;
            }
        }

        if (found)
        {

            for (int idx = 0; idx < TheCount; idx++)
            {
                int number2 = oldQi[idx];
                vector<pair<int, int>> dVector2 = relatedClosePredict[number2];
                bool isIn = false;
                for (int i = 9; i < 33; i++)
                {
                    //  cout << " findNumber  " << findNumber << " i " << i <<  " dVector[i].first  " << dVector[i].first <<endl;
                    if (testNumber == dVector2[i].first)
                    {
                        isIn = true;
                        break;
                    }
                }
                if (!isIn)
                {
                    found = false;
                    break;
                }
            }
        }
        if (found)
        {
            coldresult.push_back(testNumber);
        }
    }

cout << "ColdCode:  ";
    print_vetor(coldresult);
    
    getVectorByQiShu(qishu);
     cout << "----------calculateHotCold end " << qishu << endl;
}

void calculateRelatedNumbers(vector<int> testqi)
{

    map<int, vector<int>> relativeNumbers;

    map<int, vector<int>> allPredict;
    for (int idx = 0; idx < TheCount; idx++)
    {
        vector<int> onePredict;
        allPredict[testqi[idx]] = onePredict;
    }
    map<int, int> anotherPredict;
    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        anotherPredict[idx] = 0;
    }

    vector<int> allNumbers;
    for (int idx = 0; idx < alltargets.size(); idx++)
    {
        vector<int> onetarget = alltargets[idx];
        allNumbers.insert(allNumbers.end(), onetarget.begin(), onetarget.end());
    }

    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        vector<int> one;
        relativeNumbers[idx + 1] = one;
    }
    int maxnumbers = allNumbers.size();
    for (int idx = 0; idx < maxnumbers; idx++)
    {

        int number = allNumbers[idx];

        for (int pos = idx + 1, count = TheRelatedCount; pos<maxnumbers, count> 0; pos++, count--)
        {
            if (pos >= maxnumbers - 1)
            {
                break;
            }
            int onenumber = allNumbers[pos];

            relativeNumbers[number].push_back(onenumber);
        }
    }

    for (auto it = relativeNumbers.begin(); it != relativeNumbers.end(); it++)
    {

        int number = it->first;
        map<int, int> predict;
        for (int idx = 0; idx < TheMaxNum; idx++)
        {
            predict[idx + 1] = 0;
        }

        for (auto itor = it->second.begin(); itor != it->second.end(); itor++)
        {
            predict[*itor] = predict[*itor] + 1;
        }
        cout << " after number " << number << endl;
        vector<pair<int, int>> dVector;
        sortMapByValue(predict, dVector);
        for (int i = 0; i < dVector.size(); i++)
        {
            cout << dVector[i].first << " ";
        }
        cout << endl;
        for (int i = 0; i < dVector.size(); i++)
        {
            cout << dVector[i].second << " ";
        }
        relatedClosePredict[number] = dVector;
        cout << endl;
        cout << endl;
        dVector.clear();

        for (int idx = 0; idx < TheCount; idx++)
        {
            if (number == testqi[idx])
            {
                // cout << " findNumber is " << findNumber << endl;
                for (int i = 0; i < TheLength; i++)
                {
                    allPredict[testqi[idx]].push_back(dVector[i].first);
                    //  allPredict[testNumber[idx]].push_back(bVector[i].first + 1);
                    //  allPredict[testNumber[idx]].push_back(cVector[i].first + 1);

                    // cout << " first " << cVector[i].first << "  sedond " << cVector[i].second << endl;
                    // anotherPredict[cVector[i].first] += cVector[i].second;
                    anotherPredict[dVector[i].first] += dVector[i].second;
                    // anotherPredict[bVector[i].first] += bVector[i].second;
                }
            }
        }
    }

    map<int, int> predictCount;
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

    for (auto it = predictCount.begin(); it != predictCount.end(); it++)
    {
        cout << it->first << " " << it->second << " " << endl;
    }
    // vector<pair<int, int>> dVector;
    // sortMapByValue(predictCount, dVector);
    // for (int i = 0; i < dVector.size(); i++)
    //     cout << dVector[i].first << " " << dVector[i].second << " " << endl;

    cout << "another predict " << endl;
    for (auto itor = anotherPredict.begin(); itor != anotherPredict.end(); itor++)
    {
        cout << itor->first << " " << itor->second << endl;
    }
}

void calculateAfterByQishu(vector<int> testqi)
{
    map<int, int> beforeCount;
    map<int, int> currentCount;
    map<int, int> afterCount;

    ////////////////////////////////////////
    cout << "test alltargets.size() " << alltargets.size() << endl;

    map<int, vector<int>> allPredict;
    for (int idx = 0; idx < TheCount; idx++)
    {
        vector<int> onePredict;
        allPredict[testqi[idx]] = onePredict;
    }

    map<int, int> predictCount;

    map<int, int> anotherPredict;
    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        anotherPredict[idx + 1] = 0;
    }

    for (int number = 0; number < TheMaxNum; number++)
    {
        int findNumber = number + 1;
        //  cout << "findNumber  start " << findNumber << endl;
        for (int idx = 0; idx < TheMaxNum; idx++)
        {
            beforeCount[idx + 1] = 0;
            currentCount[idx + 1] = 0;
            afterCount[idx + 1] = 0;
        }

        for (int idx = 0; idx < alltargets.size(); idx++)
        {
            vector<int> onetarget = alltargets[idx];

            for (int index = 0; index < onetarget.size(); index++)
            {
                if (onetarget[index] == findNumber)
                {
                    for (int count = 0; count < onetarget.size(); count++)
                    {
                        ++currentCount[onetarget[count]];
                    }

                    if (idx >= 1)
                    {
                        vector<int> beforetarget = alltargets[idx - 1];
                        for (int count = 0; count < beforetarget.size(); count++)
                        {
                            ++beforeCount[beforetarget[count]];
                        }
                    }

                    if (idx < alltargets.size() - 1)
                    {
                        vector<int> aftertarget = alltargets[idx + 1];
                        for (int count = 0; count < aftertarget.size(); count++)
                        {
                            ++afterCount[aftertarget[count]];
                        }
                    }
                    break;
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

        {
            cout << "before" << findNumber << endl;
            for (int i = 0; i < bVector.size(); i++)
                cout << bVector[i].first << " ";
            cout << endl;
            for (int i = 0; i < bVector.size(); i++)
                cout << bVector[i].second << " ";

            //  for (auto it = beforeCount.begin(); it != beforeCount.end(); it++)
            // {
            //     cout << " " << 1+it->first << "   " << it->second<< endl;
            // }
            cout << endl;

            cout << "current" << findNumber << endl;

            //  for (auto it = currentCount.begin(); it != currentCount.end(); it++)
            // {
            //     cout << " " << 1+it->first << "   " << it->second<< endl;
            // }
            for (int i = 0; i < cVector.size(); i++)
                cout << cVector[i].first << " ";
            cout << endl;
            for (int i = 0; i < cVector.size(); i++)
                cout << cVector[i].second << " ";

            cout << endl;

            cout << "after" << findNumber << endl;
            //  for (auto it = afterCount.begin(); it != afterCount.end(); it++)
            // {
            //     cout << " " << 1+it->first << "   " << it->second<< endl;
            // }

            for (int i = 0; i < aVector.size(); i++)
                cout << aVector[i].first << " ";
            cout << endl;
            for (int i = 0; i < aVector.size(); i++)
                cout << aVector[i].second << " ";

            cout << endl;
            cout << endl;
        }

        for (int idx = 0; idx < TheCount; idx++)
        {
            if (findNumber == testqi[idx])
            {
                // cout << " findNumber is " << findNumber << endl;
                for (int i = 0; i < TheLength; i++)
                {
                    allPredict[testqi[idx]].push_back(aVector[i].first);
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

    for (auto it = predictCount.begin(); it != predictCount.end(); it++)
    {
        cout << it->first << " " << it->second << " " << endl;
    }
    // vector<pair<int, int>> dVector;
    // sortMapByValue(predictCount, dVector);
    // for (int i = 0; i < dVector.size(); i++)
    //     cout << dVector[i].first << " " << dVector[i].second << " " << endl;

    cout << "another predict " << endl;
    for (auto itor = anotherPredict.begin(); itor != anotherPredict.end(); itor++)
    {
        cout << itor->first << " " << itor->second << endl;
    }
}