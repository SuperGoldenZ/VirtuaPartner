#include "pch.h"
#include "CppUnitTest.h"
#include "../VirtuaPartner/WindowPixelChecker.h"
#include "../VirtuaPartner/WindowPixelChecker.cpp"
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
		graphics.DrawImage(image, 0, 0, image->GetWidth(), image->GetHeight());
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
			L"Virtua Partner Unit Test Window", // Window text
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


			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				Logger::WriteMessage(" check shoon in loop loop");
				SendMessage(vfWindow, WM_PAINT, NULL, NULL);

				result = checker.getSelectedPlayer1();

				SendMessage(vfWindow, WM_CLOSE, NULL, NULL);
			}
		}
		else {
			std::cout << "Window not made";
		}

		Logger::WriteMessage("Shutting down");

		Gdiplus::GdiplusShutdown(token);

		return result;
	}

	int checkFrameAdvantage()
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

		int result = -1;

		vfWindow = CreateWindowEx(
			0, // Optional window styles.
			CLASS_NAME, // Window class
			L"Virtua Partner Unit Test Window", // Window text
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
			PunishCheckerShun checker(vfWindow, false, false);

			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				Logger::WriteMessage(" check shoon in loop loop");
				SendMessage(vfWindow, WM_PAINT, NULL, NULL);

				checker.getAdvantageAmount();
				result = checker.frameAdvantage;

				SendMessage(vfWindow, WM_CLOSE, NULL, NULL);

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

			Assert::AreEqual("Shun", result.c_str());
		}

		TEST_METHOD(TestPlayer1Jean)
		{
			filename = _T("data\\character_select_jean_left.gif");

			std::string result = createTestWindow();
			std::wstring widestr = std::wstring(result.begin(), result.end());

			Assert::AreEqual("Jean", result.c_str());
		}

		TEST_METHOD(Test10FrameAdvantage)
		{
			filename = _T("data\\10_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(10, result);
		}

		TEST_METHOD(Test12FrameAdvantage)
		{
			filename = _T("data\\12_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(12, result);
		}

		TEST_METHOD(Test13FrameAdvantage)
		{
			filename = _T("data\\13_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(13, result);
		}

		TEST_METHOD(Test14FrameAdvantage)
		{
			filename = _T("data\\14_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(14, result);
		}

		TEST_METHOD(Test15FrameAdvantage)
		{
			filename = _T("data\\15_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(15, result);
		}

		TEST_METHOD(Test16FrameAdvantage)
		{
			filename = _T("data\\16_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(16, result);
		}

		TEST_METHOD(Test17FrameAdvantage)
		{
			filename = _T("data\\17_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(17, result);
		}

		TEST_METHOD(Test18FrameAdvantage)
		{
			filename = _T("data\\18_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(18, result);
		}

		TEST_METHOD(Test19FrameAdvantage)
		{
			filename = _T("data\\19_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(19, result);
		}

		TEST_METHOD(Test26FrameAdvantage)
		{
			filename = _T("data\\26_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(32, result);
		}

		TEST_METHOD(Test32FrameAdvantage)
		{
			filename = _T("data\\32_frame_advantage.gif");

			int result = checkFrameAdvantage();

			Assert::AreEqual(32, result);
		}
	};
}
