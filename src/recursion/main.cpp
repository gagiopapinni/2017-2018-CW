
#include <iostream>
using namespace std;



void move(int from, int to,int n ){
    
    
    if(n == 1) {
        cout<<" move "<< n <<"th plate from "<<from<<"th to "<<to<<"th stick"<<endl;
        return ;
    }
    
    move(from,6-from-to,n-1);
    
    cout<<" move "<< n <<"th plate from "<<from<<"th to "<<to<<"th stick"<<endl;

    move(6-from-to,to,n-1); 
    

}



int main()
{
    move(1,3,3);

    return 0;
}
