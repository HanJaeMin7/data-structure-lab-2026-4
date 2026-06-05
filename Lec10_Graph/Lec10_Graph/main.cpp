#include "AdjMatGraph.h"
#include <stdio.h>
int main() {
	//AdjMatGraph g;
	//SrchAMGraph g;
	
	//for (int i = 0;i < 4;i++)
	//	g.insertVertex('A' + i);
	//g.insertEdge(0, 1);
	//g.insertEdge(0, 3);
	//g.insertEdge(1, 2);
	//g.insertEdge(1, 3);
	//g.insertEdge(2, 3);
	//printf("인접 행렬로 표현한 그래프\n");
	//g.display();
	//FILE* fp;
	//fopen_s(&fp, "../text_out.txt", "w");
	//g.display(fp);
	//fclose(fp);

	
	//printf("그래프(graph.txt)\n");
	//g.display();

	//printf("DFS ==> ");
	//g.resetVisited();
	//g.DFS(0);
	//	printf("\n");

	//WGraph	g;
	WGraphPrim g;
	g.load("../graph.txt");
	printf("MST By Kruskal's Algorithm\n");
	g.Prim(0);
	//g.display();
	printf("\n");

	WGraphDijkstra wg;
	wg.load("../graph_sp.txt");
	printf("Shortest path by Dijkstra Algorithm\n");
	wg.ShortestPath(0);
	WGraphMST Mg;
	Mg.load("../graph.txt");
	printf("입력 그래프: graph.txt\n");
	//g.display("../graph.txt");
	Mg.Kruskal();
	return 0;
}



