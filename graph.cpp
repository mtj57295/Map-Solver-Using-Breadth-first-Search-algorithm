#include "graph.h"

using namespace std;
// adds a vertex to the graph and assign it the next available id
void graph::addVertex()
{
	vertex newVertex;
	newVertex.id = vertices.size();
	newVertex.path = NULL;
	vertices.push_back(newVertex);
}

// adds an undirected edge between vertices with the given ids
void graph::addEdge(int id1, int id2)
{
	vertices[id1].neighbors.push_back(&vertices[id2]);
	vertices[id2].neighbors.push_back(&vertices[id1]);
}

// conducts a breadth-first search from the vertex with the specified id
void graph::breadthFirst(int start)
{
	queue<vertex*> q;
	for (vector<vertex>::iterator itr = vertices.begin(); itr != vertices.end(); ++itr) {
		itr->distance = INT_MAX;
	}
	vertices[start].distance = 0;
	q.push(&vertices[start]);
	while (!q.empty())
	{
		vertex *v = q.front();
		q.pop();
		for (list<vertex*>::iterator itr = v->neighbors.begin(); itr != v->neighbors.end(); ++itr)
		{
			vertex *w = *itr;
			if (w->distance == INT_MAX)
			{		
				w->distance = v->distance + 1;
				w->path = v;
				q.push(w);
			}
		}
	}
}

// prints all the vertex ids along the path from the start vertex of the last 
// search to this end vertex (includes end points)
void graph::printPath(int end)
{
	vertex v = vertices[end];
	list<int> l;
	l.push_back(v.id);

	while (v.path != NULL) {		
		v = *(v.path);
		l.push_back(v.id);
	}
	
	while (!l.empty()) {
		cout << l.back() << endl;
		l.pop_back();
	}
	
}