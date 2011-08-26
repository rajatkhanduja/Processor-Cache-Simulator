#include<stdio.h>
int main(){
	int N=100,S;
	int A[N][N], B[N][N], C[N][N];
	int i,j,k;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			S=0;
			for(k=0;k<N;k++){
				printf("\n%x RD",&B[i][k]);
				printf("\n%x RD",&C[k][j]);
				S=S+B[i][k]*C[k][j];
			}
			printf("\n%x WR",&A[i][j]);
			A[i][j]=S;
		}
	}
	return 0;
}

