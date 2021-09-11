#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

#pragma warning(disable:4996) 
#pragma warning(disable:4477) 

#define SUCCESS 1
#define FAIL 0

#define YES 1
#define NO 0

#define LENGTH 16
#define WIDTH 16

#define X 0
#define Y 1

#define QUEENRANGE 1
#define NOTINRANGE 0

/*
Using Stack , LET'S SOLVE N-QUEEN

Problem- Line 234, 243, 254, 255 
*/

typedef struct _QueenCorrdinate {
	int x; // 행
	int y; // 렬
} Cor;

typedef struct _ChessBoard {
	int BoardState[LENGTH][WIDTH];
} ChessBoard;

 typedef struct _Node {
	 Cor *Corrdinate; // 퀸의 위치
	 ChessBoard *NodeChessBoard; // 체스보드 
	 struct _Node *BeforeThisQueen; // 다음 퀸 노드 
	 int AbleLocationArray_y[WIDTH]; // 체스보드를 기준으로 한 행에서 0인 지점의 위치를 저장하는 곳. 그냥 퀸이 놓일수 있는 가능한 위치를 나열한 배열이다. 
	 int y_index; // y 위치 변수. 
	 int max_y_index; // 가능한 y 위치 총 개수
} Node;

 typedef struct _Stack {
	 Node *Top; // 가장 나중에 배치된 퀸
	 Node *First; // 가장 먼저 배치된 퀸
	 ChessBoard *CurrentChessBoard; // 퀸이 배치될때마다 보드판 새로 그림
	 int AbleQueenCount; // 퀸이 제대로 전부다 배치될때마다 queencount++
	 int QueenIndex; // 퀸이 들어올때마다 +1씩 
	 int QueenAbleCoordinatesArray[LENGTH][2]; // 지금까지 배치된 퀸의 좌표들을 저장. 나중에 들어올 퀸의 좌표에 범위가 닿는지 안닿는지 검사하는 용도 
 } Stack;

 // 보드 초기화
void BoardClear(Stack *stack, int NumberofQueen) {

	 int i = 0;
	 int j = 0;

	 for (int i = 0; i < NumberofQueen; i++) {
		 for (int j = 0; j < NumberofQueen; j++) {
			stack->CurrentChessBoard->BoardState[i][j] = NOTINRANGE;
		 }
	 }
 }

// 디버깅용 함수 
void printBoard(Stack *stack, int NumberofQueen) {
	for (int i = 0; i < NumberofQueen; i++) {
		for (int j = 0; j < NumberofQueen; j++) {
			printf("%d ", stack->CurrentChessBoard->BoardState[i][j]);
		}
		printf("\n");
	}
}

 // 스택 초기화 
 void stack_init(Stack *stack, int NumberofQueen) {
	 stack->AbleQueenCount = 0;
	 stack->Top = NULL;
	 stack->First = NULL;
	 stack->CurrentChessBoard = (ChessBoard*)malloc(sizeof(ChessBoard));
	 stack->QueenIndex = 0; 
	BoardClear(stack, NumberofQueen);
 }

 // 스택이 비었는지 조사 
 int stack_is_empty(Stack *stack) {
	 if (stack->Top == NULL) return YES;

	 return NO;
 }

int DrawTopQueenRange(Stack *stack, int NumberofQueen) {

	// 스택이 비어있으면 top도 없을테니 오류발생
	 if (stack_is_empty(stack) == NO) {

		 int length = stack->Top->Corrdinate->x;
		 int width = stack->Top->Corrdinate->y;

		 // 가로 1로 바꾸기 
		 // 사실 굳이 필요없음. 어차피 x는 1씩 증가시킬거라 겹칠일이 없지만 그래도 하자 
		 for (int i = 0; i < NumberofQueen; i++) {
			 stack->CurrentChessBoard->BoardState[length][i] = QUEENRANGE;
		 }

		 // 세로 1로 바꾸기
		 for (int j = 0; j < NumberofQueen; j++) {
			 stack->CurrentChessBoard->BoardState[j][width] = QUEENRANGE;
		 }

		 // 대각선 오른쪽 아래 방향
		 while (length < NumberofQueen && width < NumberofQueen) {
			 stack->CurrentChessBoard->BoardState[length++][width++] = QUEENRANGE;
		 }

		 // 다시 초기화 해주고 
		 length = stack->Top->Corrdinate->x;
		 width = stack->Top->Corrdinate->y;

		 // 대각선 왼쪽아래방향 
		 while (length < NumberofQueen && width >= 0) {
			 stack->CurrentChessBoard->BoardState[length++][width--] = QUEENRANGE;
		 }
	 }

	 return SUCCESS;
 }

 // 퀸 좌표값 대입  
int setQueen(Stack *stack, int NumberofQueen) {

	// 종료조건은 첫 퀸의 y좌표가 첫 행의 중간열 이상에 놓였을 떄이다. 
	// 왜냐? 입력된 퀸 개수 절반까지만 하고 두배해주면 되니까.. 시간두배로 줄일 수 있다. 만약 홀수개이면 두배하고 가운데꺼 한번 빼주면 된다.

	// 하지만 지금은 그냥 끝까지 실행시켜보자고~
	do {

	// 1. 만약 전에 퀸이 놓은 곳이 없다면, (즉 맨 처음 실행할 경우) 퀸을 가능한 위치 중에 열이 가장 작은 곳에 배치한다. 물론, 첫 행은 0이다. 
	if (stack_is_empty(stack) == YES) {

		// 일단 퀸을 놓기 위한 노드생성 
		Node *NewQueen = (Node*)malloc(sizeof(Node));
		memset(NewQueen, -1, sizeof(Node));

		// 무조건 맨 처음 퀸은 0,y에서 시작할 것이다 
		NewQueen->Corrdinate = (Cor*)malloc(sizeof(Cor));
		NewQueen->Corrdinate->x = 0;
		// nullptr참조오류 
		// 그럼 이걸 뭐 어떻게든 값을 넣어줘야한다는 소리인데...?
		// NewQueen->Corrdinate = (Cor*)malloc(sizeof(Cor)); 로 해결..?


		// 일단 0부터 입력된 퀸 수-1 만큼 배열에 넣는다. 어차피 첫줄은 모든 y값이 가능하니까, 0번은 0, 1번은 1... 
		int index = 0;

		while (index < NumberofQueen) {
			NewQueen->AbleLocationArray_y[index] = index;
			index++;
		}

		// 퀸이 택할 수 있는 y 인덱스의 총개수를 구한다.
		NewQueen->max_y_index = index;

		// 맨 처음이니까 y 인덱스 위치를 0으로 잡는다. 
		NewQueen->y_index = 0;

		// 그리고나서 arr에서 가장 앞에있는거부터 선택 
		NewQueen->Corrdinate->y = NewQueen->AbleLocationArray_y[NewQueen->y_index];

		// // 맨 첫번째 퀸 인덱스는 0
		//NewQueen->QueenIndex = 0;

		// 스택의 퀸 좌표 저장배열에 첫번쨰 좌표값을 넣는다 
		stack->QueenAbleCoordinatesArray[NewQueen->Corrdinate->x][X] = NewQueen->Corrdinate->x;
		stack->QueenAbleCoordinatesArray[NewQueen->Corrdinate->x][Y] = NewQueen->Corrdinate->y;

		// 맨 처음에 한해서, 완전 초기상태, 백지상태 보드를 저장하기위한 노드를 따로 만든다. 
		Node *SaveNullBoard = (Node*)malloc(sizeof(Node));
		memset(SaveNullBoard, 0, sizeof(Node));

		SaveNullBoard->NodeChessBoard = stack->CurrentChessBoard;

		// 맨 처음 퀸은 특별히 백지상태 보드를 가리킨다. 나중에 수정에 용이하도록 
		NewQueen->BeforeThisQueen = SaveNullBoard;

		//// 퀸 번호를 부여해준다.  // 이거 필요하냐?
		//NewQueen->QueenIndex = NewQueen->Corrdinate->x;

		// 드디어 새 퀸을 스택에 맞아들일 준비가 되었다
		stack->Top = NewQueen;

		// 이 스택의 First는 변하지 않을것이다. 
		stack->First = NewQueen;

		// 퀸 좌표값에 따라 보드에 범위표시해준다.
		DrawTopQueenRange(stack, NumberofQueen);

		// 그 범위가 그려진 체스보드를 첫번쨰 노드에 담아주자 
		NewQueen->NodeChessBoard = stack->CurrentChessBoard;

		stack->QueenIndex++;

	}
	else {  // 만약 퀸이 첫번쨰로 놓아진게 아니라면..

		// 2. 전에 놓여진 퀸 범위에 모두 닿지 않는 y_index값을 찾아보자.  물론 이때 다음 노드의 행은 전 노드 행의 x값+1으로 만들어준다. 

		// 퀸 노드생성 
		Node *NewQueen = (Node*)malloc(sizeof(Node));
		memset(NewQueen, -1, sizeof(Node));

		// 3. 만약 이번 x행을 처음으로 조사하면, 현재 보드판을 가져오고, 이번 x번째 행에서 0인지점을 모두 차례대로 저장한다. 이 동작은 그 행의 노드가 삭제되기 전까지는 한번만 실행된다. 
		// 즉 이게 뭔말이냐 하면 퀸이 현재 이 행에 놓여있지 않다는 뜻
		if (stack->Top->Corrdinate->x == stack->QueenIndex - 1) {
			int index = 0;
			// w

			for (int width = 0; width < NumberofQueen; width++) {
				if (stack->CurrentChessBoard->BoardState[stack->Top->Corrdinate->x + 1][width] != 1) {
					NewQueen->AbleLocationArray_y[index++] = width;
				}
			}

			// 언제나 행마다 y인덱스 시작점은 0이다. // y열 값이 정해진 이상 변하지 않는다. 
			NewQueen->y_index = 0;

			// 새 퀸이 택할 수 있는 y 인덱스 총개수를 구한다. // y열 값이 정해진 이상 변하지 않는다. 
			NewQueen->max_y_index = index;
		}

		// 4. 만약 선택할 0이 없을 경우, 전 노드로 돌아간다. **************여기 수정만 하면 될듯 
		if (NewQueen->AbleLocationArray_y[NewQueen->y_index] == NULL) {

			// 퀸을 놓을 수 없으므로 free해준다. 
			free(NewQueen);

			// 바로 전에 놓인 퀸의 y인덱스 위치를 +1해준다 
			stack->Top->y_index++;

			// 5. 전 노드로 돌아갔는데, 하필 y인덱스값이 마지막이었다면? 다시 위로 올려줘야함
			if (stack->Top->AbleLocationArray_y[stack->Top->y_index] == NULL) {

				// 그 전에있던 퀸 노드를 없애고 또다시 그 전으로 돌아가야함. 

				// 먼저 그 노드를 없애야 하니까 삭제할 노드를 만들어주고, 이를 스택 top 으로 지정. 
				Node *DeleteQueen = stack->Top;

				// 그 퀸 노드가 갖고있던 데이터들이 스택에 들어간걸 초기화 시켜줘야함



				stack->QueenAbleCoordinatesArray[stack->Top->Corrdinate->x][X] = NULL;
				stack->QueenAbleCoordinatesArray[stack->Top->Corrdinate->x][Y] = NULL;

				//(*stack->QueenAbleCoordinatesArray[stack->Top->Corrdinate->x]) = NULL;



				// 스택 top의 위치를 변경해준다. 
				stack->Top = stack->Top->BeforeThisQueen;

				// 변경한 스택 TOP의 Y인덱스를 1 올려준다. 
				stack->Top->y_index++;

				// 체스판 역시 바꿔줘야함. 
				// 위에서 0번째 행 전에도 노드를 하나 만듦으로써 만약 0번쨰 행의 Y위치가 바뀔때도 마찬가지로 오류없이 작동되도록 했다. 
				stack->CurrentChessBoard = stack->Top->BeforeThisQueen->NodeChessBoard;

				stack->QueenIndex--;

				// 이제 보내주자..
				free(DeleteQueen);
			}
		}
		else {  // 6. 퀸들의 범위에서 벗어난 공간, 즉 0이 있을 경우 

			// NewQueen->QueenIndex = ?
			// 이거 쓰긴 하냐>?? 

			// 새 퀸의 x값은 그 전 퀸의 x값+1이다. 		
			NewQueen->Corrdinate = (Cor*)malloc(sizeof(Cor));

			NewQueen->Corrdinate->x = stack->Top->Corrdinate->x + 1;

			// 새 퀸 노드를 그전에 놓아진 퀸 노드와 연결해준다. 
			NewQueen->BeforeThisQueen = stack->Top;

			// 근데 만약 맨 마지막 퀸이면 여기서 카운트 올려줘야한다. 
			if (NewQueen->Corrdinate->x == NumberofQueen - 1) {
				stack->AbleQueenCount++;
			}
			//TODO 이거 맨 처음 경우에 추가할것 퀸이 한개일수도 있음 

			// 이제 좌표 등록하고 
			NewQueen->Corrdinate->y = NewQueen->AbleLocationArray_y[NewQueen->y_index];

			stack->QueenAbleCoordinatesArray[NewQueen->Corrdinate->x][X] = NewQueen->Corrdinate->x;
			stack->QueenAbleCoordinatesArray[NewQueen->Corrdinate->x][Y] = NewQueen->Corrdinate->y;

			// top을 newqueen으로 지정해주고 
			stack->Top = NewQueen;

			// 보드 그리고
			DrawTopQueenRange(stack, NumberofQueen);

			// 보드 등록하고 
			NewQueen->NodeChessBoard = stack->CurrentChessBoard;

			stack->QueenIndex++;

		}
	}
} while (stack->First->Corrdinate->y < NumberofQueen);

		 return stack->AbleQueenCount; 
 }

 // 

 
 int main() {

	int Queen;
	Stack stack;

	scanf("%d", &Queen);

	stack_init(&stack, Queen);

	printf("%d",setQueen(&stack, Queen));


	return 0;
}
 // 살려줘 