
#include<iostream>
#include<algorithm>
using namespace std;
struct Activity{
int start,finish;
};
bool compare(Activity a1,Activity a2){
return a1.finish<a2.finish;
}
void ActivitySelection(Activity arr[],int n){
sort (arr,arr+n,compare);
cout<<"Selection activity are:\n";
int i=0;
cout<<arr[i].start<<""<<arr[i].finish<<" ";
for(int j=1;j<n;j++){
    if(arr[j].start>=arr[i].finish){
        cout<<arr[j].start<<" "<<arr[j].finish<<" ";
        i=j;
    }
}
cout<<endl;
}
int main(){
Activity arr[]={{1,3},{2,5},{4,6},{6,7},{5,8},{8,9}};
int n=sizeof(arr)/sizeof(arr[0]);
ActivitySelection(arr,n);
return 0;
}
