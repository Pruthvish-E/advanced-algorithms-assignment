#include<iostream>
#include <vector>
using namespace std;


class survival_of_the_fittest_implementation
{
public:
    vector<double> solve(int, int, int);
};


vector<double> survival_of_the_fittest_implementation::solve(int a,int p,int k)
{
	double probabilities[a+1][p+1][k+1];
	for (int i = 0; i <= a; ++i)
	{
		for (int j = 0; j <=p ; ++j)
		{
			for (int w = 0;w <=k ; ++w)
			{
				probabilities[i][j][w] = 0;
			}
		}
	}
	probabilities[a][p][k] = 1;

	double pk = p*k;
	double ap = a*p;
	double ka = k*a;
	double total = ap+pk+ka;
	

	for (int i = a; i >=0 ; --i)
	{
		for (int j = p; j >=0 ; --j)
		{
			for (int w = k; w >=0 ; --w)
			{
				 
				if((i==0&&j==0) ||(i==0&&w==0) ||(w==0&&j==0) ) continue;
				 
				 pk = j*w;
				 ap = i*j;
				 ka = i*w;
				 total = ap+pk+ka;
	
				
					if(w>0) probabilities[i][j][w-1]+=  probabilities[i][j][w]*(pk/(double)total);
					if(i>0) probabilities[i-1][j][w]+= probabilities[i][j][w]*(ka/(double)total);
					if(j>0) probabilities[i][j-1][w]+= probabilities[i][j][w]*(ap/(double)total);
					
				
			
			}
		}
	}

	double probA = 0.0;
	double probP = 0.0;
	double probK = 0.0;
	
	for (int i = 1; i <=a ; ++i)
	{
		probA+=probabilities[i][0][0];
	}
	for (int i = 1; i <=p ; ++i)
	{
		probP+=probabilities[0][i][0];
	}
	for (int i = 1; i <=k ; ++i)
	{
		probK+=probabilities[0][0][i];
	}

	vector<double> v;
	v.push_back(probA);
	v.push_back(probP);
	v.push_back(probK);

	return v;

}
int main()
{
    survival_of_the_fittest_implementation solver;
    int a,p,k;
    cin>>a>>p>>k;
    vector<double> ans = solver.solve(a,p,k);
    printf("%.9f %.9f %.9f\n", (double)ans[0], (double)ans[1], (double)ans[2]);
}