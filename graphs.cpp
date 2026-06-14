#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

unordered_map<int,string> cityName;

class Graph{

    int V;
    list<pair<int,int>> *a;

    public:

    Graph(int V){
        this->V=V;
        a=new list<pair<int,int>> [V];
    }

    void addedge(int u,int v,int wt){
        a[u].push_back({v,wt});
        a[v].push_back({u,wt});
    }

    void printCities(){

        cout<<"\n================ AVAILABLE CITIES ================\n\n";

        for(int i=1;i<V;i++){
            cout<<i<<" -> "<<cityName[i]<<endl;
        }

        cout<<"\n==================================================\n";
    }

    void printnode(){

        cout<<"\n=============== ROAD NETWORK ===============\n\n";

        for(int i=1;i<V;i++){

            cout<<cityName[i]<<" : ";

            for(auto neigh : a[i]){

                cout<<"["<<cityName[neigh.first]
                <<" , "<<neigh.second<<" km] ";
            }

            cout<<endl;
        }

        cout<<"\n============================================\n";
    }

    void dijkstra(int src,int dest){

        vector<int>dist (V,INT_MAX);
        vector<int>parent (V,-1);

        priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
        > pq;

        dist[src]=0;

        pq.push({0,src});

        while(pq.size()>0){

            int currDist=pq.top().first;
            int u=pq.top().second;

            pq.pop();

            if(currDist>dist[u]){
                continue;
            }

            if(u==dest){
                break;
            }

            for(auto nbr : a[u]){

                int v=nbr.first;
                int wt=nbr.second;

                if(dist[u]+wt<dist[v]){

                    dist[v]=dist[u]+wt;

                    parent[v]=u;

                    pq.push({dist[v],v});
                }
            }
        }

        if(dist[dest]==INT_MAX){

            cout<<"\nNo Route Found\n";
            return;
        }

        vector<int>path;

        int node=dest;

        while(node!=-1){

            path.push_back(node);
            node=parent[node];
        }

        reverse(path.begin(),path.end());

        cout<<"\n============================================\n";
        cout<<"         SHORTEST ROUTE FOUND\n";
        cout<<"============================================\n\n";

        for(int i=0;i<path.size();i++){

            cout<<cityName[path[i]];

            if(i!=path.size()-1){
                cout<<" -> ";
            }
        }

        cout<<"\n\n--------------------------------------------\n";
        cout<<"Total Distance      : "<<dist[dest]<<" km"<<endl;
        cout<<"Cities Traversed    : "<<path.size()<<endl;
        cout<<"--------------------------------------------\n";
    }
};

int main(){

    Graph g(21);

    g.addedge(1,2,35);
    g.addedge(2,3,25);
    g.addedge(3,4,210);

    g.addedge(4,5,60);
    g.addedge(4,6,45);

    g.addedge(5,7,95);
    g.addedge(7,9,90);
    g.addedge(9,11,85);

    g.addedge(6,8,95);
    g.addedge(8,10,120);

    g.addedge(10,12,25);
    g.addedge(12,14,55);

    g.addedge(10,13,210);
    g.addedge(13,15,270);

    g.addedge(14,16,135);
    g.addedge(14,17,150);

    g.addedge(10,17,145);

    g.addedge(17,19,70);
    g.addedge(19,20,60);

    g.addedge(16,18,10);
    g.addedge(18,20,220);

    g.addedge(11,16,270);

    cityName[1]="Meerut";
    cityName[2]="Ghaziabad";
    cityName[3]="Noida";
    cityName[4]="Agra";
    cityName[5]="Mathura";
    cityName[6]="Firozabad";
    cityName[7]="Aligarh";
    cityName[8]="Etawah";
    cityName[9]="Moradabad";
    cityName[10]="Kanpur";
    cityName[11]="Bareilly";
    cityName[12]="Unnao";
    cityName[13]="Prayagraj";
    cityName[14]="Lucknow";
    cityName[15]="Gorakhpur";
    cityName[16]="Ayodhya";
    cityName[17]="Sultanpur";
    cityName[18]="Faizabad";
    cityName[19]="Jaunpur";
    cityName[20]="Varanasi";

    cout<<"\n";
    cout<<"============================================\n";
    cout<<"      UTTAR PRADESH ROUTE FINDER\n";
    cout<<"         (DIJKSTRA ALGORITHM)\n";
    cout<<"============================================\n";

    g.printCities();

    int src,dest;

    cout<<"\nEnter Source City Number      : ";
    cin>>src;

    cout<<"Enter Destination City Number : ";
    cin>>dest;

    if(src<1 || src>20 || dest<1 || dest>20){

        cout<<"\nInvalid City Selection\n";
        return 0;
    }

    cout<<"\nSource      : "<<cityName[src]<<endl;
    cout<<"Destination : "<<cityName[dest]<<endl;

    g.dijkstra(src,dest);

    return 0;
}