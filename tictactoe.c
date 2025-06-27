#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define BOLDCYAN   "\x1b[1;36m"
#define BOLDGREEN "\x1b[1;32m"
#define BOLDYELLOW "\x1b[1;33m"
#define RESET      "\x1b[0m"
typedef struct {
    char name[50];
    int wins;
} playerscore;
char** setupboard(int *size,int *maxmoves);
void updatescore(char *winner);
void playerturn(char **board,int size,char symbol);
void displayboard(char **board,int size);
char checkwinner(char **board,int size);
void loghistory(char *name1,char *name2,char symbol);
void viewleaderboard();
void viewrules();
void viewhistory();
void managehistory();
void clearhistory();
void backuphistory();
void startgameMenu();
void startpvp();
void startp_vs_easyai();
void startp_vs_medai();
void ai_easy_move(char **board, int size, char aiSymbol);
void searchname(playerscore *player,int count);
void ai_medium_move(char **board,int size, char aiSymbol);
int comparescore(const void *a,const void *b);
int main()
{   srand(time(NULL));
    int choice;
    do{
        
        printf("\n-----------------Main Menu-----------------\n");
        printf("\n1 - Start Game.");
        printf("\n2 - Manage History.");
        printf("\n3 - View Rules.");
        printf("\n4 - View Leaderboard.");
        printf("\n5 - Exit.");
        printf("\nEnter Your choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                char playagain;
                do{
                    startgameMenu();
                    printf("Do You Want to Play Again? (YES - Y / NO - N) : ");
                    getchar();
                    scanf("%c",&playagain);
                }while(playagain == 'Y' || playagain == 'y');
                break;
            }
            case 2 : {
                managehistory();
                break;
            }
            case 3 : {
                viewrules();
                break;
            }
            case 4 : {
                viewleaderboard();
                break;
            }
            case 5 : {
                printf("\nThank You For Playing.");
                break;
            }
            default : {
                printf("\nInvalid Choice! Choose Again.");
            }
        }
    }while(choice != 5);
    return 0;
}
char** setupboard(int *size,int *maxmoves)
{
    printf("Enter Game Board Size (e.g., 3 for 3x3): ");
    scanf("%d", size);
    *maxmoves = (*size) * (*size);
    char **board = (char**)malloc(*size*sizeof(char*));
    if (board == NULL) {
        printf("Memory allocation failed for Playboard.\n");
        return NULL;
    }
    for(int i=0;i<*size;i++)
    {
        board[i] = (char*)malloc(*size*sizeof(char));
        if (board[i] == NULL) {
        printf("Memory allocation failed for Playboard.\n");
        for(int j=0;j<*size;j++) 
        {
            free(board[j]);
        }
        free(board);
        return NULL;
        }
        for(int j=0;j<*size;j++)
        {
            board[i][j] = '.';
        }
    }
    return board;
}
void playerturn(char **board,int size,char symbol)
{
    int row,col;
    do{
        printf("Enter position (row col): ");
        scanf("%d %d",&row,&col);
        if(row < 0 || col < 0 || row >= size || col >= size || board[row][col] != '.')
        {
            printf("\nInvalid or taken! Try again.\n\n");
        }
        else
        {
            break;
        }
    }while(1);
    board[row][col] = symbol;
}
void displayboard(char **board,int size)
{
    printf("\nCurrent Board :-\n");
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}
char checkwinner(char **board,int size)
{
    // for Rows
    for(int i=0;i<size;i++)
    {
        char start = board[i][0];
        if(start == '.')
        {
            continue;
        }
        int j;
        for(j=1;j<size;j++)
        {
            if(board[i][j] != start)
            {
                break;
            }
        }
        if(j == size)
        {
            return start;
        }
    }
    // for column;
    for(int j=0;j<size;j++)
    {
        char start = board[0][j];
        if(start == '.')
        {
            continue;
        }
        int i;
        for(i=1;i<size;i++)
        {
            if(board[i][j] != start)
            {
                break;
            }
        }
        if(i == size)
        {
            return start;
        }
    }
    // For Diagonal
    char start = board[0][0];
    if(start != '.')
    {
        int i;
        for(i=1;i<size;i++)
        {
            if(board[i][i] != start)
            {
                break;
            }
        }
        if(i == size)
        {
            return start;
        }
    }
    // for Anti Diagonal
    start = board[0][size-1];
    if(start != '.')
    {
        int i;
        for(i=1;i<size;i++)
        {
            if(board[i][size-i-1] != start)
            {
                break;
            }
        }
        if(i == size)
        {
            return start;
        }
    }
    return '.';
}
void startgameMenu()
{
    int choice;
    printf("\nAll Playing Option:-");
    printf("\n1 - Player vs Player.");
    printf("\n2 - Player vs AI(Easy).");
    printf("\n3 - Player vs AI(Medium).");
    do {
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                startpvp();
                break;
            }
            case 2 : {
                startp_vs_easyai();
                break;
            }
            case 3 : {
                startp_vs_medai();
                break;
            }
            default : {
                printf("\nInvalid Choice. Choose Again.\n");
            }
        }
    }while(choice > 3 || choice < 1);
}
void startpvp()
{
    int size,maxmoves;
    char name1[20],name2[20];
    printf("\nWelcome To Battle Field of Tic Tac Toe Saga :\n");
    printf("Enter Player 1 Name : ");
    scanf("%s",name1);
    getchar();
    printf("Enter Player 2 Name : ");
    scanf("%s",name2);
    getchar();
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
    char** board = setupboard(&size,&maxmoves);
    if (board == NULL) return;
    int moveCount = 0;
    char winner = '.';
    char symbol;
    while(maxmoves > moveCount && winner == '.')
    {
        if(moveCount % 2 == 0 )
        {
            symbol = 'x';
        }
        else
        {
            symbol = 'o';
        }  
        if(symbol == 'x')
        {
            printf("\nTurn - %d Player - %s('%c') :\n",moveCount+1,name1,symbol);
        }
        else
        {
            printf("\nTurn - %d Player - %s('%c') :\n",moveCount+1,name2,symbol);
        }
        playerturn(board,size,symbol);
        displayboard(board,size);
        winner = checkwinner(board,size);
        moveCount ++;
    }
    displayboard(board, size);
    if(winner != '.')
    {
        if(symbol == 'x')
        {
            printf(BOLDGREEN "\nPlayer - %s (%c) Wins!\n" RESET, name1,winner); 
            updatescore(name1);
        }
        else{
            printf(BOLDGREEN "\nPlayer - %s (%c) Wins!\n" RESET, name2,winner); 
            updatescore(name2);
        }
    }
    else
    {
        printf(BOLDYELLOW "\nIt's a Draw!\n" RESET);
    }
    loghistory(name1,name2,winner);
    for(int i=0;i<size;i++)
    {
        free(board[i]);
    }
    free(board);
    printf("\n----- Game Over -----\n");
}
void loghistory(char *name1,char *name2,char symbol)
{
    FILE *fp;
    fp = fopen("history.txt","a");
    if(fp == NULL)
    {
        printf("ERROR : Unable To Open The File.");
        return ;
    }
    if(symbol == '.')
    {
        fprintf(fp,"Player1 : %s (X) vs Player2 : %s (O) => Result: Draw ",name1,name2);
    }
    else if(symbol == 'X' || symbol == 'x')
    {
        fprintf(fp,"Player1 : %s (X) vs Player2 : %s (O) => Winner : %s(x) ",name1,name2,name1);
    }
    else{
        fprintf(fp,"Player1 : %s (X) vs Player2 : %s (O) => Winner : %s(0) ",name1,name2,name2);
    }
    time_t t;
    struct tm *tm_info;
    char timesta[30];
    time(&t);
    tm_info = localtime(&t);
    strftime(timesta,30,"[%Y-%m-%d %H:%M:%S]",tm_info);
    fprintf(fp,"%s\n",timesta);
    fclose(fp);
    fp = fopen("history.txt", "r");
    if (fp == NULL) 
    {
        return;
    }
    char **lines = NULL;
    int count = 0;
    int capacity = 10;
    char buffer[256];
    lines = (char**)malloc(capacity * sizeof(char*));
    if(lines == NULL)
    {
        printf("ERROR : Unable to Store Game History.");
        return ;
    }
    while(fgets(buffer,sizeof(buffer),fp))
    {
        if(count == capacity)
        {
            capacity *= 2;
            lines = (char**)realloc(lines,capacity * sizeof(char*));
        }
        lines[count] = (char*)malloc(strlen(buffer)+1);
        if(lines[count] == NULL)
        {
            printf("ERROR : Unable to Store Game History.");
            return ;
        }
        strcpy(lines[count],buffer);
        count++;
    }
    fclose(fp);
    int start;
    #define maxhistory 100
    if(count > maxhistory)
    {
        start = count - maxhistory;
    }
    else{
        start = 0;
    }
    fp = fopen("history.txt", "w");
    if (fp == NULL) 
    {
        printf("ERROR: Unable to reopen history.txt\n");
        for (int i = 0; i < count; i++) free(lines[i]);
        free(lines);
        return;
    }
    for(int i=start;i<count;i++)
    {
        fputs(lines[i],fp);
        free(lines[i]);
    }
    fclose(fp);
    free(lines);
}
void updatescore(char *winner)
{
    playerscore *player;
    FILE *fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return;
    }
    int capacity = 2;
    int count = 0;
    player = (playerscore*)malloc(capacity * sizeof(playerscore));
    while (1) {
        char tempName[30];
        int tempwins;
        if (fscanf(fp, "%s %d", tempName, &tempwins) != 2)
            {
                break;
            }
        if (count == capacity) {
            capacity *= 2;
            player = (playerscore*)realloc(player, capacity * sizeof(playerscore));
        }
        strcpy(player[count].name, tempName);
        player[count].wins = tempwins;
        count++;
    }
    fclose(fp);
    int found = 0;
    for(int i=0;i<count;i++)
    {
        if(strcmp(player[i].name,winner) == 0)
        {
            found = 1;
            player[i].wins += 1;
            break;
        }
    }
    if(found == 0)
    {
        player = (playerscore*)realloc(player, (capacity+1) * sizeof(playerscore));
        capacity++;
        strcpy(player[count].name,winner);
        player[count].wins = 1;
        count++;
    }
    fp = fopen("score.txt", "w");
    for(int i=0;i<count;i++)
    {
        fprintf(fp,"%s %d\n",player[i].name,player[i].wins);
    }
    fclose(fp);
}
void viewleaderboard()
{
    playerscore *player;
    FILE *fp = fopen("score.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return;
    }
    int capacity = 2;
    int count = 0;
    player = (playerscore*)malloc(capacity * sizeof(playerscore));
    while (1) {
        char tempName[30];
        int tempwins;
        if (fscanf(fp, "%s %d", tempName, &tempwins) != 2)
        {
            break;
        }
        if (count == capacity) {
            capacity *= 2;
            player = (playerscore*)realloc(player, capacity * sizeof(playerscore));
        }
        strcpy(player[count].name, tempName);
        player[count].wins = tempwins;
        count++;
    }
    fclose(fp);
    qsort(player,count,sizeof(playerscore),comparescore);
    printf("\n----------------------------------\n");
    printf("\nWhole LeaderBoard Is Like This :-\n");
    printf("Rank\tPlayer Name\tTotal Wins\n");
    for(int i=0;i<count;i++)
    {
        printf("%d\t%s\t\t",i+1,player[i].name);
        printf("%d\n",player[i].wins);
    }
    int choice;
    printf("\nEnter 1 For Seaching a Player's Name : ");
    scanf("%d",&choice);
    while ((getchar()) != '\n'); 
    if(choice == 1)
    {
        searchname(player,count);
    }
}
void viewrules()
{
    printf("\n----- Tic-Tac-Toe Game Rules -----\n");
    printf("Player vs Player - Classic 2-player mode.\n");
    printf("Player vs AI (Easy) - Play against a basic AI that makes random or winning moves.\n");
    printf("Player vs AI (Medium) - The AI tries to block your winning moves in addition to winning itself.\n");
    printf("1. Two players take turns.\n");
    printf("2. Mark X and O to get a full row, column or diagonal.\n");
    printf("\nGameplay:\n");
    printf("3. Players enter the row and column to place their symbol.\n");
    printf("4. A move is invalid if the cell is already occupied.\n");
    printf("5. First to align wins. If all filled, it's a draw.\n");
    printf("6. Game results are stored in file (latest 100 games only).\n");
    printf("7. Leaderboard ranks players based on total wins.\n");
    printf("8. After a match, you can choose to Play Again, View History, or Exit.\n");
    printf("\nPlay smart, play fair, and enjoy the challenge.\n");
}
void viewhistory()
{
    FILE *fp = fopen("history.txt", "r");
    if (fp == NULL) 
    {
        printf("\nNo History Found Yet.\n");
        return;
    }
    char line[256];
    int entry = 1;
    printf("\n-------------------------------------\n");
    printf("\nHere Is The All Games History.\n\n");
    while(fgets(line,sizeof(line),fp) != NULL)
    {
        printf("%d) %s",entry,line);
        printf("--------------------------------------------------\n");
        entry++;
    }
    if (entry == 1)
    {
        printf("No History Found.\n");
    }
    fclose(fp);
}
int comparescore(const void *a,const void *b)
{
    playerscore *p1 = (playerscore*)a;
    playerscore *p2 = (playerscore*)b;
    return p2->wins - p1->wins;
}
void managehistory()
{
    int choose;
    printf("\n----- Manage History Menu -----\n");
    printf("\n1 - View Full History (Recent 100).");
    printf("\n2 - Clear History.");
    printf("\n3 - Backup History to 'history_archive.txt'.");
    do{
        printf("\nEnter Your Choice : ");
        scanf("%d",&choose);
        switch (choose)
        {
            case 1 : {
                viewhistory();
                break;
            }
            case 2 : {
                clearhistory();
                break;
            }
            case 3 : {
                backuphistory();
                break;
            }
            default : {
                printf("\nInvalid Choice. Choose Again.\n");
            }
        }
    }while(choose > 3 || choose < 1);
}
void clearhistory()
{
    FILE *fp = fopen("history.txt", "w");
    if (fp == NULL) 
    {
        printf("\nNo History Found Yet.\n");
        return;
    }
    printf("\nAll History Is Succesfully Deleted.");
    fclose(fp);
}
void backuphistory()
{
    FILE *Source = fopen("history.txt", "r");
    if (Source == NULL) 
    {
        printf("History file doesn't exist to back up.\n");
        return;
    }
    FILE *Destination = fopen("history_archive.txt", "w");
    if (Destination == NULL) 
    {
        printf("\nNo History Found Yet.\n");
        return;
    }
    char ch;
    while((ch = fgetc(Source)) != EOF)
    {
        fputc(ch,Destination);
    }
    printf("\nBackup History Is Succesfully Saved.");
    fclose(Source);
    fclose(Destination);
}
void searchname(playerscore *player,int count)
{
    char search[20];
    int found = 0;
    printf("Enter Player Name.. : ");
    scanf("%s",search);
    printf("\nRank\tPlayer Name\tTotal Wins\n");
    for(int i=0;i<count;i++)
    {
        if(strcmp(player[i].name,search) == 0)
        {
            found = 1;
            printf("%d\t%s\t\t",i+1,player[i].name);
            printf("%d\n",player[i].wins);
            return;
        }
    }
    if (!found) {
    printf("Player not found in the leaderboard.\n");
    }
}
void startp_vs_easyai()
{
    int size,maxmoves;
    char name[20];
    printf("\nWelcome To Battle Field of Tic Tac Toe Saga :\n");
    printf("Enter Your Name : ");
    scanf("%s",name);
    getchar();
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
    char** board = setupboard(&size,&maxmoves);
    if (board == NULL) return;
    int moveCount = 0;
    char winner = '.';
    char symbol;
    while(maxmoves > moveCount && winner == '.')
    {
        if(moveCount % 2 == 0 )
        {
            symbol = 'x';
        }
        else
        {
            symbol = 'o';
        }  
        if(symbol == 'x')
        {
            printf("\nTurn - %d Player - %s('%c') :\n",moveCount+1,name,symbol);
            playerturn(board,size,symbol);
        }
        else
        {
            printf("\nAI's Turn (O):\n");
            ai_easy_move(board,size,symbol);
        }
        displayboard(board,size);
        winner = checkwinner(board,size);
        moveCount ++;
    }
    displayboard(board, size);
    if(winner != '.')
    {
        if(symbol == 'x')
        {
            printf(BOLDGREEN "\nPlayer - %s (%c) Wins!\n" RESET, name,winner);
            updatescore(name);
        }
        else{
            printf(BOLDCYAN "\nAI (%c) Wins!\n" RESET,winner);
        }
    }
    else
    {
       printf(BOLDYELLOW "\nIt's a Draw!\n" RESET);
    }
    loghistory(name,"Easy-AI",winner);
    for(int i=0;i<size;i++)
    {
        free(board[i]);
    }
    free(board);
    printf("\n----- Game Over -----\n");
}
void ai_easy_move(char **board, int size, char aiSymbol) 
{
    // Try To Play Winning Move
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(board[i][j] == '.')
            {
                board[i][j] = aiSymbol;
                if(checkwinner(board,size) == aiSymbol)
                {
                    printf("AI played at (%d, %d)\n", i, j);
                    return;
                }
                board[i][j] = '.';
            }
        }
    }
    // random moves
    int row,col;
    do{
        row = rand() % size;
        col = rand() % size;
    }while(board[row][col] != '.');
    board[row][col] = aiSymbol;
    printf("AI played at (%d, %d)\n", row, col);
}
void startp_vs_medai()
{
    int size,maxmoves;
    char name[20];
    printf("\nWelcome To Battle Field of Tic Tac Toe Saga :\n");
    printf("Enter Your Name : ");
    scanf("%s",name);
    getchar();
    #ifdef _WIN32
    system("cls");
    #else
        system("clear");
    #endif
    char** board = setupboard(&size,&maxmoves);
    if (board == NULL) return;
    int moveCount = 0;
    char winner = '.';
    char symbol;
    while(maxmoves > moveCount && winner == '.')
    {
        if(moveCount % 2 == 0 )
        {
            symbol = 'x';
        }
        else
        {
            symbol = 'o';
        }  
        if(symbol == 'x')
        {
            printf("\nTurn - %d Player - %s('%c') :\n",moveCount+1,name,symbol);
            playerturn(board,size,symbol);
        }
        else
        {
            printf("\nAI's Turn (O):\n");
            ai_medium_move(board,size,symbol);
        }
        displayboard(board,size);
        winner = checkwinner(board,size);
        moveCount ++;
    }
    displayboard(board, size);
    if(winner != '.')
    {
        if(symbol == 'x')
        {
            printf(BOLDGREEN "\nPlayer - %s (%c) Wins!\n" RESET, name,winner);
            updatescore(name);
        }
        else{
            printf(BOLDCYAN "\nAI (%c) Wins!\n" RESET,winner);
        }
    }
    else
    {
        printf(BOLDYELLOW "\nIt's a Draw!\n" RESET);
    }
    loghistory(name,"Medium-AI",winner);
    for(int i=0;i<size;i++)
    {
        free(board[i]);
    }
    free(board);
    printf("\n----- Game Over -----\n");
}
void ai_medium_move(char **board,int size, char aiSymbol)
{
    char playersymbol;
    if(aiSymbol == 'x')
    {
        playersymbol = 'o';
    }
    else
    {
        playersymbol = 'x';
    }
    // Try To Play Winning Move
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(board[i][j] == '.')
            {
                board[i][j] = aiSymbol;
                if(checkwinner(board,size) == aiSymbol)
                {
                    printf("AI played at (%d, %d)\n", i, j);
                    return;
                }
                board[i][j] = '.';
            }
        }
    }
    // Block Player Move
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(board[i][j] == '.')
            {
                board[i][j] = playersymbol;
                if(checkwinner(board,size) == playersymbol)
                {
                    board[i][j] = aiSymbol;
                    printf("AI played at (%d, %d)\n", i, j);
                    return;
                }
                board[i][j] = '.';
            }
        }
    }
    // Random Move
    int row,col;
    do{
        row = rand() % size;
        col = rand() % size;
    }while(board[row][col] != '.');
    board[row][col] = aiSymbol;
    printf("AI played at (%d, %d)\n", row, col);
}