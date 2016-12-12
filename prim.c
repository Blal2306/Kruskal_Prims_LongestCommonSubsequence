#include <stdio.h>
#include <stdlib.h>

FILE *fr;
//graph to hold the adj matrix
int graph[30][30];
int size = 0;

int status[30];

//MST final tree edges
int tree[30][3];
int size_tree;
//+++++++++++++++++++++
void init()
{
	size_tree = size*(size-1)/2;
	
	for(int i = 0; i < size_tree; i++)
	{
		status[i] = 0;
	}
	
	//init the final tree array
	for(int i = 0; i < size_tree; i++)
	{
		tree[i][0] = -1;
		tree[i][1] = -1;
		tree[i][2] = -1;
	}
}
void print()
{
	printf("PRIMS ALGORITHM MST :\n");
	printf("Weight of the edge, followed by the two vertices of the edge.\n\n");
	printf("WHT\tV1\tV2\n");
	printf("***\t**\t**\n");
	for(int i = 0; i < size_tree; i++)
	{
		if(tree[i][0] != -1)
		{
			printf("%d\t%d\t%d\n",tree[i][0],(tree[i][1]+1),(tree[i][2]+1));
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
	//++++++++++ END OF FILE READING +++++++++++++++++
	
	init();
	
	int total = 0;
	int init = 0; //initial vertex
	
	//minimum found thus far
	int v1 = -1;
	int v2 = -1;
	int min_edge = 999;
	
	status[init] = 1; // mark it as active
	do
	{
		for(int i = 0; i < size_tree; i++)
		{
			if(status[i] == 1)
			{
				for(int j = 0; j < size;j++)
				{
					if(graph[i][j] != 0 && graph[i][j] != 999)
					{
						//it is not one of the edges that is already included
						if(graph[i][j] < min_edge && status[j] != 1)
						{
							min_edge = graph[i][j];
							v1 = i;
							v2 = j;
						}
					}
				}
			}
		}
		if(status[v2] == 0)
		{
			tree[total][0] = graph[v1][v2];
			tree[total][1] = v1;
			tree[total][2] = v2;
			
			status[v2] = 1;
			total++;
		}
		min_edge = 999;
	}
	while(total < size-1);
	
	//print the MST
	print();
	return 0;
}
