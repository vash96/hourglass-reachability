#include <bits/stdc++.h>
#include "dag.cpp"
using namespace std;

vector<int> naive_A(const DAG & dag)
{
    int n = dag.n_nodes();
    vector<int> A(n, 1);
    for(int i=n-1; i>=0; --i) {
        int u = dag.ith_node(i);
        int j = n;
        for(const auto v : dag.from(u)) {
            j = min(j, dag.rank_of(v));
        }
        for(int k=i+1; k<j; ++k) {
            A[k] = 0;
        }
    }

    return A;
}

vector<int> naive_B(const DAG & dag)
{
    int n = dag.n_nodes();
    vector<int> B(n, 1);
    for(int j=0; j<n; ++j) {
        int u = dag.ith_node(j);
        int i = -1;
        for(const auto v : dag.to(u)) {
            i = max(i, dag.rank_of(v));
        }
        for(int k=i+1; k<j; ++k) {
            B[k] = 0;
        }
    }

    return B;
}

void solve(const DAG & dag)
{
    const auto A = naive_A(dag);
    const auto B = naive_B(dag);

    // cout << "A: "; for(auto x : A) cout << x << " "; cout << "\n";
    // cout << "B: "; for(auto x : B) cout << x << " "; cout << "\n";

    vector<int> bottlenecks;
    for(int i=0; i<dag.n_nodes(); ++i) {
        if(A[i]*B[i] == 1) {
            bottlenecks.emplace_back(dag.ith_node(i));
        }
    }

    cout << bottlenecks.size() << "\n";
    for(const auto u : bottlenecks) {
        cout << u << " ";
    }
    cout << "\n";
}

int main()
{
    DAG dag;
    dag.read_dag(cin);
    dag.topo_sort();

    solve(dag);

    return 0;
}