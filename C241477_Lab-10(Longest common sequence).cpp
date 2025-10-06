
#include <iostream>
#include <string>
using namespace std;
int main() {
string s1, s2;
cout << "Enter first string: ";
cin >> s1;
cout << "Enter second string: ";
cin >> s2;

int n = s1.size();
int m = s2.size();

int dp[100][100];

for (int i = 0; i <= n; i++) {
for (int j = 0; j <= m; j++) {
if (i == 0 || j == 0)
dp[i][j] = 0;
else if (s1[i - 1] == s2[j - 1])
dp[i][j] = dp[i - 1][j - 1] + 1;
else
dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
}
}

cout << "Length of LCS: " << dp[n][m] << endl;
string lcs = "";
int i = n, j = m;
while (i > 0 && j > 0) {
if (s1[i - 1] == s2[j - 1]) {
lcs = s1[i - 1] + lcs;
i--;
j--;
}
else if (dp[i - 1][j] > dp[i][j - 1])
i--;
else
j--;
}
cout << "LCS is: " << lcs << endl;
return 0;
}
