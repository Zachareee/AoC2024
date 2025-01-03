#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int answer1(vector<vector<char>> arr);
int answer2(vector<vector<char>> arr);

int main(void)
{
  vector<vector<char>> v;

  string line;
  ifstream file("input.txt");

  while (!file.fail())
  {
    getline(file, line);
    if (!line.empty())
    {
      v.push_back(vector<char>(line.begin(), line.end()));
    }
  }

  cout << answer1(v) << endl;
  cout << answer2(v) << endl;
}

const string XMAS ("XMAS");
bool compare_xmas(const char *to_compare)
{
  return (string) to_compare == XMAS;
}

int count_horizontal(vector<vector<char>> arr)
{
  int value = 0;
  int size = arr.size();
  for (auto i = 0; i < size; ++i)
  {
    auto inner = arr[i];
    for (auto j = 0; j + 3 < size; ++j)
    {
      if (compare_xmas(new char[5] {inner[j], inner[j+1], inner[j+2], inner[j+3], 0}))
      {
        j += 3;
        ++value;
      }
    }
  }
  return value;
}

int count_vertical(vector<vector<char>> arr)
{
  int value = 0;
  int size = arr.size();

  for (auto i = 0; i < size; ++i)
  {
    for (auto j = 0; j + 3 < size; ++j)
    {
      if (compare_xmas(new char[5] {arr[j][i], arr[j+1][i], arr[j+2][i], arr[j+3][i], 0}))
      {
        ++value;
        j += 3;
      }
    }
  }

  return value;
}

int count_backslash(vector<vector<char>> arr)
{
  int value = 0;
  int size = arr.size();

  for (auto i = 0; i + 3 < size; ++i)
  {
    for (auto j = 0; j + 3 < size; ++j)
    {
      if (compare_xmas(new char[5] {arr[i][j], arr[i+1][j+1], arr[i+2][j+2], arr[i+3][j+3], 0}))
        ++value;
    }
  }

  return value;
}

int count_slash(vector<vector<char>> arr)
{
  int value = 0;
  int size = arr.size();

  for (auto i = size - 1; i > 2; --i)
  {
    for (auto j = 0; j + 3 < size; ++j)
    {
      if (compare_xmas(new char[5] {arr[i][j], arr[i-1][j+1], arr[i-2][j+2], arr[i-3][j+3], 0}))
        ++value;
    }
  }

  return value;
}

int count_all(vector<vector<char>> arr)
{
  return count_horizontal(arr) + count_vertical(arr) + count_backslash(arr) + count_slash(arr);
}

int answer1(vector<vector<char>> arr)
{
  int sum = count_all(arr);

  for (int i = 0; i < arr.size(); ++i)
  {
    reverse(arr[i].begin(), arr[i].end());
  }

  reverse(arr.begin(), arr.end());
  return sum + count_all(arr);
}

const int pos[] = {-1, 1};
bool x_mas(vector<vector<char>> arr, int x, int y)
{
  int m = 0, s = 0;

  for (int i : pos)
  {
    for (int j : pos)
    {
      if (arr[x+i][y+j] == 'M') ++m;
      if (arr[x+i][y+j] == 'S') ++s;
    }
  }


  if (m != 2 || s != 2) return false;

  return arr[x-1][y-1] != arr[x+1][y+1];
}

int answer2(vector<vector<char>> arr)
{
  int size = arr.size() - 1;
  int count = 0;

  for (int i = 1; i < size; ++i)
  {
    for (int j = 1; j < size; ++j)
    {
      if (arr[i][j] == 'A' && x_mas(arr, i, j))
      {
        ++count;
      }
    }
  }

  return count;
}
