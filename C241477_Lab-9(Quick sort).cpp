
#include <iostream>
using namespace std;
int main() {
int n;
cout << "Number of elements: ";
cin >> n;
int arr[1000];
cout << "Enter " << n << " numbers:\n";
for (int i = 0; i < n; i++)
cin >> arr[i];
int stack[1000];
int top = -1;
stack[++top] = 0;
stack[++top] = n - 1;
while (top >= 0) {
int high = stack[top--];
int low  = stack[top--];
int i = low, j = high;
int pivot = arr[(low + high) / 2];
while (i <= j) {
while (arr[i] < pivot) i++;
while (arr[j] > pivot) j--;
if (i <= j) {
int temp = arr[i];
arr[i] = arr[j];
arr[j] = temp;
i++; j--;
}
}
if (low < j) {
stack[++top] = low;
stack[++top] = j;
}
if (i < high) {
stack[++top] = i;
stack[++top] = high;
}
}
cout << "Sorted array: ";
for (int i = 0; i < n; i++) cout << arr[i] << " ";
cout << "\n";
return 0;
}
