// https://www.hackerrank.com/challenges/2d-array
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

int getHGSum(const vector<vector<int>>& arr, const int x, const int y) {
    int ret = 0;
    for (int i = x; i < x+3; i++) 
        ret += arr[y][i];
    ret += arr[y+1][x+1];
    for (int i = x; i < x+3; i++) 
        ret += arr[y+2][i];
    return ret;
}

/*
 * Complete the 'hourglassSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY arr as parameter.
 */
int hourglassSum(const vector<vector<int>>& arr) {
    const auto s = arr.size() - 2;
    int ret = INT_MIN;
    for (size_t x = 0; x < s; x++)
        for (size_t y = 0; y < s; y++) {
            const auto v = getHGSum(arr, x, y);
            std::cout <<x <<'\t' <<y << '\t' << v <<std::endl;
            if (v > ret)
                ret = v;
        }
    return ret;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);

    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        string arr_row_temp_temp;
        getline(cin, arr_row_temp_temp);

        vector<string> arr_row_temp = split(rtrim(arr_row_temp_temp));

        for (int j = 0; j < 6; j++) {
            int arr_row_item = stoi(arr_row_temp[j]);

            arr[i][j] = arr_row_item;
        }
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
