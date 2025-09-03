#include<iostream>
using namespace std;
int main()
{
int n;
cout<<"Enter the number of element:";
cin>>n;
int arr[n];
cout<<"Enter element:";
for(int i=0;i<n;i++){
    cin>>arr[i];
}
for(int i=1;i<n;i++)
{
   int key=arr[i] ;
   int j=i-1;
   while(j>=0 && arr[j]>key){
    arr[j+1]=arr[j];
    j--;
   }
arr[j+1]=key;
}
int maxvalue=arr[0];
int minvalue=arr[0];
for(int i=1;i<n;i++){
    if(arr[i]>maxvalue){
        maxvalue=arr[i];
    }
    if(arr[i]<minvalue){
        minvalue=arr[i];
    }
}
cout<<" Maxvalue "<<maxvalue<<endl;
cout<<" Minvalue "<<minvalue<<endl;
cout<<"Acending arry:";
for(int i=0;i<n;i++){
    cout<<arr[i]<<" ";
}
cout<<endl;
cout<<"Decending arry:";
for(int i=n-1;i>=0;i--){
    cout<<arr[i]<<" ";
}
cout<<endl;
return 0;
}
