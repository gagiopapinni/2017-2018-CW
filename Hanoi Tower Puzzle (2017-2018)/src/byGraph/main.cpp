#include <cmath>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include "ngraph/ngraph.hpp"

using namespace NGraph;
using namespace std;

enum vertexColor { white, gray, black };
typedef Graph::vertex vertex;

vertex appendLeft(vertex v,char digit){
    
  return  ( 1 * pow(10, to_string(v).length()) )*digit + v;  
 
}
void insertBiDirectedEdge (Graph& graph,Graph::vertex a,Graph::vertex b){

    graph.insert_edge(a,b);
    graph.insert_edge(b,a);

}
Graph* appendLeftOfAllNodes( const Graph& graph , char digit ){

    Graph* new_graph = new Graph(graph);

    for ( Graph::const_iterator p = graph.begin(); p != graph.end(); p++){

        long int old_node = Graph::node(p);
        long int new_node = appendLeft(old_node,digit);
        
        new_graph->insert_vertex(new_node);
        new_graph->absorb(new_node,old_node);
    
    }

    return new_graph;
}

Graph* generate( int n ){
   
    if( n == 1 ){
        Graph* smallestOne = new Graph;

        insertBiDirectedEdge(*smallestOne,1,2);
        insertBiDirectedEdge(*smallestOne,1,3);
        insertBiDirectedEdge(*smallestOne,2,3);

        return smallestOne;
    }

    Graph *base = generate(n-1),
          *first = appendLeftOfAllNodes(*base,1),
          *second = appendLeftOfAllNodes(*base,2),
          *third = appendLeftOfAllNodes(*base,3),
          *result = new Graph( *first + *second + *third );

    long int line_of_ones = 1;
    for(long int i = 0;i<n-2;i++) line_of_ones = line_of_ones*10 + 1; 
    
    insertBiDirectedEdge(*result,appendLeft(line_of_ones*1,2), appendLeft(line_of_ones*1,3));
    insertBiDirectedEdge(*result,appendLeft(line_of_ones*2,1), appendLeft(line_of_ones*2,3));
    insertBiDirectedEdge(*result,appendLeft(line_of_ones*3,2), appendLeft(line_of_ones*3,1));
    
    delete first, delete second, delete third, delete base ;
    return result;    
}

void bfsSearch(const Graph& graph, vertex s,vertex destination,map<vertex,vertex>& pred) 
{
     map<vertex,vertexColor> color;
     for ( Graph::const_iterator p = graph.begin(); p != graph.end(); p++)
        color[Graph::node(p)] = white;  
     
     pred[s] = 0;
     color[s] = gray;
     queue<vertex> q;
     q.push(s);
     
     while (!q.empty()) {
        vertex u = q.front();
        Graph::vertex_set neighbors = graph.out_neighbors(u);
        for(Graph::vertex_set::iterator ci = neighbors.begin();ci != neighbors.end (); ++ci) 
        {
           vertex v = Graph::node(ci);
           if (color[v] == white) {
             pred[v] = u;
             color[v] = gray;
             q.push(v);
           }
           if(v == destination) return; 
        } 
        q.pop() ;
        color[u] = black;
     }
}

void displayTheShortestWay( map<vertex,vertex>& pred,vertex a,vertex b){
    vertex current = b;
    int length = 0;

    while ( current != a ){
          length++;
          cout<<current<<endl;
          current = pred[current];  
    }

    cout<<a<<endl;
    cout<<"Number of moves:"<<length<<endl;
}  

int main()
{
    vertex a = 111, b = 333;
    map<vertex,vertex> pred;

    Graph *graph = generate(3);
    bfsSearch(*graph,a,b,pred);
    displayTheShortestWay(pred,a,b);

    return 0;
}
