#include <stdio.h> 
#include <string.h> 
#include <stdbool.h>
void check_lotto(); //본인이 입력한 로또 번호의 결과(당첨 여부 및 등수)를 확인하는 함수 


int main(void) {
	const int lotto[5][6] = {{1,2,3,4,5,6},{10,15,25,35,40,42},{1,9,11,22,23,25},{9,28,31,34,35,36},{1,9,23,28,33,35}}; //로또 번호를 2차원 배열로선언 동시에  초기화 
	const int myLotto[6]; 	//내가 입력한 로또 번호 
	const int myBonus; 	//내가 입력한 보너스 번호 
	
	//로또 번호 입력 
	//1. 로또 번호 (보너스 제외) 6개 입력 
	printf("금주의 로또 번호를 입력하세요->"); 
       	for(int i=0; i<6;i++){
		scanf("%d", &(myLotto[i])); 
	}	
	//2. 보너스 번호 1개 입력 
	printf("보너스 번호를 입력하세요->"); 
	scanf("%d", &myBonus); 
	
	//로또 정답이 5행 6열 2차원 배열인데, 1차원배열(한 세트당 원소 6개)별로 5번검증한다. 
	//6개 정답 로또(1세트 기준), 내가 쓴 로또 번호, 보너스 번호를 전송한다. 
	//현재 몇 번째 열(세트)인지도 함수를 통해 전송한다. 
	for(int i=0; i<5; i++) {
		check_lotto(lotto[i],myLotto,myBonus,i+1); 
	}
	return 0; 
}



void check_lotto(const int lotto[6], const int myLotto[6],const int myBonus,const int set){
	//lotto 정답 체크 
	
	int winning = 0; 				// 로또 맞춘 번호(원소)  개수 
	int resultSet[6] ={0,0,0,0,0,0}; 		//맞춘 번호가 생기면 값을 추후에 변경한다. 
	bool bonus = false; 				//보너스 당첨 여부, 초기값은 false이고 보너스번호가 당첨됐을 시에는 true로 변경, 등수에 반영한다 

	printf("%d세트 번호<",set); 	
	for(int i=0; i<6; i++) {
		printf("%d\t", lotto[i]); 
	}
	printf("> ->"); 
	
	//검증은 이중  for문을 통해 검증한다.
	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) { 
			if(lotto[i]==myLotto[j]){ 
				winning ++; 			//내가 쓴 로또 번호가 있을 시에는, winning(맞춘 번호 개수)가 증가한다.
				resultSet[i] = lotto[i];	//초기값 0에서 맞힌 로또 번호로 변경된다. 
			} 
		}
	}
	//보너스 번호도 검증을 한다. 	
	for(int i=0; i<6; i++) {
		if(lotto[i] == myBonus){ 
			bonus = true; 
			resultSet[i] = myBonus; 
		}
	}
	

	//X 포함 결과 출력 
	//맞추지 못한 경우 X를, 맞춘 경우 로또 번호가 출력이 된다. 
	for(int i=0; i<6; i++) {
		if(resultSet[i]==0) 
			printf("%c\t",88); 
		else	
			printf("%d\t", resultSet[i]); 	
	}
	
	//몇등인지 출력 
	if(winning==6) 
		printf("1등"); 
	else if(winning ==5 && bonus == true) 
		printf("2등");
	else if(winning==5)
		printf("3등"); 
	else if(winning ==4) 
		printf("4등"); 
	else if(winning == 3) 
		printf("5등"); 
	else 
		printf("꽝"); 

	printf("\n"); 
}
