#ifndef _OSIF_USER_H_
#define _OSIF_USER_H_

/*
** Copyright 2002-2006 KVASER AB, Sweden.  All rights reserved.
*/

//#################################################
#if LINUX
    typedef int OS_IF_FILE_HANDLE;

#   define OS_IF_INVALID_HANDLE -1

#   define OS_IF_SET_NOTIFY_PARAM  void (*callback) (canNotifyData *)

#   define OS_IF_IS_CLOSE_ERROR(x) (1 == x)
#   define OS_IF_CLOSE_HANDLE close
#   define OS_IF_FREE_MEM free

#   define OS_IF_EXIT_THREAD(x) pthread_exit(NULL)




//#################################################    
#else //WIN32

#   include "windows.h"
    
    typedef HANDLE OS_IF_FILE_HANDLE;

    
#   define OS_IF_INVALID_HANDLE INVALID_HANDLE_VALUE

#   define OS_IF_SET_NOTIFY_PARAM  HWND hwnd

#   define OS_IF_IS_CLOSE_ERROR(x) (0 == x)
#   define OS_IF_CLOSE_HANDLE CloseHandle
#   define OS_IF_FREE_MEM LocalFree

#   define OS_IF_EXIT_THREAD(x) ExitThread(x)
#   define errno GetLastError()

#   define snprintf _snprintf



#endif
//#################################################

    
#endif //_OSIF_USER_H_
