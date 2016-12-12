#include<stdio.h>

FILE *fr;

//input strings
char x[40];
char y[40];

int size_x;
int size_y;

//ints representing the input string
int y_char[40];
int x_char[40];

//table for LCS
int table[40][40];
int size_table_x;
int size_table_y;

char out[40];
int size_out = 0;

int max(int x, int y)
{
	if(x > y)
		return x;
	else
		return y;
}
int main(int argc, char *argv[])
{
	/*+++++ READ THE INPUT STRINGS +++++*/
	FILE *ptr_file;

    ptr_file =fopen(argv[1],"r");
    
    
    //error opening the file
    if (!ptr_file)
    {
    	return 1;
	}
	
    fgets(x,40, ptr_file);
    fgets(y,40, ptr_file);
    	
	fclose(ptr_file);
	
	//remove the new line characters
	if(x[strlen(x) - 1] == '\n')
	{
		size_x = strlen(x) - 1;
	}
	else
		size_x = strlen(x);
	
	if(y[strlen(y) -1] == '\n')
	{
		size_y = strlen(y) - 1;
	}
	else
		size_y = strlen(y);

	/*+++++ END OF FILE READING ++++++*/
	
	//initialize the table size values
	size_table_x = size_x + 1;
	size_table_y = size_y + 1;
	
	for(int i = 0; i < size_table_x; i++)
	{
		table[i][0] = -1;
	}
	for(int i = 0; i < size_table_y; i++)
	{
		table[0][i] = -1;
	}
	
	//fill the in
	for(int i = 0; i < size_y; i++)
	{
		y_char[i] = (int) y[i];
	}
	for(int i = 0; i < size_x; i++)
	{
		x_char[i] = (int) x[i];
	}
	
	//CALCULATE THE TABLE FOR LCS
	for(int i = 1; i < size_table_x; i++)
	{
		for(int j = 1; j < size_table_y; j++)
		{
			if(x_char[i-1] == y_char[j-1])
			{
				int value = table[i-1][j-1];
				value = value + 1;
				table[i][j] = value;
			}
			else
			{
				int v1 = table[i-1][j];
				int v2 = table[i][j-1];
				table[i][j] = max(v1, v2);
			}
		}
	}
	//GET THE STRING FOR THE LCS
	int m = size_table_y - 1;
	int l = size_table_x - 1;
	
	while(m != 0 && l != 0)
	{
		if(table[l][m-1] >= table[l-1][m] && !(table[l-1][m-1] < table[l][m]))
		{
			m--;
		}
		else if(table[l][m] > table[l-1][m-1] && table[l][m-1] > table[l-1][m])
		{
			m--;
		}
		else if(table[l][m] > table[l-1][m-1] && table[l][m-1] < table[l-1][m])
		{
			l--;
		}
		else if(table[l][m] > table[l-1][m-1] && table[l][m-1] == table[l-1][m])
		{
			out[size_out] = (char) y_char[m-1];
			size_out++;
			l--;
			m--;
		}
		else
		{
			l--;
		}
	}
	
	for(int i = size_out-1; i >= 0; i--)
	{
		printf("%c",out[i]);
	}
	printf(" %d",table[size_table_x-1][size_table_y-1]+1);
	printf("\n");
    return 0;
}
