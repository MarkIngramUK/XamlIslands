add_executable(HelloXaml WIN32
	../Common/Sample.cpp
	../Common/Sample.hpp
	../Common/WinMain.cpp
	../Common/XamlIslands.manifest
	HelloXaml.cpp
)

target_compile_definitions(HelloXaml
	PRIVATE
		_UNICODE=1
		UNICODE=1
)

target_link_libraries(HelloXaml
	PRIVATE
		WindowsApp.lib
)
