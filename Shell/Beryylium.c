#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cols, rows;
// from here to the las endif, it is for getting the terminal size.
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

void get_terminal_size(int *rows, int *cols) {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
#else
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        *rows = w.ws_row;
        *cols = w.ws_col;
    }
#endif
}

// string to hold the command.
char command[4196];

// string to hold the execve command.
char comexecve[4196];

int main()
{
    // gets the terminal size.
    get_terminal_size(&rows, &cols);

    // ANSI escapement for clearing the screen.
    printf("\033[H\033[J");

    // to find how many stars to print.
    cols = (cols - 20) / 2;

    // color escapements.
    printf("\033[0;42m");
    printf("\033[1;36m");

    // printing stars and the terminal name of this shell.
    for (int i = 0; i < cols; i++){
        printf("*");
    }
    printf(" Beryylium Shell B1 ");
    for (int i = 0; i < cols; i++){
        printf("*");
    }
    printf("\n");

    // infinite loop for getting commands, else you exit.
    while (1){
        printf("\033[1;40m\033[1;33mBeryylium:\\>\033[0;37m\033[1;40m ");

        // getting user input.
        fgets(command, 4196, stdin);

        // exitting
        if(command[0] == 'X' && command[1] == 'E'){
            printf("\033[H\033[J");
            return 0;
        }else if(command[0] == 'c' && command[1] == 'l'&& command[2] == 'r'){ // clearing.
            printf("\033[H\033[J");
            printf("\033[0;42m");
            printf("\033[1;36m");
            for (int i = 0; i < cols - 1; i++){
                printf("*");
            }
            printf(" Beryylium Shell B1 ");
            for (int i = 0; i < cols - 1; i++){
                printf("*");
            }
            printf("\n");
        }else if(command[0] == 'h' && command[1] == 'e' && command[2] == 'l' && command[3] == 'p'){ // for help screen.
            printf("\033[1;32mCOMMANDS:\n     help : Shows this message.\n     clr : clears the screen.\n     XE : exits the shell.\n     execve : runs a system command by stdlib.h's 'system()' command.\n");
        }else if(command[0] == 'e' && command[1] == 'x' && command[2] == 'e' && command[3] == 'c' && command[4] == 'v' && command[5] == 'e' && command[6] == ' '){ //to run a system command by 'execve()'
            for(int i = 7; i < 4185; i++){
                comexecve[i - 7] = command[i];
            }
                system(comexecve);
        }else{ // to show using unknown commands.
            printf("\033[1;31m'%s' is not recognized as a command.\n", command);
        }
    }
    return 0;
}


