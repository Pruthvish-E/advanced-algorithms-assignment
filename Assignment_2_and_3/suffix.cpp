#include "bits/stdc++.h"
using namespace std;

typedef long long int ll;
const ll N = 1e6+6;
int tmp[N],rnk[N],SA[N],lcp[N],len,step;
string S;
bool cmp( int x,int y )
{
    if( rnk[x]!=rnk[y] )return rnk[x]<rnk[y];
    x += step,y += step;
    return (x<len&&y<len)?rnk[x]<rnk[y]:x>y;
}
void buildSA()
{
    for(int i=0;i<len;i++)
        SA[i] = i,rnk[i] = S[i]-'a';
    step = 1;
    while(true)
    {
        sort( SA,SA+len,cmp );
        for(int i=0;i<len-1;i++)
            tmp[i+1] = tmp[i]+cmp(SA[i],SA[i+1]);
        for(int i=0;i<len;i++)
            rnk[SA[i]] = tmp[i];
        if( tmp[len-1]==len-1 )break;
        step *= 2;
    }
}
void buildLCP()
{
    for(int i=0,k=0;i<len;i++)
    {
        if( rnk[i]==len-1 )continue;
        int j = SA[rnk[i]+1];
        while( S[i+k]==S[j+k] )++k;
        lcp[rnk[i]] = k;
        k = max(0,k-1);
    }
}

string matchlcs(string s1,string s2)
{
    S = s1+"#"+s2;
    len = S.size();
    buildSA();
    buildLCP();
    for(int i=len-1;i>0;i--)
        swap(lcp[i],lcp[i-1]);
    int mx = 0,id = -1;
    for(int i=1;i<len;i++)
    {
        if(lcp[i]>=mx&&((SA[i-1]<=s1.size()&&SA[i]>s1.size())||(SA[i-1]>s1.size()&&SA[i]<=s1.size())))
        {
            if(id!=-1&&mx==lcp[i])
            {
                if(SA[i-1]>s1.size()&&id>SA[i-1])
                    id = SA[i-1];
                else if(SA[i]>s1.size()&&id>SA[i])
                    id = SA[i];
            }
            else
            {
                if(SA[i]>s1.size())
                    id = SA[i];
                else
                    id = SA[i-1];
            }
            mx = lcp[i];
        }
    }
    set<int>st;
    for(int i=1;i<len;i++)
    {
        if(lcp[i]==mx&&((SA[i-1]<=s1.size()&&SA[i]>s1.size())||(SA[i-1]>s1.size()&&SA[i]<=s1.size())))
        {
            if(SA[i-1]>s1.size())
                st.insert(SA[i-1]);
            else
                st.insert(SA[i]);
        }
    }
    S = s2;
    S += "#";
    len = S.size();
    buildSA();
    buildLCP();
    for(int i=len-1;i>0;i--)
        swap(lcp[i],lcp[i-1]);
    int l1 = s2.size();
    for(int i=1;i<l1;i++)
    {
        if(st.find(SA[i]+l1+1)!=st.end())
        {
            if(lcp[i]>=mx)
                st.insert(SA[i-1]+l1+1);
        }
        else if(st.find(SA[i-1]+l1+1)!=st.end())
        {
            if(lcp[i]>=mx)
                st.insert(SA[i]+l1+1);
        }
    }
    auto it = st.begin();
    id = *it;
    S = s1+"#"+s2;
    string result = S.substr(id,mx);
    return result;
    

}





struct search_results
{
    string matched_string;
    vector<pair<int, int>> indices;
};




int main() {

   int ndocs,nquerys;
   cin>>ndocs;
   vector<string> docs;
   string s;
   cin.tie(0);
   for (int i = 0; i < ndocs; ++i)
   {
       cin>>s;
       docs.push_back(s);
   }
   cin>>nquerys;
   string pattern;
   for (int i = 0; i < nquerys; ++i)
   { 
       search_results output;
       cin>>pattern;
       int maxlen = 0;
       for (int j = 0; j < ndocs; ++j)
       {
           string result =  matchlcs(docs[j],pattern);
           //cout<<j<<" result:- "<<result<<endl;

           if(result.size()>maxlen)
           {
                if(output.matched_string.size() == 0)
                {
                    output.matched_string = result;
                    output.indices.push_back(make_pair(j,docs[j].find(result)));
                }
                else
                {
                    output.matched_string = result;
                    output.indices.clear();   
                    output.indices.push_back(make_pair(j,docs[j].find(result)));
                }
                maxlen = result.size();


           }
           else if(result.size() == pattern.size() )
           {
                output.indices.push_back(make_pair(j,docs[j].find(result)));
           }
           
       }
       if(output.matched_string.size() == 0)
       {
        cout<<-1<<endl;
       }
       else
       {
            cout<<output.matched_string<<endl;
            for (int k = 0; k < output.indices.size(); ++k)
            {
                cout<<output.indices[k].first<<" "<<output.indices[k].second<<endl;
            }
       }


   }

}