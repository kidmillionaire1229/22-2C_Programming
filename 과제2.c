#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include <string.h>

struct word 
{
	char * englishWord; 
	char * meaning; 
};

struct word words[7][10] = {
    {{"apple", "사과"}, {"pear", "배"}, {"chestnut", "밤"}, {"walnut", "호두"}, {"acorn", "도토리"}, {"tangerine", "귤"}, {" strawberry", "딸기"}, {"pineapple", "파인애플"}, {" grape", "포도"}, {"peach", "복숭아"}},
    {{"aerobics", "에어로빅"}, {"archery", "양궁"}, {"athletics", "육상"}, {"badminton", "배드민턴"}, {"baseball", "야구"}, {"basketball", "농구"}, {"bowls", "볼링"}, {"boxing", "복싱"}, {"canoeing", "카누"}, {"climbing", "등산"}},
    {{"bird", "새"}, {"cat", "고양이"}, {"dog", "개"}, {"lion", "사자"}, {"tiger", "호랑이"}, {"rabbit", "토끼"}, {"fox", "여우"}, {"cow", "소"}, {"horse", "말"}, {"chicken", "닭"}},
    {{"car", "차"}, {"taxi", "택시"}, {"train", "기차"}, {"plane", "비행기"}, {"truck", "트럭"}, {"bicycle", "자전거"}, {"subway", "지하철"}, {"motorcycle", "오토바이"}, {"helicopter", "헬리콥터"}, {"scooter", "스쿠터"}},
    {{"pink", "분홍"}, {"blue", "파란"}, {"cream", "크림"}, {"gray", "회색"}, {"green", "초록"}, {"red", "빨강"}, {"yellow", "노란"}, {"brown", "갈색"}, {"black", "검은"}, {"purple", "보라"}},
    {{"cook", "요리사"}, {"doctor", "의사"}, {"model", "모델"}, {"nurse", "간호사"}, {"pilot", "조종사"}, {"lawyer", "변호사"}, {"prosecutor", "검사"}, {"professor", "교수"}, {"teacher", "교사"}, {"dentist", "치과의사"}},
    {{"cap", "모자"}, {"glove", "글러브"}, {"pants", "바지"}, {"ribbon", "리본"}, {"sock", "양말"}, {"shoes", "신발"}, {"jacket", "자켓"}, {"shirt", "셔츠"}, {"clock", "시계"}, {"ring", "반지"}},
};

void flashCard(int, int);
void game(int);
int main(void)
{
    int mode;       //메뉴중에 선택한 옵션
    int day;        //학습 일자
    int outputMode; //출력 방식
    while (1) {
        system("clear");
        printf(">>영어 단어 프로그램<<\n");
        printf("1.플래쉬 카드\t2.게임\t3.프로그램 종료\n"); //메뉴 옵션
        printf("\n");                                       //개행
        printf("번호를 선택하세요: ");
        scanf("%d", &mode);
        getchar();
        if (mode == 1)
        {
            printf("학습 일차: ");
            scanf("%d", &day);
            printf("출력 방식(수동 모드 : 1, 자동모드 : 2) : ");
            scanf("%d", &outputMode);
            flashCard(day, outputMode);
        }

        else if (mode == 2)
        {
            printf("학습 일차: ");
            scanf("%d", &day);
            getchar();
            game(day);
	    system("clear"); 
        }

        else if (mode == 3)
            return 0;
    }
    return 0;
};

void flashCard(int day, int outputMode)
{
    system("clear");
    srand((unsigned int)time(NULL)); // 매번 다른 시드값 생성
    int checkDup[10]={0,0,0,0,0,0,0,0,0,0};//중복 체크 checksum
     
    if (outputMode == 1) //수동
    {
        int i = 0;
        while (i<10) {
            int randIdx = rand() % 10; // 해당 요일에서 random한 index추출 
            
            if (checkDup[randIdx] == 1)	//이미 뽑혔으면 다시 뽑기
                continue;
            else
            {
                i++;
                checkDup[randIdx] = 1; 
            }
            
            fflush(stdin);
            char enter = getchar();
            
            if (enter == 10) {
                system("clear");
                printf("%s\n", words[day - 1][randIdx].englishWord);
            }

            enter = getchar();
            if (enter == 10) {
                system("clear");
                printf("%s\n", words[day - 1][randIdx].meaning);

            }
        }
      
    }
    else if (outputMode == 2) //자동
    {
        int i = 0;
        while(i<10)
        { 
            int randIdx = rand() % 10;
            if (checkDup[randIdx] == 1)
                continue;
            else
            {
                i++;
                checkDup[randIdx] = 1;
            }
            
            printf("%s\n", words[day - 1][randIdx].englishWord);
            sleep(1);
            system("clear");
            printf("%s\n", words[day - 1][randIdx].meaning);
            sleep(1); 
            system("clear"); 
        }
    }
}

void game(int day)
{
    srand(time(NULL)); // 매번 다른 시드값 생성
    int i; 
    int count = 1;
    int wrongCount = 0; 
    int match; 
    int wordIdx = rand() % 10; 
    
    int hangman[6] = {79,47,124,92,47,92};
    //92: 역슬래시 47:슬래시 79:대문자 O 수직막대: 124 
    char  singleWord;
    const int wordLength = strlen(words[day][wordIdx].englishWord);
     
    char matchWord[wordLength+1];  
    for (i = 0; i <wordLength; i++)
        matchWord[i] = '_';
    matchWord[wordLength] = '\0'; 
    
    while (1) 
    {
        system("clear"); 
        printf("힌트: %s\n\n", words[day][wordIdx].meaning); 
        
	//밧줄 출력문 
        for (i = 0; i < 15; i++) {
            printf("-");
        }
        printf("+\n"); 
        
	
	//행맨 모양 출력 
        if (wrongCount == 1)
            printf("%20c", hangman[0]);

        else if (wrongCount > 1 && wrongCount < 5)
        {
            printf("%20c", hangman[0]);
            printf("\n");
            for (i = 0; i < 18; i++)
                printf(" ");
            for (i = 1; i < wrongCount; i++) {
                printf("%c", hangman[i]);
            }
        }
        else if (wrongCount > 4 && wrongCount < 7)
        {
            printf("%20c", hangman[0]);
            printf("\n");

            for (i = 0; i < 18; i++)
                printf(" ");
            for (i = 1; i < 4; i++) {
                printf("%c", hangman[i]);
            }

            printf("\n");
            for (i = 0; i < 18; i++)
                printf(" ");
            for (i = 4; i < wrongCount; i++) {
                printf("%c", hangman[i]);
            }
        }
        printf("\n"); 

        //밑줄 출력
        for (i = 0; i < wordLength; i++)
            printf("%c", matchWord[i]);
        printf("\n");

	//하나의 글자 입력 
        printf("%d번째 시도:\n", count);
        scanf("%c", &singleWord); 
        getchar(); //엔터 없애기 
        
	count++; 
        
        for (i = 0; i < wordLength; i++){
            if ((matchWord[i] == '_') && (words[day][wordIdx].englishWord[i] == singleWord))   // 입력된 문자가 아직 가려져 있으면
            {
                matchWord[i] = singleWord;
                break;
            }
        }
        
        if (i == wordLength) // 못 찾았을 때 wrongCount 증가시킴 
            wrongCount++; 
        
	if (wrongCount == 6)
	{
		printf("단어 찾기 실패\n"); 
		sleep(1); 
		break;
	}
	
      
        for (i = 0; i < wordLength; i++){ //하나라도 _가 있으면 못 맞춘 거이기 때문에 break 후 다시 맞추기 시작 
            if (matchWord[i] == '_')    
                break;  
        }
	
	if (i == wordLength){       //다 맞췄을 때 축하메시지 출력 후 main 메뉴로 돌아감 
	     system("clear"); 
	     printf("congratulations\n");
	     sleep(1);
	     break;
	}

    }     	
}
