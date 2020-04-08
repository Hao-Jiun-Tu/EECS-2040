#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <utility>
#include <vector>
#include <set>
#include <climits>

#define MAX 1e9
#define INF 0x3f3f3f3f

using namespace std;

class Edge {
public:
  int from, dest, weight;
  double resp;
  bool valid;
  // struct constructor
  Edge(int from, int to, int w, double resp):from(from), dest(to), weight(w), resp(resp), valid(true) {}
  
  bool operator==(const int& dest){
    if (dest == this->dest) {
        return true ;
    }
    return false ;
  }

};

class Graph {
 private:
  int _num_vertex;         // number of vertex
  vector<list<Edge>> _AdjList;  // adj list
  vector<long long int> prede, dist, next;

  void __bfs__(int start);
  void __prim__();
  long long int __dijkstraw__(int start, int to);
  long long int __dijkstrar__(int start, int to, int credit);
  int __connected_num__();

 public:
  // Graph construct
  Graph() : _num_vertex(0) {}  // default construct
  Graph(int v) : _num_vertex(v) { _AdjList.resize(_num_vertex); }

  // Edge operorter
  void addEdge(int from, int to, int weight, double resp);
  void delEdge(int from, int to);

  // contral unit
  void Shortest(int start, int to);
  void Important();
  void Map();
  void exchange(int from, int dest, int num, int mode, int limit);
  void accumulate(double& ans, vector<pair<int, double > > predecessor, int target);
  long long int auto_walk(int v1, int v2, int credit, int limit);
  void CreditExchange(int from, int to, int credit);
  // Graph traversal
  bool DFS();
  bool BFS();
};



void Graph::__bfs__(int start) {
  // Mark all the vertices as not visited
  vector<int> visited(_num_vertex, 0);
  // Create a queue for BFS
  list<int> queue;

  // Mark the current node as visited and enqueue it
  visited[start] = true;
  queue.push_back(start);

  cout << "BFS start from [" << start << "]: ";
  while (!queue.empty()) {
    // Dequeue a vertex from queue and print it
    start = queue.front();
    cout << start << " ";
    queue.pop_front();

    // Get all adjacent vertices of the dequeued
    // vertex s. If a adjacent has not been visited,
    // then mark it visited and enqueue it
    for (list<Edge>::iterator itr = _AdjList[start].begin(); itr != _AdjList[start].end();
         ++itr) {
      int v = (*itr).dest;
      if (!visited[v]) {
        visited[v] = 1;
        queue.push_back(v);
      }
    }
  }
  cout << endl;
}


long long int Graph::__dijkstraw__(int v1, int v2){
    long long int dist[_num_vertex] ;
    bool been_chose[_num_vertex] ;
    int i ;
    
    for (i=0; i<_num_vertex; i++) {
        dist[i] = LLONG_MAX;
        been_chose[i] = false ;
    }
    dist[v1] = 0 ;
    been_chose[v1] = true ;
    for (auto c : _AdjList[v1]) {
        dist[c.dest] = c.weight ;
    }
    
    for (i=0; i<_num_vertex-1; i++) {
        long long int least_weight=LLONG_MAX ;
        int l_id=v1 ;
        
        for (int j=0; j<_num_vertex; j++) {
            if (dist[j] < least_weight && !been_chose[j]) {
                least_weight = dist[j] ;
                l_id = j ;
            }
        }
        been_chose[l_id] = true ;
        for (auto c : _AdjList[l_id]) {
            if (!been_chose[c.dest] && dist[c.dest] > dist[l_id]+c.weight) {
                dist[c.dest] = dist[l_id]+c.weight ;
            }
        }
    }
    
    return dist[v2] ;
}

long long int Graph::__dijkstrar__(int v1, int v2, int credit) {
    long long int credits[_num_vertex] ;
    bool been_chose[_num_vertex] ;
    int i ;
    
    for (i=0; i<_num_vertex; i++) {
        credits[i] = 0 ;
        been_chose[i] = false ;
    }
    credits[v1] = credit ;
    been_chose[v1] = true ;
    for (auto c : _AdjList[v1]) {
        credits[c.dest] = credit*c.resp ;
    }
    
    for (i=0; i<_num_vertex-1; i++) {
        long long int biggest_rate=0 ;
        int b_id=v1 ;
        
        for (int j=0; j<_num_vertex; j++) {
            if (credits[j] > biggest_rate && !been_chose[j]) {
                biggest_rate = credits[j] ;
                b_id = j ;
            }
        }
        been_chose[b_id] = true ;
        
        for (auto c : _AdjList[b_id]) {
            if (credits[c.dest] < credits[b_id]*c.resp && !been_chose[c.dest]) {
                credits[c.dest] = credits[b_id]*c.resp ;
            }
        }
    }
    
    return credits[v2] ;
}

void Graph::__prim__(){
    long long int dist[_num_vertex] ;
    bool been_chose[_num_vertex] ;
    long long int cost=0 ;
    int i ;
    
    for (i=0; i<_num_vertex; i++) {
        dist[i] = LLONG_MAX ;
        been_chose[i] = false ;
    }
    dist[0] = 0 ;
    been_chose[0] = true ;
    for (auto c : _AdjList[0]) {
        dist[c.dest] = c.weight ;
    }
    
    for (i=0; i<_num_vertex-1; i++) {
        long long int least_weight=LLONG_MAX ;
        int l_id=0 ;
        
        for (int j=0; j<_num_vertex; j++) {
            if (dist[j] < least_weight && !been_chose[j]) {
                least_weight = dist[j] ;
                l_id = j ;
            }
        }
        been_chose[l_id] = true ;
        
        for (auto c : _AdjList[l_id]) {
            if (!been_chose[c.dest] && dist[c.dest] > c.weight) {
                dist[c.dest] = c.weight ;
            }
        }
    }
    
    for (i=0; i<_num_vertex; i++) {
        if (been_chose[i] == false) {
            cout << "Error" << endl ;
            return ;
        }
        cost += dist[i] ;
    }
    
    cout << cost << endl ;
}



int Graph::__connected_num__(){
    int connect_num = 0 ;
    bool visited[_num_vertex];
    memset(visited, false, sizeof(bool) * _num_vertex);
    
    queue<int> q ;
    q.push(0) ;
    visited[0] = true ;
    
    while (!q.empty()) {
        int id = q.front() ; q.pop() ;
        for (list<Edge>::iterator itr = _AdjList[id].begin(); itr != _AdjList[id].end(); ++itr) {
            if (!visited[itr->dest] && itr->valid) {
                q.push(itr->dest) ;
                visited[itr->dest] = true ;
            }
        }
    }
    
    for (auto itr : visited) {
        connect_num ++ ;
        if (itr == false) {
            connect_num-- ;
        }
    }
    
    return connect_num ;
}

//Public member function
void Graph::addEdge(int from, int to, int weight, double resp) {
  if(from == to) return;
  //cout<<"Add edge in " << from <<"-"<< to <<endl;
  for(list<Edge>::iterator itr = _AdjList[from].begin(); itr != _AdjList[from].end(); ++itr){
    if((*itr).dest == to) _AdjList[from].erase(itr);
  }
  _AdjList[from].push_back(Edge(from, to, weight, resp));
   
  // add v2->v1
  for(list<Edge>::iterator itr = _AdjList[to].begin(); itr != _AdjList[to].end(); ++itr){
    if((*itr).dest == from) _AdjList[to].erase(itr);
  }
  _AdjList[to].push_back(Edge(to, from, weight, resp));
}

void Graph::delEdge(int from, int to) {
  if(from == to) return;
  for (auto itr = _AdjList[from].begin();
       itr != _AdjList[from].end(); ++itr) {
    if ((*itr).dest == to) {
      _AdjList[from].erase(itr);
    }
  }
  for (auto itr = _AdjList[to].begin(); itr != _AdjList[to].end(); ++itr) {
    if ((*itr).dest == from) {
      _AdjList[to].erase(itr);
    }
  }
}

bool Graph::BFS() {
  __bfs__(0);
  return true;
}

void Graph::Map(){
  //cout<<"Map ";
  __prim__();
}

void Graph::Shortest(int start, int to){
  //cout<<"Shortest is: ";
  cout<< __dijkstraw__(start, to) << endl;
}

long long int Graph::auto_walk(int v1, int v2, int credit, int limit){
    long long int credits[_num_vertex] ;
    bool flag ;
    int i ;
    
    for (i=0; i< _num_vertex; i++) {
        credits[i] = 0 ;
    }
    credits[v1] = credit ;
    
    vector<list<int>> ans ;
    queue<list<int>> q ;
    queue<set<pair<int, int>>> been_chose ;
    
    list<int> lv1 ;
    lv1.push_back(v1) ;
    set<pair<int, int>> sv1 ;
    q.push(lv1) ;
    been_chose.push(sv1) ;
    
    while (!q.empty()) {
        list<int> path = q.front() ; q.pop() ;
        flag = false ;
        set<pair<int, int>> done = been_chose.front() ; been_chose.pop() ;
        
        if (path.size() > limit) {
            ans.emplace_back(path) ;
            continue ;
        }
        
        int last_visit = path.back() ;
        
        for (auto c : _AdjList[last_visit]) {
            if (done.count(make_pair(last_visit, c.dest)) == 0 &&
                done.count(make_pair(c.dest, last_visit)) == 0) {
                list<int> n_path = path ;
                set<pair<int, int>> n_done = done ;
                flag = true ;
                n_path.push_back(c.dest) ;
                n_done.insert(make_pair(last_visit, c.dest)) ;
                q.push(n_path) ;
                been_chose.push(n_done) ;
            }
        }
        if (flag == false) {
            ans.emplace_back(path) ;
        }
    }
//    while (!q.empty()) {
//        ans.emplace_back(q.front()) ;
//        q.pop() ;
//    }
    
    for (auto l : ans) {
        long long int temp[_num_vertex] ;
        int last_step = v1 ;
        for (i=0; i<_num_vertex; i++) {
            temp[i] = 0 ;
        }
        temp[v1] = credit ;
        for (auto p : l) {
            if (last_step == p) {
                continue ;
            }
            int new_c;
            for(auto itr = _AdjList[last_step].begin(); itr != _AdjList[last_step].end(); ++itr){
              if((*itr).dest == p){
                new_c = (*itr).resp * temp[last_step];
              }
            }
            temp[p] = new_c ;
            if (new_c > credits[p]) {
                credits[p] = new_c ;
            }
            last_step = p ;
        }
    }
    
    return credits[v2] ;
}

void Graph::Important(){
    int original = __connected_num__() ;
    
    for (auto c=_AdjList.begin(); c!=_AdjList.end(); c++) {
        for (auto d=c->begin(); d!=c->end(); d++) {
            d->valid = false ;
            if (__connected_num__() != original) {
                d->valid = true ;
                cout << "Yes" << endl ;
                return ;
            }
            d->valid = true ;
        }
    }
    cout << "No" << endl ;
}

void Graph::CreditExchange(int from, int to, int credit){
  cout<<__dijkstrar__(from, to, credit)<<endl;
}

int main(void) {
  #ifdef DEBUG
  freopen("test.in","r", stdin);
  #endif

  int num; cin>>num;
  Graph g(num); //cout<<num<<endl;
  string com;
  while(cin >> com){
      int sub1, sub2, sub3, sub5;
      double sub4;
      if(com == "Add"){
          cin>>sub1>>sub2>>sub3>>sub4;
          g.addEdge(sub1, sub2, sub3, sub4);
      }else if(com == "Delete"){
          cin>>sub1>>sub2;
          g.delEdge(sub1, sub2);
      }else if(com == "Shortest"){
          cin>>sub1>>sub2;
          g.Shortest(sub1, sub2);
      }else if(com == "Map"){
          g.Map();
      }else if(com == "ImportantBus"){
          g.Important();
      }else if(com == "CreditExchange"){
          cin>>sub1>>sub2>>sub3;
          g.CreditExchange(sub1, sub2, sub3);
      }else if(com == "CreditExchange2"){
        cin>>sub1>>sub2>>sub3>>sub5;
        cout<<g.auto_walk(sub1, sub2, sub3, sub5) << endl;
      }else {
        
      }
  }
  return 0;
}
