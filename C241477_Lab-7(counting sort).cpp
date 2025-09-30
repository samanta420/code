#include <iostream>
#include <vector>
using namespace std;

int main() {
int n;
cout << "Enter size of array: ";
cin >> n;
int arr[n];
cout << "Enter " << n << " elements: ";
for (int i = 0; i < n; i++) {
cin >> arr[i];
}

int maxVal = arr[0];
for (int i = 1; i < n; i++) {
if (arr[i] > maxVal)
maxVal = arr[i];
    }
vector<int> count(maxVal + 1, 0);
for (int i = 0; i < n; i++) {
count[arr[i]]++;
}
int idx = 0;
for (int i = 0; i <= maxVal; i++) {
while (count[i] > 0) {
arr[idx] = i;
idx++;
count[i]--;
}
}
cout << "Sorted array: ";
for (int i = 0; i < n; i++) {
cout << arr[i] << " ";
}
cout << endl;

return 0;
}
