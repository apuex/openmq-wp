cmake ^
-DCMAKE_C_FLAGS="/DWINVER=0x0501 /D_WIN32_WINNT=0x0501 -DBOOST_USE_WINAPI_VERSION=0x0501" ^
-DCMAKE_CXX_FLAGS="/DWINVER=0x0501 /EHsc /D_WIN32_WINNT=0x0501 -DBOOST_USE_WINAPI_VERSION=0x0501" ^
-DCMAKE_EXE_LINKER_FLAGS="/machine:x86 /subsystem:console,5.01 /version:5.01" ^
-DCMAKE_SHARED_LINKER_FLAGS="/machine:x86 /subsystem:console,5.01 /version:5.01" ^
-DCMAKE_MODULE_LINKER_FLAGS="/machine:x86 /subsystem:console,5.01" ^
-DCMAKE_STATIC_LINKER_FLAGS="/machine:x86 /subsystem:console,5.01" ^
-DCMAKE_INSTALL_PREFIX=E:/usr32 ^
-DENABLE_TESTS=ON ^
-DENABLE_VALGRIND=OFF ^
..

