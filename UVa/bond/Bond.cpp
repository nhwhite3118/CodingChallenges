#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct dest{
	int dest;
	int danger;
};
int dijkstra(unordered_map<int,vector<dest>> &roads,int num_cities, int start, int end){
	priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> p;
	vector<int> cities(num_cities+1,1111111111);
	
	array<int,3> curr;
	cities[start]=0;
	for(dest d :roads[start]){
		p.push(array<int,3>{d.danger,start,d.dest});
	}
	curr=p.top();
	while(!p.empty() ){//&&!p.empty
		curr=p.top();
		p.pop();
		if(curr[0]<cities[curr[2]]){		//if this path is less dangerous 
							//than any previous one to the city
			cities[curr[2]]=curr[0];	//update the city w/ the new path
			if(curr[2]==end)
				return cities[end];
			for(dest nxt: roads[curr[2]]){	//then for each road leaving the new city
				if(max(cities[curr[2]],nxt.danger)<cities[nxt.dest])	
					p.push(array<int,3>{max(cities[curr[2]],nxt.danger),curr[2],nxt.dest});
							//add the road to the priority queue
			}
		}
	}	
	return cities[end];
}
int main(){


	int num_cities;
	cin>>num_cities;
	while(!cin.eof()){	
		int num_roads;
		cin>>num_roads;

		unordered_map<int,vector<dest>> roads;

		for(int i=0; i<num_roads; i++){
			int a;
			int b;
			int danger;
			cin>>a;
			cin>>b;
			cin>>danger;

			roads[a].push_back(dest{b,danger});
			roads[b].push_back(dest{a,danger});
		}

		int num_tests;
		cin>>num_tests;

		for(int i=0; i<num_tests; i++){
			int start;
			int end;
			cin>>start;
			cin>>end;
			cout<< dijkstra(roads,num_cities,start,end)<< endl;	
		
		}
		cout<<endl;
		cin>>num_cities;
	}

}
