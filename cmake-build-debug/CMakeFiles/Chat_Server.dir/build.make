# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\chryc\Desktop\CLion Projects\Chat-Server"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\Chat_Server.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Chat_Server.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Chat_Server.dir\flags.make

CMakeFiles\Chat_Server.dir\main.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chat_Server.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\main.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\main.cpp"
<<

CMakeFiles\Chat_Server.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\main.cpp"
<<

CMakeFiles\Chat_Server.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\main.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\main.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Server.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\Socket\Server.cpp.obj: ..\Socket\Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Chat_Server.dir/Socket/Server.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\Socket\Server.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Server.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/Socket/Server.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\Socket\Server.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Server.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/Socket/Server.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\Socket\Server.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Server.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Client.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\Socket\Client.cpp.obj: ..\Socket\Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Chat_Server.dir/Socket/Client.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\Socket\Client.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Client.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/Socket/Client.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\Socket\Client.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Client.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/Socket/Client.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\Socket\Client.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Client.cpp"
<<

CMakeFiles\Chat_Server.dir\Utils\base64.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\Utils\base64.cpp.obj: ..\Utils\base64.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Chat_Server.dir/Utils/base64.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\Utils\base64.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Utils\base64.cpp"
<<

CMakeFiles\Chat_Server.dir\Utils\base64.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/Utils/base64.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\Utils\base64.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Utils\base64.cpp"
<<

CMakeFiles\Chat_Server.dir\Utils\base64.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/Utils/base64.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\Utils\base64.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Utils\base64.cpp"
<<

CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.obj: ..\Database\mongodb.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Chat_Server.dir/Database/mongodb.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\Database\mongodb.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Database\mongodb.cpp"
<<

CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/Database/mongodb.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Database\mongodb.cpp"
<<

CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/Database/mongodb.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\Database\mongodb.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Database\mongodb.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.obj: ..\Socket\Security\Crypto.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Chat_Server.dir/Socket/Security/Crypto.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Security\Crypto.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/Socket/Security/Crypto.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Security\Crypto.cpp"
<<

CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/Socket/Security/Crypto.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Socket\Security\Crypto.cpp"
<<

CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.obj: ..\core\Dispatcher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Chat_Server.dir/core/Dispatcher.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\core\Dispatcher.cpp"
<<

CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/core/Dispatcher.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\core\Dispatcher.cpp"
<<

CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/core/Dispatcher.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\core\Dispatcher.cpp"
<<

CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.obj: CMakeFiles\Chat_Server.dir\flags.make
CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.obj: ..\Database\MediaManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Chat_Server.dir/Database/MediaManager.cpp.obj"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.obj /FdCMakeFiles\Chat_Server.dir\ /FS -c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Database\MediaManager.cpp"
<<

CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chat_Server.dir/Database/MediaManager.cpp.i"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe > CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Database\MediaManager.cpp"
<<

CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chat_Server.dir/Database/MediaManager.cpp.s"
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.s /c "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\Database\MediaManager.cpp"
<<

# Object files for target Chat_Server
Chat_Server_OBJECTS = \
"CMakeFiles\Chat_Server.dir\main.cpp.obj" \
"CMakeFiles\Chat_Server.dir\Socket\Server.cpp.obj" \
"CMakeFiles\Chat_Server.dir\Socket\Client.cpp.obj" \
"CMakeFiles\Chat_Server.dir\Utils\base64.cpp.obj" \
"CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.obj" \
"CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.obj" \
"CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.obj" \
"CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.obj"

# External object files for target Chat_Server
Chat_Server_EXTERNAL_OBJECTS =

Chat_Server.exe: CMakeFiles\Chat_Server.dir\main.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\Socket\Server.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\Socket\Client.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\Utils\base64.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\Database\mongodb.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\Socket\Security\Crypto.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\core\Dispatcher.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\Database\MediaManager.cpp.obj
Chat_Server.exe: CMakeFiles\Chat_Server.dir\build.make
Chat_Server.exe: C:\vcpkg-2019.11\installed\x86-windows\debug\lib\mongocxx.lib
Chat_Server.exe: C:\vcpkg-2019.11\installed\x86-windows\debug\lib\bsoncxx.lib
Chat_Server.exe: C:\vcpkg-2019.11\installed\x86-windows\debug\lib\ssleay32.lib
Chat_Server.exe: C:\vcpkg-2019.11\installed\x86-windows\debug\lib\libeay32.lib
Chat_Server.exe: CMakeFiles\Chat_Server.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Chat_Server.exe"
	"C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Chat_Server.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1424~1.283\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Chat_Server.dir\objects1.rsp @<<
 /out:Chat_Server.exe /implib:Chat_Server.lib /pdb:"C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\Chat_Server.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console C:\vcpkg-2019.11\installed\x86-windows\debug\lib\mongocxx.lib C:\vcpkg-2019.11\installed\x86-windows\debug\lib\bsoncxx.lib C:\vcpkg-2019.11\installed\x86-windows\debug\lib\ssleay32.lib C:\vcpkg-2019.11\installed\x86-windows\debug\lib\libeay32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	powershell -noprofile -executionpolicy Bypass -file C:/vcpkg-2019.11/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary "C:/Users/chryc/Desktop/CLion Projects/Chat-Server/cmake-build-debug/Chat_Server.exe" -installedDir C:/vcpkg-2019.11/installed/x86-windows/debug/bin -OutVariable out

# Rule to build all files generated by this target.
CMakeFiles\Chat_Server.dir\build: Chat_Server.exe

.PHONY : CMakeFiles\Chat_Server.dir\build

CMakeFiles\Chat_Server.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Chat_Server.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Chat_Server.dir\clean

CMakeFiles\Chat_Server.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\chryc\Desktop\CLion Projects\Chat-Server" "C:\Users\chryc\Desktop\CLion Projects\Chat-Server" "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug" "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug" "C:\Users\chryc\Desktop\CLion Projects\Chat-Server\cmake-build-debug\CMakeFiles\Chat_Server.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\Chat_Server.dir\depend

