#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int answer1(vector<int> v1, vector<int> v2);
int answer2(vector<int> v1, vector<int> v2);

int main(void) {
  vector<int> v1, v2;

  string line;
  int first, second;
  ifstream file("input.txt");

  while (!file.fail()) {
    getline(file, line);
    if (!line.empty()) {
      stringstream s(line);
      s >> first >> second;
      v1.push_back(first);
      v2.push_back(second);
    }
  }

  cout << answer1(v1, v2) << endl;
  cout << answer2(v1, v2) << endl;
}

int answer1(vector<int> v1, vector<int> v2) {
  sort(v1.begin(), v1.end());
  sort(v2.begin(), v2.end());

  vector<int> v;
  transform(v1.begin(), v1.end(), v2.begin(), back_inserter(v), [](int num1, int num2) -> int {
    return abs(num1 - num2);
  });

  return accumulate(v.begin(), v.end(), 0);
}

int answer2(vector<int> v1, vector<int> v2) {
  set<int> s(v1.begin(), v1.end());

  return accumulate(s.begin(), s.end(), 0, [v2](int acc, int x) -> int {
    return acc + x * count(v2.begin(), v2.end(), x);
  });
}
