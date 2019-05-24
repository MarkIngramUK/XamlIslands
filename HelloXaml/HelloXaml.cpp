#include "../Common/Sample.hpp"

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;

class HelloXaml : public Sample
{
public:
	virtual std::wstring_view GetName() const { return L"HelloXaml"; }

	virtual void OnWindowCreated() override;
};

void HelloXaml::OnWindowCreated()
{
	Sample::OnWindowCreated();

	Grid grid;
	grid.Background(SolidColorBrush({ 255, 0, 0, 255 }));

	TextBlock text;
	text.Text(L"Hello Xaml!");
	text.HorizontalAlignment(HorizontalAlignment::Center);
	text.VerticalAlignment(VerticalAlignment::Center);
	
	grid.Children().Append(text);

	SetXamlContent(grid);
}

std::unique_ptr<Sample> CreateSample()
{
	return std::make_unique<HelloXaml>();
}
