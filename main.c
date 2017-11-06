#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void csv_input();
void csv_output();
void sort();
void output();
void del();
void serch();


int main()
{
	int n;
	
	
	while(1)
	{
		printf("モードを選択してください\n");
		printf("1.CSV入力　2.CSV出力　3.ソート　4.削除　5.検索　6.終了\n");
		scanf("%d",&n);
		switch (n) {
			case 1:
				csv_input();
				break;
			case 2:
				csv_output();
				break;
			case 3:
				sort();
				break;
			case 4:
				del();
				break;
			case 5:
				serch();
				break;
			case 6:
				goto OUT;
				break;
			default:
				printf("入力エラー");
				break;
		}
	}
OUT:
	return(0);
}

void csv_input()
{
};

void csv_output()
{
};

void sort()
{
};

void output()
{
};

void del()
{
};

void serch()
{
};
	
