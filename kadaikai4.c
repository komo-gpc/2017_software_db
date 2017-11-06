#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void input();
void overwrite();
void output();
void output1();
void output2();

char kyouka[20]={0},kakunin[20]={0},file[30],name[20],namae[100][20];
int tensu,mode,flag;
FILE *fa,*fb;	//fa成績記録用,fb教科記録用

int main()
{
		
	fb=fopen("kyouka.txt","a");	//初回read形式で開くのでエラー回避用
	fclose(fb);
	
	printf("注意：数字の入力は半角アラビア数字で行ってください。\n");
	for(;;){
		printf("行いたいモードを選択。\n"
		"1,新規書き込み\n"
		"2,追加書き込み\n"
		"3,データ変更\n"
		"4,出力\n"
		"5,終了\n"
		"~~~~~~~~~~~~~~~~~~~~~~~~\n");
		scanf("%d",&mode);
		if(mode==1||mode==2){input();}
		else if(mode==3){overwrite();}
		else if(mode==4){output();}
		else if(mode==5){return 0;}
		else{printf("もう一度モードを選択してください。\n");}
	}
}

void input()
{

	printf("教科名を入力してください。\n");
	scanf("%s",kyouka);
	fb=fopen("kyouka.txt","r");	//教科が被ってないか判定
	flag=0;
	if(mode==1){
		for(;;){
			if(fscanf(fb,"%s",kakunin)==EOF){break;}
			if(strcmp(kyouka,kakunin)==0){
				printf("すでにその教科は登録されています。\n"
				"~~~~~~~~~~~~~~~~~~~~~~~~\n");
				flag=1;
				break;
			}
		}
	}
	if(mode==2){
		flag=1;
		for(;;){
			if(fscanf(fb,"%s",kakunin)==EOF){
				printf("そのような教科は登録されていません。\n"
				"~~~~~~~~~~~~~~~~~~~~~~~~\n");
				break;
			}
			if(strcmp(kyouka,kakunin)==0){
				flag=0;
				break;
			}
		}
	}
	fclose(fb);

	if(flag==0){
		sprintf(file,"%s.txt",kyouka);
		if(mode==1){fa=fopen(file,"w");}	//入力された名前でファイルを生成
		if(mode==2){fa=fopen(file,"a");}
		printf("学生名に0入力で終了です。\n");
		for(;;){
			printf("\n学生名を入力してください。\n");
			scanf("%s",name);
			char a[20]={0};	//0が入力されたか確認用
			a[0]='0';
			if(strcmp(name,a)==0){break;}
			fprintf(fa,"%s",name);
			printf("点数を入力してください。\n");
			scanf("%d",&tensu);
			fprintf(fa,"%4d\n",tensu);
		}
		printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
		fclose(fa);
		if(mode==1){
			fb=fopen("kyouka.txt","a");	//教科名記憶
			fprintf(fb,"%s\n",kyouka);
			fclose(fb);
		}

	}
}

void overwrite()
{
	int a[100]={0};	//点数を記憶する用
		
	printf("教科名を入力してください。\n");
	scanf("%s",kyouka);
	fb=fopen("kyouka.txt","r");	//教科が存在するか判定
	flag=0;
	for(;;){
		if(fscanf(fb,"%s",kakunin)==EOF){
			printf("そのような教科は登録されていません。\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~\n");
			flag=1;
			break;
		}
		if(strcmp(kyouka,kakunin)==0){break;}
	}
	fclose(fb);
	
	if(flag==0){
		printf("変更したい学生名を入力してください。\n");
		scanf("%s",name);
		printf("変更する点数を入力してください。\n");
		scanf("%d",&tensu);
		sprintf(file,"%s.txt",kyouka);
		fa=fopen(file,"r");	//点数読み込み
		int i,bango,j;
		i=0;
		bango=0;
		for(;;){
			if(fscanf(fa,"%s %d",namae[i],&a[i])==EOF){
				if(flag==1){
					flag=0;
					break;
				}
				if(flag==0){
					printf("そのような生徒は登録されていません。\n"
					"~~~~~~~~~~~~~~~~~~~~~~~~\n");
					flag=1;
					break;
				}
			}
			if(strcmp(name,namae[i])==0){
				bango=i;
				flag=1;	//EOF時の分岐用	
			}
			i++;
		}
		fclose(fa);
		if(flag==0){
			a[bango]=tensu;	//変更
			fa=fopen(file,"w");	//上書き
			for(j=0;j<i;j++){fprintf(fa,"%s %4d\n",namae[j],a[j]);}
			fclose(fa);
			printf("変更完了。\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~\n");
		}
	}
}

void output()
{
	for(;;){
		printf("出力モードを選択してください。\n"
		"1,個人の成績を出力\n"
		"2,科目の成績を出力\n"
		"3,戻る\n"
		"~~~~~~~~~~~~~~~~~~~~~~~~\n");
		scanf("%d",&mode);
		if(mode==1){output1();}
		else if(mode==2){output2();}
		else if(mode==3){break;}
		else{
			printf("もう一度モードを選択してください。"
			"\n~~~~~~~~~~~~~~~~~~~~~~~~\n");
		}
	}
}

void output1()	//1,個人の成績を出力
{

	printf("確認したい学生名を入力してください。\n");
	scanf("%s",name);
	fb=fopen("kyouka.txt","r");
	float heikin=0;
	int kyoukasu=0,i;
	for(;;){
		if(fscanf(fb,"%s",kyouka)==EOF){break;}
		sprintf(file,"%s.txt",kyouka);
		fa=fopen(file,"r");
		printf("%-20s",kyouka);
		i=1;
		for(;;){
			if(fscanf(fa,"%s %d",namae[0],&tensu)==EOF){
				printf("該当者なし\n");
				kyoukasu--;	//後でインクリする辻褄合わせ
				break;
			}
			if(strcmp(name,namae[0])==0){
				printf("%4d点\n",tensu);
				heikin=heikin + tensu;
				break;
			}
			i++;
		}
		fclose(fa);
		kyoukasu++;
	}
	fclose(fb);
	if(kyoukasu>0){
		heikin=heikin / kyoukasu;
		printf("平均%.1f点\n",heikin);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void output2()	//2,科目の成績を出力
{
	
	
	
	printf("確認したい教科名を入力してください。\n");
	scanf("%s",kyouka);
	
	fb=fopen("kyouka.txt","r");
	flag=0;
	for(;;){
		if(fscanf(fb,"%s",kakunin)==EOF){
			flag=1;
			printf("そのような教科は登録されていません。\n"
			"~~~~~~~~~~~~~~~~~~~~~~~~\n");
			break;
		}
		if(strcmp(kyouka,kakunin)==0){break;}
	}
	
	if(flag==0){
		sprintf(file,"%s.txt",kyouka);
		fa=fopen(file,"r");
		float heikin=0;
		int a=0,i;	//人数確認
		int x[10]={0};	//度数分布表用
		for(;;){
			if(fscanf(fa,"%s %d",namae[0],&tensu)==EOF){break;}
			if(tensu%10==0){x[tensu/10-1]++;}
			else if(tensu%10!=0){x[tensu/10]++;}	//10点ごとに分割
			a++;
			heikin=heikin+tensu;
		}
		int j;
		for(i=10;i>0;i--){
			printf("~%d0点 ",i);
			if(i!=10){printf(" ");}
			for(j=0;j<x[i-1];j++){printf("*");}
			printf("\n");
		}
		fclose(fa);
		heikin=heikin / a;
		printf("平均%.1f点\n~~~~~~~~~~~~~~~~~~~~~~~~\n",heikin);
	}
}	
