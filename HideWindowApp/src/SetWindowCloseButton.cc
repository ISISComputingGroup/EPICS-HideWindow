#include <windows.h>
#include <stdio.h>

// usage: SetWindowCloseButton [enable|disable]
int main(int argc, char* argv[])
{
	HWND conwin = GetConsoleWindow();
	if ( (conwin != NULL) && (argc >= 2) )
	{
		    switch(argv[1][0])
			{
				case 'E': // enable
				case 'e': 
			        EnableMenuItem(GetSystemMenu(conwin, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
					break;

				case 'D': // disable
				case 'd':
					EnableMenuItem(GetSystemMenu(conwin, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
					break;

				default:
					printf("%s: Invalid argument \"%s\"\n", argv[0], argv[1]);
					break;
			}
	}
	return 0;
}
