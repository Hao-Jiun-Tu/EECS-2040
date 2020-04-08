#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <fstream>
#include <signal.h>

using namespace std;

vector<int> coreness;

set<int> MAX_clique;
set<int> *vertex_kb;

void Print_K_core(int , int);
void BronKerbosch(set<int> , vector<int> );
void Print_Clique(set<int> );
void signalHandler(int signum);

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);
    vector<int> deg;

    int v1, v2;

    string v_num = string(argv[2]);
    int V = std::stoi(v_num);


	vector<vector<int> > vertex(V);
	vector<int> P(V);
	vertex_kb = new set<int> [V];


    freopen(argv[1], "r", stdin);
    while(cin >> v1 >> v2){
        if(v1 == v2)
            continue;
        vertex[v1].push_back(v2);
        vertex[v2].push_back(v1);
        vertex_kb[v1].insert(v2);
        vertex_kb[v2].insert(v1);
    }

    set<pair<int, int> > vert;//<deg, vertex_id>
    set<pair<int, int> >::iterator it1;


    for(int i = 0; i < V ; i++){
        vert.insert({vertex[i].size(), i});
        deg.push_back(vertex[i].size());
        coreness.push_back(vertex[i].size());
    }

    int cnt = V;
	int kb_v = 0;
    it1 = vert.begin();

    while(!vert.empty())
    {
        int vertex_id = it1->second;
        int vertex_deg = it1->first;

        coreness[vertex_id] = vertex_deg;
        vert.erase(it1);

		P[--cnt] = vertex_id;
        if(coreness[vertex_id] >= 499) //to count vertices' coreness >= 499 to find 500 >> clique
			kb_v++;

        for(int i = 0; i < vertex[vertex_id].size(); i++){
                if(deg[vertex[vertex_id][i]] > vertex_deg){
                    vert.erase({deg[vertex[vertex_id][i]], vertex[vertex_id][i]});
                    vert.insert({--deg[vertex[vertex_id][i]], vertex[vertex_id][i]});
                }
                else{
                }
        }
        it1 = vert.begin();
    }
	P.erase(P.begin() + kb_v , P.end()); //delete vertices' coreness < 499

    //Print_K_core(V, 0);

    set<int> R;
    BronKerbosch(R, P);

    return 0;

}

void BronKerbosch(set<int> R, vector<int> P)
{
	if(P.size() == 0){
        if(R.size() > MAX_clique.size()){
			MAX_clique.clear();
            Print_Clique(R);
            for(set<int>::iterator it = R.begin(); it != R.end(); ++it){
                MAX_clique.insert(*it);
            }
            return;
        }
        else
        	return;
    }
    else{
    	bool put_to_R;
        vector<int> NEW_P;
        vector<int>::iterator it = P.begin();
        while(it != P.end()){
	        R.insert(*it);
	        int temp = *it;
	        P.erase(it);
	        for(vector<int>::iterator it2 = P.begin(); it2 != P.end(); ++it2){
	            if(vertex_kb[temp].count(*it2) > 0)
	                put_to_R = 1;
	            else
	                put_to_R = 0;
	            if(put_to_R)
	                NEW_P.push_back(*it2);
	        }
	        BronKerbosch(R, NEW_P);
	       	R.erase(temp);

	       	NEW_P.clear();
	       	it = P.begin();
	    }
    }
}

void Print_K_core(int V, int n)
{
    ofstream Out_File("kcore.txt");
    for(int i = 0; i < V; i++){
        if(coreness[i] >= n)
            Out_File << i << " " << coreness[i] << endl;
    }
}

void Print_Clique(set<int> R)
{
    ofstream Out_File("clique.txt");

    for(set<int>::iterator it = R.begin(); it != R.end(); it++){
        Out_File << *it << endl;
    }
}

void signalHandler(int signum)
{
	ofstream Out_File("clique.txt");

    for(set<int>::iterator it = MAX_clique.begin(); it != MAX_clique.end(); it++){
        Out_File << *it << endl;
    }
	exit(signum);
}
