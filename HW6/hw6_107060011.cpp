#include <cstring>
#include <iostream>

#define MAX 100
#define INF 0x3f3f3f3f

using namespace std;

const int v_MAX = 100;
//int v_num;
//double edge[v_MAX][v_MAX];

void Add(double [][v_MAX] , int , int , double );
void Delete(double [][v_MAX] , int , int );
bool is_Connected(double [][v_MAX]);
void AC(double [][v_MAX]);
double Diameter(double [][v_MAX]);
double SOSPD(double [][v_MAX]);
void Floyd_Warshall__Kariv_Hakimi(double [][v_MAX], int [][v_MAX], double [][v_MAX]);

class MDST {
public:
    double edge[v_MAX][v_MAX];
    int v_num;
    MDST(int num){
        v_num = num;
        for(int i = 0; i < v_MAX; i++){
            for(int j = 0; j < v_MAX; j++)
                edge[i][j] = INF;
        }
        for(int i = 0; i < v_num; i++)
            edge[i][i] = 0;
    };
    void Add(int , int , double );
    void Delete(int , int );
    void DFS(int , bool* );
    bool is_Connected();
    void AC();
    double Diameter();
    double SOSPD();
    void Floyd_Warshall__Kariv_Hakimi(double [][v_MAX], int [][v_MAX]);

};
void MDST::Add(int v1, int v2, double w){
    edge[v1][v2] = w;
    edge[v2][v1] = w;
}
void MDST::Delete(int v1, int v2){
    edge[v1][v2] = INF;
    edge[v2][v1] = INF;
}
void MDST::DFS(int start_v, bool *visited){
    visited[start_v] = true;

    for(int v = 0; v < v_num; v++)
        if(edge[start_v][v] != INF)
            if(!visited[v])
                MDST.DFS(edge, v, visited);
}

bool MDST::is_Connected(){
    bool visited[v_num];

    MDST.DFS(edge, 0, visited);

    for(int i = 0; i < v_num; i++){
        if(visited[i] == false)
            return false;
    }
    return true;
}

void MDST::AC(){
    double dist[v_MAX][v_MAX];
    int r[v_MAX][v_MAX];

    MDST.Floyd_Warshall__Kariv_Hakimi(dist, r, edge);

    double d = INF;
    int s1 = -1, s2 = -1;

    for(int i = 0; i < v_num; i++){
        if(d > dist[i][r[i][v_num - 1]] * 2){
            d = dist[i][r[i][v_num - 1]] * 2;
            s1 = s2 = i;
        }
        for(int j = 0; j < v_num; j++){
            if(edge[i][j] != INF){
                for(int a = v_num - 1, b = v_num - 2; b >= 0; --b){
                    if(dist[j][r[i][b]] > dist[j][r[i][a]]){
                        if(d > dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]]){
                            d = dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]];
                            s1 = i;
                            s2 = j;
                        }
                        a = b;
                    }
                }
            }
        }
    }
    if(s1 == s2)
        cout << s1 << endl;
    else if(s1 < s2)
        cout << s1 << " " << s2 << endl;
    else
        cout << s2 << " " << s1 << endl;
}

double MDST::Diameter(){
    if(v_num == 1){
        return 0;
    }

    double dist[v_MAX][v_MAX];
    int r[v_MAX][v_MAX];

    MDST.Floyd_Warshall__Kariv_Hakimi(dist, r, edge);

    double d = INF;

    for(int i = 0; i < v_num; i++){
        for(int j = i + 1; j < v_num; j++) if(i != j){
            d = min(d, dist[i][r[i][v_num - 1]] * 2);
            d = min(d, dist[j][r[j][v_num - 1]] * 2);
            for(int a = v_num - 1, b = v_num - 2; b >= 0; --b)
                if(dist[i][r[i][b]] > dist[j][r[i][a]]){
                    d = min(d, dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]]);
                    a = b;
                }
        }
    }
    return d;
}

double MDST::SOSPD(){

    double dist[v_MAX][v_MAX];
    int r[v_MAX][v_MAX];

    double di[v_num];
    double sum = 0.0;

    MDST.Floyd_Warshall__Kariv_Hakimi(dist, r, edge);

    double d = INF;
    int s1 = -1, s2 = -1;

    for(int i = 0; i < v_num; i++){
        if(d > dist[i][r[i][v_num - 1]] * 2){
            d = dist[i][r[i][v_num - 1]] * 2;
            s1 = s2 = i;
            di[s1] = 0;
        }
        for(int j = 0; j < v_num; j++){
            if(edge[i][j] != INF){
                for(int a = v_num - 1, b = v_num - 2; b >= 0; --b){
                    if(dist[j][r[i][b]] > dist[j][r[i][a]]){
                        if(d > dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]]){
                            d = dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]];
                            s1 = i;
                            s2 = j;
                            di[s1] = (double)d / 2 - dist[i][r[i][b]];
                            di[s2] = (double)dist[i][j] - di[s1];
                        }
                        a = b;
                    }
                }
            }
        }
    }

    if(s1 == s2){
        for(int i = 0; i < v_num; i++)
            sum += dist[s1][i];
        return sum;
    }else{
        Add(edge, s1, v_num, di[s1]);
        Add(edge, s2, v_num, di[s2]);

        for(int i = 0; i <= v_num; i++){
            for(int j = 0; j <= v_num; j++)
            dist[i][j] = edge[i][j];
        }

        for(int k = 0; k <= v_num; k++)
            for(int i = 0; i <= v_num; i++)
                for(int j = 0; j <= v_num; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        for(int i = 0; i < v_num; i++)
            sum += dist[v_num][i];

        return sum;
        Delete(edge, s1, v_num);
        Delete(edge, s2, v_num);
    }
}

void MDST::Floyd_Warshall__Kariv_Hakimi(double dist[][v_MAX], int r[][v_MAX]){

    for(int i = 0; i <= v_num; i++){
        for(int j = 0; j <= v_num; j++){
            dist[i][j] = edge[i][j];
            r[i][j] = j;
        }
    }
    for(int k = 0; k < v_num; k++){
        for(int i = 0; i < v_num; i++){
            for(int j = 0; j < v_num; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
    for(int i = 0; i < v_num; i++){
        for(int j = 0; j < v_num; j++){
            for(int k = j + 1; k < v_num; k++){
                if(dist[i][r[i][j]] > dist[i][r[i][k]])
                    swap(r[i][j], r[i][k]);
            }
        }
    }
}




int main() {

    int v_num;
    cin >> v_num;
    MDST mdst(v_num);
    /*for(int i = 0; i < v_MAX; i++){
        for(int j = 0; j < v_MAX; j++)
            edge[i][j] = INF;
    }

    for(int i = 0; i < v_num; i++)
        edge[i][i] = 0;*/

    string com;
    while(cin >> com){
        int v1, v2;
        double w;

        if(com == "Add"){
            cin >> v1 >> v2 >> w;
            mdst.Add(v1, v2, w);
        }else if(com == "Delete"){
            cin >> v1 >> v2;
            mdst.Delete(v1, v2);
        }else if(com == "AC"){
            if(mdst.is_Connected)
                mdst.AC);
            else
                cout << "Not connected graph" << endl;
        }else if(com == "Diameter"){
            if(mdst.is_Connected)
                cout << mdst.Diameter << endl;
            else
                cout << "Not connected graph" << endl;
        }else if(com == "SOSPD"){
            if(mdst.is_Connected)
                cout << mdst.SOSPD << endl;
            else
                cout << "Not connected graph" << endl;
        }
    }
    return 0;
}
/*
void Add(double edge[][v_MAX], int v1, int v2, double w){
    edge[v1][v2] = w;
    edge[v2][v1] = w;
}
void Delete(double edge[][v_MAX], int v1, int v2){
    edge[v1][v2] = INF;
    edge[v2][v1] = INF;
}
void DFS(double edge[][v_MAX], int start_v, bool *visited){
    visited[start_v] = true;

    for(int v = 0; v < v_num; v++)
        if(edge[start_v][v] != INF)
            if(!visited[v])
                DFS(edge, v, visited);
}

bool is_Connected(double edge[][v_MAX]){
    bool visited[v_num];

    DFS(edge, 0, visited);

    for(int i = 0; i < v_num; i++){
        if(visited[i] == false)
            return false;
    }
    return true;
}

void AC(double edge[][v_MAX]){
    double dist[v_MAX][v_MAX];
    int r[v_MAX][v_MAX];

    Floyd_Warshall__Kariv_Hakimi(dist, r, edge);

    double d = INF;
    int s1 = -1, s2 = -1;

    for(int i = 0; i < v_num; i++){
        if(d > dist[i][r[i][v_num - 1]] * 2){
            d = dist[i][r[i][v_num - 1]] * 2;
            s1 = s2 = i;
        }
        for(int j = 0; j < v_num; j++){
            if(edge[i][j] != INF){
                for(int a = v_num - 1, b = v_num - 2; b >= 0; --b){
                    if(dist[j][r[i][b]] > dist[j][r[i][a]]){
                        if(d > dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]]){
                            d = dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]];
                            s1 = i;
                            s2 = j;
                        }
                        a = b;
                    }
                }
            }
        }
    }
    if(s1 == s2)
        cout << s1 << endl;
    else if(s1 < s2)
        cout << s1 << " " << s2 << endl;
    else
        cout << s2 << " " << s1 << endl;
}

double Diameter(double edge[][v_MAX]){
    if(v_num == 1){
        return 0;
    }

    double dist[v_MAX][v_MAX];
    int r[v_MAX][v_MAX];

    Floyd_Warshall__Kariv_Hakimi(dist, r, edge);

    double d = INF;

    for(int i = 0; i < v_num; i++){
        for(int j = i + 1; j < v_num; j++) if(i != j){
            d = min(d, dist[i][r[i][v_num - 1]] * 2);
            d = min(d, dist[j][r[j][v_num - 1]] * 2);
            for(int a = v_num - 1, b = v_num - 2; b >= 0; --b)
                if(dist[i][r[i][b]] > dist[j][r[i][a]]){
                    d = min(d, dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]]);
                    a = b;
                }
        }
    }
    return d;
}

double SOSPD(double edge[][v_MAX]){

    double dist[v_MAX][v_MAX];
    int r[v_MAX][v_MAX];

    double di[v_num];
    double sum = 0.0;

    Floyd_Warshall__Kariv_Hakimi(dist, r, edge);

    double d = INF;
    int s1 = -1, s2 = -1;

    for(int i = 0; i < v_num; i++){
        if(d > dist[i][r[i][v_num - 1]] * 2){
            d = dist[i][r[i][v_num - 1]] * 2;
            s1 = s2 = i;
            di[s1] = 0;
        }
        for(int j = 0; j < v_num; j++){
            if(edge[i][j] != INF){
                for(int a = v_num - 1, b = v_num - 2; b >= 0; --b){
                    if(dist[j][r[i][b]] > dist[j][r[i][a]]){
                        if(d > dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]]){
                            d = dist[i][r[i][b]] + dist[i][j] + dist[j][r[i][a]];
                            s1 = i;
                            s2 = j;
                            di[s1] = (double)d / 2 - dist[i][r[i][b]];
                            di[s2] = (double)dist[i][j] - di[s1];
                        }
                        a = b;
                    }
                }
            }
        }
    }

    if(s1 == s2){
        for(int i = 0; i < v_num; i++)
            sum += dist[s1][i];
        return sum;
    }else{
        Add(edge, s1, v_num, di[s1]);
        Add(edge, s2, v_num, di[s2]);

        for(int i = 0; i <= v_num; i++){
            for(int j = 0; j <= v_num; j++)
            dist[i][j] = edge[i][j];
        }

        for(int k = 0; k <= v_num; k++)
            for(int i = 0; i <= v_num; i++)
                for(int j = 0; j <= v_num; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        for(int i = 0; i < v_num; i++)
            sum += dist[v_num][i];

        return sum;
        Delete(edge, s1, v_num);
        Delete(edge, s2, v_num);
    }
}

void Floyd_Warshall__Kariv_Hakimi(double dist[][v_MAX], int r[][v_MAX], double edge[][v_MAX]){

    for(int i = 0; i <= v_num; i++){
        for(int j = 0; j <= v_num; j++){
            dist[i][j] = edge[i][j];
            r[i][j] = j;
        }
    }
    for(int k = 0; k < v_num; k++){
        for(int i = 0; i < v_num; i++){
            for(int j = 0; j < v_num; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
    }
    for(int i = 0; i < v_num; i++){
        for(int j = 0; j < v_num; j++){
            for(int k = j + 1; k < v_num; k++){
                if(dist[i][r[i][j]] > dist[i][r[i][k]])
                    swap(r[i][j], r[i][k]);
            }
        }
    }
}
*/
