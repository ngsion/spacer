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
#define TheMaxRow 3082
#define TheMaxNum 33
#define TheLength 12 ////取前面几个
#define TheRelatedCount 12
#define TheTestInCount 24 /// 判断下一期是否在当前数字的Related序列中,此值小于等于 33

static int maxrowcount = 471;

static int target[TheCount][TheMaxRow];
static vector<vector<int>> alltargets;
/// @brief 获取所有历史
void getAllTargets();

static map<int, vector<pair<int, int>>> relatedClosePredict;
/// @brief 计算单个数字后面出现的序列 TheRelatedCount
void geteRelatedNumbers();

/// @brief 加载序列文件
void testNumbers(vector<int> testqi);

/// @brief  取一组的后面出现的序列，TheLength 个
void calculateRelatedNumbers(vector<int> testqi);

// 判断qishu+1期是否在当前qishu的数字的Related序列中
void testRelatedByQishu(int qishu);
void testRelatedByQishuNext(int qishu);

/// @brief 计算某一期的差值
void calculateDifference(int qishu);

/// @brief 计算前两期的冷热码
void calculateHotCold(int qishu);

/// @brief 另一种计算方式，单个数字后面的一期6个数字
void calculateAfterByQishu(vector<int> testqi);

/// @brief 另一种计算方式，取两个数字后面一期6个数字
void calculateAfterByQishuAgain(vector<int> testqi);

/// @brief 获取当期序列
/// @return
vector<int> getVectorByQiShu(int qishu);

/// @brief测试序列
/// @param qishu
void testThreeByQishu(int qishu);
void testThreeWithVector(vector<int> data, int qishu);

static ofstream outFile;
/// yilou
void calculateYiLou();

void testKill(int qishu);

void doubleKill(int qishu);

int main()
{

    char filename[64] = {0};

    sprintf(filename, "results");

    outFile.open(filename);

    // for (maxrowcount = 100; maxrowcount < 500; maxrowcount++)
    {

        int maxQishu = maxrowcount - 1;

        getAllTargets();

        vector<int> testqi = getVectorByQiShu(maxQishu);

        geteRelatedNumbers();

        // calculateYiLou();

        // calculateRelatedNumbers(testqi);
        //{1,2, 19 , 21, 26, 28};
        //    vector<int> data = {26, 22,  7,  20,2 ,12,  9,   15, 10};
        //  testThreeWithVector( data, maxQishu);

        //  calculateDifference(maxQishu);
        //   calculateHotCold(maxQishu);
         //testKill(maxQishu);

       // doubleKill(maxQishu);

        for (int index = maxQishu - 100; index < maxQishu; index++)
        {
           // testKill(index);
             doubleKill(index);
            // testThreeByQishu(index);
            //  calculateHotCold(index);
            //    testRelatedByQishu(index);
            // if(index+1 < maxQishu)
            // testRelatedByQishuNext(index);
        }
        // testNumbers(testqi);

        // calculateAfterByQishu(testqi);
        //  calculateAfterByQishuAgain(testqi);
    }

    outFile.close();

    return 0;
}

bool LoadMatrixFileToA(const char *fileName, int column, int row, int A[TheW][TheH]);

bool LoadMatrixFileToT(const char *fileName, int column, int row, int A[TheCount][TheMaxRow]);

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

void testKill(int qishu)
{
    vector<int> testqi = getVectorByQiShu(qishu);
    sort(testqi.begin(), testqi.end());
    vector<int> killVector;
    int A = testqi[0];
    int B = testqi[1];
    int C = testqi[2];
    int D = testqi[3];
    int E = testqi[4];
    int F = testqi[5];
    killVector.push_back(A + B + 1);
    killVector.push_back(B - A);
    killVector.push_back((D + A) % 33);
    killVector.push_back(E - C);
    killVector.push_back(F - A + 1);
    killVector.push_back(F - C);
    killVector.push_back(F - B + 7);
    killVector.push_back(D - A);
    killVector.push_back((int)(A + B + C) / 3);
    killVector.push_back((int)(B + C + D + E) / 6);

    sort(killVector.begin(), killVector.end());
    killVector.erase(unique(killVector.begin(), killVector.end()), killVector.end());

    for (auto it = killVector.begin(); it != killVector.end(); it++)
    {
        if (*it == 0)
        {
            *it = 33;
            break;
        }
    }
    sort(killVector.begin(), killVector.end());

    cout << "testKill : ";
    print_vetor(killVector);

    if (qishu < maxrowcount)
    {
        vector<int> nextqi = getVectorByQiShu(qishu + 1);
        vector<int> array = vector_intersection(killVector, nextqi);
         if (array.size() == 3 || array.size() == 1 || array.size() == 2)
        {
            cout << "testKill  ok " << qishu << endl;
        }
        else
        {
            cout << "testKill  failed " << qishu << endl;
        }
    }
}

void doubleKill(int qishu)
{
    vector<int> testqi = getVectorByQiShu(qishu);
    sort(testqi.begin(), testqi.end());
    vector<int> killVector;

    for (int index = 0; index < testqi.size(); index++)
    {
        int A = testqi[index];
        killVector.push_back((2 * A) % 33);
        killVector.push_back((3 * A) % 33);
        killVector.push_back((4 * A) % 33);
        killVector.push_back((5 * A) % 33);
    }

    sort(killVector.begin(), killVector.end());
    killVector.erase(unique(killVector.begin(), killVector.end()), killVector.end());

    for (auto it = killVector.begin(); it != killVector.end(); it++)
    {
        if (*it == 0)
        {
            *it = 33;
            break;
        }
    }
    sort(killVector.begin(), killVector.end());

    cout << "double kill ";
    print_vetor(killVector);

    if (qishu < maxrowcount)
    {
        vector<int> nextqi = getVectorByQiShu(qishu + 1);
        vector<int> array = vector_intersection(killVector, nextqi);
        if (array.size() == 3 || array.size() == 4 || array.size() == 2)
        {
            cout << "double kill ok " << qishu << endl;
           
        }
        else
        {
             cout << "double kill failed " << qishu << endl;
        }
    }
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

bool LoadMatrixFileToT(const char *fileName, int column, int row, int A[TheCount][TheMaxRow])
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
    cout << "getVectorByQiShu qishu " << qishu << "  ";

    if (qishu >= 0 && qishu < alltargets.size())
    {
        print_vetor(alltargets[qishu]);
        return alltargets[qishu];
    }

    return onetarget;
}

void calculateDifference(int qishu)
{
    vector<int> target = getVectorByQiShu(qishu);
    int size = target.size();
    cout << "difference: ";
    for (int index = 0; index < size; index++)
    {
        int number1 = target[index];
        for (int count = index + 1; count < size; count++)
        {
            int number2 = target[count];
            int difference = abs(number1 - number2);
            cout << difference << " ";
        }
    }
    cout << endl;
}

void calculateYiLou()
{

    map<int, vector<int>> yilouCount;
    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        vector<int> one;
        one.push_back(0);
        yilouCount[idx + 1] = one;
    }
    for (int index = 0; index < alltargets.size(); index++)
    {
        vector<int> one = alltargets[index];
        vector<int> yilouzhiforonetarget;
        for (int idx = 0; idx < TheMaxNum; idx++)
        {
            int number = idx + 1;
            bool found = false;
            for (int count = 0; count < one.size(); count++)
            {
                if (one[count] == number)
                {
                    yilouzhiforonetarget.push_back(yilouCount[number].back());
                    yilouCount[number].push_back(0);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                yilouCount[number].back() = yilouCount[number].back() + 1;
            }
        }

        int sum = 0;
        for (auto it = yilouzhiforonetarget.begin(); it != yilouzhiforonetarget.end(); it++)
        {
            sum += *it;
        }
        cout << "yilouzhi " << index << " sum: " << sum << endl;
        // sort(yilouzhiforonetarget.begin(),yilouzhiforonetarget.end());
        print_vetor(yilouzhiforonetarget);
        sort(one.begin(), one.end());
        print_vetor(one);
    }

    cout << "yilou " << endl;
    map<int, int> yilouMap;
    for (auto it = yilouCount.begin(); it != yilouCount.end(); it++)
    {
        cout << "first  " << it->first;
        print_vetor(it->second);

        for (auto itor = it->second.begin(); itor != it->second.end(); itor++)
        {

            if (yilouMap.find(*itor) == yilouMap.end())
            {
                yilouMap[*itor] = 0;
            }
            yilouMap[*itor] = yilouMap[*itor] + 1;
        }
    }
    vector<pair<int, int>> dVector;
    sortMapByValue(yilouMap, dVector);
    for (int i = 0; i < dVector.size(); i++)
    {
        cout << dVector[i].first << ": ";
        cout << dVector[i].second;
        cout << endl;
    }
    cout << endl;
}

void getAllTargets()
{
    alltargets.clear();
    char filename[64] = {0};
    sprintf(filename, "targets.txt");
    if (isFileExists_fopen(filename))
    {
        LoadMatrixFileToT(filename, TheCount, TheMaxRow, target);
    }

    for (int row = TheMaxRow - maxrowcount; row < TheMaxRow; row++)
    {

        vector<int> onetarget;

        for (int idx = 0; idx < TheCount; idx++)
        {
            onetarget.push_back(target[idx][row]);
            // cout << "is " << target[idx][row] << endl;
        }

        alltargets.push_back(onetarget);
    }
    cout << "alltargets size " << alltargets.size() << "    the last one is ";
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

void testThreeByQishu(int qishu)
{
    vector<int> oldQi = getVectorByQiShu(qishu - 2);
    vector<int> lastQi = getVectorByQiShu(qishu - 1);

    vector<vector<int>> threeVector;

    for (int idx = 0; idx < TheCount; idx++)
    {
        int number = oldQi[idx];
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        for (int index = 0; index < TheMaxNum; index += 3)
        {
            vector<int> one;
            one.push_back(dVector[index].first);
            one.push_back(dVector[index + 1].first);
            one.push_back(dVector[index + 2].first);
            threeVector.push_back(one);
        }
    }
    for (int idx = 0; idx < TheCount; idx++)
    {
        int number = lastQi[idx];
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        for (int index = 0; index < TheMaxNum; index += 3)
        {
            vector<int> one;
            one.push_back(dVector[index].first);
            one.push_back(dVector[index + 1].first);
            one.push_back(dVector[index + 2].first);
            threeVector.push_back(one);
        }
    }

    vector<int> currentQi = getVectorByQiShu(qishu);
    for (int index = 0; index < threeVector.size(); index++)
    {
        vector<int> one = threeVector[index];
        int foundCount = 0;
        for (int idx = 0; idx < 3; idx++)
        {
            for (int count = 0; count < TheCount; count++)
            {
                if (one[idx] == currentQi[count])
                {
                    ++foundCount;
                    break;
                }
            }
        }
        if (foundCount >= 2)
        {
            cout << "found count " << foundCount;
            print_vetor(one);
        }
    }
}

void testThreeWithVector(vector<int> data, int qishu)
{
    vector<int> oldQi = getVectorByQiShu(qishu - 1);
    vector<int> lastQi = getVectorByQiShu(qishu);

    vector<vector<int>> threeVector;

    for (int idx = 0; idx < TheCount; idx++)
    {
        int number = oldQi[idx];
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        for (int index = 0; index < TheMaxNum; index += 3)
        {
            vector<int> one;
            one.push_back(dVector[index].first);
            one.push_back(dVector[index + 1].first);
            one.push_back(dVector[index + 2].first);
            threeVector.push_back(one);
        }
    }
    for (int idx = 0; idx < TheCount; idx++)
    {
        int number = lastQi[idx];
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        for (int index = 0; index < TheMaxNum; index += 3)
        {
            vector<int> one;
            one.push_back(dVector[index].first);
            one.push_back(dVector[index + 1].first);
            one.push_back(dVector[index + 2].first);
            threeVector.push_back(one);
        }
    }

    vector<int> currentQi = data;
    for (int index = 0; index < threeVector.size(); index++)
    {
        vector<int> one = threeVector[index];
        int foundCount = 0;
        for (int idx = 0; idx < 3; idx++)
        {
            for (int count = 0; count < currentQi.size(); count++)
            {
                if (one[idx] == currentQi[count])
                {
                    ++foundCount;
                    break;
                }
            }
        }
        if (foundCount >= 2)
        {
            cout << "found count " << foundCount;
            print_vetor(one);
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
    vector<int> oldQi = getVectorByQiShu(qishu - 1);
    vector<int> lastQi = getVectorByQiShu(qishu);

    vector<int> hotresult;
    vector<int> currentHotresult;
    vector<int> currentColdresult;

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

            currentHotresult.push_back(testNumber);
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

    cout << "CurrentHotCode:  ";
    print_vetor(currentHotresult);

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

            currentColdresult.push_back(testNumber);
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

    cout << "CurrentColdCode:  ";
    print_vetor(currentColdresult);

    if (qishu + 1 < maxrowcount)
    {
        vector<int> future = getVectorByQiShu(qishu + 1);

        if (contain(currentHotresult, future))
        {
            cout << "-----gooood find " << qishu << " :  "
                 << "   " << maxrowcount << endl;
        }
        if (contain(currentColdresult, future))
        {
            cout << "-----gooood find  22" << qishu << " :  "
                 << "   " << maxrowcount << endl;
        }
    }

    getVectorByQiShu(qishu);
    cout << "----------calculateHotCold end " << qishu << endl;
}

void geteRelatedNumbers()
{
    relatedClosePredict.clear();

    vector<int> allNumbers;
    for (int idx = 0; idx < alltargets.size(); idx++)
    {
        vector<int> onetarget = alltargets[idx];
        allNumbers.insert(allNumbers.end(), onetarget.begin(), onetarget.end());
    }

    map<int, vector<int>> relativeNumbers;
    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        vector<int> one;
        relativeNumbers[idx + 1] = one;
    }

    int maxnumbers = allNumbers.size();
    for (int idx = 0; idx < maxnumbers; idx++)
    {

        int number = allNumbers[idx];

        for (int pos = idx + 1, count = TheRelatedCount; pos < maxnumbers, count > 0; pos++, count--)
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
            if (i % 3 == 2)
            {
                cout << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < dVector.size(); i++)
        {
            cout << dVector[i].second << " ";
            if (i % 3 == 2)
            {
                cout << " ";
            }
        }
        relatedClosePredict[number] = dVector;
        cout << endl;
        cout << endl;
        dVector.clear();
    }
}

void calculateRelatedNumbers(vector<int> testqi)
{

    map<int, vector<int>> allPredict;
    for (int idx = 0; idx < TheCount; idx++)
    {
        vector<int> onePredict;
        allPredict[testqi[idx]] = onePredict;
    }
    map<int, int> anotherPredict;
    for (int idx = 0; idx < TheMaxNum; idx++)
    {
        anotherPredict[idx + 1] = 0;
    }

    ////分组打印
    for (int idx = 0; idx < TheCount; idx++)
    {
        int number = testqi[idx];
        cout << number << ":  ";
        vector<pair<int, int>> dVector = relatedClosePredict[number];
        int arrayIndex = 0;
        for (int i = 0; i < dVector.size(); i++)
        {
            cout << dVector[i].first << " ";
            if (i % 3 == 2)
            {
                cout << " ";
                ++arrayIndex;
                if (idx < 3)
                {
                    if (arrayIndex == 4 || arrayIndex == 7)
                    {
                        cout << "        ";
                    }
                }
                else
                {
                    if (arrayIndex == 3 || arrayIndex == 7)
                    {
                        cout << "        ";
                    }
                }
            }
        }

        cout << endl;
    }

    for (int idx = 0; idx < TheCount; idx++)
    {
        int number = testqi[idx];
        vector<pair<int, int>> dVector = relatedClosePredict[number];

        for (int i = 0; i < TheLength; i++)
        {
            allPredict[testqi[idx]].push_back(dVector[i].first);

            anotherPredict[dVector[i].first] += dVector[i].second;
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

    vector<pair<int, int>> pVector;
    sortMapByValue(predictCount, pVector);
    for (int i = 0; i < pVector.size(); i++)
        cout << pVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < pVector.size(); i++)
    {
        if (pVector[i].first > 10)
            cout << " ";
        cout << pVector[i].second << " ";
    }
    cout << endl;
    // for (auto it = predictCount.begin(); it != predictCount.end(); it++)
    // {
    //     cout << it->first << " " << it->second << " " << endl;
    // }
    // vector<pair<int, int>> dVector;
    // sortMapByValue(predictCount, dVector);
    // for (int i = 0; i < dVector.size(); i++)
    //     cout << dVector[i].first << " " << dVector[i].second << " " << endl;

    cout << "another predict " << endl;
    // for (auto itor = anotherPredict.begin(); itor != anotherPredict.end(); itor++)
    // {
    //     cout << itor->first << " " << itor->second << endl;
    // }
    vector<pair<int, int>> anVector;
    sortMapByValue(anotherPredict, anVector);
    for (int i = 0; i < anVector.size(); i++)
        cout << anVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < anVector.size(); i++)
    {
        if (anVector[i].first > 10)
            cout << " ";
        cout << anVector[i].second << " ";
    }
    // for (int i = 0; i < anVector.size(); i++)
    //     cout << anVector[i].first << " " << anVector[i].second << " " << endl;
}

void calculateAfterByQishuAgain2(vector<int> testqi2)
{

    vector<int> testqi = testqi2;
    //  sort(testqi.begin(),testqi.end());
    cout << "after compose: " << endl;
    for (int index = 0; index < testqi.size() - 1; index++)
    {
        // for( int idx = index+1; idx < testqi.size(); idx++ ){
        int idx = index + 1;

        int number1 = testqi[index];
        int number2 = testqi[idx];

        vector<int> oneCompose;

        oneCompose.push_back(number1);
        oneCompose.push_back(number2);

        map<int, int> afterCount;
        for (int idx = 0; idx < TheMaxNum; idx++)
        {
            afterCount[idx + 1] = 0;
        }

        for (int idx = 0; idx < alltargets.size() - 1; idx++)
        {
            vector<int> onetarget = alltargets[idx];

            if (contain(onetarget, oneCompose))
            {

                vector<int> nexttarget = alltargets[idx + 1];
                //   print_vetor(onetarget);
                //  print_vetor(nexttarget);
                for (int count = 0; count < nexttarget.size(); count++)
                {
                    ++afterCount[nexttarget[count]];
                }
            }
        }

        print_vetor(oneCompose);

        vector<pair<int, int>> aVector;
        sortMapByValue(afterCount, aVector);
        for (int i = 0; i < aVector.size(); i++)
            cout << aVector[i].first << " ";
        cout << endl;
        for (int i = 0; i < aVector.size(); i++)
        {
            if (aVector[i].first > 10)
                cout << " ";
            cout << aVector[i].second << " ";
        }
        cout << endl;

        // }
    }
}

void calculateAfterByQishuAgain(vector<int> testqi2)
{
    print_vetor(testqi2);
    vector<int> testqi = testqi2;
    calculateAfterByQishuAgain2(testqi);
    cout << "order again " << endl;
    sort(testqi.begin(), testqi.end());
    calculateAfterByQishuAgain2(testqi);
}
void calculateAfterByQishu(vector<int> testqi)
{
    map<int, int> beforeCount;
    map<int, int> currentCount;
    map<int, int> afterCount;

    map<int, int> repeatCount;
    map<int, int> tripleCount;
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
        repeatCount[idx + 1] = 0;
        tripleCount[idx + 1] = 0;
    }

    ////计算before中有上期的数
    map<int, map<int, int>> beforemap;

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

                    bool foundBefore = false;
                    if (idx >= 1 && idx < alltargets.size())
                    {
                        vector<int> beforetarget = alltargets[idx - 1];
                        for (int count = 0; count < beforetarget.size(); count++)
                        {

                            ++beforeCount[beforetarget[count]];

                            if (beforetarget[count] == findNumber)
                            {
                                foundBefore = true;
                            }
                        }
                    }

                    if (idx < alltargets.size() - 1)
                    {
                        vector<int> aftertarget = alltargets[idx + 1];
                        for (int count = 0; count < aftertarget.size(); count++)
                        {
                            ++afterCount[aftertarget[count]];

                            if (aftertarget[count] == findNumber)
                            {
                                ++repeatCount[findNumber];

                                if (foundBefore)
                                {
                                    ++tripleCount[findNumber];
                                }
                            }
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

            for (int index = 0; index < 8; index++)
            {
                if (testqi[idx] == bVector[index].first)
                {
                    if (beforemap.find(findNumber) == beforemap.end())
                    {
                        map<int, int> values;
                        beforemap[findNumber] = values;
                    }
                    beforemap[findNumber][bVector[index].first] = index + 1;
                }
            }
        }

        aVector.clear();
        bVector.clear();
        cVector.clear();
    }

    cout << "repeatCount is: ";
    vector<pair<int, int>> rVector;
    sortMapByValue(repeatCount, rVector);
    for (int i = 0; i < rVector.size(); i++)
        cout << rVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < rVector.size(); i++)
    {
        if (rVector[i].first > 10)
            cout << " ";
        cout << rVector[i].second << " ";
    }
    cout << endl;

    cout << "tripleCount is: ";
    vector<pair<int, int>> triVector;
    sortMapByValue(tripleCount, triVector);
    for (int i = 0; i < triVector.size(); i++)
        cout << triVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < triVector.size(); i++)
    {
        if (triVector[i].first > 10)
            cout << " ";
        cout << triVector[i].second << " ";
    }
    cout << endl;

    map<int, int> beforeorders;
    for (auto it = beforemap.begin(); it != beforemap.end(); it++)
    {
        cout << " before " << it->first << "   " << it->second.size() << "    ";
        print_map(it->second);

        beforeorders[it->first] = it->second.size();
    }
    vector<pair<int, int>> tVector;
    sortMapByValue(beforeorders, tVector);
    for (int i = 0; i < tVector.size(); i++)
        cout << tVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < tVector.size(); i++)
    {
        if (tVector[i].first > 10)
            cout << " ";
        cout << tVector[i].second << " ";
    }

    cout << endl;
    cout << endl;

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
    vector<pair<int, int>> pVector;
    sortMapByValue(predictCount, pVector);
    // for (auto it = predictCount.begin(); it != predictCount.end(); it++)
    // {
    //     cout << it->first << " " << it->second << " " << endl;
    // }
    for (int i = 0; i < pVector.size(); i++)
        cout << pVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < pVector.size(); i++)
    {
        if (pVector[i].first > 10)
            cout << " ";
        cout << pVector[i].second << " ";
    }
    cout << endl;
    // vector<pair<int, int>> dVector;
    // sortMapByValue(predictCount, dVector);
    // for (int i = 0; i < dVector.size(); i++)
    //     cout << dVector[i].first << " " << dVector[i].second << " " << endl;

    cout << "another predict " << endl;
    // for (auto itor = anotherPredict.begin(); itor != anotherPredict.end(); itor++)
    // {
    //     cout << itor->first << " " << itor->second << endl;
    // }
    vector<pair<int, int>> anVector;
    sortMapByValue(anotherPredict, anVector);
    // for (int i = 0; i < anVector.size(); i++)
    //     cout << anVector[i].first << " " << anVector[i].second << " " << endl;
    for (int i = 0; i < anVector.size(); i++)
        cout << anVector[i].first << " ";
    cout << endl;
    for (int i = 0; i < anVector.size(); i++)
    {
        if (anVector[i].first > 10)
            cout << " ";
        cout << anVector[i].second << " ";
    }
}