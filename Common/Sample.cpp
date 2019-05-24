#include "Sample.hpp"

#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Hosting;

void Sample::Initialise()
{
	// No longer required with WinRT 2.0
	//init_apartment();

	// Note: This is only necessary if you initialise any controls before the DesktopWindowXamlSource
	_windowsXamlManager = WindowsXamlManager::InitializeForCurrentThread();
}

void Sample::Uninitialise()
{
	_windowsXamlManager = nullptr;

	// No longer required with WinRT 2.0
	//uninit_apartment();
}

void Sample::OnWindowCreated()
{
	// Create the Xaml Island, and attach it to the main window's HWND.
	// The Xaml Island will be created as a child HWND.
	_xamlSource = {};

	auto xamlSourceNative = _xamlSource.as<IDesktopWindowXamlSourceNative>();
	check_hresult(xamlSourceNative->AttachToWindow(_hWnd));
	check_hresult(xamlSourceNative->get_WindowHandle(&_hWndXaml));

	LayoutXaml();
	SetWindowPos(_hWndXaml, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void Sample::OnWindowDestroyed()
{
	_xamlSource = nullptr;
}

void Sample::OnWindowResized()
{
	LayoutXaml();
}

// Returns true to allow further processing via TranslateMessage / DispatchMessage
bool Sample::PreTranslateMessage(MSG &msg)
{
	if (!_xamlSource)
		return true;

	auto xamlSourceNative = _xamlSource.as<IDesktopWindowXamlSourceNative2>();

	BOOL processed = FALSE;
	check_hresult(xamlSourceNative->PreTranslateMessage(&msg, &processed));
	return !processed;
}

RECT Sample::GetXamlRect() const
{
	RECT rect = {};
	GetClientRect(_hWnd, &rect);
	return rect;
}

void Sample::SetXamlContent(const UIElement &value)
{
	_xamlSource.Content(value);
}

void Sample::LayoutXaml()
{
	if (_hWndXaml)
	{
		const RECT rect = GetXamlRect();
		SetWindowPos(_hWndXaml, nullptr, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
	}
}
