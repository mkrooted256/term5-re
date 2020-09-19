#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ((a>b)?b:a)
#define max(a,b) ((a>b)?a:b)
#define N 5

int ** new_M() 
{
    int ** M = new int*[N];
    for (int i=0; i<N; i++) M[i] = new int[N];
    return M;
}

void fill_G(int ** G)
{
    srand(13314);
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++) 
        {
            // zeroes on diagonal
            if (i==j) G[i][j] = 0;
            // symmetric - fill upper triangle, then copy to the lower
            else if (i>j) G[i][j] = G[j][i];
            // fill upper triangle with random N from 0 to 10
            else G[i][j] = rand()%5;
        }
    }
}

void delete_M(int ** M)
{
    for (int i=0; i<N; i++) delete [] M[i];
    delete [] M;
}

void printM(int ** M) {
    printf("   ");
    for (int j=0; j<N; j++)
    {
        printf("%2i ", j);
    }
    printf("\n");
    for (int i=0; i<N; i++) 
    {
        printf("%2i ", i);
        for (int j=0; j<N; j++)
        {
            printf("%2i ", M[i][j]);
        }
        printf("\n");
    }
}

// G - input graph, W - output max stream matrix
void FW(int ** G, int ** W) 
{
    printf("\n");
    // First iteration - W=G, k=0;
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
        {
            int a = min(G[i][0], G[0][j]);
            W[i][j] = max(G[i][j],a); 
            // W[i][j] = G[i][j]+a; 
        }
    printM(W);
    for (int k=1; k<N; k++)
    {
        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
            {
                int a = min(W[i][k], W[k][j]);
                W[i][j] = max(W[i][j],a); 
                // W[i][j] = W[i][j]+a; 
            }
        printM(W);
    }
        
    printf("\n");
}


int main() 
{
    int ** G = new_M();
    fill_G(G);
    
    // Let Vertex0 be source and VertexN be sink
    // Moal: calculate max stream through the Graph from source to sink

    // Classic (+,*)-problem. I am going to use modified Floyd-Warshell algorithm
    int ** W = new_M();

    printM(G);
    FW(G, W);
    printM(W);

    delete_M(W);
    delete_M(G);
}