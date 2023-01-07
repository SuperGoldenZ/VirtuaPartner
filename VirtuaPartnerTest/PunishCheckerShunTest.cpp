#include "pch.h"
#include "CppUnitTest.h"
#include "../VirtuaPartner/WindowPixelChecker.h"
//#include "../VirtuaPartner/WindowPixelChecker.cpp"
#include "../VirtuaPartner/PunishChecker.h"
//#include "../VirtuaPartner/PunishChecker.cpp"
#include "../VirtuaPartner/PunishCheckerShun.h"
//#include "../VirtuaPartner/PunishCheckerShun.cpp"
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


namespace PunishCheckerShunTest
{
	HWND vfWindow;
	WCHAR* filename;
	int frameAdvantage;
	bool maxDamage = false;
	bool recoversLow = false;

	void DrawPlayer1ShunImage(HDC hdc)
	{
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::Image* image = Gdiplus::Image::FromFile(filename);
		//graphics.DrawImage(image, 0, 0, 1282, 721);
		graphics.DrawImage(image, 0, 0, image->GetWidth(), image->GetHeight());
		//
	}

	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool testShunPunishWithWindow()
	{
		ULONG_PTR token;
		Gdiplus::GdiplusStartupInput input = { 0 };
		input.GdiplusVersion = 1;
		Gdiplus::GdiplusStartup(&token, &input, NULL);

		const wchar_t CLASS_NAME[] = L"Punish Checker Shun Class";
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
			L"Virtua Partner Punish Checker Shun Unit Test Window", // Window text
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
			int i = 0;
			PunishCheckerShun checker(vfWindow, recoversLow, recoversLow);
			checker.frameAdvantage = frameAdvantage;

			while (GetMessage(&msg, NULL, 0, 0) > 0)
			{
				SendMessage(vfWindow, WM_PAINT, NULL, NULL);
				Sleep(250);
				checker.judgePunishment();
				result = checker.maxPunishment;
				SendMessage(vfWindow, WM_CLOSE, NULL, NULL);
			}
		}
		else {
			Logger::WriteMessage("Window not made");
		}

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

	TEST_CLASS(PunishCheckerShunTest)
	{
	public:
		TEST_METHOD(TestPlayer1Shun14FramePunish)
		{
			filename = _T("data\\shun_14_frame_1p_counter_0_drinks.gif");
			frameAdvantage = 14;
			recoversLow = false;
			bool result = testShunPunishWithWindow();
			Assert::AreEqual(true, result);

			filename = _T("data\\shun_15_frame_1pk_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(TestPlayer1Shun15FramePunishStanding)
		{
			filename = _T("data\\shun_15_frame_1pk_counter_0_drinks.gif");
			frameAdvantage = 15;
			recoversLow = false;
			bool result = testShunPunishWithWindow();
			Assert::AreEqual(true, result, _T("15 frame counter did not count as expected"));

			filename = _T("data\\shun_14_frame_1p_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(TestPlayer1Shun15FramePunishDucking)
		{
			frameAdvantage = 15;
			recoversLow = true;

			bool result;

			filename = _T("data\\shun_15_frame_6pp_crouch_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(true, result);

			filename = _T("data\\shun_14_frame_1p_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result, _T("14 frame counted as max punish for 15 frame move"));
		}

		TEST_METHOD(TestPlayer1Shun19FramePunish)
		{
			frameAdvantage = 19;
			recoversLow = false;

			bool result;

			filename = _T("data\\shun_19_frame_66k_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(true, result, _T("19 frame punish did not count as max for 19 frames"));

			filename = _T("data\\shun_15_frame_6pp_crouch_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result, _T("15 frame punish counted as max for 19 frames"));

			filename = _T("data\\shun_14_frame_1p_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result, _T("14 frame counted as max punish for 19 frame move"));
		}

		TEST_METHOD(TestPlayer1Shun18FramePunish)
		{
			frameAdvantage = 18;
			recoversLow = false;

			bool result;

			filename = _T("data\\shun_18_frame_8kg_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(true, result, _T("18 frame punish did not count as max for 18 frames"));

			filename = _T("data\\shun_15_frame_6pp_crouch_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result, _T("15 frame punish counted as max for 19 frames"));

			filename = _T("data\\shun_14_frame_1p_counter_0_drinks.gif");
			result = testShunPunishWithWindow();
			Assert::AreEqual(false, result, _T("14 frame counted as max punish for 19 frame move"));
		}
	};
}
