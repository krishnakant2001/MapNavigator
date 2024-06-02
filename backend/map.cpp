#include <bits/stdc++.h>
using namespace std;

void addEdge(unordered_map<int, list<pair<int, int>>> &adjList, int u, int v, int dist)
{
    adjList[u].push_back(make_pair(v, dist));
    adjList[v].push_back(make_pair(u, dist));
}

vector<int> dijkstra(unordered_map<int, list<pair<int, int>>> &adjList, int vertices, int source)
{
    vector<int> dist(vertices, INT_MAX);
    vector<int> parent(vertices, -1);
    set<pair<int, int>> st;

    dist[source] = 0;
    st.insert(make_pair(0, source));

    while (!st.empty())
    {
        auto top = *(st.begin());
        int nodeDistance = top.first;
        int topNode = top.second;
        st.erase(st.begin());

        for (auto neighbour : adjList[topNode])
        {
            if (nodeDistance + neighbour.second < dist[neighbour.first])
            {
                auto record = st.find(make_pair(dist[neighbour.first], neighbour.first));
                if (record != st.end())
                {
                    st.erase(record);
                }
                dist[neighbour.first] = nodeDistance + neighbour.second;
                parent[neighbour.first] = topNode;
                st.insert(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }
    return parent;
}

vector<string> shortestPath(unordered_map<string, int> &nodeMap, vector<int> &parent, string src, string des)
{
    vector<int> temp;
    int currNode = nodeMap[des];
    temp.push_back(nodeMap[des]);

    while (currNode != nodeMap[src])
    {
        currNode = parent[currNode];
        temp.push_back(currNode);
    }

    reverse(temp.begin(), temp.end());
    vector<string> ans;

    for (int i : temp)
    {
        for (const auto &it : nodeMap)
        {
            if (it.second == i)
            {
                ans.push_back(it.first);
                break;
            }
        }
    }

    return ans;
}

unordered_map<string, int> initNodeMap(vector<string> &nodes)
{
    unordered_map<string, int> nodeMap;
    for (int i = 0; i < nodes.size(); i++)
    {
        nodeMap[nodes[i]] = i;
    }
    return nodeMap;
}

unordered_map<int, list<pair<int, int>>> initAdjList(unordered_map<string, int> &nodeMap)
{
    unordered_map<int, list<pair<int, int>>> adjList;
    addEdge(adjList, nodeMap["Jaipur"], nodeMap["Agra"], 270);
    addEdge(adjList, nodeMap["Jaipur"], nodeMap["Chandigarh"], 500);
    addEdge(adjList, nodeMap["Ahmedabad"], nodeMap["Agra"], 880);
    addEdge(adjList, nodeMap["Ahmedabad"], nodeMap["Bhopal"], 600);
    addEdge(adjList, nodeMap["Ahmedabad"], nodeMap["Jaipur"], 660);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Chandigarh"], 250);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Kolkata"], 1560);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Jaipur"], 310);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Ahmedabad"], 980);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Agra"], 240);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Gwalior"], 340);
    addEdge(adjList, nodeMap["NewDelhi"], nodeMap["Lucknow"], 500);
    addEdge(adjList, nodeMap["Agra"], nodeMap["Morena"], 80);
    addEdge(adjList, nodeMap["Agra"], nodeMap["Gwalior"], 120);
    addEdge(adjList, nodeMap["Gwalior"], nodeMap["Morena"], 50);
    addEdge(adjList, nodeMap["Lucknow"], nodeMap["Agra"], 330);
    addEdge(adjList, nodeMap["Lucknow"], nodeMap["Bhopal"], 650);
    addEdge(adjList, nodeMap["Kolkata"], nodeMap["Chandigarh"], 1790);
    addEdge(adjList, nodeMap["Kolkata"], nodeMap["Lucknow"], 1000);
    addEdge(adjList, nodeMap["Kolkata"], nodeMap["Bhopal"], 1430);
    addEdge(adjList, nodeMap["Bhopal"], nodeMap["Gwalior"], 410);
    return adjList;
}

string jsonResponse(vector<string> &path)
{
    stringstream ss;
    ss << "[";
    for (size_t i = 0; i < path.size(); i++)
    {
        ss << "\"" << path[i] << "\"";
        if (i < path.size() - 1)
        {
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

int main(int argc, char *argv[])
{
    vector<string> nodes = {
        "Ahmedabad", "NewDelhi", "Agra", "Gwalior", "Bhopal",
        "Chandigarh", "Kolkata", "Lucknow", "Morena", "Jaipur"};

    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <source> <destination>" << endl;
        return 1;
    }

    string src = argv[1];
    string des = argv[2];

    unordered_map<string, int> nodeMap = initNodeMap(nodes);
    unordered_map<int, list<pair<int, int>>> adjList = initAdjList(nodeMap);

    vector<int> parent = dijkstra(adjList, nodes.size(), nodeMap[src]);
    vector<string> path = shortestPath(nodeMap, parent, src, des);

    cout << jsonResponse(path) << endl;
    return 0;
}
