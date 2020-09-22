#include<iostream>
#include <string>

using namespace std;
int t, n, a, b;
string s;
int longestmatch[4001];
int dp[4001];



int main() {
  ios_base::sync_with_stdio(0);

    
    cin >> a >> b >> n >> s;
    //cout<<s.substr(0,1)<<endl;
    string part1,part2;
    longestmatch[0] = 0;
    int found = 0;
    for (int i = 1; i < s.size(); ++i)
    {
      //longestmatch[i] = 0;
      int partition;
      if(i%2)
        partition = ((i)/2)+1;
      else partition = (i)/2;
      found = 0;
      longestmatch[i] =0;
      while(partition>0 && !found)
      {
        part1 = s.substr(0,i-partition+1);

        part2 = s.substr(i-partition+1,partition);
        int pos = part1.find(part2);
        //cout<<"parts:- "<<i<<" "<<part1<<"      "<<part2<<"   pos:- "<<pos<<endl;
        if(pos<part1.size() && pos>=0){ found = 1;longestmatch[i] = partition;}
        else partition--;
      }
      //cout<<"see:- "<<i<<" "<<longestmatch[i]<<endl;


    }





    dp[0] = a;
    for (int i = 1; i < s.size(); i++) {
      if(longestmatch[i]>0)
      dp[i] = min(dp[i-1]+a, dp[i-longestmatch[i]]+b);
      else dp[i] = dp[i-1]+a;
      
    }
    cout<<dp[s.size()-1]<<endl;
  
  return 0;
}