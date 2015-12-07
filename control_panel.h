/*
Copyright David Poulsen

Email: Dpoulsen@e-box.dk
ICQ: 150873892
*/
#include <winioctl.h>					// Windows NT IOCTL codes
//#include <vwin32.h>					// Windows 95 IOCTL codes

/* 
	The <vwin32.h> header file is part of the Windows 95 DDK.
	If you don't have the Windows 95 DDK, then use the definitions below.
*/ 
#include <windows.h>
#include <commctrl.h>
#include "resource.h"



LRESULT CALLBACK ControlWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK MainTimeProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK WndFindProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK aboutproc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
void MakeDriveList(HWND hwndCombo);
BOOL DriveListMeasure(HWND hwnd, UINT uCtrlId, MEASUREITEMSTRUCT *mis);
BOOL DriveListDraw(HWND hwnd, UINT uCtrlId, DRAWITEMSTRUCT *dis);
DWORD GetDriveFormFactor(int iDrive);
LRESULT CALLBACK WndNotePad(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);
BOOL DriveList_GetDrive(HWND hwnd, TCHAR szDrive[]);
void AddFile(HWND hwndList,char *pFile);
void LockStation(); 
void Error(char *msg);
void SearchDirectory(HWND hwnd,char *ach,char *mask);
int ListBox_GetLineHeight(HWND hwndListBox,HFONT hFont,int nBitmapHeight);
#ifndef VWIN32_DIOC_DOS_IOCTL
#define VWIN32_DIOC_DOS_IOCTL 1

typedef struct _DIOC_REGISTERS 
{
	DWORD reg_EBX;
	DWORD reg_EDX;
	DWORD reg_ECX;
	DWORD reg_EAX;
	DWORD reg_EDI;
	DWORD reg_ESI;
	DWORD reg_Flags;
}DIOC_REGISTERS, *PDIOC_REGISTERS;

#endif

// Intel x86 processor status fla
#define CARRY_FLAG  0x1

#pragma pack(1)
typedef struct _DOSDPB 
{
	BYTE	specialFunc;	// 
	BYTE	devType;		// 
	WORD	devAttr;		// 
	WORD	cCyl;			// number of cylinders
	BYTE	mediaType;		// 
	WORD	cbSec;			// Bytes per sector
	BYTE	secPerClus;		// Sectors per cluster
	WORD	cSecRes;		// Reserved sectors
	BYTE	cFAT;			// FATs
	WORD	cDir;			// Root Directory Entries
	WORD	cSec;			// Total number of sectors in image
	BYTE	bMedia;			// Media descriptor
	WORD	secPerFAT;		// Sectors per FAT
	WORD	secPerTrack;	// Sectors per track
	WORD	cHead;			// Heads
	DWORD	cSecHidden;		// Hidden sectors
	DWORD	cTotalSectors;	// Total sectors, if cbSec is zero
	BYTE	reserved[6];	// 
} DOSDPB, *PDOSDPB;
#pragma pack()

