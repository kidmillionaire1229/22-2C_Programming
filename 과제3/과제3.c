#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
struct word{
	char  eng[15];
	char  kor[10];
	struct word * next;
};


FILE* dic;
struct word * sort(struct word *);
void match(struct word *); 
struct word * storeWord();
struct word* firstWord=NULL;
int main(void) {
	int mode; 
	while(1){
	//모드 입력 
	printf("1)영어 맞추기");
	printf("2)프로그램 종료\n");
	scanf("%d", &mode); 
	if(mode==2){
		system("clear");
		return 0; 
	}
	dic = fopen("1.txt", "r");
	//저장 후 처음 시작 노드 반환 
	firstWord = storeWord(); 
	firstWord= sort(firstWord);
	match(firstWord); 
	}
	return 0;
}
struct word* storeWord() {
	struct word * head; 
	head =(struct word *) malloc(sizeof(struct word));
	if(fscanf(dic, "%s %s", head->eng,head->kor)==EOF){
		return NULL; 
	}
	else 
	{
		head->next = storeWord();
	}	
	return head;  
	
}

struct word* sort(struct word * head){
	struct word * a,* b;
	struct word * tmp; 
        for(a=head; a!=NULL;a=a->next){ 
		for(b = a; b!=NULL;b= b->next)
		{
			if(strcmp(a->eng,b->eng)>0){
				strcpy(tmp -> eng , a->eng); 
				strcpy(tmp -> kor , a ->kor); 
				strcpy(a -> eng , b ->eng); 
				strcpy(a -> kor , b ->kor); 
				strcpy(b ->eng , tmp -> eng); 
				strcpy(b -> kor , tmp -> kor); 		
			} 
		}
	} 
	head = head->next; 
	return head; 
}
void match(struct word * head){
	int score=0; //맞은 개수 
	int count=0; //전체 단어 개수 
	float totalScore; 
	char * inputWord; 
	int enter;  
	while(head != NULL) {
		count ++; 
		printf("%s\n",head->eng);
		printf("뜻을 입력하세요:");
		scanf("%s", inputWord); 
		if(strcmp(inputWord,".quit")==0){
			printf("점수는 %.1f점 입니다\n",((float)score/count)*100); 
			getchar();
			enter = getchar(); 
			if(enter=='\n')
				system("clear");
			break; 
		}
		else if(strcmp(head->kor, inputWord)==0){
			printf("correct!\n");
			score ++; 
		}
		else{
			printf("incorrect!\n");
		}
		if(head->next ==NULL){
			printf("점수는 %.1f점 입니다\n",((float)score/count)*100); 
			getchar();//남은 개행 하나 제거 
			enter = getchar(); 
			if(enter=='\n')
				system("clear"); 
		}
		head = head->next; 
	}
}


