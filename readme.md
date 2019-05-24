# Xaml Islands

This repository contains example projects that demonstrate the use of Xaml Islands in a Win32 application.

## Requirements

* Windows 10 1903
* Windows 10 1903 SDK (10.0.18362.0)
* Visual Studio 2019

## Projects

* HelloXaml - A minimal example showing how to connect a Xaml Island to a Win32 HWND. A CMake project is included in order to demonstrate that no special vcxproj settings are required (it's just regular C++).
* FilePicker - Demonstrates how to use FileOpenPicker in a Win32 application (via IInitializeWithWindow).