#include <windows.h>
#include <wchar.h>
#include <stdio.h>

#include "MessageHandler.h"

HINSTANCE g_hInst;           // The global instance
char szClassName[] = "cwin"; // Global name

/* All Button Definitions */

LRESULT CALLBACK MainWndProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    /* Handles all Windows Messages */
    switch (uMsg)
    {
    case WM_CREATE:     // A simple handler to deal with window creation
    {
        HandleCreate(g_hInst, hwnd);
        break;
    }
    case WM_DESTROY:    // send a WM_QUIT to Message Queue, to shut off program
    {
        PostQuitMessage(0);
        break;
    }
    case WM_COMMAND:    // A handler for button creation
    {
        HandleButtons(wParam, lParam);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam); // messages that we will not process
    }
    return 0;
}

// Entry point for all windows applications
int WINAPI WinMain(
    HINSTANCE hInstance,                // handle to the instance
    HINSTANCE hPrevInstance,            // UNUSED SINCE 16-bit
    PSTR lpCmdLine,                     // Command line arg string
    int nCmdShow                        // Flag for minimized, maximized, or normal
)
{
    HWND hwnd;                          // Window Handler
    MSG messages;                       // Messages from windows
    WNDCLASSEX wincl;                   // Window class information

    /* The Window structure */
    g_hInst = hInstance;
    wincl.hInstance = hInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = MainWndProc;    // Called by windows
    wincl.style = CS_DBLCLKS;           // Catches double clicks
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;          // No Menu
    wincl.cbClsExtra = 0;               // No extra bytes after the window class
    wincl.cbWndExtra = 0;               // structure or the window instance

    /* Use Windows' default color as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program */
    hwnd = CreateWindowEx(
        0,                              // Extended possibilites for variation
        szClassName,                    // Classname
        TEXT("Test Window"),            // Title Text
        WS_OVERLAPPED | WS_CAPTION | 
        WS_SYSMENU | WS_MINIMIZEBOX,    // default window
        700,                            // Windows decides the position
        300,                            // where the window ends up on the screen
        BWIDTH * 4,                     // The programs width
        BHEIGHT * 6,                    // and height in pixels
        HWND_DESKTOP,                   // The window is a child-window to desktop
        NULL,                           // No menu
        hInstance,                      // Program Instance handler
        NULL                            // No Window Creation data
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/* your functions here like allocation and file locking and so on */