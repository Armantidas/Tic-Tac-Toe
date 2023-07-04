#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "dataFile.h"

#define window 3
#define Timefile "time.log"
#define FILENAME1 "xwins.bin"
#define FILENAME2 "owins.bin"

#define failoerror "Error opening file"
#define tiemsg "Its a tie!"
#define xhighscore "x player won that many times: %d \n"
#define yhighscore "o player won that many times: %d"
#define highscoreask "Do you want to see the highscores?(1 for yes, any other key else for no): "
#define winmsg "Player %c wins!!!!! \n"
#define wrongmove "Wrong move this tile is taken try again! \n"
#define positioninput "Player %c enter your desired position (YX), (A1,A2, t.t, 00 saves the game): "
#define askcontinue "Do you want to continue an old save?(1 for yes, 0 for no): "

int highscores(char currentPlayer, int xwins, int ywins)
{
    int input = 0;
    if(currentPlayer == 'x')
    {
        ++xwins;
    }
    else
    {
        ++ywins;
    }
    FILE* fp1;
    fp1 = fopen(FILENAME1, "w+");
    if(!fp1)
    {
        printf(failoerror);
    }
    FILE* fp2;
    fp2 = fopen(FILENAME2, "w+");
    if(!fp2)
    {
        printf(failoerror);
    }
    fprintf(fp1, "%d", xwins);
    fprintf(fp2, "%d", ywins);
    printf (highscoreask);
    scanf("%d", &input);

    if(input == 1)
    {
        printf(xhighscore, xwins);
        printf(yhighscore, ywins);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}

typedef struct Log
{
    time_t begin;
    time_t end;
} Log;


void* timeFile(int begin, int end)
{
    FILE* fp;
    fp = fopen(Timefile, "a+");
    time_t t;
    time(&t);
    if (!fp)
    {
        perror(failoerror);
        exit(1);
    }
    else
    {
        fprintf(fp,"%s%d s.\n",ctime(&t), (end - begin));
    }
    fclose(fp);
}

void initBoard(char** state)
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            state[i][j] = ' ';
        }
    }
}

void printBoard(char** state)
{
    printf("___________________\n");
    printf("|     |     |     |\n");
    printf("|  %c  |  %c  |  %c  |\n", state[0][0], state[0][1], state[0][2]);
    printf("|_____|_____|_____|\n");
    printf("|     |     |     |\n");
    printf("|  %c  |  %c  |  %c  |\n", state[1][0], state[1][1], state[1][2]);
    printf("|_____|_____|_____|\n");
    printf("|     |     |     |\n");
    printf("|  %c  |  %c  |  %c  |\n", state[2][0], state[2][1], state[2][2]);
    printf("|_____|_____|_____|\n");
}

int winCheck(char** state)
{
    //checkina x ir y eiles ir stulpelius
    for(int i = 0; i < 3; ++i)
    {
        if(state[i][0] == state[i][1] && state[i][1] == state[i][2])
        {
            return state[i][0] != ' ' ? 1 : 0;
        }
        else if(state[0][i] == state[1][i] && state[1][i] == state[2][i])
        {
            return state[0][i] != ' ' ? 1 : 0;
        }
    }
    //Patikrina atveji ar vidurinis x arba o space yra tuscias ir sulygina istrizaines
    if(state[1][1] != ' ')
    {
        if(state[0][0] == state[1][1] && state[1][1] == state[2][2])
        {
            return 1;
        }
        else if(state[2][0] == state[1][1] && state[1][1] == state[0][2])
        {
            return 1;
        }
    }
    //Patikrina ar visi state'ai yra tusti
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(state[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 2;
}

#define FILENAME "savefile.bin"

int main()
{
    char** state = calloc(window * window, sizeof(char*));
    state[0] = calloc(3, sizeof(char));
    state[1] = calloc(3, sizeof(char));
    state[2] = calloc(3, sizeof(char));

    int xwins = 0, ywins = 0;
    Log log;
    log.begin = time(NULL);
    char currentPlayer = 'x';

    FILE* fp1 = fopen(FILENAME1, "a+");
    if(!fp1)
    {
        printf(failoerror);
    }
    FILE* fp2 = fopen(FILENAME2, "a+");
    if(!fp2)
    {
        printf(failoerror);
    }
    fscanf(fp1, "%d", &xwins);
    fscanf(fp2, "%d", &ywins);
    fclose(fp1);
    fclose(fp2);
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp)
    {
        printf(failoerror);
        initBoard(state);
    }
    else
    {
        while(1)
        {
            int save;
            char endline;
            printf (askcontinue);
            if (scanf("%d%c", &save, &endline) == 2 && endline == '\n')
            {
                if (!save || !readState(state, FILENAME))
                {
                    initBoard(state);
                }
                break;
            }
            else
            {
                while(getchar() != '\n')
                    ;
            }
        }
        fclose(fp);
    }
    srand(time(NULL));

    initBoard(state);
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            assert(state[i][j] = ' ');
        }
    }

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            state[i][j] = 'a';
            saveState(state, FILENAME);
        }
    }

    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            state[i][j] = 'b';
            saveState(state, FILENAME);
            readState(state, FILENAME);
        }
    }

    initBoard(state);

    while(1)
    {
        printBoard(state);
        char x, y;
        while(1)
        {
            char endline;
            printf(positioninput,currentPlayer);
            log.end = time(NULL);
            if (scanf("%c%c%c", &x, &y, &endline) == 3 && endline == '\n')
            {
                if (x >= 'A' && x <= 'C' && y >= '1' && y <= '3')
                {
                    break;
                }
                else if (x == '0' && y == '0')
                {
                    saveState(state, FILENAME);
                    return 0;
                }
            }
            else
            {
                while(getchar() != '\n')
                    ;
            }
        }
        if(state[x - 'A'][y - '1'] != ' ')
        {
            printf(wrongmove);
            currentPlayer = currentPlayer == 'x' ? 'o' : 'x';
        }
        else
        {
            state[x - 'A'][y - '1'] = currentPlayer;
        }
        currentPlayer = currentPlayer == 'x' ? 'o' : 'x';
        system("cls");
        int result = 0;
        result = winCheck(state);
        if (result == 1)
        {
            printf (winmsg, currentPlayer = currentPlayer == 'x' ? 'o' : 'x');
            highscores(currentPlayer, xwins, ywins);
            break;
        }
        else if (result == 2)
        {
            printf (tiemsg);
            break;
        }
    }
    log.end = time(NULL);
    free(state);
    atexit(timeFile(log.begin, log.end));
    return 0;
}
