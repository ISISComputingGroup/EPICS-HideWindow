#include <windows.h>
#include <stdio.h>

// usage: hidewindow [m|M|h|H] [title]
int main(int argc, char* argv[])
{
	HWND conwin = GetConsoleWindow();
	if ( (conwin != NULL) && (argc >= 2) )
	{
		    switch(argv[1][0])
			{
				case 'M': // minimise
				case 'm': 
			        ShowWindowAsync(conwin, SW_MINIMIZE);
					break;

				case 'H': // hide
				case 'h':
					ShowWindowAsync(conwin, SW_HIDE);
					break;

				default:
					printf("%s: Invalid argument \"%s\"\n", argv[0], argv[1]);
					break;
			}
	}
#if 0
	// set console window title
	if (argc >= 3)
	{
	    SetConsoleTitle(argv[2]);
		HWND parent = GetParent(conwin);
		SetWindowText(parent, argv[2]);
		HWND anc = GetAncestor(conwin, GA_PARENT);
		SetWindowText(anc, argv[2]);
		SendMessage(parent, WM_SETTEXT, 0, (LPARAM)argv[2]);
		SendMessage(conwin, WM_SETTEXT, 0, (LPARAM)argv[2]);
	}
#endif
	return 0;
}
