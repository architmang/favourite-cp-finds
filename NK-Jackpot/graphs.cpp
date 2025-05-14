#include <bits/stdc++.h>
using namespace std;

int find(int x, vector<int> parent)
{
    if( x  == parent[x])
        return x;
    return parent[x] = find(parent[x], parent);
}

int getMinMaxLatency(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight, int k)
{
    int left = 1;
    int right = *max_element(g_weight.begin(), g_weight.end());
    int result = right;
    // sort(g_weight.begin(), g_weight.end()); disconnects ordering

    while(left <= right)
    {
        int mid = (left + right)/2;
        vector<int> parent(g_nodes + 1, 0);
        for(int i=1; i<g_nodes + 1; i++)
        {
            parent[i] = i;
        }
        for(int i=0; i<g_weight.size(); i++) 
        {
            if(g_weight[i] > mid) continue;
            int u = find(g_from[i], parent);
            int v = find(g_to[i], parent);
            if(u!=v)
                parent[u] = v;
        }

        // no of components
        set<int> comp;
        for(int i=1; i<=g_nodes; i++) 
        {
            comp.insert(find(i, parent));
        }
        if(comp.size() <= k)
        {
            result = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    return result;
}

int main() {
    // Test Case
    int g_nodes = 4;
    vector<int> g_from = {1, 2, 3};
    vector<int> g_to = {2, 3, 4};
    vector<int> g_weight = {3, 5, 1};
    int k = 2;

    int result = getMinMaxLatency(g_nodes, g_from, g_to, g_weight, k);
    cout << "Minimum Maximum Latency: " << result << endl;  // Expected: 3

    return 0;
}