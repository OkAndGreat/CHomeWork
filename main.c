#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <string.h>

void showMainMenu();
void showIntroduction();
void startGameing(int BoardSize);
void showResults(); 
void DisplyNode(struct link *head);
void startGamingPre();
bool judge(int n);
struct link *InsertNode(struct link *head, int score,int id);
void cnt(int BoardSize);
void EightQueen(int n,int BoardSize);
int needCount=10;
int count=0; 
int completedCount=0; 
int Queen[8];
void showRanks();
bool isCompletedGame=true;
struct link
{
	int id;
	int score;
	struct link *next;
};

int main() {
	int mainMenuSelector;
	bool keepPlaying=true;
	while(keepPlaying) {
		showMainMenu();
		scanf("%d",&mainMenuSelector);
		switch(mainMenuSelector) {
			case 1:
			showIntroduction();	
			break;
			case 2:
			startGamingPre();
			break;
			case 3:
				showResults();
			break;
			case 4:
				showRanks();
				break;
			case 5:
			keepPlaying=false;
			break;
			default:printf("输入错误！请重新输入!\n");
		}
	}
	printf("欢迎下次再来游玩！\n");
}

void showRanks(){
	printf("您的id默认为 0 \n");
	//init
	FILE *fp = NULL;
	struct link *head = NULL;
	int Score=0;
	int Id=0;
    char id[4];
    char score[4];
    fp = fopen("/tmp/data.txt", "r");
    //将自己的成绩插入链表
    head=InsertNode(head,completedCount,0);
   do{
   	for (int i = 0; i < strlen(id); i++)
              id[i] = '\0';  
    for (int i = 0; i < strlen(score); i++)
              score[i] = '\0'; 
              fgets(id, 4, (FILE*)fp);
              fgets(score, 4, (FILE*)fp);
	if(id[0]!='\0'){
		int IdLength=0;
		int ScoreLength=0;
		while(48<=id[IdLength]&&id[IdLength]<=57) IdLength++;
		while(48<=score[ScoreLength]&&score[ScoreLength]<=57) ScoreLength++;
		for(int i=0;i<ScoreLength;i++)
			Score+=(score[i]-'0')*(pow(10,ScoreLength-i-1));
		for(int i=0;i<IdLength;i++)
		 Id+=(id[i]-'0')*(pow(10,IdLength-i-1));
		head=InsertNode(head,Score,Id);
		Score=0;
		Id=0;
	}
   }while(id[0]!='\0');
   fclose(fp);
   DisplyNode(head);
}

void showMainMenu() {
	printf("==============================================================\n\n");
	printf("\t八\t皇\t后\t小\t游\t戏\t\n\n");
	printf("==============================================================\n\n");
	printf("\t1.\t游\t戏\t规\t则\n\n");
	printf("\t2.\t开\t始\t游\t戏\n\n");
	printf("\t3.\t查\t看\t结\t果\n\n");
	printf("\t4.\t查\t看\t榜\t单\n\n");
	printf("\t5.\t退\t出\t游\t戏\n\n");
	printf("==============================================================\n");
}

void showIntroduction(){
		printf("==============================================================\n\n");
		printf("\t游\t戏\t规\t则\t\n\n");
	printf("\t在8×8格的国际象棋上摆放8个皇后，使其不能互相攻击，即任意两个皇后都不能处于同一行、同一列或同一斜线上\n");
	printf("==============================================================\n\n");
}

void startGamingPre(){
	if(isCompletedGame){
		printf("恭喜您成功完成八皇后游戏，请试着挑战N皇后吧！\n");
		printf("请选择棋盘大小\n");
		int BoardSize;
		scanf("%d",&BoardSize);
		startGameing(BoardSize); 
	}else{
		startGameing(8);
	}
}

void startGameing(int BoardSize){
	//initBoard
	int board[BoardSize][BoardSize];
	for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			board[i][j]=0;
		}
	}
	int row;
	int column;
	bool isSuccess=true;
	
	printf("请输入对应的下标值来表示将棋子放在此处\n");
	printf("如输入 0 0 则表示将皇后放在(0,0)这个位置\n");
	
		//showBoardStart
		printf("============棋================================盘==============\n\n");
		for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			printf("%d\t",board[i][j]);
		}
		printf("\n\n");
		}
		printf("==============================================================\n\n");
		//showBoardEnd
	
	//start the real game
	for(int i=0;i<BoardSize;i++){
		//make sure that the input is right
		while(true){
		scanf("%d %d",&row,&column);
		if(row<0||row>=BoardSize||column<0||column>=BoardSize){
			printf("输入的数值错误！请重新输入！\n");
		}else{
			break;
		}
		}
		board[row][column]=1;
		
		//showBoardStart
		printf("============棋================================盘==============\n\n");
		for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			printf("%d\t",board[i][j]);
		}
		printf("\n\n");
		}
		printf("==============================================================\n\n");
		//showBoardEnd
		bool result=true;
		int cntForRow=0;
		int cntForColumn=0;
		for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(board[i][j]==1) cntForRow++;
			if(board[j][i==1]) cntForColumn++;
		}
		if(cntForRow>1||cntForColumn>1){
			result=false;
			break;
		}else{
			cntForRow=0;
			cntForColumn=0;
		}
	}
	
	//检查对角线方向是否有放置俩个及以上的皇后 
	if(result){
		for(int i=0;i<BoardSize;i++){
			for(int j=0;j<BoardSize;j++){
				if(board[i][j]==1){
					int tempi=i;int tempj=j;
					while(--tempi>=0&&--tempj>=0){
						if(board[tempi][tempj]==1){
							result=false;
							break;
						}
					}
					
					tempi=i;tempj=j;
					while(++tempi<BoardSize&&++tempj<BoardSize){
						if(board[tempi][tempj]==1){
							result=false;
							break;
						}
					} 
				}
			}
		}
	}
		if(!result){
			printf("此次输入不符合游戏规则！\n");
			isSuccess=false;
			break;
		}
	}
	if(isSuccess) {
		isCompletedGame=true;
	completedCount++; 
	printf("恭喜您挑战成功了!\n");	
	printf("截至目前，您成功给出了%d种解法\n",completedCount); 
	} else{
	 printf("很遗憾您挑战失败了！请再试试吧！\n");
	}
}


void showResults(){
	int BoardSize;
	printf("请输入棋盘大小\n");
	scanf("%d",&BoardSize);
	printf("请输入想要得到多少种解法！\n");
	scanf("%d",&needCount);
	count=0;
	printf("请稍等，正在努力找寻结果中！\n");
	Sleep(2000);
	EightQueen(0,BoardSize);
}

//递归回溯 
void EightQueen(int n,int BoardSize){
	for(int i=0;i<BoardSize;i++){
		Queen[n]=i;
		if(judge(n)){
			if(n!=BoardSize-1) EightQueen(n+1,BoardSize);
			//表示找到一种解法 
			else cnt(BoardSize);
		}
	}
}

//如果符合条件返回true 不符合条件返回false
bool judge(int n){
	//第一个条件判断是否在同一列,第二个条件判断是否在同一斜线(要用绝对值,因为可能45度角,可能135度角)
	for(int i=0;i<n;i++){
		if (Queen[i] == Queen[n] || abs(n - i) == abs(Queen[n] - Queen[i])) {
                return false;
            }
	}
	return true;
}

//每调用一次cnt()则说明找到一种解法
void cnt(int BoardSize){
	count++;
	if(needCount>=count){
			printf("============第=========%d=========种======方========法==========\n\n",count);
		printf("============棋================================盘==============\n\n");
	for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			if(Queen[i]==j) printf("1\t");
			else  printf("0\t");
			
		}
		printf("\n\n");
	}
	printf("==============================================================\n\n");
	Sleep(200);
	}
}

struct link *InsertNode(struct link *head, int score,int id)
{
	struct link *pr = head, *p = head, *temp = NULL;
	p = (struct link *)malloc(sizeof(struct link));
	if (p == NULL)    		
	{
		printf("No enough memory!\n");
		exit(0);
	}
	p->next = NULL;		
	p->id = id;	
	p->score=score;
	if (head == NULL)		
	{
     	head = p;           
  	}
	else
	{ 	
		while (pr->score < score && pr->next != NULL)
       	{
				temp = pr;     
				pr = pr->next;
		}
		if (pr->score >= score)
		{
				if (pr == head)      
				{
				p->next = head;
				head = p;       
				}
				else                   
				{
					pr = temp;
					p->next = pr->next;
					pr->next = p;       
				}
		}
		else                    
		{
				pr->next = p;    
		}
	}
	return head;			   
}

void DisplyNode(struct link *head)
{
	printf("   Id     Score\n");
	struct link *p = head;
	while (p != NULL)        	          
	{
		printf("%5d%10d\n", p->id,p->score);
		p = p->next;             		  
	}
}
