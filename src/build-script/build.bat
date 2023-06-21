cmake.exe ^
-DCMAKE_CXX_FLAGS="/EHsc /DWINVER=0x0600 /EHsc /D_WIN32_WINNT=0x0600 -DBOOST_USE_WINAPI_VERSION=0x0600" ^
-DCMAKE_CXX_FLAGS_DEBUG="/EHsc /Zi /DDEBUG /DWINVER=0x0600 /EHsc /D_WIN32_WINNT=0x0600 -DBOOST_USE_WINAPI_VERSION=0x0600" ^
-DCMAKE_CXX_FLAGS_RELEASE="/EHsc /O2 /DNDEBUG /DWINVER=0x0600 /EHsc /D_WIN32_WINNT=0x0600 -DBOOST_USE_WINAPI_VERSION=0x0600" ^
-DCMAKE_EXE_LINKER_FLAGS="/machine:amd64 /subsystem:console,6.00 /version:6.00 /RELEASE" ^
-DCMAKE_SHARED_LINKER_FLAGS="/machine:amd64 /subsystem:console,6.00 /version:6.00 /RELEASE" ^
-DCMAKE_MODULE_LINKER_FLAGS="/machine:amd64 /subsystem:console,6.00" ^
-DCMAKE_STATIC_LINKER_FLAGS="/machine:amd64 /subsystem:console,6.00" ^
-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL ^
-DCMAKE_INSTALL_PREFIX=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows ^
-DPThreads4W_INCLUDE_DIR=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows/include ^
-DPThreads4W_LIBRARY=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows/lib ^
-DPThreads4W_CXXEXC_LIBRARY=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows/bin ^
-DPThreads4W_STRUCTEXC_LIBRARY=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows/bin ^
-DPThreads4W_DLL_DIR=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows/bin ^
-DPThreads4W_DEBUG_DLL_DIR=C:/Users/xtwxy/github/Microsoft/vcpkg/installed/x64-windows/debug/bin ^
..

