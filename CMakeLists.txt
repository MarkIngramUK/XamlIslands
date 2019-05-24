cmake_minimum_required(
	VERSION
		3.9.0 # Arbitrary version...
)

if (NOT WIN32)

	message(FATAL_ERROR "Unsupported platform!")

endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

project(XamlIslands
	LANGUAGES
		CXX
	VERSION
		1.0.0.0
)

add_subdirectory(HelloXaml)
add_subdirectory(FilePicker)
