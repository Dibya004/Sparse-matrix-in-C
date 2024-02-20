#include <stdio.h>
#include <stdlib.h>
void input_matrix(int [][10], int, int);
void display_matrix(int [][10], int, int);
int check_sparse_matrix(int [][10], int, int);
void create_sparse_matrix(int [][10], int [][3], int, int, int);
void display_triplet_representation(int [][3], int);
int main(void)
{
    int m[10][10],r,c;
    printf("Enter the dimensions of the sparse matrix:\n");
    scanf("%d%d",&r,&c);
    if(r<=0||c<=0)
        printf("Invalid input.\n");
    else
    {
        int nz;
        printf("Enter the elements of the sparse matrix:\n");
        input_matrix(m,r,c);
        nz=check_sparse_matrix(m,r,c);
        if(nz)
            {
                int t[10][3];
                printf("Sparse Matrix:\n");
                display_matrix(m,r,c);
                create_sparse_matrix(m,t,r,c,nz);
                printf("Triplet representation of the sparse matrix:\n");
                display_triplet_representation(t,nz+1);
            }
        else
            printf("The matrix entered is not a sparse matrix.\n");
    }
    return 0;
}
void input_matrix(int m[][10], int r, int c)
{
    int i,j;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            scanf("%d",&m[i][j]);
}
void display_matrix(int m[][10], int r, int c)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
            printf("%d ",m[i][j]);
        printf("\n");
    }
}
int check_sparse_matrix(int m[][10], int r, int c)
{
    int i,j,nz=0;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(m[i][j]!=0)
                nz++;
        }
    }
    if((r*c)-nz>nz)
        return nz;
    else
        return 0;
}
void create_sparse_matrix(int m[][10], int t[][3], int r, int c, int nz)
{
    t[0][0]=r;
    t[0][1]=c;
    t[0][2]=nz;
    int i,j,tmp=1;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(m[i][j]!=0)
            {
                t[tmp][0]=i;
                t[tmp][1]=j;
                t[tmp][2]=m[i][j];
                tmp++;
            }
        }
    }
}
void display_triplet_representation(int t[][3], int r)
{
    int i,j;
    printf("row\t\tcoloumn\t\tvalue\n");
    for(i=0;i<r;i++)
    {
        for(j=0;j<3;j++)
            printf("%d\t\t",t[i][j]);
        printf("\n");
    }
}