#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>

#define maxNode 100
#define maxID 13

 
using namespace std;

// GLOBAL

vector<vector<string> > content;
stack<char> paths[maxNode][maxNode];
int distances[maxNode][maxNode];
int directions[maxNode][maxNode];
int graph[maxNode][5];
int IDS[maxID];
queue<int> q;
//

void readFile(){
	string fname;
	cout<<"Enter the file name: ";
	cin>>fname;
 
	
	vector<string> row;
	string line, word;
 
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
 
			stringstream str(line);
 
			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";
}

void printCSV(){
	for(int i=0;i<content.size();i++)
	{
		for(int j=0;j<content[i].size();j++)
		{
            if (content[i][j] != ""){
                cout<<content[i][j]<<" ";
            }
			
		}
		cout<<"\n";
	}
}

void buildGraph(){
	// directions in graph: NORTH 1 EAST 2 SOUTH 3 WEST 4
    for (int i = 1; i<content.size(); ++i){
        for (int j = 1; j<5; ++j){
			if (content[i][j] != ""){
				if (j == 1){
					graph[i][j] = content[i][j][0]-'0';
					directions[i][content[i][j][0]-'0'] = 1;
				}
				else if (j == 2){
					graph[i][3] = content[i][j][0]-'0';
					directions[i][content[i][j][0]-'0'] = 3;
				}
				else if (j == 3){
					graph[i][4] = content[i][j][0]-'0';
					directions[i][content[i][j][0]-'0'] = 4;
				}
				else{
					graph[i][2] = content[i][j][0]-'0';
					directions[i][content[i][j][0]-'0'] = 2;	
				}
					
			}else{
				if (j == 1){graph[i][j] = -1;}
				else if (j == 2){graph[i][3] = -1;}
				else if (j == 3){graph[i][4] = -1;}
				else{graph[i][2] = -1;}
			}
		}
    }
}

void bfs(int node1, int node2){
	queue<int> q;
	int pred[maxNode];
	q.push(node1);
	int cur = node1;
	while (cur != node2){
		cur = q.front();
		for (int i = 1; i<5; ++i){
			if (graph[cur][i] != -1){
				q.push(graph[cur][i]);
				pred[graph[cur][i]] = cur;
			}
		}
		q.pop();
	}
	int lastDir = directions[pred[cur]][cur];
	cur = pred[cur];
	while (cur != node1){
		distances[node1][node2] ++;
		int dir = directions[pred[cur]][cur];
		int margin =  dir-lastDir;
		if (margin == 1 || margin == -3){
			paths[node1][node2].push('l');
		}else if (margin == -1 || margin == 3){
			paths[node1][node2].push('r');
		}else{
			paths[node1][node2].push('f');
		}
		cur = pred[cur];
		lastDir = dir;
	}
	paths[node1][node2].push('f');
	distances[node1][node2] ++;
}


 
int main()
{
    readFile();
	buildGraph();
	// for (int i = 0; i< maxID; ++i){
	// 	for (int j = 0; j<maxID; ++j){
	// 		bfs(IDS[i], IDS[j]);
	// 	}
	// }
	int start,end;
	cout << "start: ";
	cin >> start;
	cout << "end: ";
	cin >> end;
	bfs(start,end);
	while (!paths[start][end].empty()){
		cout << paths[start][end].top();
		paths[start][end].pop();
	}
	return 0;
}
