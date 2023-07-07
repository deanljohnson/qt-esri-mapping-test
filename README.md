Installed "ArcGIS Runtime SDK for Qt" from https://developers.arcgis.com/downloads/#qt-runtime

Note that the "ArcGIS Maps SDK for Qt" is for Qt6 only

The file "ArcGISRuntime.cmake" in the installation seems to be broken (at least for windows x64).
- Open "C:\Program Files (x86)\ArcGIS SDKs\Qt100.15.2\sdk\ideintegration\ArcGISRuntime.cmake"
- Replace (line 63):
  x86_64 STREQUAL ${CMAKE_OSX_ARCHITECTURES} AND arm64 STREQUAL ${CMAKE_SYSTEM_PROCESSOR}
  with
  x86_64 STREQUAL "${CMAKE_OSX_ARCHITECTURES})" AND (arm64 STREQUAL ${CMAKE_SYSTEM_PROCESSOR})

The CMake find module provided with the installation is also broken. Instead, use the find
module included in this repo under the cmake folder.
