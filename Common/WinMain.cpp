#include "Sample.hpp"

HWND CreateSampleWindow(HINSTANCE hInstance, Sample *sample);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	std::unique_ptr<Sample> sample = CreateSample();

	sample->Initialise();

	HWND hWnd = CreateSampleWindow(hInstance, sample.get());

	int result = -1;

	if (hWnd)
	{
		ShowWindow(hWnd, nCmdShow);

		MSG msg = { };
		while (GetMessageW(&msg, nullptr, 0, 0))
		{
			if (sample->PreTranslateMessage(msg))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}
		}

		result = static_cast<int>(msg.wParam);
	}

	sample->Uninitialise();

	return result;
}

HWND CreateSampleWindow(HINSTANCE hInstance, Sample *const sample)
{
	WNDCLASSW wc = { };

	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"XamlIslands";
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));

	RegisterClassW(&wc);

	return CreateWindowExW(0, wc.lpszClassName, sample->GetName().data(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, sample);
}

Sample* GetSample(HWND hWnd)
{
	return reinterpret_cast<Sample*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		Sample* const sample = GetSample(hWnd);
		sample->SetHwnd(hWnd);
		sample->OnWindowCreated();
		return 0;
	}
	else if (msg == WM_DESTROY)
	{
		Sample* const sample = GetSample(hWnd);
		sample->OnWindowDestroyed();
		PostQuitMessage(0);
		return 0;
	}
	else if (msg == WM_NCCREATE)
	{
		LPCREATESTRUCT creationData = reinterpret_cast<LPCREATESTRUCT>(lParam);
		Sample* const sample = reinterpret_cast<Sample*>(creationData->lpCreateParams);
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(sample));
		return TRUE;
	}
	else if (msg == WM_SIZE)
	{
		Sample* const sample = GetSample(hWnd);
		sample->OnWindowResized();
		return 0;
	}

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}
