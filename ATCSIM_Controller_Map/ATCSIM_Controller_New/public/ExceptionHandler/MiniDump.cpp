/*
	Author:	Vladimir Sedach.

	Purpose: demo of Call Stack creation by our own means,
	and with MiniDumpWriteDump() function of DbgHelp.dll.
*/

//#include "StdAfx.h"
#include "MiniDump.h"
#include <Shlwapi.h>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <direct.h>
#include <errno.h>
#include <iostream>
using namespace std;

#include "debug_tool.hpp"

#pragma comment(lib,"shlwapi.lib")

HMODULE	hDbgHelp;
MINIDUMP_WRITE_DUMP	MiniDumpWriteDump_;

CREATE_TOOL_HELP32_SNAPSHOT	CreateToolhelp32Snapshot_;
MODULE32_FIRST	Module32First_;
MODULE32_NEST	Module32Next_;

#define	DUMP_SIZE_MAX	8000	//max size of our dump
#define	CALL_TRACE_MAX	((DUMP_SIZE_MAX - 2000) / (MAX_PATH + 40))	//max number of traced calls
#define	NL				"\r\n"	//new line

extern string GetExePath();

//****************************************************************************************
BOOL WINAPI Get_Module_By_Ret_Addr(PBYTE Ret_Addr, PWCHAR Module_Name, PBYTE & Module_Addr)
//****************************************************************************************
// Find module by Ret_Addr (address in the module).
// Return Module_Name (full path) and Module_Addr (start address).
// Return TRUE if found.
{
	MODULEENTRY32	M = {sizeof(M)};
	HANDLE	hSnapshot;

	Module_Name[0] = 0;
	
	if (CreateToolhelp32Snapshot_)
	{
		hSnapshot = CreateToolhelp32Snapshot_(TH32CS_SNAPMODULE, 0);
		
		if ((hSnapshot != INVALID_HANDLE_VALUE) &&
			Module32First_(hSnapshot, &M))
		{
			do
			{
				if (DWORD(Ret_Addr - M.modBaseAddr) < M.modBaseSize)
				{
					lstrcpyn(Module_Name, M.szExePath, MAX_PATH);
					Module_Addr = M.modBaseAddr;
					break;
				}
			} while (Module32Next_(hSnapshot, &M));
		}

		CloseHandle(hSnapshot);
	}

	return !!Module_Name[0];
} //Get_Module_By_Ret_Addr

//******************************************************************
int WINAPI Get_Call_Stack(PEXCEPTION_POINTERS pException, PCHAR Str)
//******************************************************************
// Fill Str with call stack info.
// pException can be either GetExceptionInformation() or NULL.
// If pException = NULL - get current call stack.
{
	WCHAR	Module_Name[MAX_PATH];
	PBYTE	Module_Addr = 0;
	PBYTE	Module_Addr_1;
	int		Str_Len;
	
	typedef struct STACK
	{
		STACK *	Ebp;
		PBYTE	Ret_Addr;
		DWORD	Param[0];
	} STACK, * PSTACK;

	STACK	Stack = {0, 0};
	PSTACK	Ebp;

	if (pException)		//fake frame for exception address
	{
		Stack.Ebp = (PSTACK)pException->ContextRecord->Ebp;
		Stack.Ret_Addr = (PBYTE)pException->ExceptionRecord->ExceptionAddress;
		Ebp = &Stack;
	}
	else
	{
		Ebp = (PSTACK)&pException - 1;	//frame addr of Get_Call_Stack()

		// Skip frame of Get_Call_Stack().
		if (!IsBadReadPtr(Ebp, sizeof(PSTACK)))
			Ebp = Ebp->Ebp;		//caller ebp
	}

	Str[0] = 0;
	Str_Len = 0;

	// Trace CALL_TRACE_MAX calls maximum - not to exceed DUMP_SIZE_MAX.
	// Break trace on wrong stack frame.
	for (int Ret_Addr_I = 0;
		(Ret_Addr_I < CALL_TRACE_MAX) && !IsBadReadPtr(Ebp, sizeof(PSTACK)) && !IsBadCodePtr(FARPROC(Ebp->Ret_Addr));
		Ret_Addr_I++, Ebp = Ebp->Ebp)
	{
		// If module with Ebp->Ret_Addr found.
		if (Get_Module_By_Ret_Addr(Ebp->Ret_Addr, Module_Name, Module_Addr_1))
		{
			if (Module_Addr_1 != Module_Addr)	//new module
			{
				// Save module's address and full path.
				Module_Addr = Module_Addr_1;
				Str_Len += sprintf(Str + Str_Len, NL "%08X  %s", Module_Addr, Module_Name);
			}

			// Save call offset.
			Str_Len += sprintf(Str + Str_Len,
				NL "  +%08X", Ebp->Ret_Addr - Module_Addr);

			// Save 5 params of the call. We don't know the real number of params.
			if (pException && !Ret_Addr_I)	//fake frame for exception address
				Str_Len += sprintf(Str + Str_Len, "  Exception Offset");
			else if (!IsBadReadPtr(Ebp, sizeof(PSTACK) + 5 * sizeof(DWORD)))
			{
				Str_Len += sprintf(Str + Str_Len, "  (%X, %X, %X, %X, %X)",
					Ebp->Param[0], Ebp->Param[1], Ebp->Param[2], Ebp->Param[3], Ebp->Param[4]);
			}
		}
		else
			Str_Len += sprintf(Str + Str_Len, NL "%08X", Ebp->Ret_Addr);
	}

	return Str_Len;
} //Get_Call_Stack

//***********************************
int WINAPI Get_Version_Str(PCHAR Str)
//***********************************
// Fill Str with Windows version.
{
	OSVERSIONINFOEX	V = {sizeof(OSVERSIONINFOEX)};	//EX for NT 5.0 and later

	if (!GetVersionEx((POSVERSIONINFO)&V))
	{
		ZeroMemory(&V, sizeof(V));
		V.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx((POSVERSIONINFO)&V);
	}

	if (V.dwPlatformId != VER_PLATFORM_WIN32_NT)
		V.dwBuildNumber = LOWORD(V.dwBuildNumber);	//for 9x HIWORD(dwBuildNumber) = 0x04xx

	return sprintf(Str,
		NL "Windows:  %d.%d.%d, SP %d.%d, Product Type %d",	//SP - service pack, Product Type - VER_NT_WORKSTATION,...
		V.dwMajorVersion, V.dwMinorVersion, V.dwBuildNumber, V.wServicePackMajor, V.wServicePackMinor/*, V.wProductType*/);
} //Get_Version_Str

//*************************************************************
PCHAR WINAPI Get_Exception_Info(PEXCEPTION_POINTERS pException)
//*************************************************************
// Allocate Str[DUMP_SIZE_MAX] and return Str with dump, if !pException - just return call stack in Str.
{
	PCHAR		Str;
	int			Str_Len;
	int			i;
	WCHAR		Module_Name[MAX_PATH];
	PBYTE		Module_Addr;
	HANDLE		hFile;
	FILETIME	Last_Write_Time;
	FILETIME	Local_File_Time;
	SYSTEMTIME	T;
	
	Str = new CHAR[DUMP_SIZE_MAX];

	if (!Str)
		return NULL;

	Str_Len = 0;
	Str_Len += Get_Version_Str(Str + Str_Len);

	Str_Len += sprintf(Str + Str_Len, NL "Process:  ");
	GetModuleFileNameA(NULL, Str + Str_Len, MAX_PATH);
	Str_Len = lstrlenA(Str);

	// If exception occurred.
	if (pException)
	{
		EXCEPTION_RECORD &	E = *pException->ExceptionRecord;
		CONTEXT &			C = *pException->ContextRecord;

		// If module with E.ExceptionAddress found - save its path and date.
		if (Get_Module_By_Ret_Addr((PBYTE)E.ExceptionAddress, Module_Name, Module_Addr))
		{
			Str_Len += sprintf(Str + Str_Len,
				NL "Module:  %s", Module_Name);

			if ((hFile = CreateFile(Module_Name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, NULL)) != INVALID_HANDLE_VALUE)
			{
				if (GetFileTime(hFile, NULL, NULL, &Last_Write_Time))
				{
					FileTimeToLocalFileTime(&Last_Write_Time, &Local_File_Time);
					FileTimeToSystemTime(&Local_File_Time, &T);

					Str_Len += sprintf(Str + Str_Len,
						NL "Date Modified:  %02d/%02d/%d",
						T.wMonth, T.wDay, T.wYear);
				}
				CloseHandle(hFile);
			}
		}
		else
		{
			Str_Len += sprintf(Str + Str_Len,
				NL "Exception Addr:  %08X", E.ExceptionAddress);
		}
		
		Str_Len += sprintf(Str + Str_Len,
			NL "Exception Code:  %08X", E.ExceptionCode);
		
		if (E.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
		{
			// Access violation type - Write/Read.
			Str_Len += sprintf(Str + Str_Len,
				NL "%s Address:  %08X",
				(E.ExceptionInformation[0]) ? "Write" : "Read", E.ExceptionInformation[1]);
		}

		// Save instruction that caused exception.
		Str_Len += sprintf(Str + Str_Len, NL "Instruction: ");
		for (i = 0; i < 16; i++)
			Str_Len += sprintf(Str + Str_Len, " %02X", PBYTE(E.ExceptionAddress)[i]);

		// Save registers at exception.
		Str_Len += sprintf(Str + Str_Len, NL "Registers:");
		Str_Len += sprintf(Str + Str_Len, NL "EAX: %08X  EBX: %08X  ECX: %08X  EDX: %08X", C.Eax, C.Ebx, C.Ecx, C.Edx);
		Str_Len += sprintf(Str + Str_Len, NL "ESI: %08X  EDI: %08X  ESP: %08X  EBP: %08X", C.Esi, C.Edi, C.Esp, C.Ebp);
		Str_Len += sprintf(Str + Str_Len, NL "EIP: %08X  EFlags: %08X", C.Eip, C.EFlags);
	} //if (pException)
	
	// Save call stack info.
	Str_Len += sprintf(Str + Str_Len, NL "Call Stack:");
	Get_Call_Stack(pException, Str + Str_Len);

	if (Str[0] == NL[0])
		lstrcpyA(Str, Str + sizeof(NL) - 1);

	return Str;
} //Get_Exception_Info

//*************************************************************************************
void WINAPI Create_Dump(PEXCEPTION_POINTERS pException, BOOL File_Flag, BOOL Show_Flag)
//*************************************************************************************
// Create dump. 
// pException can be either GetExceptionInformation() or NULL.
// If File_Flag = TRUE - write dump files (.dmz and .dmp) with the name of the current process.
// If Show_Flag = TRUE - show message with Get_Exception_Info() dump.
{
	HANDLE	hDump_File;
	PCHAR	Str;
	DWORD	Bytes;
	DWORD	nLen = 0;

	string strDir,strTXTFile,strDMPFile;//文件夹路径，txt文件路径，dump文件路径
	string strDirName = "Log_ExceptionInfo";//文件夹名
	char szFileName[MAX_PATH] = {0x00};//文件全路径
	char strFileNameWithNoExp[512] = {0x00};//exe文件名称（无扩展名）

	::GetModuleFileNameA(NULL, szFileName, MAX_PATH);
	GetAppName(szFileName, strFileNameWithNoExp);

	time_t now;
	struct tm * fmt;
	time(&now);
	fmt = localtime(&now);

	stringstream ss;
	strDir = GetExePath()+"\\"+strDirName+"\\"+string(strFileNameWithNoExp);
	ss << strDir << "\\";
	ss << setw(4) << setfill('0') << fmt->tm_year+1900 << "-";
	ss << setw(2) << setfill('0') << fmt->tm_mon+1 << "-";
	ss << setw(2) << setfill('0') << fmt->tm_mday << " ";
	ss << setw(2) << setfill('0') << fmt->tm_hour;
	ss << setw(2) << setfill('0') << fmt->tm_min;
	ss << setw(2) << setfill('0') << fmt->tm_sec;

	strTXTFile = ss.str() + ".txt";//txt文件名格式举例：2013-06-15 145106.txt
	strDMPFile = ss.str() + ".dmp";//dump文件名格式举例：2013-06-15 145106.dump

	//创建文件夹 begin
	CreateFolder(GetExePath()+"\\"+strDirName);//创建Log_ExceptionInfo文件夹
	CreateFolder(strDir);//创建Log_ExceptionInfo/exename文件夹
	//创建文件夹 end

	Str = Get_Exception_Info(pException);

	//if (Show_Flag && Str)
	//	MessageBox(NULL, Str, "MiniDump", MB_ICONHAND | MB_OK);

	if (File_Flag)
	{
		if (Str)
		{
			hDump_File = CreateFileA(strTXTFile.c_str(),
				GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			
			nLen = lstrlenA(Str);
			Str[nLen] = '\0';

			WriteFile(hDump_File, Str, lstrlenA(Str) + 1, &Bytes, NULL);

			//输出异常文件、行信息到txt文件
			dbsoft::callstack::callstack_ptr pCall = dbsoft::callstack::generate( pException->ContextRecord );

			cout<<" Error:: " << GetLastErrorDescA( pException->ExceptionRecord->ExceptionCode&0x0fffffff ) << endl;

			if( pCall )
			{
				for( dbsoft::callstack::const_iterator it = pCall->begin();
					it != pCall->end();
					++it )
				{
					//cout<< *it << endl;
					string strTemp = "\r\n" + *it + "\r\n";
					WriteFile(hDump_File, strTemp.c_str(), lstrlenA(strTemp.c_str()) + 1, &Bytes, NULL);
				}
			}

			CloseHandle(hDump_File);
		}

		// If MiniDumpWriteDump() of DbgHelp.dll available.
		if (MiniDumpWriteDump_)
		{
			MINIDUMP_EXCEPTION_INFORMATION	M;

			M.ThreadId = GetCurrentThreadId();
			M.ExceptionPointers = pException;
			M.ClientPointers = 0;

			hDump_File = CreateFileA(strDMPFile.c_str(),
				GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

			MiniDumpWriteDump_(GetCurrentProcess(), GetCurrentProcessId(), hDump_File,
				MiniDumpNormal, (pException) ? &M : NULL, NULL, NULL);

			CloseHandle(hDump_File);
		}
	} //if (File_Flag)

	delete Str;
} //Create_Dump


/*
*	获取EXE所在目录
*/
string GetExePath()
{
	char pathbuf[MAX_PATH];
	int  pathlen = ::GetCurrentDirectoryA(MAX_PATH ,pathbuf);
	
	string path = string(pathbuf);
	return path;
}

/*
*	异常处理模块
*/
LONG WINAPI CrashReportEx(LPEXCEPTION_POINTERS ExceptionInfo)
{
	char	szFileName[MAX_PATH] = {0x00};
	UINT	nRet = 0;

	// 重启程序
	//::GetModuleFileNameA(NULL, szFileName, MAX_PATH);
	//nRet = WinExec(szFileName, SW_SHOW);

	// 创建DUMP文件
	Create_Dump(ExceptionInfo,1,1);
	return EXCEPTION_EXECUTE_HANDLER;
}

/*
*	初始化异常处理
*/
void InitException()
{
	SetUnhandledExceptionFilter(CrashReportEx);
	HMODULE	hKernel32;

	// Try to get MiniDumpWriteDump() address.
	hDbgHelp = LoadLibraryA("DBGHELP.DLL");
	MiniDumpWriteDump_ = (MINIDUMP_WRITE_DUMP)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
	//	d("hDbgHelp=%X, MiniDumpWriteDump_=%X", hDbgHelp, MiniDumpWriteDump_);

	// Try to get Tool Help library functions.
	hKernel32 = GetModuleHandleA("KERNEL32");
	CreateToolhelp32Snapshot_ = (CREATE_TOOL_HELP32_SNAPSHOT)GetProcAddress(hKernel32, "CreateToolhelp32Snapshot");
	Module32First_ = (MODULE32_FIRST)GetProcAddress(hKernel32, "Module32First");
	Module32Next_ = (MODULE32_NEST)GetProcAddress(hKernel32, "Module32Next");
}

/* 根据全路径获取程序名
*	作者：lijin 日期：2013-05-21
*/
void GetAppName(const char * strFullAppPath, char * app_name)
{
	char full_path[512] = {0};
	char temp_name[512] = {0};

	//将路径中的“/”替换为“\”
	const char * p = strFullAppPath;
	int n = 0;
	while (*p)
	{
		full_path[n] = (*p == '/' ? '\\' : *p);
		p++;
		n++;
	}
	printf("full_path : %s\n", full_path);

	char * name = _strrev(full_path);//翻转
	if (name != NULL)
	{
		//从路径中取得程序名称（去掉最后一个“\”之前的字串及“.exe”）
		char * find1 = "exe.";
		char * find2 = "\\";
		int length_name	 = strlen(name);
		int length_find1 = strlen(find1);

		int p1 = 0;
		bool bEqual = true;
		if (length_name >= length_find1)
		{
			int i = 0;
			for (i=0; i<length_find1; ++i)
			{
				if (name[i] != find1[i])
				{
					bEqual = false;//前几个字母与find1不等
				}
			}

			if (bEqual)//判断倒序前4个字符是否为“exe.”
			{
				p1 = strlen(find1);
			}
		}

		int start = p1;//名称起始位置（倒序）

		int p2 = strcspn(name, find2);
		int end = (p2!=length_name ? p2-strlen(find2) : strlen(name)-1);//名称终止位置（倒序）

		printf("p1=%d p2=%d\n", p1, p2);
		int i = 0;
		for (; i<end-start+1; ++i)
		{
			temp_name[i] = name[i+start];
		}
		printf("temp_name : %s\n", temp_name);
		name = _strrev(temp_name);//翻转
		printf("name : %s\n", name);
		memcpy(app_name, name, strlen(name));
	}
}

/*
*   创建文件夹
*/
bool CreateFolder(const string& strPath)
{
	const char * strDirPath = strPath.c_str();
	int ret = _mkdir(strDirPath);
	if (0 == ret)
	{
		printf("directory:\"%s\" was created succeed\n", strDirPath);
		return true;
	} 
	else
	{
		switch (errno)
		{
		case EEXIST:
			printf("directory:\"%s\" exist\n", strDirPath);
			break;
		case ENOENT:
			printf("directory:\"%s\" was not found\n", strDirPath);
			break;
		default:
			break;
		}
		return false;
	}
}