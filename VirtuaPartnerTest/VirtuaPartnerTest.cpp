#include "pch.h"
#include "CppUnitTest.h"
#include "../VirtuaPartner/PunishChecker.h"
#include "../VirtuaPartner/PunishChecker.cpp"
#include "../VirtuaPartner/PunishCheckerShun.h"
#include "../VirtuaPartner/PunishCheckerShun.cpp"
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#pragma comment (lib, "Gdiplus.lib")


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

	bool createTestWindow()
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

		bool result = false;

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

			Sleep(500);
			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				if (i++ == 10) {
					Logger::WriteMessage(" check shoon in loop loop");
					PunishCheckerShun shun(vfWindow, false, false);
					result = (shun.isPlayer1());
					SendMessage(vfWindow, WM_CLOSE, NULL, NULL);
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
		TEST_METHOD(TestIsPlayer1ShunPositive)
		{			
			filename = _T("data\\shun_left_side.jpg");
			Assert::IsTrue(createTestWindow());						
		}

		TEST_METHOD(TestIsPlayer1ShunNegative)
		{			
			filename = _T("data\\all_black.jpg");
			Assert::IsFalse(createTestWindow());
		}

		TEST_METHOD(GetSelectedPlayerOne)
		{
			PunishChecker checker();

		}
	};
}
