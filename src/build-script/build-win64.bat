set CMAKE_WINDOWS_KITS_10_DIR="C:/Program Files (x86)/Windows Kits/10"

cmake -G "NMake Makefiles" ^
-DCMAKE_C_FLAGS="/DWINVER=0x0502 /D_WIN32_WINNT=0x0502 -DBOOST_USE_WINAPI_VERSION=0x0502" ^
-DCMAKE_CXX_FLAGS="/DWINVER=0x0502 /EHsc /D_WIN32_WINNT=0x0502 -DBOOST_USE_WINAPI_VERSION=0x0502" ^
-DCMAKE_C_FLAGS_DEBUG="/Zi /DDEBUG" ^
-DCMAKE_CXX_FLAGS_DEBUG="/Zi /DDEBUG" ^
-DCMAKE_C_FLAGS_RELEASE="/O2 /DNDEBUG" ^
-DCMAKE_CXX_FLAGS_RELEASE="/O2 /DNDEBUG" ^
-DCMAKE_EXE_LINKER_FLAGS="/machine:amd64 /subsystem:console,5.02 /version:5.02 /RELEASE" ^
-DCMAKE_SHARED_LINKER_FLAGS="/machine:amd64 /subsystem:console,5.02 /version:5.02 /RELEASE" ^
-DCMAKE_MODULE_LINKER_FLAGS="/machine:amd64 /subsystem:console,5.02" ^
-DCMAKE_STATIC_LINKER_FLAGS="/machine:amd64 /subsystem:console,5.02" ^
-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL ^
-DCMAKE_INSTALL_PREFIX=C:/usr64 ^
-DCMAKE_BUILD_TYPE=Release ^
-DMSVC_TOOLSET_VERSION=140 ^
-DMSVC_REDIST_DIR="C:/Program Files (x86)/Microsoft Visual Studio 14.0/VC/redist" ^
-DENABLE_TESTS=ON ^
-DENABLE_VALGRIND=OFF ^
..

