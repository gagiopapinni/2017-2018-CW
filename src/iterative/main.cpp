
#include <iostream>
#include <cmath>
using namespace std;



int getPateNum(int move_num ){
    int plate_num = 1;
    
    while ( !( move_num % 2 ) ){
        
       move_num /= 2;    
       plate_num++;
    }
    
    return plate_num;
}

void solve(int from,int to,int n){
    
    
    for(int i = 1; i <= pow(2,n)-1; i++ ){
        
        int f = from, t = to,
            plate_num = getPateNum(i),
            root_node = pow(2,n-1), needed_node = i ,
            current_node = root_node,
            step_to_next_node = pow(2,n-2);
        while (  current_node != needed_node ){
            
            if( needed_node > current_node ){// to right
                current_node += step_to_next_node;                  
                f = 6-t-f;
            }else
            
            if( needed_node < current_node ){
                current_node -= step_to_next_node;                  
                t = 6-t-f;
            }
             
            
            step_to_next_node /= 2;
                 
            
        }
                  
        cout<<" move "<< plate_num <<"th plate from "<<f<<"th to "<<t<<"th stick"<<endl;
        
    
        
    }
    
    

    
    
}



int main()
{
    solve(1,3,3);
	return 0;
}
