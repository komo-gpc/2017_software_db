#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void input();

int main()
{
	FILE *fp;
	char *fname ="datebase2.csv";	//ここに入力したいファイル名を書く。入力してもらったファイル名を入れるように変更可能。
	char save1[6][150];
	char save2[6][150];
	char c[1000][6][150];	//改行文字の関係で配列を3個使って終了判定をしています。
	
	fp = fopen(fname,"r");
	if(fp==NULL){
		printf("ぬるぽ\n");
		return -1;
	}
	
	int i,j,k;
	i=1;
	fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%s",c[0][0],c[0][1],c[0][2],c[0][3],c[0][4],c[0][5]);
	fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%s",save1[0],save1[1],save1[2],save1[3],save1[4],save1[5]);
	for(;;){
		printf("%s %s %s %s %s %s",c[i-1][0],c[i-1][1],c[i-1][2],c[i-1][3],c[i-1][4],c[i-1][5]);
		if(fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%s",save2[0],save2[1],save2[2],save2[3],save2[4],save2[5])==EOF){
			break;
		}
		for(j=0;j<5;j++){
			for(k=0;k<150;k++){
				c[i][j][k]=save1[j][k];
				save1[j][k]=save2[j][k];
			}
		}
		i++;
	}
	
	printf("\n");
	fclose(fp);
	return 0;
}
