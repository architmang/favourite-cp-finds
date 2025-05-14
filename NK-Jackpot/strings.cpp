#include<bits/stdc++.h>
using namespace std; 

long getTotalPalindromeTransformationCost(string dna)
{
    long total = 0;
    int n = dna.size();
    for(int i=0; i<n; i++)
    {
        // start point i
        unordered_map<char, int> mp;
        for(int j=i; j<n; j++)
        {
            // end point j
            int odd = 0; 
            // declard fr every substring
            
            char c = dna[j];
            mp[c]++;
            
            for(auto k:mp)
            {
                if(k.second % 2 ) odd++;
            }
            total += odd/2;
        }
    }
    return total;
}

int main()
{
    cout << getTotalPalindromeTransformationCost("abba") << endl;
    return 0;
}