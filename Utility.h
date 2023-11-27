#ifndef _UTILITY_H
#define _UTILITY_H
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;
bool isFileExists_fopen(char *name)
{
  return access(name, F_OK) == 0;
  if (FILE *file = fopen(name, "r"))
  {
    fclose(file);
    return true;
  }
  else
  {
    return false;
  }
}

vector<int> vector_intersection(vector<int> v1, vector<int> v2)
{
  vector<int> v;
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());
  set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));
  return v;
}
void print_vetor(vector<int> v)
{
  if (v.size() > 0)
  {
    cout << "{";
    for (int i = 0; i < int(v.size()); i++)
    {
      cout << v[i] << ",";
    }
    cout << "\b}\n";
  }
  else
  {
    cout << "{}\n";
  }
}

void print_map(map<int, int> &m)
{
  cout << "{ ";
  for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
  {

    cout << it->first << " : " << it->second << "   ";
  }
  cout << "\b}\n";
}

bool contain(vector<int> v1, vector<int> v2)
{
  bool retValue = true;
  for (int index = 0; index < v2.size(); index++)
  {
    int number = v2[index];
    bool found = false;
    for (int idx = 0; idx < v1.size(); idx++)
    {
      int number2 = v1[idx];
      if (number == number2)
      {
        found = true;
        break;
      }
    }

    if (!found)
    {
      retValue = false;
      break;
    }
  }
  return retValue;
}

#endif
