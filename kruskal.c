#include <stdio.h>
#include <stdlib.h>

FILE *fr;
//graph to hold the adj matrix
int graph[30][30];
int size = 0;

//edges of the graph
int edges[30][3];
int size_edges;

//set for holding the representatives of the set
int set[30];

//set for representing the height of the tree
int height[30];

//final tree edges representing the MST
int edges_T[30][30];
int size_T;

//+++++++ RANDOMIZED QUICK SORT IMPLEMENTATION +++++++ 

int partition(int A[size_edges][3], int p, int r)
{
	int x = A[r][0]; //pick the last element as the pivot
	int i = p - 1;
	for(int j = p; j <= r-1; j++)
	{
		if(A[j][0] <= x)
		{
			i++;
			int  temp = A[j][0];
			int temp_x = A[j][1];
			int temp_y = A[j][2];
			
			A[j][0] = A[i][0];
			A[j][1] = A[i][1];
			A[j][2] = A[i][2];
			
			A[i][0] = temp;
			A[i][1] = temp_x;
			A[i][2] = temp_y;
		}
	}
	//move the pivot into position
	int temp = A[r][0];
	int temp_x = A[r][1];
	int temp_y = A[r][2];
	
	A[r][0] = A[i+1][0];
	A[r][1] = A[i+1][1];
	A[r][2] = A[i+1][2];
	
	A[i+1][0] = temp;
	A[i+1][1] = temp_x;
	A[i+1][2] = temp_y;
	
	return i+1;
}
int rand_partition(int A[size_edges][3], int p, int r)
{
	srand(time(NULL));
	int randomNum = rand() % (r + 1 - p) + p;
	
	int temp = A[r][0];
	int temp_x = A[r][1];
	int temp_y = A[r][2];
	
	A[r][0] = A[randomNum][0];
	A[r][1] = A[randomNum][1];
	A[r][2] = A[randomNum][2];
	
	A[randomNum][0] = temp;
	A[randomNum][1] = temp_x;
	A[randomNum][2] = temp_y;
	
	return partition(A,p,r);
}
void quickSort(int A[size_edges][3], int p, int r)
{
	if(p < r)
	{
		int q = rand_partition(A, p, r);
		quickSort(A, p, q-1);
		quickSort(A, q+1, r);
	}
}

//+++++++ END OF QUCIK SORT IMPLEMENTATION
void print_data()
{
	printf("KRUSKAL ALGORITHM MST :\n");
	printf("Weight of the edge, followed by the two vertices of the edge.\n\n");
	printf("WHT\tV1\tV2\n");
	printf("***\t**\t**\n");
	
	for(int i = 0; i < size_T; i++)
	{
		if(edges_T[i][0] != -1)
		{
			printf("%d\t%d\t%d\n",edges_T[i][0],(edges_T[i][1]+1),(edges_T[i][2]+1));
		}
	}
}
void union3(int repx, int repy)
{
	if(height[repx] == height[repy])
	{
		height[repx] ++;
		set[repy] = repx;
	}
	else if(height[repx] > height[repy])
	{
		set[repy] = repx;
	}
	else
	{
		set[repx] = repy;
	}
}
int find3(int x)
{
	int root = x;
	while(root != set[root])
	{
		root = set[root];
	}
	
	int node = x;
	int parent = -1;
	while(node != root)
	{
		parent = set[node];
		set[node] = root;
		node = parent;
	}
	
	return root;
}
void set_height_init()
{
	for(int i = 0; i < size; i++)
	{
		set[i] = i;
	}
	
	for(int i = 0; i < size; i++)
	{
		height[i] = 0;
	}
	
	size_T = size - 1;
	for(int i = 0; i < size_T; i++)
	{
		edges_T[i][0] = -1;
		edges_T[i][1] = 0;
		edges_T[i][2] = 0;
	}
}
void edges_init()
{
	size_edges = size*(size - 1)/2;
	
	for(int i = 0; i < size_edges; i++)
	{
		edges[i][0] = -1;
	}
	
	int count = 0;
	//get the information for all the edges
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(i > j && graph[i][j] != 999)
			{
				edges[count][0] = graph[i][j];
				edges[count][1] = i;
				edges[count][2] = j;
				count++;
			}
		}
	}
}
int main(int argc, char *argv[])
{
	// *** START OF FILE READING *** //
	char line[80];
	fr = fopen (argv[1], "rt");
	
	//get the dimensions of the matrix
	fgets(line,30,fr);
	char temp[30] = ""; //first line is stored here
	char* pch;
	pch = strtok(line,",");
	while(pch != NULL)
	{
		strcat(temp,pch);
		strcat(temp," ");
		pch = strtok(NULL,",");
		size++;
	}
	
	int row = 0;
	int column = 0;
	
	//parse the first line
	pch = strtok(temp," ");
	while(pch != NULL)
	{
		graph[row][column] = atoi(pch);
		pch = strtok(NULL," ");
		column++;
	}
	
	//read all the files	
	while(fgets(line, 40, fr) != NULL)
	{
		row++;
		char* pch;
		pch = strtok(line,",");
		column = 0;
		while(pch != NULL)
		{
			graph[row][column] = atoi(pch);
			pch = strtok(NULL,",");
			column++;
		}
	}
	fclose(fr);
	//+++++++++++++++++++++++++++++++++++++++++++
	
	edges_init();
	set_height_init();
	
	//sort all the edges
	quickSort(edges,0,size_edges-1);
	
	//counters
	int total = 0;
	int e_count = 0;
	int t_count = 0;
	
	do
	{
		if(edges[e_count][0] != -1)//get a valid edge
		{
			//get the representative of both vertices
			int ucomp = find3(edges[e_count][1]);
			int vcomp = find3(edges[e_count][2]);
			
			
			if(ucomp != vcomp)
			{
				edges_T[t_count][0] = edges[e_count][0];
				edges_T[t_count][1] = edges[e_count][1];
				edges_T[t_count][2] = edges[e_count][2];
				
				union3(ucomp,vcomp);
				
				t_count++;
				total++;
			}
		}
		e_count++; //get the next edge
	}
	while(total < size -1 || total == size_edges -1);
	
	//print the MST
	print_data();
	
	return 0;
}
