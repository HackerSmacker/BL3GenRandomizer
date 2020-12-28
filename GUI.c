#include <windows.h>
#include "GUIresourceID.h"

char g_szClassName[] = "b3grWindowClass";

HWND g_hSpawnsDialog = NULL;
HWND g_hSkillsDialog = NULL;
HWND g_hItemsDialog = NULL;

STARTUPINFO si;
PROCESS_INFORMATION pi;

BOOL CALLBACK SpawnsDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CLOSE:
			DestroyWindow(g_hSpawnsDialog);
                        break;
                case WM_DESTROY:
			DestroyWindow(g_hSpawnsDialog);
                        break;
		case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case IDC_SPAWNS_RUN:
			{
				if(!(CreateProcessA(NULL, "mkspawnrand.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))) {
					MessageBox(hwnd, "Failed to run randomizer generator program. Make sure you downloaded all the files.", "Error", MB_OK);
				}
				else {
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					MessageBox(hwnd, "Randomizer generated successfully.", "Success", MB_OK);
				}
			}
 				break;
			case IDC_SPAWNS_OPEN:
			{
				if(!(CreateProcessA(NULL, "notepad.exe spawn_randomizer.txt", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))) {
					MessageBox(hwnd, "Failed to open notepad.", "Error", MB_OK);
				}
				else {
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
				}
			}
				break;
		}
		break;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}

BOOL CALLBACK ItemsDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CLOSE:
			DestroyWindow(g_hItemsDialog);
                        break;
                case WM_DESTROY:
			DestroyWindow(g_hItemsDialog);
                        break;
		case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case IDC_ITEMS_RUN:
			{
				if(!(CreateProcessA(NULL, "mkitemrand.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))) {
					MessageBox(hwnd, "Failed to run randomizer generator program. Make sure you downloaded all the files.", "Error", MB_OK);
				}
				else {
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					MessageBox(hwnd, "Randomizer generated successfully.", "Success", MB_OK);
				}
			}

				break;
			case IDC_ITEMS_OPEN:
			{
				if(!(CreateProcessA(NULL, "notepad.exe item_randomizer.txt", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))) {
					MessageBox(hwnd, "Failed to open notepad.", "Error", MB_OK);
				}
				else {
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
				}
			}
				break;
		}
		break;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}

BOOL CALLBACK SkillsDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CLOSE:
			DestroyWindow(g_hSkillsDialog);
                        break;
                case WM_DESTROY:
			DestroyWindow(g_hSkillsDialog);
                        break;
		case WM_COMMAND:
		switch(LOWORD(wParam)) {
			case IDC_SKILLS_RUN:
			{
				if(!(CreateProcessA(NULL, "mkskillrand.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))) {
					MessageBox(hwnd, "Failed to run randomizer generator program. Make sure you downloaded all the files.", "Error", MB_OK);
				}
				else {
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
					MessageBox(hwnd, "Randomizer generated successfully.", "Success", MB_OK);
				}
			}

				break;
			case IDC_SKILLS_OPEN:
			{
				if(!(CreateProcessA(NULL, "notepad.exe skill_randomizer.txt", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))) {
					MessageBox(hwnd, "Failed to open notepad.", "Error", MB_OK);
				}
				else {
					WaitForSingleObject(pi.hProcess, INFINITE);
					CloseHandle(pi.hProcess);
					CloseHandle(pi.hThread);
				}
			}
				break;
		}
		break;
		default:
			return FALSE;
			break;
	}
	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch(msg) {
		case WM_CREATE:
		{
			HMENU hMenu, hSubMenu;
			hMenu = CreateMenu();
			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, ID_FUNC_SPAWNS, "Spawn Randomizer");
			AppendMenu(hSubMenu, MF_STRING, ID_FUNC_SKILLS, "Skill Randomizer");
			AppendMenu(hSubMenu, MF_STRING, ID_FUNC_ITEMS, "Item Randomizer");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Functions");
			hSubMenu = CreatePopupMenu();
			AppendMenu(hSubMenu, MF_STRING, ID_HELP_ONLINE, "&Online Help");
			AppendMenu(hSubMenu, MF_STRING, ID_HELP_ABOUT, "&About");
			AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");
			SetMenu(hwnd, hMenu);
			
		}
		break;
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case ID_FILE_EXIT:
					DestroyWindow(hwnd);
					break;
				case ID_HELP_ABOUT:
					MessageBox(hwnd, "This is the user interface for the mkrandomizer programs. Written by HackerSmacker and SSpyR. This is public-domain software and neither of us are responsible for any of the outcomes that you may incur using this program.", "About", MB_OK);
					break;
				case ID_FUNC_SPAWNS:
					g_hSpawnsDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SPAWNS), hwnd, SpawnsDlgProc);
					if(g_hSpawnsDialog != NULL) {
						ShowWindow(g_hSpawnsDialog, SW_SHOW);
					}
					break;
				case ID_FUNC_SKILLS:
					g_hSkillsDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SKILLS), hwnd, SkillsDlgProc);
					if(g_hSkillsDialog != NULL) {
						ShowWindow(g_hSkillsDialog, SW_SHOW);
					}
					break;
				case ID_FUNC_ITEMS:
					g_hItemsDialog = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ITEMS), hwnd, ItemsDlgProc);
					if(g_hItemsDialog != NULL) {
						ShowWindow(g_hItemsDialog, SW_SHOW);
					}
					break;
			}
		break;
		/* For path debugging
		case WM_LBUTTONDOWN:
		{
			char szFileName[MAX_PATH];
			HINSTANCE hInstance = GetModuleHandle(NULL);
			GetModuleFileName(hInstance, szFileName, MAX_PATH);
			MessageBox(hwnd, szFileName, "This program is: ", MB_OK | MB_ICONINFORMATION);
		}
		break;
		*/
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	MessageBox(NULL, "Warning: this is largely untested and has a chance of crashing your game. Please report any bugs you find as soon as you can.", "Beta software", MB_OK);
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_APPMENU);
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
	if(!(RegisterClassEx(&wc))) {
		MessageBox(NULL, "Failed to register window...", "Massive issue", MB_OK | MB_ICONEXCLAMATION);
		return -1;
	}
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "BL3 Randomzier Generators", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,	CW_USEDEFAULT, 400, 60, NULL, NULL, hInstance, NULL);
	if(hwnd	== NULL) {
		MessageBox(NULL, "Failed to create window...", "Massive issue", MB_OK | MB_ICONEXCLAMATION);
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while(GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

