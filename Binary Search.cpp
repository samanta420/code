#include<iostream>
using namespace std;
int main()
{
int arr[6]={20,30,40,50,60,70,};
int n=6;
int search_value;
cout<<"Enter the search value:";
cin>>search_value;
int fast=0;
int last=n-1;
int middle;
bool found=false;
while(fast<=last){
    middle=(fast+last)/2;
    if(search_value== arr[middle]){
        cout<<"value found at index:"<<middle<<endl;
         cout<<"value found at index:"<<middle+1<<endl;
        found=true;
        break;
    }
    else if(arr[middle]<search_value)
    {
        fast=middle+1;
    }
    else{
        last=middle-1;
    }
}
if(!found)
{
    cout<<"value not found"<<endl;
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
return 0;

}
