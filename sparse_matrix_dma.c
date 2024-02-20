#include <stdio.h>
#include <stdlib.h>
void input_matrix(int **, int, int);
void display_matrix(int **, int, int);
int check_sparse_matrix(int **, int, int);
void create_sparse_matrix(int **, int **, int, int, int);
void display_triplet_representation(int **, int);
int main(void)
{
    int r,c;
    printf("Enter the dimensions of the sparse matrix:\n");
    scanf("%d%d",&r,&c);
    if(r<=0||c<=0)
        printf("Invalid input.\n");
    else
    {
        int **m=(int**)calloc(r,sizeof(int*));
        if(m==NULL)
            printf("Memory Allocation unsuccessful.\n");
        else
        {
            int i;
            for(i=0;i<r;i++)
            {
                *(m+i)=(int*)calloc(c,sizeof(int));
                if(*(m+i)==NULL)
                {
                    printf("Memory Allocation unsuccessful.\n");
                    exit(0);
                }
            }
            printf("Enter the elements of the sparse matrix:\n");
            input_matrix(m,r,c);
            int nz=check_sparse_matrix(m,r,c);
            if(nz)
            {
                int **t=(int**)calloc(nz+1,sizeof(int*));
                if(t==NULL)
                    printf("Memory Allocation unsuccessful.\n");
                else
                {
                    for(i=0;i<nz+1;i++)
                    {
                        *(t+i)=(int*)calloc(3,sizeof(int));
                        if(*(t+i)==NULL)
                        {
                            printf("Memory Allocation unsuccessful.\n");
                            exit(0);
                        }
                    }
                    printf("Sparse Matrix:\n");
                    display_matrix(m,r,c);
                    create_sparse_matrix(m,t,r,c,nz);
                    printf("Triplet representation of the sparse matrix:\n");
                    display_triplet_representation(t,nz+1);
                    free(t);
                }
            }
            else
                printf("The matrix entered is not a sparse matrix.\n");
            free(m);
        }
    }
    return 0;
}
void input_matrix(int **m, int r, int c)
{
    int i,j;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            scanf("%d",(*(m+i)+j));
}
void display_matrix(int **m, int r, int c)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
            printf("%d ",*(*(m+i)+j));
        printf("\n");
    }
}
int check_sparse_matrix(int **m, int r, int c)
{
    int i,j,nz=0;
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            if(*(*(m+i)+j)!=0)
                nz++;
    if((r*c)-nz>nz)
        return nz;
    else
        return 0;
}
void create_sparse_matrix(int **m, int **t, int r, int c, int nz)
{
    **t=r;      //*(*(t+0)+0)=r;
    *(*t+1)=c;  //*(*(t+0)+1)=c;
    *(*t+2)=nz; //*(*(t+0)+2)=nz;
    int i,j,tmp=1;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(*(*(m+i)+j)!=0)
            {
                **(t+tmp)=i; //*(*(t+tmp)+0)=i;
                *(*(t+tmp)+1)=j;
                *(*(t+tmp)+2)=*(*(m+i)+j);
                tmp++;
            }
        }
    }
}
void display_triplet_representation(int **t, int r)
{
    int i,j;
    printf("row\t\tcoloumn\t\tvalue\n");
    for(i=0;i<r;i++)
    {
        for(j=0;j<3;j++)
            printf("%d\t\t",*(*(t+i)+j));
        printf("\n");
    }
}