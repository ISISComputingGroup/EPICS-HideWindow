#include <windows.h>
#include <stdio.h>

// usage: setquickedit [0nN|1yY]
int main(int argc, char* argv[])
{
    DWORD mode;
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    if ( (hStdin != NULL) && (argc >= 2) )
    {
        if (GetConsoleMode(hStdin, &mode) != 0)
        {
            switch(argv[1][0])
            {
                case '0':
                case 'n':
                case 'N':
                    mode &= ~ENABLE_QUICK_EDIT_MODE;
                    mode |= ENABLE_EXTENDED_FLAGS;
                    break;
                
                case '1':
                case 'y':
                case 'Y':
                    mode |= (ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);
                    break;

                default:
                    fprintf(stderr, "Invalid arg: %s\n", argv[1]);
                    break;
            }
            SetConsoleMode(hStdin, mode);
        }
        else
        {
            fprintf(stderr, "error: %d\n", GetLastError());
        }
    }
    return 0;
}
