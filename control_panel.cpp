#define _WIN32_WINNT 0x501
#include <windows.h>
#include <stdlib.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <tchar.h>
#include "control_panel.h"
#include <stdio.h>
#include <windowsx.h>

#define ID_USER 1000
#define ID_DATE 1001
#define ID_GAME 1002
#define ID_INTERNATIONAL 1003
#define ID_INTERNET 1004
#define ID_MULTI 1005
#define ID_MOUSE 1006
#define ID_NETWORK 1007
#define ID_PRINTER 1008
#define ID_SCREEN 1009
#define ID_SYSTEM 1010
#define ID_ADD 1011
#define ID_SEARCH 1012

#define ID_TABEL 1013
#define ID_STATUSBAR 1014
#define ID_TIMER 1015
#define ID_LISTBOX_TWO 1016
#define ID_LIST_BOX_THREE 1017
#define ID_LB_GETITEMDATA 1018
#define ID_RICHEDIT 1019
#define ID_SEARCH_INPUT 2000
#define ID_TOOLBAR 2001
// Verification of OS
#define Win32_95_Major	4
#define Win32_98_Major	4
#define Win32_Me_Major	4
#define Win32_NT351_Major	3
#define Win32_NT4_Major	4
#define Win32_2K_Major	5
#define Win32_XP_Major	5
#define Win32_Net_Major	5
#define Win32_95_Minor	0
#define Win32_98_Minor	10
#define Win32_Me_Minor	90
#define Win32_NT351_Minor	51
#define Win32_NT4_Minor	4
#define Win32_2K_Minor	0
#define Win32_XP_Minor	1
#define Win32_Net_Minor	1

#define Win9x 10000
#define WinNT 20000
#define Win2K 30000
#define WinXP 40000
#ifndef ODS_NOFOCUSRECT
#define ODS_NOFOCUSRECT     0x0200
#endif
static int nBitmapHeight = 16;	//we always use 16-pixel bitmaps
static int nBitmapYOff = 0;		//y-adjustment when text is taller than bitmap
static HIMAGELIST hSysImgList;
HIMAGELIST GetSystemImageList();

HINSTANCE _user32dll;
PROC _user32proc;
int iWidth;
void Search(HWND hwnd,char *ach,char *mask);

BOOL Is_Workstation(int OS)
{
	/*
	dwMinorVersion
	Windows 95 0 
	Windows 98 10 
	Windows Me 90 
	Windows NT 3.51 51 
	Windows NT 4.0 0 
	Windows 2000 0 
	Windows XP 1 
	Windows .NET Server 1 
	dwMajorVersion
	Windows 95 4 
	Windows 98 4 
	Windows Me 4 
	Windows NT 3.51 3 
	Windows NT 4.0 4 
	Windows 2000 5 
	Windows XP 5 
	Windows .NET Server 5 
	*/

	OSVERSIONINFOEX os;
	BOOL workstation = FALSE;
	char lpBuffer[64];
	/*	ZeroMemory(&osex,sizeof(OSVERSIONINFOEX));
	osex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if(!(workstation = GetVersionEx((OSVERSIONINFO *)&osex)))
	{
		osex.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if(!GetVersionEx((OSVERSIONINFO*)&osex))
			return FALSE;
	}*/
	ZeroMemory(&os,sizeof(OSVERSIONINFOEX));
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if(!(workstation = GetVersionEx((OSVERSIONINFO*)&os)))
	{
		os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if(!GetVersionEx((OSVERSIONINFO*)&os))
			return FALSE;
	}
	switch(OS)
	{
		case Win9x:
		if((os.dwMajorVersion == Win32_95_Major) && (os.dwMinorVersion == Win32_95_Minor) || (os.dwMajorVersion == Win32_98_Major)&&(os.dwMinorVersion == Win32_98_Minor)||(os.dwMajorVersion == Win32_Me_Major)&&(os.dwMinorVersion == Win32_Me_Minor))
		{
//			Error("Found Windows 95 or 98");
			workstation = FALSE;
		}
			return OS;
			break;
		case WinNT:
		if((os.dwMajorVersion == Win32_NT351_Major) && (os.dwMinorVersion == Win32_NT351_Minor) || (os.dwMajorVersion == Win32_NT4_Major)&&(os.dwMinorVersion == Win32_NT4_Minor))
		{
//				Error("Found Windows NT 3.51 or Windows NT 4");
				workstation = FALSE;
			}
			return OS;
			break;
		case Win2K:
		if((os.dwMajorVersion == Win32_2K_Major) && (os.dwMinorVersion == Win32_2K_Minor))
		{
			_user32dll = LoadLibrary("user32.dll");
			if(!_user32dll)
			{
				Error("Not found!");
			}

//			Error("Found Windows 2000");
			workstation = TRUE;
		}
			return OS;
			break;
		case WinXP:
		if((os.dwMajorVersion == Win32_XP_Major) && (os.dwMinorVersion == Win32_XP_Minor))
		{
			_user32dll = LoadLibrary("user32");
			if(!_user32dll)
			{
				Error("Not found!");
			}
//			Error("Found Windows XP");
			workstation = TRUE;
		}
			return OS;
			break;
			}
	return workstation;
/*
	ZeroMemory(&osex,sizeof(OSVERSIONINFOEX));
	osex.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if(!(workstation = GetVersionEx((OSVERSIONINFO *)&osex)))
	{
		osex.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if(!GetVersionEx((OSVERSIONINFO*)&osex))
			return FALSE;
	}
	else if((osex.dwMajorVersion == Win32_2K_Major) && (osex.dwMinorVersion == Win32_2K_Minor))
	{
		Error("Found a OS(W2K)");
	}
	else if((osex.dwMajorVersion == Win32_XP_Major) && (osex.dwMinorVersion == Win32_XP_Minor))
	{
		Error("Found a OS (XP)");
	}
	else if((osex.dwMajorVersion == Win32_NT4_Major) && (osex.dwMinorVersion == Win32_NT4_Minor))
	{
		Error("Found a OS (NT4)");
	}
	else
	{
		Error("Found a non-compatible OS");
	}


*/

	
}
static TCHAR sz_appname[] = "Control Panel By David Poulsen";
extern HINSTANCE g_hInst = NULL;
RECT rct;
void ProcessDirectory(HWND hwnd,char *ptr_directory,char *mask)
{
	HANDLE hFile;
	char directory[1024];
	SearchDirectory(hwnd,ptr_directory,mask);
	Search(hwnd,ptr_directory,mask);
	
}
void SearchDirectory(HWND hwnd,char *ach,char *mask)
{
	WIN32_FIND_DATA w32findDirectory;
	HANDLE hDirectory;
	char drive_directory[1024],directory[1024];
	wsprintf(drive_directory,"%s\\*",ach);
	Search(hwnd,ach,mask);
	//BOOL isFinish = FALSE;
	hDirectory = FindFirstFile(drive_directory,&w32findDirectory);

	if(hDirectory == INVALID_HANDLE_VALUE)
	{
		Error("Sorry,\nA error was found.");
//		isFinish = TRUE;
	}
//	while(!isFinish)
//	{
		do
		{
			if(w32findDirectory.cFileName[0] != '.' && (w32findDirectory.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(w32findDirectory.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				wsprintf(directory,"%s\\%s",ach,w32findDirectory.cFileName);
				//SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_INSERTSTRING,-1,(LPARAM)directory/*w32findDirectory.cFileName*/);
				//Error(directory);	
				ProcessDirectory(hwnd,directory,mask/*w32findDirectory.cFileName*/);
			}	
		}
		while(FindNextFile(hDirectory,&w32findDirectory) != 0);
//	}
	FindClose(hDirectory);
	iWidth = ListBox_GetHorizontalExtent(hwnd);
}

void Search(HWND hwnd,char *ach,char *mask)
{
	/*
		WIN32_FIND_DATA w32finddata,w32directory;
	*/
	HANDLE hFind;
	WIN32_FIND_DATA w32finddata;
	char search[1024];
	BOOL isFinish = FALSE;
	char debug[2048];				
	wsprintf(search,"%s\\%s",ach,mask);
	hFind = FindFirstFile(search,&w32finddata);
	//Error(search);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		//MessageBox(hwnd,"Couldn't find any images.","Error",MB_OK | MB_ICONERROR);
		isFinish=TRUE;
	}
	int i = 0;
	
	while(!isFinish)
	{
			char output[2048];
			int iCount = SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_GETCOUNT,0,0);
			wsprintf(output,"%s\\%s",ach,w32finddata.cFileName);
			//	SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_ADDSTRING,(WPARAM)0,(LPARAM)output);
			AddFile(GetDlgItem(hwnd,ID_LIST_BOX_THREE),output);
			if(!FindNextFile(hFind,&w32finddata))
			{
				if(GetLastError() == ERROR_NO_MORE_FILES)
				{
					//MessageBox(hwnd,"Search completed.","Kontrol Panel",MB_OK | MB_ICONWARNING);
					isFinish = TRUE;
				}
				isFinish = TRUE;
			}
			
	}
	FindClose(hFind);
}

void LockStation(void)
{
	if(Is_Workstation(Win2K))
	{
		if(WinExec("rundll32.exe user32.dll,LockWorkStation",SW_SHOW) <= 31)
		{
			Error("Couldn't execute the function");

		}
	}
	else if(Is_Workstation(WinXP))
	{
		if(WinExec("rundll32.exe user32.dll,LockWorkStation",SW_SHOW) <= 31)
		{
			Error("Couldn't exeute the function");
			
		}
	}
	else
	{
		Error("Not Found");
	}
}
void Error(char *msg)
{
	MessageBox(HWND_DESKTOP,(LPSTR) msg,"Error",MB_OK | MB_SYSTEMMODAL | MB_TASKMODAL | MB_ICONERROR);
}
/*	
	
  GetDriveFormFactor returns the drive form factor.

  It returns 350 if the drive is a 3.5" floppy drive.
  It returns 525 if the drive is a 5.25" floppy drive.
  It returns 800 if the drive is a 8" floppy drive.
  It returns   0 on error.
  It returns   1 if the drive is a hard drive.
  It returns   2 if the drive is something else.
  
	iDrive is 1 for drive A:, 2 for drive B:, etc.
	
	Note that iDrive is not range-checked or otherwise validated.
	It is the responsibility of the caller only to pass values for
	iDrive between 1 and 26 (inclusive).
	  
	Although the function, as written, returns only the drive form
	factor, it can easily be extended to return other types of
	drive information.

*/ 

DWORD GetDriveFormFactor(int iDrive)
{
	HANDLE h;
	TCHAR tsz[8];
	DWORD dwRc;
	
	if(GetVersion() >= 0x80000000)		// Windows 95
	{   
		
		/*
			On Windows 95, use the technique described in
			the Knowledge Base article Q125712 and in MSDN under
			"Windows 95 Guide to Programming", "Using Windows 95
			features", "Using VWIN32 to Carry Out MS-DOS Functions".
		*/ 

		h = CreateFileA("\\\\.\\VWIN32", 0, 0, 0, 0, FILE_FLAG_DELETE_ON_CLOSE, 0);
		
		if(h != INVALID_HANDLE_VALUE)
		{
			DWORD          cb;
			DIOC_REGISTERS reg;
			DOSDPB         dpb;
			
			dpb.specialFunc = 0;  // return default type; do not hit disk
			
			reg.reg_EBX   = iDrive;       // BL = drive number (1-based)
			reg.reg_EDX   = (DWORD)&dpb;  // DS:EDX -> DPB
			reg.reg_ECX   = 0x0860;       // CX = Get DPB
			reg.reg_EAX   = 0x440D;       // AX = Ioctl
			reg.reg_Flags = CARRY_FLAG;   // assume failure
			
			// Make sure both DeviceIoControl and Int 21h succeeded.
			if (DeviceIoControl (h, VWIN32_DIOC_DOS_IOCTL, &reg,
				sizeof(reg), &reg, sizeof(reg),	&cb, 0)
				&& !(reg.reg_Flags & CARRY_FLAG))
			{
                switch (dpb.devType)
                {
                case 0: // 5.25 360K floppy
                case 1: // 5.25 1.2MB floppy
					dwRc = 525; break;
					
                case 2: // 3.5  720K floppy
                case 7: // 3.5  1.44MB floppy
                case 9: // 3.5  2.88MB floppy
					dwRc = 350; break;
					
                case 3: // 8" low-density floppy
                case 4: // 8" high-density floppy
					dwRc = 800; break;
					
                case 5: // hard drive
					dwRc = 1; break;
					
                case 6: // tape drive
                case 8: // optical disk
					dwRc = 2; break;
					
                default: // unknown
					dwRc = 0; break;
                }
			}
			else
                dwRc = 0;
			
			
			CloseHandle(h);
		}
		else
			dwRc = 0;
		
	}
	else		// Windows NT
	{  
		
	   /*
			On Windows NT, use the technique described in the Knowledge
			Base article Q115828 and in the "FLOPPY" SDK sample.
		*/ 

		wsprintf(tsz, TEXT("\\\\.\\%c:"), TEXT('a') + iDrive);
		h = CreateFile(tsz, 0, FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		
		if(h != INVALID_HANDLE_VALUE)
		{
            DISK_GEOMETRY Geom[20];
            DWORD cb;
			
            if (DeviceIoControl (h, IOCTL_DISK_GET_MEDIA_TYPES, 0, 0,
				Geom, sizeof(Geom), &cb, 0) 
				&& cb > 0)
            {
				switch (Geom[0].MediaType)
				{
				case F5_1Pt2_512: // 5.25 1.2MB floppy
				case F5_360_512:  // 5.25 360K  floppy
				case F5_320_512:  // 5.25 320K  floppy
				case F5_320_1024: // 5.25 320K  floppy
				case F5_180_512:  // 5.25 180K  floppy
				case F5_160_512:  // 5.25 160K  floppy
					dwRc = 525;
					break;
					
				case F3_1Pt44_512: // 3.5 1.44MB floppy
				case F3_2Pt88_512: // 3.5 2.88MB floppy
				case F3_20Pt8_512: // 3.5 20.8MB floppy
				case F3_720_512:   // 3.5 720K   floppy
					dwRc = 350;
					break;
					
				case RemovableMedia:
					dwRc = 2;
					break;
					
				case FixedMedia:
					dwRc = 1;
					break;
					
				default:
					dwRc = 0;
					break;
				}
            }
            else
				dwRc = 0;
			
            CloseHandle(h);
		}
		else
            dwRc = 0;
	}
	
	/*
	If you are unable to determine the drive type via ioctls,
	then it means one of the following:
	
	  1.  It is hard drive and we do not have administrator privilege
	  2.  It is a network drive
	  3.  The drive letter is invalid
	  
		GetDriveType can distinguish these three cases.
	*/ 
	if (dwRc == 0)
	{
		wsprintf(tsz, TEXT("%c:\\"), TEXT('a') + iDrive);
		
		switch (GetDriveType(tsz))
		{
		case DRIVE_FIXED:
			dwRc = 1;
			break;
		case DRIVE_REMOVABLE:
		case DRIVE_REMOTE:
		case DRIVE_CDROM:
		case DRIVE_RAMDISK:
			dwRc = 2;
			break;
		default:
			dwRc = 0;
		}
	}
	
	return dwRc;
}
   

BOOL CenterWindow(HWND hwndChild, HWND hwndParent)
{
    RECT    rcChild, rcParent;
    int     cxChild, cyChild, cxParent, cyParent;
    int     cxScreen, cyScreen, xNew, yNew;
    HDC     hdc;

    // Get the Height and Width of the child window
    GetWindowRect(hwndChild, &rcChild);
    cxChild = rcChild.right - rcChild.left;
    cyChild = rcChild.bottom - rcChild.top;

    // Get the Height and Width of the parent window
    GetWindowRect(hwndParent, &rcParent);
    cxParent = rcParent.right - rcParent.left;
    cyParent = rcParent.bottom - rcParent.top;

    // Get the display limits
    hdc = GetDC(hwndChild);
    cxScreen = GetDeviceCaps(hdc, HORZRES);
    cyScreen = GetDeviceCaps(hdc, VERTRES);
    ReleaseDC(hwndChild, hdc);

    // Calculate new X position, then adjust for screen
    xNew = rcParent.left + ((cxParent - cxChild) / 2);
    if (xNew < 0)
    {
        xNew = 0;
    }
    else if ((xNew + cxChild) > cxScreen)
    {
        xNew = cxScreen - cxChild;
    }

    // Calculate new Y position, then adjust for screen
    yNew = rcParent.top  + ((cyParent - cyChild) / 2);
    if (yNew < 0)
    {
        yNew = 0;
    }
    else if ((yNew + cyChild) > cyScreen)
    {
        yNew = cyScreen - cyChild;
    }

    // Set it, and return
    return SetWindowPos(hwndChild,
                        NULL,
                        xNew, yNew,
                        0, 0,
                        SWP_NOSIZE | SWP_NOZORDER);
}


BOOL LoadBitmapFromFile(LPTSTR szFileName,HBITMAP *phBitmap,HPALETTE *phPalette)
{
	BITMAP bm;
	*phBitmap = NULL;
	*phPalette = NULL;

	*phBitmap = (HBITMAP) LoadImage(NULL,szFileName,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if(*phBitmap == NULL)
		return FALSE;
	GetObject(*phBitmap,sizeof(BITMAP),&bm);
	if((bm.bmBitsPixel * bm.bmPlanes ) <= 8)
	{
		HDC hdc;
		HBITMAP hbmp;
		RGBQUAD rgb[256];
		LPLOGPALETTE pLogPal;
		WORD i;
		
		hdc = CreateCompatibleDC(NULL);
		hbmp = (HBITMAP) SelectObject(hdc,*phBitmap);
		GetDIBColorTable(hdc,0,256,rgb);
		pLogPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) + (256*sizeof(PALETTEENTRY)) );
		pLogPal->palVersion = 0x300;
		pLogPal->palNumEntries = 256;
		for(i = 0; i < 256; i++)
		{
			pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
			pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
			pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
			pLogPal->palPalEntry[i].peFlags = 0;
		}
		*phPalette = CreatePalette(pLogPal);
		free(pLogPal);
		SelectObject(hdc,hbmp);
		DeleteDC(hdc);
	}
	else
	{
		HDC hdc;
		hdc = GetDC(NULL);
		*phPalette = CreateHalftonePalette(hdc);
	}
	return TRUE;
}


HWND CreateButton(HWND parent,LPSTR szTitle,int id,int x,int y,HINSTANCE hInst)
{

	HWND button;
	button = CreateWindow("BUTTON",szTitle,WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,x,y,120,45,parent,(HMENU) id,hInst,0);
	return button;

}

HWND Create_Center(HWND parent,LPSTR szTitle,int id,int x,int y,HINSTANCE hInst)
{

	HWND button;
	button = CreateWindow("BUTTON",szTitle,WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,x,y,500,90,parent,(HMENU) id,hInst,0);
	return button;

}

BOOL On_Ownerdraw(LPDRAWITEMSTRUCT dis,HINSTANCE hInst,char *szTitle)
{
	HRGN rgn_1;
	HBITMAP hbmp;
	HDC memdc = CreateCompatibleDC(NULL);

				
			if(dis->itemState & ODS_SELECTED)
				DrawEdge(dis->hDC,&dis->rcItem,BDR_SUNKENOUTER,BF_RECT);
			else			
				DrawEdge(dis->hDC,&dis->rcItem,BDR_RAISEDINNER,BF_RECT);

			if(dis->itemAction & ODA_DRAWENTIRE)
			{
				SetBkMode(dis->hDC,TRANSPARENT);
				hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));
				SelectObject(memdc,hbmp);
				rgn_1 = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,100,100);
				SelectObject(dis->hDC,rgn_1);
				rgn_1 = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,150,100);
				SelectObject(dis->hDC,rgn_1);				
				BitBlt(dis->hDC,0,0,200,50,memdc,0,0,SRCCOPY);
				dis->rcItem.top +=7;
				DrawText(dis->hDC,szTitle,-1,&dis->rcItem,DT_CENTER|DT_VCENTER | DT_WORDBREAK);		
				DeleteObject(hbmp);
				DeleteObject(rgn_1);				
			}
			if(dis->itemAction & ODA_SELECT)
			{
				rgn_1 = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,150,100);
				SelectObject(dis->hDC,rgn_1);				
				InvertRect(dis->hDC,&dis->rcItem);
				DeleteObject(rgn_1);
			}
			DeleteObject(hbmp);
			DeleteDC(memdc);

			return TRUE;
}
// Her kommer Custom Draw nr. 2
BOOL On_Ownerdraw2(LPDRAWITEMSTRUCT dis,HINSTANCE hInst,char *szTitle)
{
	HRGN rgn_1;
//	HBITMAP hbmp;
	HDC memdc = CreateCompatibleDC(NULL);
	HFONT font_2_use;
	font_2_use = CreateFont(30,30,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_TT_ONLY_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"SYLFAEN");
	SelectObject(dis->hDC,font_2_use);
	if(!font_2_use)
	{
		MessageBox(0,"Couldn't create the font.","Error",MB_OK | MB_ICONHAND);
		return 0;	
	}

				
			if(dis->itemState & ODS_SELECTED)
				DrawEdge(dis->hDC,&dis->rcItem,BDR_SUNKENOUTER,BF_RECT);
			else			
				DrawEdge(dis->hDC,&dis->rcItem,BDR_RAISEDINNER,BF_RECT);

			if(dis->itemAction & ODA_DRAWENTIRE)
			{
				SetBkMode(dis->hDC,TRANSPARENT);
				//hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP6));
///				SelectObject(memdc,hbmp);
				
				rgn_1 = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,100,100);
				SelectObject(dis->hDC,rgn_1);
				rgn_1 = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,150,100);
				SelectObject(dis->hDC,rgn_1);				
				BitBlt(dis->hDC,0,0,500,175,memdc,0,0,SRCCOPY);
				SetTextColor(dis->hDC,RGB(0,0,0));
				dis->rcItem.top = dis->rcItem.top;
				dis->rcItem.bottom = dis->rcItem.bottom +5;
				dis->rcItem.left +=5;
				DrawText(dis->hDC,szTitle,-1,&dis->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				SetTextColor(dis->hDC,RGB(112,98,255));
				dis->rcItem.top -= 7;
				dis->rcItem.right -=7;
				DrawText(dis->hDC,szTitle,-1,&dis->rcItem,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

//				DeleteObject(hbmp);
				DeleteObject(rgn_1);				
			}
			if(dis->itemAction & ODA_SELECT)
			{
				rgn_1 = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,150,100);
				SelectObject(dis->hDC,rgn_1);				
				InvertRect(dis->hDC,&dis->rcItem);
				DeleteObject(rgn_1);
			}

			return TRUE;
			RemoveFontResource(MAKEINTRESOURCE(IDR_FONT_TYPE2));
			DeleteObject(font_2_use);
			DeleteObject(memdc);
		//	DeleteObject(hbmp);
}
// Her slutter Custom Draw nr. 2
int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASS wc;
	MSG msg;
	HWND hwnd;

	g_hInst = hInst;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hIcon = LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = MainWndProc;
	wc.lpszClassName = sz_appname;
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	if(!RegisterClass(&wc))
	{
		Error("Couldn't register WNDCLASS");
		return 0;
	}
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_INFOBK+1);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hIcon = LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = ControlWndProc;
	wc.lpszClassName = "Control";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_INFOBK+1);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hIcon = LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = MainTimeProc;
	wc.lpszClassName = "Tid";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);	
	
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_INFOBK+1);
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hIcon = LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndFindProc;
	wc.lpszClassName = "WndFindDlg";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_INFOBK+1);
	wc.hCursor = LoadCursor(g_hInst,IDC_ARROW);
	wc.hIcon = LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndNotePad;
	wc.lpszClassName = "WndNotePad";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW|CS_VREDRAW;
	RegisterClass(&wc);
	//QHTM_Initialize(g_hInst );
	LoadLibrary("riched32.dll");
	hwnd = CreateWindowEx(0/*WS_EX_CLIENTEDGE*/,sz_appname,"DAPO Systems",WS_VISIBLE | WS_CAPTION  | WS_SYSMENU | WS_MINIMIZEBOX ,0,0,640,480,0,0,hInst,NULL);
	ShowWindow(hwnd,nShowCmd);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void TestNetwork()
{
/*	char szUsername[80];
	DWORD dwResult, cchBuf = 80;

//	dwResult = WNetGetUser("e:",(LPSTR) szUsername,&cchBuf);

	if(dwResult == NO_ERROR)
	{
		MessageBox(GetDesktopWindow(),(LPSTR) szUsername,"Network",MB_OK);
	}
*/
}

BOOL on_Paint(HWND hwnd,PAINTSTRUCT *ps)
{
	HDC hdc,memdc;
	hdc = BeginPaint(hwnd,ps);
	memdc = CreateCompatibleDC(NULL);
	HBITMAP hbmp;

	hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP1));
/*	if(LoadBitmapFromFile("ProtossC.bmp",&hbmp,&hpal))
	{
		hOldpal = SelectPalette(hdc,hpal,FALSE);
	}
*/
	SelectObject(memdc,hbmp);
	BitBlt(hdc,0,0,640,480,memdc,0,0,SRCCOPY);
	EndPaint(hwnd,ps);
	DeleteObject(hbmp);
	DeleteDC(memdc);
	return TRUE;
}

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HWND control_panel;
	LPDRAWITEMSTRUCT dis;
//	HPALETTE hpal,hOldpal;
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_CREATE:
		AddFontResource(MAKEINTRESOURCE(IDR_FONT_TYPE2));
		CreateStatusWindow(  WS_VISIBLE | WS_CHILD | CCS_BOTTOM,"Kontrol panel af David Poulsen",hwnd, ID_STATUSBAR );
		CenterWindow(hwnd,GetDesktopWindow());
		Create_Center(hwnd,"Kontrol panel",	20002,50,15,g_hInst);
		Create_Center(hwnd,"Uret",			20003,50,115,g_hInst);
		Create_Center(hwnd,"Seeker",		20004,50,215,g_hInst);	
		Create_Center(hwnd,"Notepad",		20005,50,315,g_hInst);
	return 0;
	case WM_COMMAND:
		switch (wParam)
		{
		
		case IDR_LOCKWORKSTATION:
			LockStation();
			break;
		case 20002:
			control_panel = CreateWindow("Control","Kontrol panel",WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU, 0,0,640,480,hwnd,0,g_hInst,NULL);
			break;
		case 20003:
			control_panel = CreateWindowEx(0,"Tid","Uret",WS_POPUP | WS_VISIBLE ,0,0,105,50,hwnd,0,g_hInst,0);
			break;
		case 20004:
			control_panel = CreateWindow("WndFindDlg","Seeker",WS_POPUP|WS_VISIBLE|WS_CAPTION|WS_SYSMENU,0,0,640,480,hwnd,0,g_hInst,0);
			break;
		case 20005:
			control_panel = CreateWindow("WndNotePad","NotePad",WS_POPUP|WS_VISIBLE|WS_CAPTION|WS_SYSMENU,0,0,640,480,hwnd,0,g_hInst,0);
			break;
		case IDM_ABOUT:
			DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,aboutproc);
			break;
		case IDM_EXIT:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
		}
		return 0;
		case WM_CTLCOLORBTN:
		SetBkMode((HDC)wParam,TRANSPARENT);
		return (INT_PTR) GetStockObject(NULL_BRUSH);
		break;
	case WM_PAINT:
		return on_Paint(hwnd,&ps);
	break;
	case WM_DRAWITEM:
		dis = (LPDRAWITEMSTRUCT) lParam;
		switch (LOWORD(wParam))
		{
		case 20002:
			return On_Ownerdraw2(dis,g_hInst,"Kontrol Panel");
			break;
		case 20003:
			return On_Ownerdraw2(dis,g_hInst,"Uret");
			break;
		case 20004:
			return On_Ownerdraw2(dis,g_hInst,"Billedesøger");
			break;
		case 20005:
			return On_Ownerdraw2(dis,g_hInst,"Notepad");
			break;
		}
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}
VOID APIENTRY DisplayContextMenu(HWND hwnd, POINT pt) 
{ 
    HMENU hmenu;            // top-level menu 
    HMENU hmenuTrackPopup;  // shortcut menu 
 
    // Load the menu resource. 
 
    if ((hmenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_MENU1))) == NULL) 
        return; 
 
    // TrackPopupMenu cannot display the menu bar so get 
    // a handle to the first shortcut menu. 
 
    hmenuTrackPopup = GetSubMenu(hmenu, 0); 
 
    // Display the shortcut menu. Track the right mouse 
    // button. 
 
    TrackPopupMenu(hmenuTrackPopup, 
            TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
            pt.x, pt.y, 0, hwnd, NULL); 
 
    // Destroy the menu. 
 
    DestroyMenu(hmenu); 
} 

/*
En lille sidebemærkning
SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, szFileName, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
*/
LRESULT CALLBACK MainTimeProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	SYSTEMTIME st; 
	HDC hdc,memdc;
	PAINTSTRUCT ps;
	char time[255];
	RECT rct;
	HRGN rgn;
	HBITMAP hbmp;
	POINT pt;

	switch (msg)
	{
	case WM_NCCREATE:
		GetWindowRect(hwnd,&rct);
		rgn = CreateRoundRectRgn(rct.left,rct.top,rct.right,rct.bottom,200,200);
//		DrawEdge((HDC)wParam,&rct,BDR_SUNKENOUTER,BF_RECT);
		SetWindowRgn(hwnd,rgn,TRUE);
		DeleteObject(rgn);

		break;
	case WM_CREATE:

		SetTimer(hwnd,ID_TIMER,1000,NULL);
		return 0;
	case WM_TIMER:
		InvalidateRect(hwnd,NULL,TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		GetCursorPos(&pt);
		DisplayContextMenu(hwnd,pt);
		break;
	case WM_COMMAND:
		switch(wParam)
		{
		case IDM_EXIT:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		case IDM_ABOUT:
			DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,aboutproc);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		memdc = CreateCompatibleDC(NULL);
		hbmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));
		SelectObject(memdc,hbmp);
		DrawEdge(hdc,&rct,BDR_RAISEDINNER,BF_RECT);
		BitBlt(hdc,0,0,200,200,memdc,0,0,SRCCOPY);
		GetClientRect(hwnd,&rct);
		SelectObject(hdc,GetStockObject(GRAY_BRUSH));
		GetLocalTime(&st);
		SetBkMode(hdc,TRANSPARENT);
		SetTextColor(hdc,RGB(68,112,118));
		wsprintf(time,"Klokken er nu:\n%d:%d:%d",st.wHour,st.wMinute,st.wSecond);
		rct.top += 15;
		DrawText(hdc,time,-1,&rct,DT_VCENTER | DT_CENTER );
		EndPaint(hwnd,&ps);
		DeleteObject(hbmp);
		DeleteDC(memdc);
		return 0;
	case WM_LBUTTONDOWN:
	//ShellAbout(hwnd,"Hello#Hellow","Hi this is a test",NULL);
		SendMessage(hwnd,WM_NCLBUTTONDOWN,HTCAPTION,0);
		break;
	case WM_CLOSE:
		KillTimer(hwnd,ID_TIMER);
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}

LRESULT CALLBACK ControlWndProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{

	RECT rct;
	HDC memdc;
	PAINTSTRUCT ps;
	HWND statusbar;
	LPDRAWITEMSTRUCT dis;
	switch (msg)
	{
	case WM_CREATE:	
		GetClientRect(hwnd,&rct);
		CenterWindow(hwnd,GetDesktopWindow());
		statusbar = CreateStatusWindow(  WS_VISIBLE | WS_CHILD | CCS_BOTTOM,"Kontrol panel af David Poulsen",hwnd, ID_STATUSBAR );
		CreateButton(hwnd,"Tilføj/Fjern programmer",
			ID_ADD,rct.left+10,rct.top+50,g_hInst);
		CreateButton(hwnd,"Bruger/Adgangskoder",
			ID_USER,rct.left+10,rct.top+100,g_hInst);
		CreateButton(hwnd,"Dato og klokkeslæt",
			ID_DATE,rct.left+10,rct.top+150,g_hInst);
		CreateButton(hwnd,"Gaming Options",
			ID_GAME,rct.left+150,rct.top+50,g_hInst);
		CreateButton(hwnd,"International",
			ID_INTERNATIONAL,rct.left+150,rct.top+100,g_hInst);
		CreateButton(hwnd,"Internet Indstillinger",
			ID_INTERNET,rct.left+150,rct.top+150,g_hInst);
		CreateButton(hwnd,"Multimedier",
			ID_MULTI,rct.left+325,rct.top+50,g_hInst);
		CreateButton(hwnd,"Mus",
			ID_MOUSE,rct.left+325,rct.top+100,g_hInst);
		CreateButton(hwnd,"Netværk",
			ID_NETWORK,rct.left+325,rct.top+150,g_hInst);
		CreateButton(hwnd,"Printere",
			ID_PRINTER,rct.left+475,rct.top+50,g_hInst);
		CreateButton(hwnd,"Skærm",
			ID_SCREEN,rct.left+475,rct.top+100,g_hInst);
		CreateButton(hwnd,"System",
			ID_SYSTEM,rct.left+475,rct.top+150,g_hInst);
		return 0;

	case WM_CTLCOLORBTN:
		SetBkMode((HDC)wParam,TRANSPARENT);
		return (INT_PTR) GetStockObject(NULL_BRUSH);
	case WM_DRAWITEM:
		dis = (LPDRAWITEMSTRUCT) lParam;
		memdc = CreateCompatibleDC(NULL);
		switch (dis->CtlID)
		{
		case ID_ADD:
				return On_Ownerdraw(dis,g_hInst,"Tilføj/Fjern Programmer");
			break;
		case ID_USER:
				return On_Ownerdraw(dis,g_hInst,"Bruger Password");
			break;
		case ID_DATE:
				return On_Ownerdraw(dis,g_hInst,"Datoen");
			break;
		case ID_INTERNATIONAL:
				return On_Ownerdraw(dis,g_hInst,"Sprog");
			break;
		case ID_GAME:
				return On_Ownerdraw(dis,g_hInst,"Joystick og gamepads");
			break;
		case ID_INTERNET:			
				return On_Ownerdraw(dis,g_hInst,"Internet Explorer");
			break;
		case ID_MULTI:
				return On_Ownerdraw(dis,g_hInst,"Multimedier");
			break;
		case ID_MOUSE:
				return On_Ownerdraw(dis,g_hInst,"Mus");
			break;
		case ID_NETWORK:
				return On_Ownerdraw(dis,g_hInst,"Netværk");
			break;
		case ID_PRINTER:
				return On_Ownerdraw(dis,g_hInst,"Printere");
			break;
		case ID_SCREEN:
				return On_Ownerdraw(dis,g_hInst,"Skærmen");
			break;
		case ID_SYSTEM:
				return On_Ownerdraw(dis,g_hInst,"System");
			break;
		}
		return 0;
	case WM_COMMAND:
		switch(LOWORD (wParam))
		{
		case IDM_EXIT:
			SendMessage(hwnd,WM_CLOSE,(WPARAM)NULL,(LPARAM) NULL);
			break;
		case IDM_ABOUT:
			//ShellAbout(hwnd,"Kontrol Panel","Kontrol Panel af David Poulsen",(HICON)LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON2)));
			DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,aboutproc);
			break;
		case ID_SCREEN:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL desk.cpl",SW_SHOW);
			break;
		case ID_MULTI:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL mmsys.cpl",SW_SHOW);
			break;
		case ID_INTERNET:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL inetcpl.cpl",SW_SHOW);
			break;
		case ID_GAME:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL joy.cpl",SW_SHOW);
			break;
		case ID_USER:
			if(Is_Workstation(Win2K))
			{
				WinExec("%SystemRoot%\\system32\\lusrmgr.msc",SW_SHOW);
			}
			if(Is_Workstation(WinXP))
			{
					WinExec("rundll32.exe shell32.dll,Control_RunDLL nusrmgr.cpl",SW_SHOW);
			}
			if( Is_Workstation(Win9x))
			{
					WinExec("rundll32.exe shell32.dll,Control_RunDLL password.cpl",SW_SHOW);
			}
			break;
		case ID_DATE:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL timedate.cpl",SW_SHOW);
			break;
		case ID_NETWORK:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL ncw.cpl",SW_SHOW);
			break;
		case ID_PRINTER:
			if(Is_Workstation(Win9x))
			{
				WinExec("rundll32.exe shell32.dll,Control_RunDLL {2227A280-3AEA-1069-A2DE-08002B30309D}",SW_SHOW);
			}
			if(Is_Workstation(WinXP))
			{
				Error("Cannot find a suitable device.");
			}
			else if(Is_Workstation(Win2K))
			{
				Error("Cannot find a suitable device.");
			}
			break;
		case ID_SYSTEM:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL sysdm.cpl",SW_SHOW);
			break;
		case ID_INTERNATIONAL:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL intl.cpl",SW_SHOW);
			break;
		case ID_MOUSE:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL main.cpl",SW_SHOW);
			break;
		case ID_ADD:
			WinExec("rundll32.exe shell32.dll,Control_RunDLL appwiz.cpl",SW_SHOW);
			break;
			
		case IDR_LOCKWORKSTATION:
			LockStation();
			break;
		}
		return 0;
	case WM_PAINT:
		return on_Paint(hwnd,&ps);
		break;
	case WM_QUERYENDSESSION:
	case WM_CLOSE:
		if(IDOK != MessageBox(hwnd,"Do you really want to exit?","Question",MB_SYSTEMMODAL|MB_TASKMODAL|MB_ICONQUESTION|MB_OKCANCEL))
			return 0;
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return DefWindowProc(hwnd,msg,wParam,lParam);
}
HRGN BitmapToRegion (HBITMAP hBmp, COLORREF cTransparentColor = 0, COLORREF cTolerance = 0x101010)
{	
	HRGN hRgn = NULL;

	if (hBmp)
	{
		// Create a memory DC inside which we will scan the bitmap content
		HDC hMemDC = CreateCompatibleDC(NULL);
		if (hMemDC)
		{
			// Get bitmap size
			BITMAP bm;
			GetObject(hBmp, sizeof(bm), &bm);

			// Create a 32 bits depth bitmap and select it into the memory DC 
			BITMAPINFOHEADER RGB32BITSBITMAPINFO = {	
					sizeof(BITMAPINFOHEADER),	// biSize 
					bm.bmWidth,					// biWidth; 
					bm.bmHeight,				// biHeight; 
					1,							// biPlanes; 
					32,							// biBitCount 
					BI_RGB,						// biCompression; 
					0,							// biSizeImage; 
					0,							// biXPelsPerMeter; 
					0,							// biYPelsPerMeter; 
					0,							// biClrUsed; 
					0							// biClrImportant; 
			};
			VOID * pbits32; 
			HBITMAP hbm32 = CreateDIBSection(hMemDC, (BITMAPINFO *)&RGB32BITSBITMAPINFO, DIB_RGB_COLORS, &pbits32, NULL, 0);
			if (hbm32)
			{
				HBITMAP holdBmp = (HBITMAP)SelectObject(hMemDC, hbm32);

				// Create a DC just to copy the bitmap into the memory DC
				HDC hDC = CreateCompatibleDC(hMemDC);
				if (hDC)
				{
					// Get how many bytes per row we have for the bitmap bits (rounded up to 32 bits)
					BITMAP bm32;
					GetObject(hbm32, sizeof(bm32), &bm32);
					while (bm32.bmWidthBytes % 4)
						bm32.bmWidthBytes++;

					// Copy the bitmap into the memory DC
					HBITMAP holdBmp = (HBITMAP)SelectObject(hDC, hBmp);
					BitBlt(hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, hDC, 0, 0, SRCCOPY);

					// For better performances, we will use the ExtCreateRegion() function to create the
					// region. This function take a RGNDATA structure on entry. We will add rectangles by
					// amount of ALLOC_UNIT number in this structure.
					#define ALLOC_UNIT	100
					DWORD maxRects = ALLOC_UNIT;
					HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
					RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
					pData->rdh.dwSize = sizeof(RGNDATAHEADER);
					pData->rdh.iType = RDH_RECTANGLES;
					pData->rdh.nCount = pData->rdh.nRgnSize = 0;
					SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);

					// Keep on hand highest and lowest values for the "transparent" pixels
					BYTE lr = GetRValue(cTransparentColor);
					BYTE lg = GetGValue(cTransparentColor);
					BYTE lb = GetBValue(cTransparentColor);
					BYTE hr = min(0xff, lr + GetRValue(cTolerance));
					BYTE hg = min(0xff, lg + GetGValue(cTolerance));
					BYTE hb = min(0xff, lb + GetBValue(cTolerance));

					// Scan each bitmap row from bottom to top (the bitmap is inverted vertically)
					BYTE *p32 = (BYTE *)bm32.bmBits + (bm32.bmHeight - 1) * bm32.bmWidthBytes;
					for (int y = 0; y < bm.bmHeight; y++)
					{
						// Scan each bitmap pixel from left to right
						for (int x = 0; x < bm.bmWidth; x++)
						{
							// Search for a continuous range of "non transparent pixels"
							int x0 = x;
							LONG *p = (LONG *)p32 + x;
							while (x < bm.bmWidth)
							{
								BYTE b = GetRValue(*p);
								if (b >= lr && b <= hr)
								{
									b = GetGValue(*p);
									if (b >= lg && b <= hg)
									{
										b = GetBValue(*p);
										if (b >= lb && b <= hb)
											// This pixel is "transparent"
											break;
									}
								}
								p++;
								x++;
							}

							if (x > x0)
							{
								// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the region
								if (pData->rdh.nCount >= maxRects)
								{
									GlobalUnlock(hData);
									maxRects += ALLOC_UNIT;
									hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE);
									pData = (RGNDATA *)GlobalLock(hData);
								}
								RECT *pr = (RECT *)&pData->Buffer;
								SetRect(&pr[pData->rdh.nCount], x0, y, x, y+1);
								if (x0 < pData->rdh.rcBound.left)
									pData->rdh.rcBound.left = x0;
								if (y < pData->rdh.rcBound.top)
									pData->rdh.rcBound.top = y;
								if (x > pData->rdh.rcBound.right)
									pData->rdh.rcBound.right = x;
								if (y+1 > pData->rdh.rcBound.bottom)
									pData->rdh.rcBound.bottom = y+1;
								pData->rdh.nCount++;

								// On Windows98, ExtCreateRegion() may fail if the number of rectangles is too
								// large (ie: > 4000). Therefore, we have to create the region by multiple steps.
								if (pData->rdh.nCount == 2000)
								{
									HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
									if (hRgn)
									{
										CombineRgn(hRgn, hRgn, h, RGN_OR);
										DeleteObject(h);
									}
									else
										hRgn = h;
									pData->rdh.nCount = 0;
									SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
								}
							}
						}

						// Go to next row (remember, the bitmap is inverted vertically)
						p32 -= bm32.bmWidthBytes;
					}

					// Create or extend the region with the remaining rectangles
					HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
					if (hRgn)
					{
						CombineRgn(hRgn, hRgn, h, RGN_OR);
						DeleteObject(h);
					}
					else
						hRgn = h;

					// Clean up
					GlobalFree(hData);
					SelectObject(hDC, holdBmp);
					DeleteDC(hDC);
				}

				DeleteObject(SelectObject(hMemDC, holdBmp));
			}

			DeleteDC(hMemDC);
		}	
	}

	return hRgn;
}

/*
Future idea.
Network functions:
NetUserEnum 
NetRemoteTOD 
NetApiBufferFree 
NetScheduleJobAdd 
*/
HIMAGELIST _fileImgList;
BOOL ListboxDraw(LPDRAWITEMSTRUCT dis,HWND hwnd,UINT id)
{
	char output[2048];
	HDC hdc;
	int iCount = SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_GETCOUNT,0,0);
	switch(dis->itemAction)
	{
	case ODA_FOCUS:
		if(!(dis->itemState & ODS_NOFOCUSRECT))
		{
			DrawFocusRect(dis->hDC,&dis->rcItem);
		}
		
		return 0;
		break;
	case ODA_SELECT:
	case ODA_DRAWENTIRE:
		SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_GETTEXT,(WPARAM) dis->itemID,(LPARAM)output);
		if(dis->itemState & ODS_SELECTED)
		{
			SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
			SetBkColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHT));
		}
		else
		{
			SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
			SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
		} 
		ExtTextOut(dis->hDC, dis->rcItem.left/*+22*/ , dis->rcItem.top+1, ETO_OPAQUE, &dis->rcItem, output, lstrlen(output), 0);
		if(dis->itemState & ODS_FOCUS) 
		{
			if(!(dis->itemState & ODS_NOFOCUSRECT))
				DrawFocusRect(dis->hDC, &dis->rcItem);
		}

		//Draw the drive icon over the top of the selection
	//	ImageList_Draw(_fileImgList, 0, dis->hDC, 
	//		dis->rcItem.left + 2, 
	//		dis->rcItem.top + nBitmapYOff, 
	//		ILD_TRANSPARENT);
		break;
	}
	return 0;

}
#define IDM_NEW 1
#define IDM_OPEN 2
#define IDM_SAVE 3
#define IDM_LARGEICON 4
#define IDM_SMALLICON 5
#define IDM_LISTVIEW 6
#define IDM_REPORTVIEW 7
int NUM_BUTTONS = 0;
HWND CreateAToolBar2(HWND hWndParent)
{
HWND hWndToolbar;
TBADDBITMAP tb;
int index, stdidx;
INITCOMMONCONTROLSEX icex;

// Toolbar buttons
TBBUTTON tbButtons [ ] = 
{
{STD_FILENEW, IDM_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
{STD_FILEOPEN, IDM_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
{STD_FILESAVE, IDM_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, 0},
{0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, 0},
{VIEW_LARGEICONS, IDM_LARGEICON, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
0L, 0},
{VIEW_SMALLICONS, IDM_SMALLICON, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
0L, 0},
{VIEW_LIST, IDM_LISTVIEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
0L, 0},
{VIEW_DETAILS, IDM_REPORTVIEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 
0L, 0},
}; 

// Ensure that the common control DLL is loaded. 
icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
icex.dwICC  = ICC_BAR_CLASSES;
InitCommonControlsEx(&icex);

// Create the toolbar and add the first three buttons and a separator.
hWndToolbar = CreateToolbarEx (hWndParent, 
WS_CHILD | WS_BORDER | WS_VISIBLE | TBSTYLE_TOOLTIPS, 
ID_TOOLBAR, 11, (HINSTANCE)HINST_COMMCTRL, IDB_STD_SMALL_COLOR, 
(LPCTBBUTTON)&tbButtons, 4, 0, 0, 100, 30, sizeof (TBBUTTON));

// Add the next four buttons
tb.hInst = HINST_COMMCTRL;
tb.nID = IDB_VIEW_SMALL_COLOR;
stdidx = SendMessage (hWndToolbar, TB_ADDBITMAP, 12, (LPARAM)&tb);

for (index = 4; index < NUM_BUTTONS; index++)
tbButtons[index].iBitmap += stdidx;

SendMessage (hWndToolbar, TB_ADDBUTTONS, 4, (LONG) &tbButtons[4]);
                     
return hWndToolbar;

} 
void _OpenFile(HWND hwnd,HWND hwndClient)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
	        0, (LPSECURITY_ATTRIBUTES) NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);

}
LRESULT CALLBACK WndNotePad(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HWND hwndChild;
	INITCOMMONCONTROLSEX ixec;
	HIMAGELIST _toolbar_img_list;
	TBBUTTON tbb[2];
	int iOpen,iSave,iTemp;
	switch(msg)
	{
	case WM_CREATE:
		ixec.dwICC = ICC_BAR_CLASSES;
		ixec.dwSize = sizeof(INITCOMMONCONTROLSEX);
		InitCommonControlsEx(&ixec);
		SendMessage(GetDlgItem(hwnd,ID_TOOLBAR), TB_BUTTONSTRUCTSIZE,(WPARAM) sizeof(TBBUTTON), 0); 
		//hwndChild = CreateWindowEx(NULL,TOOLBARCLASSNAME,"",TBSTYLE_TOOLTIPS|WS_VISIBLE|WS_CHILD,0,0,0,0,hwnd,(HMENU) ID_TOOLBAR,g_hInst,NULL);
		CreateAToolBar2(hwnd);
		CenterWindow(hwnd,GetDesktopWindow());
		hwndChild = CreateWindowEx(WS_EX_CLIENTEDGE,"RICHEDIT","\0",WS_VISIBLE|WS_CHILD|ES_MULTILINE,0,28,640,460,hwnd,(HMENU)ID_RICHEDIT,g_hInst,NULL);

		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			
			case IDR_LOCKWORKSTATION:
				LockStation();
				break;
			case IDM_EXIT:
				SendMessage(hwnd,WM_CLOSE,0,0);
				break;
			case IDM_OPEN:
				_OpenFile(hwnd,hwnd);
				break;
		}
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		ImageList_Destroy(_toolbar_img_list);
		
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

LRESULT CALLBACK WndFindProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{

	PAINTSTRUCT ps;
	HWND hwndChild;
	LPDRAWITEMSTRUCT dis;
	HDC hDC,memDC;
	int i;
	char ach[32];
	char iText[1024];
	int iSelected = SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_GETCURSEL,0,0);
	POINT pt;
	switch(msg)
	{
	case WM_CREATE:
		GetWindowRect(hwnd,&rct);

		CenterWindow(hwnd,GetDesktopWindow());
		hwndChild = CreateStatusWindow(  WS_VISIBLE | WS_CHILD | CCS_BOTTOM,"Kontrol panel af David Poulsen",hwnd, ID_STATUSBAR );
		hwndChild = CreateWindow("COMBOBOX",
			"*",
			WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|CBS_OWNERDRAWFIXED|CBS_HASSTRINGS|CBS_DROPDOWNLIST,
			10,10,150,100,
			hwnd,(HMENU) ID_LISTBOX_TWO,g_hInst,NULL);
		hwndChild = CreateWindowEx(WS_EX_CLIENTEDGE,"LISTBOX",
			"Searchoutput",
			WS_CHILD|WS_VISIBLE|LBS_STANDARD|LBS_NOTIFY|WS_VSCROLL|WS_HSCROLL|LBS_HASSTRINGS|LBS_OWNERDRAWFIXED,
			325,25,300,300,
			hwnd,
			(HMENU)ID_LIST_BOX_THREE,
			g_hInst,
			NULL);
		SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_SETHORIZONTALEXTENT,1024,0);
		CreateButton(hwnd,"Search",ID_SEARCH,160,10,g_hInst);
		hwndChild = CreateWindow("STATIC","Search for:",WS_CHILD|WS_VISIBLE,10,45,100,25,hwnd,(HMENU) NULL,g_hInst,NULL);
		hwndChild = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT",
			"",WS_CHILD|WS_VISIBLE,10,75,100,20,hwnd,
			(HMENU) ID_SEARCH_INPUT,
			g_hInst,NULL);

		MakeDriveList(GetDlgItem(hwnd,ID_LISTBOX_TWO));
		return 0;
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam,TRANSPARENT);
		SetTextColor((HDC)wParam,RGB(255,0,255));
		return (INT_PTR) GetStockObject(NULL_BRUSH);
		break;
	case WM_CTLCOLORBTN:
		SetBkMode((HDC)wParam,OPAQUE);
		return (INT_PTR) GetStockObject(NULL_BRUSH);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_TABEL:
			break;

		case IDM_ABOUT:
			DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),hwnd,aboutproc);
			//ShellAbout(hwnd,"Kontrol Panel","Kontrol Panel by David Poulsen",(HICON) LoadIcon(g_hInst,MAKEINTRESOURCE(IDI_ICON1)));
			break;
		case ID_LISTBOX_TWO:
			switch(HIWORD(wParam))
			{
				case CBN_SELCHANGE:
					//SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_RESETCONTENT,0,0);
					DriveList_GetDrive(GetDlgItem(hwnd,ID_LISTBOX_TWO),ach);
					SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_RESETCONTENT,0,0);
					//SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_DELETESTRING,0,0);
					return TRUE;

			}
			break;
		case ID_LIST_BOX_THREE:
			switch(HIWORD(wParam))
			{
				case LBN_SELCHANGE:
					SendMessage(GetDlgItem(hwnd,ID_LB_GETITEMDATA),WM_ERASEBKGND,(WPARAM)wParam,(LPARAM)0);
					SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_GETTEXT,(WPARAM)iSelected,(LPARAM)iText);
					
					return TRUE; 
				case LBN_DBLCLK:
					SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_GETTEXT,(WPARAM)iSelected,(LPARAM)iText);
					ShellExecute(hwnd,"open",iText,NULL,NULL,SW_SHOW);
					break;
			}
			break;
			case IDR_LOCKWORKSTATION:
				LockStation();
				break;
			case IDM_EXIT:
				SendMessage(hwnd,WM_CLOSE,(WPARAM) NULL,(LPARAM) NULL);
				break;
			case ID_SEARCH:
				char txt_mask[255];
				int iText = GetWindowText(GetDlgItem(hwnd,ID_SEARCH_INPUT),txt_mask,sizeof(txt_mask));
				if(iText == 0)
				{
					Error("Type a filename or a mask to search for!");
				}else
				{
					DriveList_GetDrive(GetDlgItem(hwnd,ID_LISTBOX_TWO),ach);
					SearchDirectory(hwnd,ach,txt_mask );
				}
				
				SendMessage(GetDlgItem(hwnd,ID_LIST_BOX_THREE),LB_SETHORIZONTALEXTENT,iWidth+1025,0);


					break;
			}
		return 0;
	/*	case WM_CTLCOLORLISTBOX:
			SetBkMode((HDC)wParam,TRANSPARENT);
			SetTextColor((HDC)wParam,RGB(0,0,0));
			return (INT_PTR) GetStockObject(NULL_BRUSH);
			break;
		case WM_CTLCOLORSTATIC:
			SetBkMode((HDC)wParam,OPAQUE);
			return (INT_PTR) GetStockObject(NULL_BRUSH);
			break;
	*/


//	case WM_CTLCOLORSTATIC:
//		SendMessage(GetDlgItem(hwnd,ID_LB_GETITEMDATA),WM_ERASEBKGND,(WPARAM)wParam,(LPARAM)0);
//
//		SetBkMode((HDC)wParam,OPAQUE);
//		return (INT_PTR) GetStockObject(NULL_BRUSH);
//		break;
	case WM_DRAWITEM:
		dis = (LPDRAWITEMSTRUCT) lParam;

		switch(dis->CtlID)
		{
		case ID_LB_GETITEMDATA:
			return TRUE;
			break;
		case ID_LISTBOX_TWO:
			return DriveListDraw(hwnd,wParam,dis);
			break;
		case ID_SEARCH:
			return On_Ownerdraw(dis,g_hInst,"Search");
			break;
		case ID_TABEL:
			return On_Ownerdraw(dis,g_hInst,"Vis tabel");
			break;
		case ID_LIST_BOX_THREE:
			return ListboxDraw(dis,hwnd,wParam);
			break;
		}
		break;
	case WM_PAINT:
		return on_Paint(hwnd,&ps);
		break;
	case WM_MEASUREITEM:
		return DriveListMeasure(hwnd,wParam,(MEASUREITEMSTRUCT*)lParam);
		break;
	case WM_QUERYENDSESSION:
	case WM_CLOSE:
		if(IDOK != MessageBox(hwnd,"Do you really want to exit?","Question",MB_SYSTEMMODAL|MB_TASKMODAL|MB_ICONQUESTION|MB_OKCANCEL))
			return 0;
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

void SetDlgItemUrl(HWND hwnd,int ID,const char *url);
void SetDlgItemUrlWWW(HWND hwnd,int ID,const char *url);
BOOL CALLBACK aboutproc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	LPDRAWITEMSTRUCT dis;
	PAINTSTRUCT ps;
	HDC hdc,memdc;
	HBRUSH hbr_Brush;

	HRGN rgn;

	HBITMAP bmp,mask;
	BITMAP bm;
	
	switch (msg)
	{
	case WM_INITDIALOG:
		SetDlgItemUrl(hwnd,IDC_EMAIL_Address,"dpoulsen@e-box.dk");
		SetDlgItemUrlWWW(hwnd,IDC_WWW,"http://www.dkvalby.dk");
		return 0;
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam,TRANSPARENT);
		SetTextColor((HDC)wParam,RGB(0,255,0));
		return (INT_PTR) GetStockObject(NULL_BRUSH);
	case WM_CTLCOLORBTN:
		SetBkMode((HDC)wParam,OPAQUE);
		SetTextColor((HDC)wParam,RGB(0,255,0));
		return (INT_PTR) GetStockObject(NULL_BRUSH);
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		memdc = CreateCompatibleDC(NULL);
		bmp = (HBITMAP) LoadImage(g_hInst,MAKEINTRESOURCE(IDB_BITMAP2),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
		mask = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP4));
		rgn = BitmapToRegion(mask);
		SetWindowRgn(hwnd,rgn,TRUE);
		GetObject(bmp,sizeof(BITMAP),&bm);
		SelectObject(memdc,bmp);
		BitBlt(hdc,0,0,bm.bmWidth,bm.bmHeight,memdc,0,0,SRCAND);
		DeleteObject(bmp);
		DeleteObject(memdc);
		DeleteObject(rgn);
		break;
	case WM_LBUTTONDOWN:
		SendMessage(hwnd,WM_NCLBUTTONDOWN,HTCAPTION,NULL);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		}
		break;
	
	case WM_DRAWITEM:
		HRGN rgn;
		HBITMAP bmp;
		HDC mem;
		dis = (LPDRAWITEMSTRUCT) lParam;
		hbr_Brush = CreateSolidBrush(RGB(68,112,118));
		BITMAP bm;
		switch(dis->CtlID)
		{
		case IDOK:
			if(dis->itemState & ODS_SELECTED)
				DrawEdge(dis->hDC,&dis->rcItem,BDR_SUNKENOUTER,BF_RECT);
			else
				DrawEdge(dis->hDC,&dis->rcItem,BDR_RAISEDINNER,BF_RECT);
			if(dis->itemAction & ODA_DRAWENTIRE)
			{	
				SetBkMode(dis->hDC,TRANSPARENT);
				SetTextColor(dis->hDC,RGB(0,0,0));
				bmp = LoadBitmap(g_hInst,MAKEINTRESOURCE(IDB_BITMAP3));
				mem = CreateCompatibleDC(NULL);
				SelectObject(mem,bmp);
				GetObject(bmp,sizeof(BITMAP),&bm);
				BitBlt(dis->hDC,0,0,bm.bmWidth,bm.bmHeight,mem,0,0,SRCCOPY);
				DrawText(dis->hDC,"Okay",-1,&dis->rcItem,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			}
			if(dis->itemAction & ODA_SELECT)
			{
				rgn = CreateRoundRectRgn(dis->rcItem.left,dis->rcItem.top,dis->rcItem.right,dis->rcItem.bottom,150,100);
				SelectObject(dis->hDC,rgn);
				//InvertRect(dis->hDC,&dis->rcItem);
			}
			break;
		}
		return 0;
	case WM_CLOSE:
		EndDialog(hwnd,0);
		break;
	}
	return 0;
}


static HIMAGELIST GetSystemImageList()
{
	SHFILEINFO  sfi;
	return (HIMAGELIST)SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(SHFILEINFO), SHGFI_SMALLICON|SHGFI_SYSICONINDEX);
}

static TCHAR *lstrchr(TCHAR *str, TCHAR c)
{
	//do the search
	while(*str && *str != c) str++;
	if(*str == _T('\0'))		return (TCHAR *)0;
	else					return (TCHAR *)str;

	return 0;
}

void AddDrive(HWND hwndCombo, TCHAR *pszText, int nIcon)
{
	int idx;
	idx = SendMessage(hwndCombo, CB_INSERTSTRING, -1, (LPARAM)pszText);
	SendMessage(hwndCombo, CB_SETITEMDATA, idx, nIcon);
}
void AddFile(HWND hwndList,char *pFile)
{
	int idx;
	idx = SendMessage(hwndList,LB_INSERTSTRING,-1,(LPARAM)pFile);
}
int ListBox_GetLineHeight(HWND hwndListBox,HFONT hFont,int nBitmapHeight)
{
	TEXTMETRIC tm;
	HANDLE hOldFont = NULL;
	HDC hdc;

	int nTextHeight;
	int nLineHeight;
	hdc = GetDC(hwndListBox);
	hOldFont = SelectObject(hdc,hFont);
	GetTextMetrics(hdc,&tm);
	SelectObject(hdc,hOldFont);
	ReleaseDC(hwndListBox,hdc);
	nTextHeight = tm.tmHeight + tm.tmInternalLeading;
	nLineHeight = max(nBitmapHeight,nTextHeight);
	return nLineHeight;
}

int DriveList_GetLineHeight(HWND hwndCombo, HFONT hFont, int nBitmapHeight)
{
	TEXTMETRIC      tm;
	HANDLE          hOldFont = NULL;
	HDC             hdc;

	int nTextHeight;
	int nLineHeight;

	hdc = GetDC(hwndCombo);

	hOldFont = SelectObject(hdc, hFont);
	GetTextMetrics(hdc, &tm);
	SelectObject(hdc, hOldFont);
	ReleaseDC(hwndCombo, hdc);

	nTextHeight = tm.tmHeight + tm.tmInternalLeading;

	nLineHeight = max(nBitmapHeight, nTextHeight);

	return nLineHeight;
}

void MakeDriveList(HWND hwndCombo)
{
	static TCHAR szDrives[1024];
	TCHAR *driveptr = szDrives;
	TCHAR szVolume[MAX_PATH];
	TCHAR szText[MAX_PATH];
	int drivelen;
	DWORD vollen;
	SHFILEINFO shfi;
	DWORD formfactor;
	
	hSysImgList = GetSystemImageList();

	SendMessage(hwndCombo, CB_RESETCONTENT, 0, 0);

	drivelen = GetLogicalDriveStrings(1024, szDrives);

	while(drivelen != 0)
	{
		int drivetype, len;
		
		len = lstrlen(driveptr) + 1; //plus the NULL
		drivelen -= len;
		
		driveptr = strlwr(driveptr);
		drivetype = GetDriveType(driveptr);

		lstrcpyn(szText, driveptr, 3);	//only copy the 'X:' portion

		//retrieve the index of the icon in the system image list
		SHGetFileInfo(driveptr, 0, &shfi, sizeof(SHFILEINFO), SHGFI_SMALLICON | SHGFI_ICON | SHGFI_LINKOVERLAY );

		switch(drivetype)
		{
		case DRIVE_REMOVABLE:	
			formfactor = GetDriveFormFactor(driveptr[0] - _T('a'));

			if(formfactor == 350)
				wsprintf(szText, _T("%c: (3½ Floppy)"), driveptr[0]);
			else if(formfactor == 512)
				wsprintf(szText, _T("%c: (5¼ Floppy)"), driveptr[0]);
			else
				lstrcat(szText, _T(" (Removable)"));

			break;

		case DRIVE_CDROM:		lstrcat(szText, _T(" (CD)"));			break;
		case DRIVE_REMOTE:		lstrcat(szText, _T(" (Network)"));		break;
		case DRIVE_RAMDISK:		lstrcat(szText, _T(" (RAM-Disk)"));		break;

		case DRIVE_FIXED:
			
			if(GetVolumeInformation(driveptr, szVolume, MAX_PATH, 0, &vollen, 0, 0, 0))
			{
				if(szVolume[0] != _T('\0'))
				{
					lstrcat(szText, _T(" ["));
					lstrcat(szText, szVolume);
					lstrcat(szText, _T("]"));
				}
			}
			break;

		}
				
		AddDrive(hwndCombo, szText, shfi.iIcon);
		driveptr += len;
	}
		
	SendMessage(hwndCombo, CB_SETCURSEL, 0, 0);
}

BOOL DriveListMeasure(HWND hwnd, UINT uCtrlId, MEASUREITEMSTRUCT *mis)
{
	HFONT hFont = (HFONT)SendMessage(hwnd, WM_GETFONT, 0, 0);
	mis->itemHeight = DriveList_GetLineHeight(hwnd, hFont, nBitmapHeight);  //(16)

	nBitmapYOff = (mis->itemHeight - (nBitmapHeight-1)) / 2;
	return TRUE;
}

BOOL DriveListDraw(HWND hwnd, UINT uCtrlId, DRAWITEMSTRUCT *dis)
{
	HWND hwndCombo = GetDlgItem(hwnd, uCtrlId);
	TCHAR szText[MAX_PATH+1];
	TCHAR *ptr;
	int idx;
	
	switch(dis->itemAction)
	{
	case ODA_FOCUS:
		if(!(dis->itemState & ODS_NOFOCUSRECT))
			DrawFocusRect(dis->hDC, &dis->rcItem);
		break;

	case ODA_SELECT:
	case ODA_DRAWENTIRE:

		SendMessage(hwndCombo, CB_GETLBTEXT, dis->itemID, (LONG)szText);
	
		if(dis->itemState & ODS_SELECTED)
		{
			SetTextColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
			SetBkColor(dis->hDC, GetSysColor(COLOR_HIGHLIGHT));
		}
		else
		{
			SetTextColor(dis->hDC, GetSysColor(COLOR_WINDOWTEXT));
			SetBkColor(dis->hDC, GetSysColor(COLOR_WINDOW));
		}

		//we set the SB_SETITEMDATA DWORD to be the system image list index
		//for this drive icon. Retrieve the value so we know which picture
		//to display for this drive
		idx = dis->itemData;

		ptr = lstrchr(szText, _T(':'));
		if(ptr) ptr = ptr[1] == _T(' ') ? ptr + 1 : 0;
		if(ptr) *ptr = _T('\0');

		//Draw the text
		ExtTextOut(dis->hDC, dis->rcItem.left+22, dis->rcItem.top+1, ETO_OPAQUE, &dis->rcItem, szText, lstrlen(szText), 0);

		if(ptr)
			ExtTextOut(dis->hDC, dis->rcItem.left+22+16, dis->rcItem.top+1, 0, 0, ptr+1, lstrlen(ptr+1), 0);

		if(dis->itemState & ODS_FOCUS) 
		{
			if(!(dis->itemState & ODS_NOFOCUSRECT))
				DrawFocusRect(dis->hDC, &dis->rcItem);
		}

		//Draw the drive icon over the top of the selection
		ImageList_Draw(hSysImgList, idx, dis->hDC, 
			dis->rcItem.left + 2, 
			dis->rcItem.top + nBitmapYOff, 
			ILD_TRANSPARENT);

		break;
	}

	return TRUE;
}

BOOL DriveList_GetDrive(HWND hwnd, TCHAR szDrive[])
{
	TCHAR *ptr;
	TCHAR szText[MAX_PATH];

	GetWindowText(hwnd, szText, MAX_PATH);

	ptr = lstrchr(szText, _T(':'));
	if(ptr) ptr[1] = _T('\0');

	lstrcpy(szDrive, szText);

	return TRUE;
}