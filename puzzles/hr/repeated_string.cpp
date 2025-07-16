#include <bits/stdc++.h>

using namespace std;

// Complete the repeatedString function below.
long repeatedString(string s, long n) {
    // Understand problem
    const auto len = s.length();
    const auto times = n / len;
    const auto rem = n % len;
    
    // Handle repeated case
    int a_per_time = 0;
    if (time != 0)
        for (unsigned long i = 0; i < len; i++)
            if (s[i] == 'a')
                a_per_time++;

    // Handle remaining text
    int a_rem = 0;
    for (unsigned long i = 0; i < rem; i++)
        if (s[i] == 'a')
            a_rem++;
    
    // Return total
    return times * a_per_time + a_rem;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    long n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    long result = repeatedString(s, n);

    fout << result << "\n";

    fout.close();

    return 0;
}