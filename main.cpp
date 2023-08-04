#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <limits>
#include <ctime>

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
    ifstream file("/home/virgil/Downloads/USA-road-d.NY.gr");
//    ifstream file("/home/virgil/CLionProjects/dijkstra/mapDataTest2.txt");
    if (!file) {
        cerr << "Cannot open file." << endl;
        return 1;
    }

    string line;
    int num_nodes, num_edges;

    while (getline(file, line)) {
        istringstream iss(line);
        char identifier;
        iss >> identifier;

        if (identifier == 'p') {
            string temp;
            iss >> temp >> num_nodes >> num_edges;
            num_nodes++;
            graph.resize(num_nodes);
            dist.resize(num_nodes, numeric_limits<int>::max());
        } else if (identifier == 'a') {
            Edge edge;
            iss >> edge.src >> edge.dest >> edge.weight;
            graph[edge.src].push_back(edge);
        }
    }

    file.close();

    int start_node = 1;
    cout << "Running Dijkstra's algorithm with starting node " << start_node << "\n";

    clock_t start, stop;
    double duration;
    start = clock();

    dijkstra(start_node);

    stop = clock();
    duration = ((double)(stop - start)) / CLOCKS_PER_SEC;


    cout << "Finished\n";

    for (int i = 0; i < num_nodes; ++i) {
        cout << "Shortest path from node " << start_node << " to node " << i << ": ";
        if (dist[i] == numeric_limits<int>::max()) {
            cout << "infinity" << endl;
        }
        else {
            cout << dist[i] << endl;
        }
    }
    cout << "Time: " << duration << " seconds.\n";

    return 0;
}
