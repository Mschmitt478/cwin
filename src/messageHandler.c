/**
 * @file messageHandler
 * @author Matthew J. Schmitt
 * @date 2023-11-27
 *
 * @copyright (c) 2023
 */
#include "MessageHandler.h"

#include <stdio.h>
#include <stdlib.h>

// Button variables
#define MAX_BUTTONS 100
#define BUTTON_MIN_ID 100
#define BUTTON_MAX_ID (BUTTON_MIN_ID + MAX_BUTTONS)
#define BTEXT_BUF_SIZE 2
static size_t total_buttons = 0;

// Text box variables
#define MAX_TEXT_BOXES 24
#define TEXT_BOX_MIN_ID 100
#define TEXT_BOX_MAX_ID (TEXT_BOX_MIN_ID + MAX_TEXT_BOXES)
static size_t total_text_boxes = 0;

#define BOXHEIGHT (BHEIGHT)
#define BOXWIDTH (BWIDTH * 4)

HWND buttons[MAX_BUTTONS];
HWND boxes[MAX_TEXT_BOXES];

int GetXPos(int i)
{
    return (i * BWIDTH);
}

int GetYPos(int i)
{
    return (i * BHEIGHT);
}

void CreateEditBox(HINSTANCE hInstance, HWND hwnd, int x, int y)
{
    if (total_text_boxes >= MAX_TEXT_BOXES)
    {
        PostQuitMessage(1);
        return;
    }
    HWND hwndBox = CreateWindowEx(
        0,                                          /* more or ''extended'' styles */
        TEXT("EDIT"),                               /* GUI ''class'' to create */
        "",                                         /* GUI caption */
        WS_BORDER | WS_CHILD | WS_VISIBLE,          /* control styles separated by | */
        x, y, BOXWIDTH, BOXHEIGHT,                  /* x, y, w, h */
        hwnd,                                       /* Parent window handle */
        (HMENU)(TEXT_BOX_MIN_ID + total_text_boxes),/* control''s ID for WM_COMMAND */
        hInstance,                                  /* application instance */
        NULL
    );

    boxes[0] = hwndBox;
    total_text_boxes++;
}

void CreateCalcButton(HINSTANCE hInstance, HWND hwnd, wchar_t *str, int x, int y)
{
    if (total_buttons >= MAX_BUTTONS)
    {
        PostQuitMessage(1);
        return;
    }
    HWND hwndButton = CreateWindowEx(
        0,                                          /* more or ''extended'' styles */
        TEXT("BUTTON"),                             /* GUI ''class'' to create */
        str,                                        /* GUI caption */
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,   /* control styles separated by | */
        x, y, BWIDTH, BHEIGHT,                      /* x, y, w, h */
        hwnd,                                       /* Parent window handle */
        (HMENU)(BUTTON_MIN_ID + total_buttons),     /* control''s ID for WM_COMMAND */
        hInstance,                                  /* application instance */
        NULL
    );

    buttons[total_buttons] = hwndButton;
    total_buttons++;
}

void HandleCreate(HINSTANCE hInstance, HWND hwnd)
{
    int success;
    int x = 0;
    int y = 3 * BHEIGHT; // Position of the third row in the calculator
    
    CreateEditBox(hInstance, hwnd, GetXPos(0), GetYPos(0));

    for (int i = 0; i < 3 && y >= BHEIGHT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            x = GetXPos(j);
            char buf[BTEXT_BUF_SIZE];
            success = snprintf(buf, BTEXT_BUF_SIZE, TEXT("%d"), (j + 1) + (3 * i));
            if (!success)
            {
                PostQuitMessage(1);
                return;
            }
            CreateCalcButton(hInstance, hwnd, buf, x, y);
        }
        y -= BHEIGHT;
    }
    CreateCalcButton(hInstance, hwnd, TEXT("0"), GetXPos(1), GetYPos(4));
    CreateCalcButton(hInstance, hwnd, TEXT("+/-"), GetXPos(0), GetYPos(4));
    CreateCalcButton(hInstance, hwnd, TEXT("."), GetXPos(2), GetYPos(4));
    CreateCalcButton(hInstance, hwnd, TEXT("DEL"), GetXPos(3), GetYPos(1));
    CreateCalcButton(hInstance, hwnd, TEXT("/"), GetXPos(3), GetYPos(2));
    CreateCalcButton(hInstance, hwnd, TEXT("x"), GetXPos(3), GetYPos(3));
    CreateCalcButton(hInstance, hwnd, TEXT("-"), GetXPos(3), GetYPos(4));
}

void HandleButtons(
    WPARAM wParam,
    LPARAM lParam
)
{
    if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED))
    {
        int iMID;
        iMID = LOWORD(wParam);
        // reading events
        switch (iMID)
        {
        case BUTTON_MIN_ID ... BUTTON_MAX_ID:   // Only valid when using GCC
        {
            printf("BUTTON WITH ID=%d PRESSED\n", iMID);
            break;
        }
        /*
        add your cases here
        */
        default:
            break;
        }
    }
}