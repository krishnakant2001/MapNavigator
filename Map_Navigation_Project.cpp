#include <bits/stdc++.h>
using namespace std;

void addEdge(unordered_map<int, list<pair<int, int>>> &adjList, int u, int v, int dist)
{
    adjList[u].push_back(make_pair(v, dist));
    adjList[v].push_back(make_pair(u, dist));
}

vector<int> dijkstra(unordered_map<int, list<pair<int, int>>> &adjList, int vertices, int source)
{

    // creation of distance array with infinite value initially
    vector<int> dist(vertices);
    vector<int> parent(vertices, -1);

    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
    }

    // creation of set on basis (distance, node)
    set<pair<int, int>> st;

    // initialise distance and set with source node
    dist[source] = 0;
    st.insert(make_pair(0, source));

    while (!st.empty())
    {
        // fetch top record
        auto top = *(st.begin());

        int nodeDistance = top.first;
        int topNode = top.second;

        // remove top record node
        st.erase(st.begin());

        // traverse on neighbours
        for (auto neighbour : adjList[topNode])
        {
            if (nodeDistance + neighbour.second < dist[neighbour.first])
            {

                // find record
                auto record = st.find(make_pair(dist[neighbour.first], neighbour.first));

                // if record found, then erase it
                if (record != st.end())
                {
                    st.erase(record);
                }

                // distance update
                dist[neighbour.first] = nodeDistance + neighbour.second;
                parent[neighbour.first] = topNode;

                // record push in set
                st.insert(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }

    return parent;
}
vector<string> shortestPath(unordered_map<string, int> &nodeMap, vector<int> &parent, string src, string des){
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

    for (int i = 0; i < temp.size(); i++)
    {
        for (auto &it : nodeMap)
            if (it.second == temp[i])
                ans.push_back(it.first);
    }

    return ans;
}
int main()
{
    vector<string> nodes;
    nodes.push_back("Ahmedabad");
    nodes.push_back("NewDelhi");
    nodes.push_back("Agra");
    nodes.push_back("Gwalior");
    nodes.push_back("Bhopal");
    nodes.push_back("Chandigarh");
    nodes.push_back("Kolkata");
    nodes.push_back("Lucknow");
    nodes.push_back("Morena");
    nodes.push_back("Jaipur");

    int vertices = nodes.size();

    unordered_map<string, int> nodeMap;

    for (int i = 0; i < vertices; i++)
    {
        nodeMap[nodes[i]] = i;
    }

    // prepare adjList
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


    cout << endl;
    cout << endl;
    //start
    cout << "****** Welcome to the Railways Train Route between two Stations ******" << endl;

    cout << endl;

    for(auto i : nodes){
        cout << i << endl;
    }
    cout << endl;

    cout << "NOTE : Pick the Source and Destination Stations with in the above List only" << endl;

    cout << endl;
    cout << endl;

    string src, des;
    cout << "Enter the Source Station : ";
    cin >> src;
    cout << endl;
    cout << "Enter the Destination Staion : ";
    cin >> des;

    cout << endl;

    vector<int> parent = dijkstra(adjList, vertices, nodeMap[src]);

    // find Shortest Path
    vector<string> ans = shortestPath(nodeMap, parent, src, des);


    cout << "Train Route :" << endl;

    int j = 0;
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
        if (j < ans.size() - 1)
        {
            cout << " -> ";
            j++;
        }
    }

    cout << endl;
    cout << endl;

    return 0;
}

// time : O(elogv);
// space : O(n + e);