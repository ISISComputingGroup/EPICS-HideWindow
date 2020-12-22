#include <windows.h>
#include <process.h>
#include <iostream>

//
// usage: RunWithGlobalLock lock_name command arg1 arg2 ...
//
// runs only one instance of command and arguments per lock_name
//

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
      std::cerr << "RunWithGlobalLock: at least 2 arguments required" << std::endl;
      return -1;
  }
  const char* mutex_name = argv[1];    
  HANDLE h = CreateMutex(NULL, TRUE, mutex_name);
  DWORD err = GetLastError();
  if (h == NULL || err == ERROR_ALREADY_EXISTS)
  {
      LPVOID lpMsgBuf;
      FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
      std::cerr << "RunWithGlobalLock: error creating mutex \"" << mutex_name << "\": " << reinterpret_cast<const char*>(lpMsgBuf) << std::endl;
      LocalFree(lpMsgBuf);
      if (h != NULL)
      {
          CloseHandle(h);
      }
      return -1;
  }
  intptr_t ret = _spawnvp(_P_WAIT, argv[2], argv + 2);
  CloseHandle(h);
  return static_cast<int>(ret);
}
