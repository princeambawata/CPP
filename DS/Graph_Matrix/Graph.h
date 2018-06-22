#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<queue>
#include<climits>
#include<limits>
#include<set>
#include<algorithm>
#include "heap.h" // this is not used but can be used to get minimum edge in o(logn)
using namespace std;

class Graph{
vector<vector<int>*>* vertices; 
public:
   Graph(){
       vertices = new vector<vector<int>*>();
   }

   void addVertex(){
   	   vector<int>* v = new vector<int>();
   	   for(int i=0;i<vertices->size()+1;i++){
   	   	  v->push_back(0);
   	   }
   	   for(int i=0;i<vertices->size();i++){
          vector<int>* each = vertices->at(i);
          each->push_back(0);
   	   }
   	   vertices->push_back(v);
   }

   void removeVertex(int v){
   	  vector<int>* vec = vertices->at(v);
   	  for(int i=0;i<vertices->size();i++){
   	  	vector<int>* each = vertices->at(i);
   	  	each->erase(each->begin()+v);
   	  }
   	  vertices->erase(vertices->begin()+v);
   	  delete vec;
   }

   void addEdge(int u,int v,int w){
   	vector<int>* first = vertices->at(u);
   	vector<int>* sec = vertices->at(v);
   	first->at(v) = w;
   	sec->at(u) = w;
   	return;
   }

   void removeEdge(int u,int v){
   	vector<int>* first = vertices->at(u);
   	vector<int>* sec = vertices->at(v);
   	first->at(v) = 0;
   	sec->at(u) = 0;
   	return;
   }

   bool adjacents(int u,int v){
   	vector<int>* first = vertices->at(u);
   	vector<int>* sec = vertices->at(v);
   	if(first->at(v) == 1){
   		return true;
   	}
   	return false;
   }

   void print(){
   	for(int i=0;i<vertices->size();i++){
   		vector<int>* each = vertices->at(i);
   		cout<<i<<" : ";
   		for(int j=0;j<each->size();j++){
            cout<<each->at(j)<<",";
   		}
   		cout<<endl;
   	}
   	return;
   }

   void DFS(bool visited[],int i){
   	visited[i] = true;
   	vector<int>* v = vertices->at(i);
   	cout<<i<<",";
   	for(int j=0;j<v->size();j++){
   		if(v->at(j) == 1 && visited[j] == false){
           DFS(visited,j);
   		}
   	}
   	return;
   }

   void DFSTraversal(){
   	 bool* visited = new bool[vertices->size()];
   	 for(int i=0;i<vertices->size();i++){
   	 	visited[i] = false;
   	 }
   	 for(int i=0;i<vertices->size();i++){
   	 	if(visited[i] == false){
   	 		DFS(visited,i);
   	 	}
   	 }
   	 cout<<endl;
   	 delete visited;
   	 return;
   }

   void BFSTraversal(){
   	 queue<int> q;
   	 int x = 0;
   	 bool visited[vertices->size()];
   	 for(int i=0;i<vertices->size();i++){
   	 	visited[i] = false;
   	 }
   	 q.push(x);
   	 visited[0] = true;
   	 while(!q.empty()){
   	 	int i = q.front();
   	 	q.pop();
   	 	cout<<i<<",";
        vector<int>* v = vertices->at(i);
        for(int j=0;j<v->size();j++){
        	if(v->at(j) == 1 && visited[j] == false){
        		visited[j] = true;
        		q.push(j);
        	}
        } 
        if(q.empty()){
        	break;
        }
   	 }
   	 cout<<endl;
   	 return;
   }

   int mindist(int dist[],bool visited[]){
   	int min = INT_MAX,min_index;
   	for(int i=0;i<vertices->size();i++){
   		if(dist[i]<min && !visited[i]){
   			min = dist[i];
   			min_index = i;
   		}
   	}
   	return min_index;
   }

   void dijkastra(int src){
       bool visited[vertices->size()];
       int dist[vertices->size()];
       for(int i=0;i<vertices->size();i++){
       	 visited[i] = false;
       	 dist[i] = INT_MAX;
       }
       dist[src] = 0;
       for(int i=0;i<vertices->size()-1;i++){
       	 int index = mindist(dist,visited);
       	 visited[index] = true;
       	 vector<int>* adj = vertices->at(index);
       	 for(int j=0;j<adj->size();j++){
       	 	if((adj->at(j) + dist[index] < dist[j]) && adj->at(j) != 0 
       	 		                            && dist[index] != INT_MAX && !visited[j]){
       	 		dist[j] = adj->at(j) + dist[index];
       	 	}
       	 }
       }
       for(int i=0;i<vertices->size();i++){
       	cout<<dist[i]<<",";
       }
       cout<<endl;
       return;
   }

   void BellmanFord(int src){
   	 int dist[vertices->size()];
   	 for(int i=0;i<vertices->size();i++){
   	 	dist[i] = INT_MAX;
   	 }
   	 dist[src] = 0;
   	 set<pair<int,int>> s;

   	 for(int i=0;i<vertices->size();i++){ // maintaining all edges in set of pairs
   	 	vector<int>* v = vertices->at(i);
   	 	for(int j=0;j<v->size();j++){
   	 		if(v->at(j) != 0){
   	 		   pair<int,int> p(i,j);
   	 		   s.insert(p);
   	 		}
   	 	}
   	 }

   	 for(int i=0;i<vertices->size()-1;i++){ // iterate over graph v-1 times
   	 	set<pair<int,int>>::iterator it = s.begin();  // for all the edges
   	 	while(it != s.end()){
   	 		pair<int,int> p = (*it);
   	 		int x = p.first;
   	 		int y = p.second;
   	 		if((dist[y] > dist[x] + (vertices->at(x))->at(y)) && dist[x] != INT_MAX){
   	 			dist[y] = dist[x] + (vertices->at(x))->at(y);
   	 		}
   	 		it++;
   	 	}
   	 }

   	 for(int i=0;i<vertices->size();i++){
   	 	cout<<dist[i]<<",";
   	 }
   	 cout<<endl;
   	 return;
   }

   // MINIMUM Spanning Tree

   void PrimsAlgo(int src){ // same to same dijkastra only not adding the total sum
   	   int parent[vertices->size()];
       int dist[vertices->size()];
       bool visited[vertices->size()];
       for(int i=0;i<vertices->size();i++){
       	 dist[i] = INT_MAX;
       	 visited[i] = false;
       }
       dist[src] = 0;
       parent[src] = -1;
       for(int i=0;i<vertices->size()-1;i++){
       	 int index = mindist(dist,visited);
       	 visited[index] = true;
       	 vector<int>* adj = vertices->at(index);
         for(int j=0;j<adj->size();j++){
         	if(adj->at(j) != 0 && dist[j] > adj->at(j) && !visited[j]){
         		dist[j] = adj->at(j);
         		parent[j] = index;
         	}
         }
       }
       int cost = 0;
       for(int i=1;i<vertices->size();i++){
          cost = cost + (vertices->at(i))->at(parent[i]);
       } 
       cout<<"Minimum Cost Spanning tree : "<<cost<<endl;
       for(int i=0;i<vertices->size();i++){
       	  cout<<"parent of "<<i<<" is "<<parent[i]<<endl;
       }
       cout<<endl;
       return;
   }
   // used for the sort function 
   static bool compare(pair<pair<int,int>,int> p1,pair<pair<int,int>,int> p2){
       return (p1.second < p2.second);
   }

   int parentI(int i, int parent[]){
   	 if(parent[i] == i){
   	 	return i;
   	 }else{
   	 	return parentI(parent[i],parent);
   	 }
   }

   void KruskalsAlgo(){
   	  vector<pair<pair<int,int>,int>>* edges = new vector<pair<pair<int,int>,int>>();
      for(int i=0;i<vertices->size();i++){ // extract all the edges with weight
      	 vector<int>* adj = vertices->at(i);
      	 for(int j=0;j<adj->size();j++){
      	 	if(adj->at(j)!=0){
      	 		pair<int,int> p(i,j);
      	 		pair<pair<int,int>,int> P(p,adj->at(j));
      	 		edges->push_back(P);
      	 	}
      	 }
      }
      int parent[vertices->size()];
      for(int i=0;i<vertices->size();i++){
      	parent[i] = i;
      }
      sort(edges->begin(),edges->end(),compare); // sort according to weight

      int count = 0;  // maintainig count for unvisited edge in vector Edges;
      int i=0;
      while(i<vertices->size()-1){  // minimum spanning tree will have v-1 edges
          int min_index = count;
          count++; 
          pair<pair<int,int>,int> p = edges->at(min_index);
          pair<int,int> edge = p.first;
          int start = edge.first;
          int end = edge.second;
          // check wether start and end have same parent
          // if yes then discard that edge because it forms a cycle else add the cycle to MST
          int startParentI = parentI(start,parent);
          int endParentI = parentI(end,parent);
          if(startParentI != endParentI){
          	cout<<start<<" -- "<<end<<", weight : "<<(vertices->at(start))->at(end)<<endl;
            parent[start] = end;
            i++;
          }
      }
      return;
   }

};

#endif