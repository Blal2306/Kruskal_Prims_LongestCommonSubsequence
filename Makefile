all : p1

p1 : 
	gcc prim.c -o prim.out -std=c99
	gcc kruskal.c -o kruskal.out -std=c99
	gcc lcs.c -o lcs.out -std=c99
	
	
clean :
	rm *.o