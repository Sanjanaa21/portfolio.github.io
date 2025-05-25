#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
    int V; // Number of vertices (products)
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int vertices);
    void addEdge(int u, int v);
    void tarjansAlgorithm(vector<vector<int>>& result);

private:
    void tarjanDFS(int u, vector<int>& low, vector<int>& discovery, vector<bool>& inStack, stack<int>& st, int& time, vector<vector<int>>& result);
};

Graph::Graph(int vertices) : V(vertices) {
    adj.resize(V);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
}

void Graph::tarjanDFS(int u, vector<int>& low, vector<int>& discovery, vector<bool>& inStack, stack<int>& st, int& time, vector<vector<int>>& result) {
    discovery[u] = low[u] = ++time;
    st.push(u);
    inStack[u] = true;

    for (int v : adj[u]) {
        if (discovery[v] == -1) {
            tarjanDFS(v, low, discovery, inStack, st, time, result);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], discovery[v]);
        }
    }

    if (low[u] == discovery[u]) {
        vector<int> component;
        while (true) {
            int v = st.top();
            st.pop();
            inStack[v] = false;
            component.push_back(v);
            if (v == u) break;
        }
        result.push_back(component);
    }
}

void Graph::tarjansAlgorithm(vector<vector<int>>& result) {
    vector<int> discovery(V, -1);
    vector<int> low(V, -1);
    vector<bool> inStack(V, false);
    stack<int> st;
    int time = 0;

    for (int i = 0; i < V; ++i) {
        if (discovery[i] == -1) {
            tarjanDFS(i, low, discovery, inStack, st, time, result);
        }
    }
}

// Example usage
int main() {
    int numProducts = 5;
    Graph g(numProducts);

    // Add edges (example: product relationships)
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(3, 4);

    vector<vector<int>> sccs;
    g.tarjansAlgorithm(sccs);

    // Output SCCs (product clusters)
    cout << "Strongly Connected Components (SCCs):\n";
    for (const auto& scc : sccs) {
        cout << "Cluster:";
        for (int product : scc) {
            cout << " " << product;
        }
        cout << endl;
    }

    return 0;
}
