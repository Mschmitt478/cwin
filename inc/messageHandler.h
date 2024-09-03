/**
 * @file messageHandler
 * @author Matthew J. Schmitt
 * @date 2023-11-27
 *
 * @copyright (c) 2023
 */
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <windows.h>

#define BHEIGHT 35
#define BWIDTH 35

void HandleButtons(
    WPARAM wParam,
    LPARAM lParam);

void HandleCreate(HINSTANCE hInstance, HWND hwnd);

#endif // MESSAGEHANDLER_H