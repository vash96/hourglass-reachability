#pragma once

#include <vector>
#include <algorithm>
using namespace std;

class DAG {
private:
    int n, m;
    vector<int> t_sort, t_rank;
    vector<vector<int>> adj, reverse_adj;

    void topo_sort(int, vector<char>&);

public:
    void read_dag(istream&);

    void topo_sort();

    int n_nodes() const { return n; }
    int n_edges() const { return m; }
    int ith_node(int i) const { return t_sort[i]; }
    int rank_of(int u) const { return t_rank[u]; }
    const vector<int>& from(int u) const { return adj[u]; }
    const vector<int>& to(int u) const { return reverse_adj[u]; }

};



void DAG:: read_dag(istream& in)
{
    in >> n >> m;
    adj.resize(n);
    reverse_adj.resize(n);
    for(int i=0, u, v; i<m; ++i) {
        in >> u >> v;
        adj[u].emplace_back(v);
        reverse_adj[v].emplace_back(u);
    }
}

void DAG:: topo_sort()
{
    t_sort.reserve(n);
    t_rank.resize(n);

    vector<char> vis(n, 0);

    for(int u=0; u<n; ++u) {
        if(not vis[u]) {
            topo_sort(u, vis);
        }
    }

    reverse(t_sort.begin(), t_sort.end());
}

void DAG:: topo_sort(int u, vector<char> & vis)
{
    vis[u] = 1;
    for(const auto v : adj[u]) {
        if(not vis[v]) {
            topo_sort(v, vis);
        }
    }
    t_sort.emplace_back(u);
    t_rank[u] = n - t_sort.size();
}