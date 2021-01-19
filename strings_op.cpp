#include <iostream>
#include <string>
#include <algorithm>

bool greater(std::string s1, std::string s2){
    if (s1.length() > s2.length() || s1 == s2) return true;
    if (s1.length() < s2.length()) return false;
    for (int i = 0; i < s1.length(); ++i){
        if ((s1[i] - '0') > (s2[i] - '0')) return true;
        if ((s1[i] - '0') < (s2[i] - '0')) return false;
    }
    return false;
}

std::string subtract(const std::string& s1, const std::string& s2){
    if (s1 == s2) return "0";
    if (greater(s2, s1)) return "-" + subtract(s2, s1);
    const int l1 = s1.length();
    const int l2 = s2.length();
    const int n = std::max(l1, l2);
    std::string ans(n, '0');
    int diff = 0;
    for (int i = 0; i < n; ++i){
        int d1 = i < l1 ? (s1[l1 - i - 1] - '0') : 0;
        int d2 = i < l2 ? (s2[l2 - i - 1] - '0') : 0;
        int new_diff = (d1 - diff < d2 ? 1 : 0);
        d1 = (d1 >= diff ? d1 - diff : d1 - diff + 10);
        ans[i] = '0' + (d1 - d2 + (d1 < d2 ? 10 : 0));
        diff = new_diff;
    }
    while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
    std::reverse(ans.begin(), ans.end());
    return ans;
}

std::string add(const std::string s1, const std::string s2){
    if (s1[0] == '-' && s2[0] == '-') return add(std::string(s1.begin() + 1, s1.end()), std::string(s2.begin() + 1, s2.end()));
    if (s1[0] == '-') return subtract(s2, std::string(s1.begin() + 1, s1.end()));
    if (s2[0] == '-') return subtract(s1, std::string(s2.begin() + 1, s2.end()));
    const int l1 = s1.length();
    const int l2 = s2.length();
    const int n = std::max(l1, l2) + 1;
    std::string total(n, '0');
    int carry = 0;
    for (int i = 0; i < n; ++i) {
        const int d1 = i < l1 ? (s1[l1 - 1 - i] - '0') : 0;
        const int d2 = i < l2 ? (s2[l2 - 1 - i] - '0') : 0;
        total[i] = '0' + ((d1 + d2 + carry) % 10);
        carry = (d1 + d2 + carry) / 10;
    }
    while (total.size() > 1 && total.back() == '0') total.pop_back();
    std::reverse(total.begin(), total.end());
    return total;
}

std::string multiply(std::string s1, std::string s2){
    if (s1 == "0" || s2 == "0") return "0";
    if (s1[0] == '-' && s2[0] == '-') return multiply(std::string(s1.begin() + 1, s1.end()), std::string(s2.begin() + 1, s2.end()));
    if (s1[0] == '-') return '-' + multiply(std::string(s1.begin() + 1, s1.end()), s2);
    if (s2[0] == '-') return '-' + multiply(s1, std::string(s2.begin() + 1, s2.end()));

    const int n = std::max(s1.length(), s2.length());
    while (s1.length() < n) s1.insert(0, "0");
    while (s2.length() < n) s2.insert(0, "0");
    
    if (n == 1) return std::to_string((s1[0] - '0') * (s2[0] - '0'));
    
    std::string a = s1.substr(0, n / 2), b = s1.substr(n / 2, n - n / 2);
    std::string c = s2.substr(0, n / 2), d = s2.substr(n / 2, n - n / 2);

    std::string u = multiply(a, c), v = multiply(b, d);
    std::string w = multiply(add(a, b), add(c, d));
    std::string t = subtract(w, add(u, v));

    for (int i = 0; i < 2 * (n - n / 2); ++i) u.append("0");
    for (int i = 0; i < (n - n / 2); ++i) t.append("0");

    return add(u, add(t, v));
}

int main(){
    std::string s1, s2; std::cin >> s1 >> s2;
    //s1 = "3141592653589793238462643383279502884197169399375105820974944592";
    //s2 = "2718281828459045235360287471352662497757247093699959574966967627";
    std::cout << multiply(s1, s2);
}