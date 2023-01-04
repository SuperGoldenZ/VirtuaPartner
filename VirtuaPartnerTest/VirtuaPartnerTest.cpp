#include "pch.h"
#include "CppUnitTest.h"
#include "../VirtuaPartner/WindowPixelChecker.h"
#include "../VirtuaPartner/WindowPixelChecker.cpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#pragma comment (lib, "Gdiplus.lib")
#pragma comment(lib, "WinMM.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace VirtuaPartnerTest
{
	HWND vfWindow;
	WCHAR* filename;

	void DrawPlayer1ShunImage(HDC hdc)
	{
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Image* image = Gdiplus::Image::FromFile(filename);
		graphics.DrawImage(image, 0, 0, 1282, 721);
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	std::string createTestWindow()
	{
		ULONG_PTR token;
		Gdiplus::GdiplusStartupInput input = { 0 };
		input.GdiplusVersion = 1;
		Gdiplus::GdiplusStartup(&token, &input, NULL);

		const wchar_t CLASS_NAME[] = L"Sample Window Class";
		WNDCLASS wc = {};
		wc.lpfnWndProc = &WindowProc; //attach this callback procedure
		// wc.hInstance = hInstance; //handle to application instance
		wc.lpszClassName = CLASS_NAME;
		RegisterClass(&wc); //register wc
		// Create the window.

		std::string result = "";

		vfWindow = CreateWindowEx(
			0, // Optional window styles.
			CLASS_NAME, // Window class
			L"Learn to Program Windows", // Window text
			WS_OVERLAPPEDWINDOW, // Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL, // Parent window
			NULL, // Menu
			NULL, // hInstance, // Instance handle
			NULL // Additional application data
		);

		if (vfWindow != NULL)
		{
			ShowWindow(vfWindow, SW_NORMAL);

			RECT rect;
			if (GetWindowRect(vfWindow, &rect))
			{
				SetWindowPos(vfWindow, NULL, rect.left, rect.top, 1296, 759, SWP_NOZORDER);
			}

			MSG msg;
			Logger::WriteMessage("Starting loop");
			int i = 0;
			WindowPixelChecker checker(vfWindow);

			Sleep(250);
			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				if (i++ == 10) {
					Logger::WriteMessage(" check shoon in loop loop");
					SendMessage(vfWindow, WM_PAINT, NULL, NULL);
					Sleep(250);
					result = checker.getSelectedPlayer1();
					Sleep(250);
					SendMessage(vfWindow, WM_CLOSE, NULL, NULL);
					Sleep(250);
					break;
				}


				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			std::cout << "Window not made";
		}

		Logger::WriteMessage("Shutting down");

		Gdiplus::GdiplusShutdown(token);
		Sleep(250);
		return result;
	}


	//callback procedure for this window, takes in all the window details
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			DrawPlayer1ShunImage(hdc);
			EndPaint(hwnd, &ps);
			return 0;
		}
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	TEST_CLASS(VirtuaPartnerTest)
	{
	public:
		TEST_METHOD(TestPlayer1Unknown1)
		{
			filename = _T("data\\shun_left_side.gif");
			std::string result = createTestWindow();
			std::wstring widestr = std::wstring(result.begin(), result.end());

			Assert::AreEqual("Unknown", result.c_str());
		}

		TEST_METHOD(TestPlayer1Unknown2)
		{
			filename = _T("data\\all_black.jpg");

			std::string result = createTestWindow();
			std::wstring widestr = std::wstring(result.begin(), result.end());

			Assert::AreEqual("Unknown", result.c_str());
		}

		TEST_METHOD(TestPlayer1Shun)
		{
			filename = _T("data\\character_select_shun_left.gif");

			std::string result = createTestWindow();
			std::wstring widestr = std::wstring(result.begin(), result.end());

			Assert::AreEqual("S[h]un", result.c_str());
		}

		TEST_METHOD(TestPlayer1Jean)
		{
			filename = _T("data\\character_select_jean_left.gif");

			std::string result = createTestWindow();
			std::wstring widestr = std::wstring(result.begin(), result.end());

			Assert::AreEqual("[J]ean", result.c_str());
		}
	};
}
