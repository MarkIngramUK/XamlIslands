#include "../Common/Sample.hpp"

#include <winrt/Windows.Storage.Pickers.h>

using namespace winrt;
//using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Pickers;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;

using winrt::Windows::Foundation::IAsyncAction;
using winrt::Windows::Foundation::IInspectable;

class FilePicker : public Sample
{
public:
	virtual std::wstring_view GetName() const { return L"FilePicker"; }

	virtual void OnWindowCreated() override;

private:
	void pickerButton_Click(const IInspectable &sender, const RoutedEventArgs &eventArgs);

	IAsyncAction PickFileAsync();

	TextBox _textBox = nullptr;
};

void FilePicker::OnWindowCreated()
{
	Sample::OnWindowCreated();

	Button pickerButton;
	pickerButton.Content(box_value(L"FileOpenPicker"));
	pickerButton.HorizontalAlignment(HorizontalAlignment::Center);
	pickerButton.Click(RoutedEventHandler(this, &FilePicker::pickerButton_Click));
	
	Border spacer;
	spacer.Height(20.0);

	_textBox = {};
	_textBox.IsReadOnly(true);
	_textBox.Height(250.0);
	_textBox.Width(250.0);
	_textBox.TextWrapping(TextWrapping::Wrap);

	StackPanel verticalPanel;
	verticalPanel.Orientation(Orientation::Vertical);
	verticalPanel.HorizontalAlignment(HorizontalAlignment::Center);
	verticalPanel.VerticalAlignment(VerticalAlignment::Center);
	verticalPanel.Children().Append(pickerButton);
	verticalPanel.Children().Append(spacer);
	verticalPanel.Children().Append(_textBox);

	Grid grid;
	grid.Background(SolidColorBrush({ 255, 0, 0, 255 }));
	grid.Children().Append(verticalPanel);

	SetXamlContent(grid);
}

void FilePicker::pickerButton_Click(const IInspectable& sender, const RoutedEventArgs& eventArgs)
{
	static_cast<void>(PickFileAsync());
}

IAsyncAction FilePicker::PickFileAsync()
{
	FileOpenPicker picker;
	picker.as<IInitializeWithWindow>()->Initialize(_hWnd);
	picker.FileTypeFilter().Append(L".txt");

	StorageFile file = co_await picker.PickSingleFileAsync();

	if (!file)
		co_return;

	hstring fileContents = co_await FileIO::ReadTextAsync(file);
	co_await resume_foreground(_textBox.Dispatcher());
	
	_textBox.Text(fileContents);

	co_return;
}

std::unique_ptr<Sample> CreateSample()
{
	return std::make_unique<FilePicker>();
}
