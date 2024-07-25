#include <math.h>
#include <stdio.h>
using namespace std;
const int inf =  2*1000*1000*1000;
int main(){
  
   int Nstones,jumps;
   scanf("%d %d", &Nstones, &jumps);


   jumps++;
   int m[Nstones];
   int height[Nstones];
   for (int i  =0;i<Nstones;i++){m[i] = inf; scanf("%d", &height[i]);}
   m[0] = 0;


   for (int s = 0; s<Nstones;s++){
       int curh = height[s];
       int curw = m[s];
       for (int r = 1; r<jumps;r++){
           if ((s+r )< Nstones){
               int cand = curw + abs(height[s+r] - curh);
               m[s + r] = min(m[s+r], cand );
           }
       }
   }
   printf("%d\n", m[Nstones-1]);
  
  


}
