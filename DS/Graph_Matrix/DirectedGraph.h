#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<climits>
#include<limits>
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
   	first->at(v) = w;
   	return;
   }

   void removeEdge(int u,int v){
   	vector<int>* first = vertices->at(u);
   	first->at(v) = 0;
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

   void BFS(bool visited[],queue<int>& q){
    if(q.empty()){
      return;
    }
    int v = q.front();
    q.pop();
    cout<<v<<",";
    visited[v] = true;
    vector<int>* adj = vertices->at(v);
    for(int j=0;j<adj->size();j++){
      if(adj->at(j) == 1 && visited[j] == false){
         visited[j] = true;
         q.push(j);
      }
    }
    BFS(visited,q);
    return;
   }

   void BFSTraversal(){ // prob in case if a vertex is not an edge of any other vertex
   	 queue<int> q;
   	 bool visited[vertices->size()];
   	 for(int i=0;i<vertices->size();i++){
   	 	visited[i] = false;
   	 }
   	 for(int i=0;i<vertices->size();i++){
      if(visited[i] == false){
        q.push(i);
        BFS(visited,q);
      }
     }
     cout<<endl;
     return;
   }

   void Topo(bool visited[],stack<int>& s,int i){
    visited[i] = true;
    vector<int>* adj = vertices->at(i);
    for(int j=0;j<adj->size();j++){
      if(adj->at(j) == 1 && visited[j] == false){
        Topo(visited,s,j);
      }
    }
    s.push(i);
    return;
   }

   void TopologicalSort(){
     stack<int> s;
     bool visited[vertices->size()];
     for(int i=0;i<vertices->size();i++){
      visited[i] = false;
     }

     for(int i=0;i<vertices->size();i++){
       if(visited[i] == false){
         Topo(visited,s,i);
       }
     }
     while(!s.empty()){
      cout<<s.top()<<",";
      s.pop();
     }
     cout<<endl;
     return;
   }

   void path(bool visited[],queue<int>& q,map<int ,int>& m,int b){
    if(q.front() == b){
      return;
    }
    int v = q.front();
    q.pop();
    int cpl = m.at(v);
    vector<int>* adj = vertices->at(v);
    for(int i=0;i<adj->size();i++){
      if(adj->at(i) == 1 && visited[i] == false){
        m.insert(pair<int,int>(i,cpl + 1));
        q.push(i);
      }else if(adj->at(i) == 1 && visited[i] == true){
        int PathLenTillThis = m.at(i);
        if(cpl < PathLenTillThis -1){
          m.at(i) = cpl+1;
          q.push(i);
        }
      }
    }
    path(visited,q,m,b);
    return;
   }

   void ShortestPath(int a,int b){  // prob if there is no path b/w 'a' nad 'b'
     if(a==b){
      cout<<"ShortestPath len b/w "<<a<<" and "<<b<<" is : 0"<<endl;
     }
     queue<int> q;
     map<int ,int> m;
     int cpl = 0; // currentpathlen
     bool visited[vertices->size()];
     for(int i=0;i<vertices->size();i++){
      visited[i] = false;
     }
     q.push(a);
     m.insert(pair<int,int>(a,0));
     path(visited,q,m,b);
     cout<<"ShortestPath len b/w "<<a<<" and "<<b<<" is : "<<m.at(b)<<endl;
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
          //cout<<"called"<<endl;
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

// Minimize Cash Flow among a given set of friends who have borrowed money from each other
// directed graph problem.

/* Algo : 
   1. make an array of net amount of each vertex(total credited - total debited);
   2. send this array to the recursive function 
   3. get the most debited index(db) and most credited index(cr)
   4. get min of of the most debited and most credited amount;
   5. let say debited is less so and for example it be 3500;
   6. amount[cr] -= 3500 & amount[debited] += 3500; so debited will become 0;
   7. again call the recursive function on this updated amount.  
*/

int getMin(int x,int y){
  return(x<y ? x : y);
}

int getMaxI(int amount[]){
  int max_index = -1;
    int max = -999999;
    for(int i=0;i<vertices->size();i++){
      if(amount[i] > max){
        max = amount[i];
        max_index = i;
      }
    }
    return max_index;
}

int getMinI(int amount[]){
  int min_index = -1;
    int min = 999999;
    for(int i=0;i<vertices->size();i++){
      if(amount[i] < min){
        min = amount[i];
        min_index = i;
      }
    }
    return min_index;
}

void MinimizeCashFlowRec(int amount[]){
     int min_index = getMinI(amount);
     int max_index = getMaxI(amount);

     if(amount[max_index] == 0 && amount[min_index] == 0){
      return;
     }

     int min = getMin(-amount[min_index],amount[max_index]);
     amount[max_index] -= min;
     amount[min_index] += min;

     cout<<min_index<<" pays "<<min<<" to "<<max_index<<endl;

     MinimizeCashFlowRec(amount);
}

void MinimizeCashFlow(){
  int amount[vertices->size()];
  for(int i=0;i<vertices->size();i++){
    int total_debit = 0;
    int total_credit = 0;
    for(int j=0;j<vertices->size();j++){
            total_debit += (vertices->at(i))->at(j);
    }
        for(int j=0;j<vertices->size();j++){
          total_credit += (vertices->at(j))->at(i);
        }
        amount[i] = total_credit - total_debit;
  }
  MinimizeCashFlowRec(amount);
  return;
}


int TSP(int dp[][4],int mask,int pos,int VISITED_ALL,int cities,int start){
   if(mask == VISITED_ALL){
      return (vertices->at(pos))->at(start);
   }

   if(dp[mask][pos] != -1){
     return dp[mask][pos];
   }

   int ans = INT_MAX;

   for(int city=0;city<cities;city++){
      if((mask&(1<<city)) == 0){
          int newAns = (vertices->at(pos))->at(city)
                                  + TSP(dp,mask|(1<<city),city,VISITED_ALL,cities,start);
          ans = min(ans,newAns);
      }
   }
   return dp[mask][pos] = ans;
}

};

#endif