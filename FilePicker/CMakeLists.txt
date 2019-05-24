add_executable(FilePicker WIN32
	../Common/Sample.cpp
	../Common/Sample.hpp
	../Common/WinMain.cpp
	../Common/XamlIslands.manifest
	FilePicker.cpp
)

target_compile_options(FilePicker
	PRIVATE
		/await
)

target_compile_definitions(FilePicker
	PRIVATE
		_UNICODE=1
		UNICODE=1
)

target_link_libraries(FilePicker
	PRIVATE
		WindowsApp.lib
)
