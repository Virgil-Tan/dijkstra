#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <fstream>
#include <time.h>

using namespace std;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> note;

vector<vector<Edge>> graph;
vector<int> dist;

void dijkstra(int start) {
    priority_queue<note, vector<note>, greater<note>> pq;
    pq.push({ 0, start });
    dist[start] = 0;

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist > dist[cur_node]) {
            continue;
        }

        for (const Edge& edge : graph[cur_node]) {
            int next_node = edge.dest;
            int next_dist = edge.weight;

            if (dist[next_node] > cur_dist + next_dist) {
                dist[next_node] = cur_dist + next_dist;
                pq.push({ dist[next_node], next_node });
            }
        }
    }
}

int main() {
    //get map from txt file
    ifstream infile("/home/virgil/Documents/data/USA-road-d.FLA.gr");
//    ifstream infile("/home/virgil/CLionProjects/bellmanFord/mapDataTest.txt");
    if (!infile) {
        cerr << "Cannot open file: mapDataTest.txt" << endl;
        return 1;
    }

    int num_nodes, num_edges;
    infile >> num_nodes >> num_edges;
    num_nodes++;
    graph.resize(num_nodes);
    dist.resize(num_nodes, numeric_limits<int>::max());
    printf("notd num: %d, edges: %d", num_nodes, num_edges);
    for (int i = 0; i < num_edges; ++i) {
        Edge edge;
        char skip_word;
        infile >> skip_word  >> edge.src >> edge.dest >> edge.weight;
        graph[edge.src].push_back(edge);
    }
    infile.close();

    // Run Dijkstra's algorithm with a random starting node
    int start_node = 1;
    cout << "running dijkstra's algorithm with starting node " << start_node << endl;

    clock_t start, stop;
    double duration;
    start = clock();

    dijkstra(start_node);

    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC;

    cout << duration << endl;

    // print the shortest path distances
    cout << "finished" << endl;
//    for (int i = 0; i < num_nodes; ++i) {
//        cout << "node " << i << ": ";
//        if (dist[i] == numeric_limits<int>::max()) {
//            cout << "infinity" << endl;
//        }
//        else {
//            cout << dist[i] << endl;
//        }
//    }

    return 0;
}
