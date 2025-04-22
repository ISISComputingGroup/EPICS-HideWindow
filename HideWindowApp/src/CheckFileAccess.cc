// usage: CheckFileAccess fileName access shareMode
//
// wait for the desired access to a file to be available
// useful to use in a batch script before e.g. a robocopy move
// so you can be sure file is able to be moved as in some cases we have
// not been able to delete file afterwards. To avoid this specific case use
//
//     CheckFileAccess "filename" "R" ""
//
// which requests exclusive access (as no share mode specified), "R" or "RW"
// does not matter here, we just want to be sure no other process is accessing
// 
#include <windows.h>
#include <cstdio>
#include <string>

static int checkAccess(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode)
{
    HANDLE fh = CreateFile(lpFileName, dwDesiredAccess, dwShareMode, NULL,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (fh != INVALID_HANDLE_VALUE) {
        CloseHandle(fh);
        return 0;
    }
    DWORD last_error = GetLastError();
    LPVOID lpMsgBuf;
    if (FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        last_error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL) == 0) {
            printf("CheckFileAccess: \"%s\" failed with error code 0x%x\n", lpFileName, last_error);
    } else {
        printf("CheckFileAccess: \"%s\" failed with error \"%s\"\n", lpFileName, (LPCTSTR)lpMsgBuf);
        LocalFree(lpMsgBuf);
    }
    return last_error;
}

int main(int argc, char* argv[])
{
    if (argc < 4) {
        printf("usage: CheckFileAccess fileName access shareMode\n");
        printf("access     can be \"\" (only file metadata access requested), \"R\", \"W\" or \"RW\"\n");
        printf("shareMode  can be \"\" (exclusive access, no sharing) or mix of R, W and D\n");
        printf("           e.g. \"RW\" for shared read and write\n");
        return -1;
    }
    if (argv[1] == NULL || *(argv[1]) == '\0') {
        printf("CheckFileAccess: no filename given\n");
        return -1;
    }
    LPCSTR lpFileName = argv[1];
    DWORD dwDesiredAccess = 0;
    if (argv[2] != NULL) {
        std::string am = argv[2];
        if (am.find("R") != std::string::npos) {
            dwDesiredAccess |= GENERIC_READ;
        }
        if (am.find("W") != std::string::npos) {
            dwDesiredAccess |= GENERIC_WRITE;
        }
    }
    DWORD dwShareMode = 0;
    if (argv[3] != NULL) {
        std::string sm = argv[3];
        if (sm.find("R") != std::string::npos) {
            dwDesiredAccess |= FILE_SHARE_READ;
        }
        if (sm.find("W") != std::string::npos) {
            dwDesiredAccess |= FILE_SHARE_WRITE;
        }
        if (sm.find("D") != std::string::npos) {
            dwDesiredAccess |= FILE_SHARE_DELETE;
        }
    }
    int ret, retry_delay = 30;
    while( (ret = checkAccess(lpFileName, dwDesiredAccess, dwShareMode)) != 0 ) {
        printf("Retrying in %d seconds...\n", retry_delay);
        Sleep(retry_delay * 1000);
    }
    return ret;
}
