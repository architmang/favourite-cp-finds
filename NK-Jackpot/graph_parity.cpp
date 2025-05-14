/*
An undirected graph with n nodes and m bidirectional edges.
A bit string b of length n, where each character b[i] is either '0' or '1'.

Define:
d_i = degree of node i modulo 2 (i.e., d_i = (number of edges connected to node i) % 2).

Task:
Modify the graph by removing some edges (you cannot add new edges) such that 
for every node i, d_i = b[i] (where b[i] is treated as a number, 0 or 1).

Print "YES" if possible else "NO"
*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back

vector<int> graph[10010];
set<pair<int,int>> edges;

int main()
{
    int m, n;
    cin >> n >> m;
    string b;
    cin >> b;
    for(int i=0; i<m; i++)
    {
        int a,b;
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
        edges.insert({min(a,b), max(a,b)});
    }

    int count_ones = 0;
    vector<int> d(n+1, 0);
    vector<int> mismatch;
    for(int i=1; i<=n; i++)
    {
        if(b[i-1] == '1') count_ones++;
        d[i] = graph[i].size();
        if(d[i]%2 != (int)b[i-1])
        {
            mismatch.pb(i);
        }
    }
    if(count_ones %2 || mismatch.size()%2) // sum of degrees is odd or odd no of mismatches
    {
        cout << "NO" << endl;
        return 0;
    }
    bool possible = true;
    vector<bool> visited (n+1, false);
    // iterate over set
    for(int i=0; i<mismatch.size(); i++)
    {
        int node = mismatch[i];
        if(visited[node]) continue;

        bool found = false;
        // try to find direct mismatch wala connection
        for(auto neigh: graph[node])
        {
            // if present in mismatch & unvisited
            if(find(mismatch.begin(), mismatch.end(), neigh)!=mismatch.end() && visited[neigh] == false)
            {
                found = true;
                visited[neigh] = true;
                visited[node] = true;
                edges.erase({min(neigh, node), max(neigh, node)});
                break;
            }
        }
        if(found) continue;

        // indirect connection
        for(auto neigh: graph[node])
        {
            // neigh is matched
            if(find(mismatch.begin(), mismatch.end(), neigh) != mismatch.end()) continue;
            for(auto k: graph[neigh])
            {
                // neigh has a mismatched node
                if(k == node) continue;
                if(find(mismatch.begin(), mismatch.end(), k) == mismatch.end()) continue;

                found = true;
                edges.erase({min(neigh, k), max(neigh, k)});
                edges.erase({min(node, neigh), max(node, neigh)});
                visited[node] = true;
                visited[k] = true;
                break;
            }
            if(found) break;
        }
        if(found == false)
        {
            possible = false;
            break;
        }
    }
    // final check -> if all mismatches are resolved
    for(auto node: mismatch)
    {
        if(visited[node] == false)
        {
            possible = false;
            break;
        }
    }
    if(possible == false)
        cout << "NO" << endl;
    else cout << "YES" << endl;
    
    return 0;
}
