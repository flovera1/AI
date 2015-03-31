#include "nqueens.h"
int k,x[20],c,n;
class queen{
  public:
    void nqueen(int k,int n){ 
      int i;
      for(i = 1;i <= n;i++){
        if(place(k,i)){
          x[k]=i;
          if(k==n){
            c++; 
            printing();
          }else{
            nqueen(k+1,n);
          }
        }          
      }             
    };
    int place(int k,int i){
      for(int j=1;j<=k-1;j++){
          if (x[j]==i || (abs(x[j]-i)==abs(j-k))){
                return 0;
          }
      }
      return 1;
    }
    void printing(){
      for(int i = 1;i <= n;i++){
        for(int j=1;j<=n;j++){
          if(x[i] == j){
            cout<<" Q " ;
          }else{
            cout<<" # ";
          }    
         }
         cout<<"\n";
       }
     cout<<"\n\n";
     }
};
void main(){
  queen q;
  cout<<"\n\t\t N- QUEEN'S PROBLEM USING BACKTRACKING METHOD \n ";
  cout<<"\n\n ENTER THE NUMBER OF QUEEN'S : ";
  cin>>n;
  q.nqueen(1,n);  
  cout<<"\n\n TOTAL NUMBER OF COMBINATIONS : "<<c;
//  getch();
}