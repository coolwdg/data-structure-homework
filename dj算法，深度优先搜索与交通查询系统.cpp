#include <iostream>
#include<vector>
using namespace std;
#define maxVertices 30   
#define maxEdges 30    
#define maxWeight 32767
string city[8] = { "beijing","shanghai","wulumuqi","xian","guangzhou","lasha" , "kunmng" , "wuhan"};
typedef int Type;		
typedef int Weight;		
typedef struct {
    int numVertices, numEdges;					
    Type VerticesList[maxVertices];				
    Weight Edge[maxVertices][maxVertices]; 		
}MGraph;


int getVertexPos(MGraph& G, Type x)		
{
    for (int i = 0; i < G.numVertices; i++)
    {
        if (G.VerticesList[i] == x)
            return i;
    }
    return -1;
}


int numberOfVertices(MGraph& G)   
{
    return G.numVertices;
}

void createMGraph(MGraph& G, Type v[], int n, Type ed[][2], Weight c[], int e)  
{
    G.numVertices = n; G.numEdges = e;
    int i, j, k;
    for (i = 0; i < G.numVertices; i++)  
    {
        G.VerticesList[i] = v[i];
        for (j = 0; j < G.numVertices; j++)
            G.Edge[i][j] = (i == j) ? 0 : maxWeight;			
    }
    for (k = 0; k < G.numEdges; k++)    
    {
        i = getVertexPos(G, ed[k][0]);  
        j = getVertexPos(G, ed[k][1]);
        G.Edge[i][j] = c[k];         
    }
}


void ShortestPath(MGraph& G, int v, Weight dist[], int path[])
{
    int n = numberOfVertices(G);
    int S[maxVertices];
    int i, j, k;
    Weight w, min;
    for (i = 0; i < n; i++)
    {
        dist[i] = G.Edge[v][i];
        S[i] = 0;
        if (i != v && dist[i] < maxWeight)
            path[i] = v;
        else
            path[i] = -1;
    }
    S[v] = 1;  dist[v] = 0; 
    for (i = 0; i < n - 1; i++)
    {
        min = maxWeight;
        int u = v;
        for (j = 0; j < n; j++)
            if (!S[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        S[u] = 1;
        for (k = 0; k < n; k++) {
            w = G.Edge[u][k];
            if (!S[k] && w < maxWeight && dist[u] + w < dist[k])
            {
                dist[k] = dist[u] + w;
                path[k] = u;
            }
        }

    }

}

void printShortestPath_price(MGraph& G, int v,int target,Weight dist[], int path[])
{
    
    int i, j, k, n = numberOfVertices(G);
    int d[maxVertices];

    if (target != v) {
        j = target;
        k = 0;
        while (j != v) {
            d[k++] = j;
            j = path[j];
        }
        d[k++] = v;
        cout << "The optimal path to city [" << city[target] << "] is:";

        while (k > 1)
        {
            cout << city[d[--k]] << "->";
        }
        cout << city[d[k - 1]];

        cout << endl;
        cout << "The cost is: " << dist[target] << " yuan" << endl;
    }
    
        
    
}

void printShortestPath_time(MGraph& G, int v,int target, Weight dist[], int path[])
{
    int i, j, k, n = numberOfVertices(G);
    int d[maxVertices];
    if (target != v) {
        j = target;
        k = 0;
        while (j != v) {
            d[k++] = j;
            j = path[j];
        }
        d[k++] = v;
        cout << "The optimal path to city [" << city[target] << "] is:";

        while (k > 1)
        {
            cout << city[d[--k]] << "->";
        }
        cout << city[d[k - 1]];

        cout << endl;
        cout << "The flying time is: " << dist[target] <<"min"<<endl;
        
    }
}

void printShortestPath_num(MGraph& G, int v,int target,Weight dist[], int path[])
{
    int i, j, k, n = numberOfVertices(G);
    int d[maxVertices];
    if (target != v) {
        j = target;
        k = 0;
        while (j != v) {
            d[k++] = j;
            j = path[j];
        }
        d[k++] = v;
        cout << "The optimal path to city [" << city[target] << "] is:";

        while (k > 1)
        {
            cout << city[d[--k]] << "->";
        }
        cout << city[d[k - 1]];

        cout << endl;
        
        cout << "The number of transfers is: " << dist[target] - 1 << endl;
    }
            
       
}
void printAllPaths(MGraph& G, int v, int target, int visited[], int pathLength, vector<vector<int>>& allPaths, vector<int>& currentPath) {
    visited[v] = 1;
    vector<int> path(pathLength);
    for (int i = 0; i < pathLength; i++) {
        path[i] = currentPath[i];
    }
    path.push_back(v);

    if (v == target) {
        allPaths.push_back(path);
    }
    else {
        for (int i = 0; i < G.numVertices; i++) {
            if (G.Edge[v][i] < maxWeight && visited[i] == 0) {
                printAllPaths(G, i, target, visited, pathLength + 1, allPaths, path);
            }
        }
    }

    visited[v] = 0;
}

void printPathsFromSourceToTarget(MGraph& G, int source, int target, vector<vector<int>>& allPaths) {
    int visited[maxVertices];

    for (int i = 0; i < G.numVertices; i++) {
        visited[i] = 0;
    }

    vector<int> currentPath;
    printAllPaths(G, source, target, visited, 0, allPaths, currentPath);
}
int main()
{
    MGraph G;

    int location, operation;
    int n = 8, e = 16;
    int path[20];
    int target;

    Type v[8] = { 0,1,2,3,4,5,6,7 };
    Type ed[16][2] = { 0,1,1,0,0,2,2,0,0,3,3,0,3,4,4,3,5,6,6,5,5,7,7,5,2,6,6,2,7,4,4,7 };	
    Weight a[16] = { 680,680,1150,1150,930,930,1320,1320,830,830,890,890,1480,1480,810,810 }; 
    Weight b[16] = { 65,65,115,115,95,95,140,140,85,85,90,90,165,165,100,100 }; 
    Weight c[16] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    Weight d[16][2] = {1620,1725,1800,1905,800,955,1045,1140,1525,1700,1235,1415,715,935,1015,1135,1020,1145,1235,1400,1415,1515,1625,1755,930,1215,1305,1550,705,845,1125,1305};
    Weight dist[100];

    cout << "enter from where to go(0:beijing 1:shanghai 2:wulumuqi 3:xian 4:guangzhou 5:lasha 6:kunmng 7:wuhan)" << endl;
    cin >> location;
    cout << "enter destination" << endl;
    cin >> target;
    cout << "enter operation(1:cost 2:flight time 3:transfers 4:total time)" << endl;
    cin >> operation;

    switch (operation) {
    case 1: {
        createMGraph(G, v, n, ed, a, e);
        ShortestPath(G, location, dist, path);
        printShortestPath_price(G, location, target,dist, path);
        break; }
    case 2: {
        createMGraph(G, v, n, ed, b, e);
        ShortestPath(G, location, dist, path);
        printShortestPath_time(G, location, target,dist, path);
        break; }
    case 3: {
        createMGraph(G, v, n, ed, c, e);
        ShortestPath(G, location, dist, path);
        printShortestPath_num(G, location, target,dist, path);
        break; }
    case 4: {
        createMGraph(G, v, n, ed, a, e);
    vector<vector<int>> allPaths;
    printPathsFromSourceToTarget(G, location, target, allPaths);
    int w1,w2;
    int result;
    int sum=0;
    int min=maxWeight;
    for (int i = 0; i < allPaths.size(); i++) {
        sum = 0;
        
        for (int j = 0; j < allPaths[i].size()-2; j+=2) {
            for (int k = 0; k < 16; k++)
            {
                if (allPaths[i][j] == ed[k][0] && allPaths[i][j + 1] == ed[k][1])
                {
                    sum += b[k];
                    w1 = k;
                   
                }
                if (allPaths[i][j+1] == ed[k][0] && allPaths[i][j + 2] == ed[k][1])
                {
                    
                    w2 = k;
                    
                }
            }
            if(d[w1][1]< d[w2][0])
                sum += (d[w2][0]/100- d[w1][1]/100)*60+ d[w2][0] % 100 - d[w1][1] % 100;
            else
                sum += (d[w2][0] / 100 - d[w1][1] / 100) * 60 + d[w2][0] % 100 - d[w1][1] % 100+24*60;
           
        }
        for (int k = 0; k < 16; k++)
        {
            if (allPaths[i][allPaths[i].size() - 2] == ed[k][0] && allPaths[i][allPaths[i].size() - 1] == ed[k][1])
            {
                sum += b[k];
                w1 = k;

            }
        }
        if (sum < min)
        {
            min = sum;
            result = i;
        }
        
        
    }
    cout << "The optimal path to city [" << city[target] << "] is:";
    for (int i = 0; i < allPaths[result].size(); i++)
    {
        cout << city[allPaths[result][i]] << " -> ";
        
    }
    cout << endl;

    cout <<"the total time is: " << min<<"min";

    }
    default:
        break;
    }
    


    return 0;
}
