#include <stdio.h>
#define nmax 100
#define mmax 100
int head;
int tail;
char matr[nmax+2][mmax+2];
int used[nmax+2][mmax+2];
int di[4]={-1, 1, 0, 0};
int dj[4]={0, 0, -1, 1};
int n, m;

struct pair{
	int i;
	int j;
};

struct pair queue[nmax*nmax];
struct pair parent[nmax+2][mmax+2];

void pushQueue (struct pair v){
	queue[head]=v;
	head++;
}

struct pair popQueue(){
	tail++;
	return queue[tail-1];
}

void restore(struct pair finish){
	struct pair cur=parent[finish.i][finish.j];
	while (cur.i!=0 && cur.j!=0){
		matr[cur.i][cur.j]='0';
		cur=parent[cur.i][cur.j];
	}
}

void bfs (struct pair start){
	struct pair to;
	struct pair from;
	int i, j, k;
	head=0;
	tail=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=m;j++){
			used[i][j]=0;
			parent[i][j].i=0;
			parent[i][j].j=0;
		}
	pushQueue(start);
	used[start.i][start.j]=1;
	while (head!=tail){
		from=popQueue();
		for (k=0;k<=3;k++){
			to.i=from.i+di[k];
			to.j=from.j+dj[k];
			if (used[to.i][to.j]==0 && matr[to.i][to.j]!='X'){
				pushQueue(to);
				used[to.i][to.j]=1;
				parent[to.i][to.j]=from;
			}
		}
	}
}

int main(){
	int i, j;
	char x;
	struct pair start;
	struct pair finish;
	scanf ("%d %d", &n, &m);
	for (i=0;i<=n+1;i++)
		for (j=0;j<=m+1;j++){
			scanf ("%c", &x);
			if (x=='S'){
				start.i=i;
				start.j=j;
			}
			if (x=='F'){
				finish.i=i;
				finish.j=j;
			}
			if (x!='\n')
				matr[i][j]=x;
			if (x=='\n')
				j--;
		}
	bfs (start);
	restore (finish);
	for (i=0;i<=n+1;i++){
		for (j=0;j<=m+1;j++)
			printf ("%c", matr[i][j]);
		printf("\n");
	}
	return 0;
}
