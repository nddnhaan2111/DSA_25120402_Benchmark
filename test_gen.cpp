#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

void test_int() {
    int n = 100000;
    ofstream f1("int/test001.in");
    if (f1.is_open()) {
            f1 << n << "\n";
            for (int i = 0; i < n; i++) f1 << i << "\n";
            f1.close();
        }
    ofstream f2("int/test002.in");
    if (f2.is_open()) {
        f2 << n << "\n";
        for (int i = 0; i < n; i++) f2 << n - i << "\n";
        f2.close();
    }
    ofstream f3("int/test003.in");
    if (f3.is_open()) {
        f3 << n << "\n";
        for (int i = 0; i < n; i++) f3 << 1005 << "\n";
        f3.close();
    }
    ofstream f4("int/test004.in");
    if (f4.is_open()) {
        f4 << n << "\n";
        for (int i = 0; i < n / 2; i++) {
            f4 << "2147483647\n-2147483648\n";
        }
        f4.close();
    }
    ofstream f5("int/test005.in");
    if (f5.is_open()) {
        f5 << n << "\n";
        mt19937 r(2111);
        uniform_int_distribution<long long> d(-2147483648LL, 2147483647LL);
        for (int i = 0; i < n; i++) {
            f5 << d(r) << "\n";
        }
        f5.close();
    }
}
void test_strlexi() {
    int n = 100000;
    mt19937 r(2111);
    ofstream f1("strlexi/test001.in");
    if (f1.is_open()) {
        f1 << n << "\n";
        string s(100, 'a');
        for (int i = 0; i < n; i++) f1 << s << "\n";
        f1.close();
    }
    ofstream f2("strlexi/test002.in");
    if (f2.is_open()) {
        f2 << n << "\n";
        string prefix(99, 'a');
        for (int i = 0; i < n; i++) {
            f2 << prefix << (char)('a' + (i % 26)) << "\n";
        }
        f2.close();
    }
    ofstream f3("strlexi/test003.in");
    if (f3.is_open()) {
        f3 << n << "\n";
        vector<string> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = string(100, (char)('z' - (i % 26)));
        }
        sort(v.rbegin(), v.rend()); 
        for (int i = 0; i < n; i++) f3 << v[i] << "\n";
        f3.close();
    }

    ofstream f4("strlexi/test004.in");
    if (f4.is_open()) {
        f4 << n << "\n";
        vector<string> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = string(10 + (i % 91), 'a'); 
        }
        sort(v.rbegin(), v.rend()); 
        for (int i = 0; i < n; i++) f4 << v[i] << "\n";
        f4.close();
    }

    ofstream f5("strlexi/test005.in");
    if (f5.is_open()) {
        f5 << n << "\n";
        uniform_int_distribution<int> len_dist(10, 100);
        uniform_int_distribution<int> char_dist('a', 'z');
        for (int i = 0; i < n; i++) {
            int len = len_dist(r);
            string s(len, ' ');
            for (int j = 0; j < len; j++) {
                s[j] = (char)char_dist(r);
            }
            f5 << s << "\n";
        }
        f5.close();
    }
}
void test_strlenlexi() {
    int n = 10000; 
    mt19937 r(2111);
    ofstream f1("strlenlexi/test001.in");
    if (f1.is_open()) {
        f1 << n << "\n";
        vector<string> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = string(99, 'a') + (char)('z' - (i % 26));
        }
        sort(v.rbegin(), v.rend()); 
        for (int i = 0; i < n; i++) f1 << v[i] << "\n";
        f1.close();
    }
    ofstream f2("strlenlexi/test002.in");
    if (f2.is_open()) {
        f2 << n << "\n";
        string short_s(10, 'a');
        string long_s(100, 'z');
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) f2 << short_s << "\n";
            else f2 << long_s << "\n";
        }
        f2.close();
    }
    ofstream f3("strlenlexi/test003.in");
    if (f3.is_open()) {
        f3 << n << "\n";
        for (int i = 0; i < n; i++) {
            int len = 100 - (i % 91); 
            f3 << string(len, 'a') << "\n";
        }
        f3.close();
    }
    ofstream f4("strlenlexi/test004.in");
    if (f4.is_open()) {
        f4 << n << "\n";
        string s(100, 'z');
        for (int i = 0; i < n; i++) f4 << s << "\n";
        f4.close();
    }

    ofstream f5("strlenlexi/test005.in");
    if (f5.is_open()) {
        f5 << n << "\n";
        uniform_int_distribution<int> len_dist(10, 100);
        uniform_int_distribution<int> char_dist('a', 'z');
        for (int i = 0; i < n; i++) {
            int len = len_dist(r);
            string s(len, ' ');
            for (int j = 0; j < len; j++) {
                s[j] = (char)char_dist(r);
            }
            f5 << s << "\n";
        }
        f5.close();
    }
}
int main() {
    srand(2111);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    test_int();
    test_strlexi();
    test_strlenlexi();
	return 0;
}