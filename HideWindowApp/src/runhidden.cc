#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// usage: runhidden program command_line
static int mymain(int argc, char* argv[])
{
    std::string cmdLine;
    for (int i=1; i<argc; ++i)
    {
        if (strchr(argv[i], ' ') != NULL)
        {
            cmdLine += "\"";
            cmdLine += argv[i];
            cmdLine += "\"";
        }
        else
        {
            cmdLine += argv[i];
        }
        if (i < (argc - 1)) {
            cmdLine += " ";
        }
    }
//    MessageBox(NULL, cmdLine.c_str(), "runhidden", MB_OK);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    memset(&pi, 0, sizeof(pi));
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    DWORD proc_create_flags = CREATE_NEW_CONSOLE;
    if (CreateProcess(NULL, strdup(cmdLine.c_str()), NULL, NULL, FALSE,
                      proc_create_flags, NULL, NULL, &si, &pi) == 0)
    {
//        MessageBox(NULL, "create error", "runhidden", MB_OK);
        return 1; /* error */
    }
    DWORD ret = WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD exit_code = 1;
    if (ret == WAIT_OBJECT_0) {
//        MessageBox(NULL, "wait over", "runhidden", MB_OK);
        GetExitCodeProcess(pi.hProcess, &exit_code);
    }
    CloseHandle(pi.hProcess);
//    MessageBox(NULL, "exit", "runhidden", MB_OK);
    return exit_code;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    return mymain(__argc, __argv);
}
