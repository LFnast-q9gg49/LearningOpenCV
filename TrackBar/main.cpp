#include <cstdio>
#include <opencv2/opencv.hpp>
#include <windows.h>


LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR iCmdLine, int iCmdShow){
    HWND hwnd;
    WNDCLASS wndclass;
    MSG msg;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = MainWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor (nullptr, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszClassName = TEXT("PicMod");
    wndclass.lpszMenuName = nullptr;

    if (!RegisterClassA(&wndclass)){
        MessageBox(nullptr, "error: can't register wndclass", "error box", MB_OKCANCEL);
    }

    hwnd = CreateWindow(TEXT("PicMod"), TEXT("PicMod"), WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        nullptr, nullptr, hInstance, nullptr);
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, nullptr, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    static int id;
    static int cxClient, cyClient;
    static HWND Single_Button;
    switch (message) {
        case WM_SIZE:
            cxClient = LOWORD(lparam);
            cyClient = HIWORD(lparam);
            return 0;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        case WM_CREATE:
            return 0;
        case WM_COMMAND:
            id = LOWORD(wparam);
            switch (id) {
                case 1001:
                    MessageBoxA(nullptr, "click me", "click", MB_OKCANCEL);
                case 1002:



                default:
                    break;
            }
            return 0;
        case WM_CLOSE:
            if (MessageBox(hwnd, TEXT("please click yes if you want to quit"), TEXT("close box"), MB_OKCANCEL) == IDOK){
                DestroyWindow(hwnd);
            } else{
                return 0;
            }
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            break;
    }
    return DefWindowProcA(hwnd, message, wparam, lparam);
}