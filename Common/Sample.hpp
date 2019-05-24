#pragma once

#include <memory>
#include <string_view>

#include <Unknwn.h>
#undef GetCurrentTime
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Media.h>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Sample
{
public:
	virtual void Initialise();
	virtual void Uninitialise();

	virtual std::wstring_view GetName() const = 0;

	virtual void OnWindowCreated();
	virtual void OnWindowDestroyed();
	virtual void OnWindowResized();

	void SetHwnd(HWND hWnd) { _hWnd = hWnd; }
	bool PreTranslateMessage(MSG &msg);

protected:
	virtual RECT GetXamlRect() const;
	void SetXamlContent(const winrt::Windows::UI::Xaml::UIElement &value);

protected:
	HWND _hWnd = nullptr;
	HWND _hWndXaml = nullptr;

private:
	void LayoutXaml();

private:
	winrt::Windows::UI::Xaml::Hosting::WindowsXamlManager _windowsXamlManager = nullptr;
	winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource _xamlSource = nullptr;
};

std::unique_ptr<Sample> CreateSample();
