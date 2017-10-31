/*
    Programmer: Dalton Modlin
    Class: CS1510 Data Structures
    Section: A
    Professor: Dr. Morales
*/

#include <iostream>
#include <queue>
#include <vector>
#include <climits>

//Macro's for convenience
#define veci vector<int>
#define vecb vector<bool>
#define vecs vector<string>
#define vecpairi vector<pair<int,int> >
#define INF INT_MAX

using namespace std;

const int size=10001; //Maximum possible number of vertices. Preallocating space for DataStructures accordingly

// Comparitor for checking edges
class prioritize
{
  public: bool operator ()(pair<int, int>&p1, pair<int, int>&p2)
  {
    return p1.second>p2.second;
  }
};

void Dijkstra(int source, int dis[], bool vis[], vecpairi a[])
{
  //Initialize distances to infinity.
  for(int i=0;i<size;i++)
    dis[i]=INF;
  //Priority queue to store vertex,weight pairs
  priority_queue<pair<int,int > ,vector<pair< int, int> >, prioritize > pq;

  //Pushing the source with distance from itself as 0 to guarantee it as starting point.
  pq.push(make_pair(source, dis[source] = 0));
  while(!pq.empty())
  {
    /*Current vertex. The shortest distance for this has been found*/
    pair<int, int> curr = pq.top();
    pq.pop();
    /*'cw' the final shortest distance for this vertex*/
    int cv = curr.first,cw = curr.second;
    
    /* If the vertex is already visited,
       no point in exploring adjacent vertices*/
    if(vis[cv])
        continue;
    vis[cv]=true;
    /*Iterating through all adjacent vertices*/
    for(int i = 0; i<a[cv].size(); i++) {
      /*If this node is not visited and the current parent node
        distance+distance from there to this node is shorter than the
        initial distace set to this node, update it*/
      if(!vis[a[cv][i].first] && a[cv][i].second+cw < dis[a[cv][i].first]) {
        /*Set the new distance and add to priority queue*/
        pq.push(make_pair(a[cv][i].first,(dis[a[cv][i].first]=a[cv]
          [i].second+cw)));
      }
    }
  }
}

int main()
{
  string graphName, sourceName, targetName, tempString;
  int sourceNumber = 0;
  int numTests     = 0;
  int nodeEdges    = 0; 
  int finishNumber = 0; 
  int weight       = 0;
  int totalEdges   = 0;

  vector <veci > matrix;
  veci numEdges;
  vector <vecs > verts;     //Intakes names of vertex's.
  sourceName = "airport";   //Required start location name for assignment.
  targetName = "robotbar";  //Required finish location name for assignment.
  int counter = 0;

  int numNodes,x,y,w;
  cin >> numTests;
  while (counter < numTests)
  {
    vecpairi a[size];       //Adjacency list
    int dis[size];          //Stores shortest distance
    bool vis[size]={0};     //Determines whether the node has been visited or not
    totalEdges = 0;

    cin >> graphName;
    cin >> numNodes;

    matrix.clear(); numEdges.clear(); verts.clear();

    for (int k = 0; k < numNodes; k++)
    {
      vecs rowStrings;
      veci rowDist;
      rowStrings.clear();
      rowDist.clear();
      cin >> tempString;  //Intakes name of vertex.
      if (tempString == sourceName)
      {
        sourceNumber = k;
      }
      else if (tempString == targetName)
      {
        finishNumber = k;
      }

      rowStrings.push_back(tempString);

      cin >> nodeEdges;                        //Intakes number of edges for a node.
      numEdges.push_back(nodeEdges);
      totalEdges += nodeEdges;
      for(int j = 0; j < nodeEdges; j++) {
        cin >> tempString;             //Intakes the name of a target node.
        rowStrings.push_back(tempString);
        cin >> weight;                 //Intakes the weight of an edge to a target node.
        rowDist.push_back(weight);
      }

      verts.push_back(rowStrings);
      matrix.push_back(rowDist);
    }

    for(int j = 0; j < numNodes; j++) {
      x = j;
      for(unsigned int k = 1; k < verts[j].size(); k++) {
        for(int p = 1; p < numNodes; p++) {
          if(verts[j][k] == verts[p][0])
          {
            y = p;
            w = matrix[j][k - 1];
            a[x].push_back(make_pair(y,w));
            a[y].push_back(make_pair(x,w));
            break;
          }
        }
      }
    }

    Dijkstra(sourceNumber, dis, vis, a);

    cout<< "#" << counter + 1<< " : "<< graphName << ", "
         << dis[finishNumber] << " tokens.\n";

    counter++;
  }

  return 0;
}
