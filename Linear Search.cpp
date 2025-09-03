#include<iostream>
using namespace std;
int main(){
int n,key;
cout<<"Enter the number of element:";
cin>>n;
int arr[n];
cout<<"Enter element:"<<endl;
for(int i=0;i<n;i++){
cin>>arr[i];
}
cout<<"Enter element to search:";
cin>>key;
bool found=false;
for(int i=0;i<n;i++){
    if(arr[i]==key){
 cout<<"Element found at index " << i <<endl;
        found=true;
        break;
    }
}
if(!found){
    cout<<"value are not found"<<" ";
}
return 0;
}
