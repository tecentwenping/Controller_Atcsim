/**
 * @brief   调试工具
 * @author  
 * @date    2013/06/17
 * @remarks	程序出现异常时，生成dump文件。
			与debug_tool结合后，可将堆栈信息输出到txt文件。
			（1）在#include "windows.h"前增加#define WIN32_LEAN_AND_MEAN，
			以解决在与boost asio混用时“WinSock.h has already been included”的错误
			注：WIN32_LEAN_AND_MEAN表示不包含一些极少使用和偏门的资料
**/

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tlhelp32.h>
#include <imagehlp.h>

#include <fstream>
using namespace std;

//#include "dbghelp.h"
//#define DEBUG_DPRINTF		1	//allow d()
//#include "wfun.h"

#pragma optimize("y", off)		//generate stack frame pointers for all functions - same as /Oy- in the project
#pragma warning(disable: 4200)	//nonstandard extension used : zero-sized array in struct/union
#pragma warning(disable: 4100)	//unreferenced formal parameter
#pragma comment(lib, "imagehlp.lib")

/*BOOL WINAPI Get_Module_By_Ret_Addr(PBYTE Ret_Addr, PCHAR Module_Name, PBYTE & Module_Addr);
int	 WINAPI Get_Call_Stack(PEXCEPTION_POINTERS pException, PCHAR Str);
int  WINAPI Get_Version_Str(PCHAR Str);
PCHAR WINAPI Get_Exception_Info(PEXCEPTION_POINTERS pException);
void WINAPI Create_Dump(PEXCEPTION_POINTERS pException, BOOL File_Flag, BOOL Show_Flag);*/

// In case you don't have dbghelp.h.
#ifndef _DBGHELP_

//typedef struct _MINIDUMP_EXCEPTION_INFORMATION {
//	DWORD	ThreadId;
//	PEXCEPTION_POINTERS	ExceptionPointers;
//	BOOL	ClientPointers;
//} MINIDUMP_EXCEPTION_INFORMATION, *PMINIDUMP_EXCEPTION_INFORMATION;
//
//typedef enum _MINIDUMP_TYPE {
//	MiniDumpNormal =			0x00000000,
//		MiniDumpWithDataSegs =		0x00000001,
//} MINIDUMP_TYPE;

typedef	BOOL (WINAPI * MINIDUMP_WRITE_DUMP)(
											IN HANDLE			hProcess,
											IN DWORD			ProcessId,
											IN HANDLE			hFile,
											IN MINIDUMP_TYPE	DumpType,
											IN CONST PMINIDUMP_EXCEPTION_INFORMATION	ExceptionParam, OPTIONAL
											IN PVOID									UserStreamParam, OPTIONAL
											IN PVOID									CallbackParam OPTIONAL
											);

#else

typedef	BOOL (WINAPI * MINIDUMP_WRITE_DUMP)(
											IN HANDLE			hProcess,
											IN DWORD			ProcessId,
											IN HANDLE			hFile,
											IN MINIDUMP_TYPE	DumpType,
											IN CONST PMINIDUMP_EXCEPTION_INFORMATION	ExceptionParam, OPTIONAL
											IN PMINIDUMP_USER_STREAM_INFORMATION		UserStreamParam, OPTIONAL
											IN PMINIDUMP_CALLBACK_INFORMATION			CallbackParam OPTIONAL
											);
#endif //#ifndef _DBGHELP_

// Tool Help functions.
typedef	HANDLE (WINAPI * CREATE_TOOL_HELP32_SNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID);
typedef	BOOL (WINAPI * MODULE32_FIRST)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef	BOOL (WINAPI * MODULE32_NEST)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);


extern void WINAPI Create_Dump(PEXCEPTION_POINTERS pException, BOOL File_Flag, BOOL Show_Flag);

extern HMODULE	hDbgHelp;
extern MINIDUMP_WRITE_DUMP	MiniDumpWriteDump_;

extern CREATE_TOOL_HELP32_SNAPSHOT	CreateToolhelp32Snapshot_;
extern MODULE32_FIRST	Module32First_;
extern MODULE32_NEST	Module32Next_;

/*
*	获取EXE所在目录
*/
extern string GetExePath();

/*
*	异常处理模块
*/
extern LONG WINAPI CrashReportEx(LPEXCEPTION_POINTERS ExceptionInfo);

/*
*	初始化异常处理
*/
extern void InitException();

/*
*	根据全路径获取程序名
*/
void GetAppName(const char * strFullAppPath, char * app_name);

/*
*   创建文件夹
*/
bool CreateFolder(const string& strPath);

/*
*	初始化异常处理宏
*/
#define INIT_EXCEPTION \
	InitException()

inline std::string  GetLastErrorDescA( unsigned uErrorCode = ::GetLastError() )
{
	LPVOID lpMsg = NULL;
	::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, uErrorCode, MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
		(LPSTR)&lpMsg,
		0,
		NULL
		);

	if( lpMsg == NULL )
	{
		return "msg is null";
	}

	std::string strReason = (const char*)lpMsg;

	::LocalFree( lpMsg );

	return strReason;
}