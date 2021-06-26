CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0 FATAL_ERROR)
PROJECT(freeglut)

# setup version numbers
# TODO: Update these for each release!
set(VERSION_MAJOR 3)
set(VERSION_MINOR 2)
set(VERSION_PATCH 1)
set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

# Update fg_version.h to match the versions number here in cmake
CONFIGURE_FILE(src/fg_version.h.in src/fg_version.h)

# shared lib version numbers (change before release)
set(SO_MAJOR 3)		# increment on backwards incompatible API/ABI changes
set(SO_MINOR 11)	# increment on backwards compatible or internal changes
set(SO_REV 0)		# if nothing else changed increment this

# FREEGLUT_BUILD_SHARED_LIBS is already a standard CMake variable, but we need to
# re-declare it here so it will show up in the GUI.
# by default, we want to build both
OPTION(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." ON)
OPTION(FREEGLUT_BUILD_STATIC_LIBS "Build FreeGLUT static library." OFF)

# option for whether warnings and errors should be printed
OPTION(FREEGLUT_PRINT_ERRORS "Lib prints errors to stderr" ON)
#MARK_AS_ADVANCED(FREEGLUT_PRINT_ERRORS)
OPTION(FREEGLUT_PRINT_WARNINGS "Lib prints warnings to stderr" ON)
#MARK_AS_ADVANCED(FREEGLUT_PRINT_WARNINGS)

# OpenGL ES support
OPTION(FREEGLUT_GLES "Use OpenGL ES (requires EGL)" OFF)

# option to build either as "glut" (ON) or "freeglut" (OFF)
IF(WIN32)
    OPTION(FREEGLUT_REPLACE_GLUT "Be a replacement for GLUT" OFF)
ELSE()
    OPTION(FREEGLUT_REPLACE_GLUT "Be a replacement for GLUT" ON)
ENDIF()

IF(NOT WIN32)
    # Wayland support
    OPTION(FREEGLUT_WAYLAND "Use Wayland (no X11)" OFF)
ENDIF()


SET(FREEGLUT_HEADERS
    include/GL/freeglut.h
    include/GL/freeglut_ucall.h
    include/GL/freeglut_ext.h
    include/GL/freeglut_std.h
)
IF(FREEGLUT_REPLACE_GLUT)
    LIST(APPEND FREEGLUT_HEADERS
        include/GL/glut.h
    )
ENDIF()
SET(FREEGLUT_SRCS
    ${FREEGLUT_HEADERS}
    src/fg_callbacks.c
    src/fg_cursor.c
    src/fg_display.c
    src/fg_ext.c
    src/fg_font_data.c
    src/fg_gamemode.c
    src/fg_geometry.c
    src/fg_gl2.c
    src/fg_gl2.h
    src/fg_init.c
    src/fg_init.h
    src/fg_internal.h
    src/fg_callback_macros.h
    src/fg_input_devices.c
    src/fg_joystick.c
    src/fg_main.c
    src/fg_misc.c
    src/fg_overlay.c
    src/fg_spaceball.c
    src/fg_state.c
    src/fg_stroke_mono_roman.c
    src/fg_stroke_roman.c
    src/fg_structure.c
    src/fg_teapot.c
    src/fg_teapot_data.h
    src/fg_videoresize.c
    src/fg_window.c
)
# TODO: OpenGL ES requires a compatible version of these files:
IF(NOT FREEGLUT_GLES)
    LIST(APPEND FREEGLUT_SRCS
        src/fg_font.c
        src/fg_menu.c
    )
ELSE()
    LIST(APPEND FREEGLUT_SRCS
        src/gles_stubs.c
    )
ENDIF()

IF(WIN32)
    LIST(APPEND FREEGLUT_SRCS
        src/mswin/fg_cursor_mswin.c
        src/mswin/fg_display_mswin.c
        src/mswin/fg_ext_mswin.c
        src/mswin/fg_gamemode_mswin.c
        src/mswin/fg_init_mswin.c
        src/mswin/fg_internal_mswin.h
        src/mswin/fg_input_devices_mswin.c
        src/mswin/fg_joystick_mswin.c
        src/mswin/fg_main_mswin.c
        src/mswin/fg_menu_mswin.c
        src/mswin/fg_spaceball_mswin.c
        src/mswin/fg_state_mswin.c
        src/mswin/fg_structure_mswin.c
        src/mswin/fg_window_mswin.c
        ${CMAKE_BINARY_DIR}/freeglut.rc # generated below from freeglut.rc.in
    )
    IF (MSVC AND NOT CMAKE_CL_64)
        # .def file only for 32bit Windows builds (TODO: MSVC only right
        # now, needed for any other Windows platform?)
        LIST(APPEND FREEGLUT_SRCS
            ${CMAKE_BINARY_DIR}/freeglutdll.def # generated below from src/freeglutdll.def.in
        )
    ENDIF()

ELSE()
    # UNIX (Wayland)
    IF(FREEGLUT_WAYLAND)
        LIST(APPEND FREEGLUT_SRCS
            src/wayland/fg_cursor_wl.c
            src/wayland/fg_ext_wl.c
            src/wayland/fg_gamemode_wl.c
            src/wayland/fg_init_wl.c
            src/wayland/fg_internal_wl.h
            src/wayland/fg_input_devices_wl.c
            src/wayland/fg_main_wl.c
            src/wayland/fg_state_wl.c
            src/wayland/fg_structure_wl.c
            src/wayland/fg_window_wl.c
            # font, serial port & joystick code are agnostic
            src/x11/fg_glutfont_definitions_x11.c
            src/x11/fg_input_devices_x11.c
            src/x11/fg_joystick_x11.c
        )
    # UNIX (X11)
    ELSE()
        LIST(APPEND FREEGLUT_SRCS
            src/x11/fg_cursor_x11.c
            src/x11/fg_ext_x11.c
            src/x11/fg_gamemode_x11.c
            src/x11/fg_glutfont_definitions_x11.c
            src/x11/fg_init_x11.c
            src/x11/fg_internal_x11.h
            src/x11/fg_input_devices_x11.c
            src/x11/fg_joystick_x11.c
            src/x11/fg_main_x11.c
            src/x11/fg_menu_x11.c
            src/x11/fg_spaceball_x11.c
            src/x11/fg_state_x11.c
            src/x11/fg_structure_x11.c
            src/x11/fg_window_x11.c
            src/x11/fg_xinput_x11.c
        )
        IF(NOT(FREEGLUT_GLES))
            LIST(APPEND FREEGLUT_SRCS
                src/x11/fg_internal_x11_glx.h
                src/x11/fg_display_x11_glx.c
                src/x11/fg_state_x11_glx.c
                src/x11/fg_state_x11_glx.h
                src/x11/fg_window_x11_glx.c
                src/x11/fg_window_x11_glx.h
            )
        ENDIF()
    ENDIF()
ENDIF()

# OpenGL ES requires EGL, and so does Wayland
IF(FREEGLUT_GLES OR FREEGLUT_WAYLAND)
    LIST(APPEND FREEGLUT_SRCS
        src/egl/fg_internal_egl.h
        src/egl/fg_display_egl.c
        src/egl/fg_ext_egl.c
        src/egl/fg_init_egl.c
        src/egl/fg_init_egl.h
        src/egl/fg_state_egl.c
        src/egl/fg_state_egl.h
        src/egl/fg_structure_egl.c
        src/egl/fg_structure_egl.h
        src/egl/fg_window_egl.c
        src/egl/fg_window_egl.h
    )
ENDIF()

# For OpenGL ES (GLES): compile with -DFREEGLUT_GLES to cleanly
# bootstrap headers inclusion in freeglut_std.h; this constant also
# need to be defined in client applications (e.g. through pkg-config),
# but do use GLES constants directly for all other needs
# GLES1 and GLES2 libraries are compatible and can be co-linked.
IF(FREEGLUT_GLES)
    LIST(APPEND PUBLIC_DEFINITIONS -DFREEGLUT_GLES)
    LIST(APPEND LIBS GLESv2 GLESv1_CM EGL)
ELSE()
  FIND_PACKAGE(OpenGL REQUIRED)
  LIST(APPEND LIBS ${OPENGL_gl_LIBRARY})
  INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ENDIF()

# For Wayland: compile with -DFREEGLUT_WAYLAND and pull EGL
IF(FREEGLUT_WAYLAND)
  ADD_DEFINITIONS(-DFREEGLUT_WAYLAND)
  LIST(APPEND LIBS wayland-client wayland-cursor wayland-egl EGL xkbcommon)
ENDIF()

# lib m for math, not needed on windows
IF (NOT WIN32)
    # For compilation:
    LIST(APPEND LIBS m)
    # For CHECK_FUNCTION_EXISTS:
    LIST(APPEND CMAKE_REQUIRED_LIBRARIES m)
ENDIF()

IF(WIN32)
    # hide insecure CRT warnings, common practice
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
    IF(MSVC)
        SET( CMAKE_DEBUG_POSTFIX "d" )
    ENDIF(MSVC)
    
    IF(NOT(MSVC_VERSION LESS "1600"))
    # minimum requirement for WM_TOUCH device
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0601)
        ADD_DEFINITIONS(-DWINVER=0x0601)
    ELSEIF(NOT(MSVC_VERSION LESS "1300"))
    # minimum requirement for spaceball device
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
        ADD_DEFINITIONS(-DWINVER=0x0501)
    ELSE()
    # enable the use of Win2000 APIs (needed for really old compilers like MSVC6)
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0500)
        ADD_DEFINITIONS(-DWINVER=0x0500)
    ENDIF()

ENDIF()

IF(CMAKE_COMPILER_IS_GNUCC)
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  IF(NOT(ANDROID OR BLACKBERRY OR FREEGLUT_WAYLAND))
    # not setting -ansi as EGL/KHR headers doesn't support it
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
  ENDIF()
ENDIF(CMAKE_COMPILER_IS_GNUCC)

INCLUDE(CheckIncludeFiles)
IF(UNIX AND NOT(ANDROID OR BLACKBERRY OR FREEGLUT_WAYLAND))
    FIND_PACKAGE(X11 REQUIRED)
    INCLUDE_DIRECTORIES(${X11_X11_INCLUDE_PATH})
    LIST(APPEND LIBS ${X11_X11_LIB})
    IF(X11_Xrandr_FOUND)
        SET(HAVE_X11_EXTENSIONS_XRANDR_H TRUE)
        LIST(APPEND LIBS ${X11_Xrandr_LIB})
    ENDIF()
    IF(X11_xf86vmode_FOUND)
        SET(HAVE_X11_EXTENSIONS_XF86VMODE_H TRUE)
        LIST(APPEND LIBS ${X11_Xxf86vm_LIB})
    ENDIF()
    IF(X11_Xinput_FOUND)
        # Needed for multi-touch:
        CHECK_INCLUDE_FILES("${X11_Xinput_INCLUDE_PATH}/X11/extensions/XInput2.h" HAVE_X11_EXTENSIONS_XINPUT2_H)
        LIST(APPEND LIBS ${X11_Xinput_LIB})
    ELSE()
        MESSAGE(FATAL_ERROR "Missing X11's XInput.h (X11/extensions/XInput.h)")
    ENDIF()
ENDIF()

INCLUDE(CheckFunctionExists)
INCLUDE(CheckTypeSize)
CHECK_INCLUDE_FILES(sys/types.h HAVE_SYS_TYPES_H)
CHECK_INCLUDE_FILES(unistd.h 	HAVE_UNISTD_H)
CHECK_INCLUDE_FILES(sys/time.h 	HAVE_SYS_TIME_H)
CHECK_INCLUDE_FILES(stdbool.h 	HAVE_STDBOOL_H)
CHECK_INCLUDE_FILES(sys/param.h HAVE_SYS_PARAM_H)
CHECK_INCLUDE_FILES(sys/ioctl.h HAVE_SYS_IOCTL_H)
CHECK_INCLUDE_FILES(fcntl.h 	HAVE_FCNTL_H)
CHECK_INCLUDE_FILES(usbhid.h 	HAVE_USBHID_H)
CHECK_FUNCTION_EXISTS(gettimeofday HAVE_GETTIMEOFDAY)
CHECK_FUNCTION_EXISTS(XParseGeometry   HAVE_XPARSEGEOMETRY)
IF (NOT HAVE_XPARSEGEOMETRY)
   LIST(APPEND FREEGLUT_SRCS
        src/util/xparsegeometry_repl.c
        src/util/xparsegeometry_repl.h)
   SET(NEED_XPARSEGEOMETRY_IMPL TRUE)
ENDIF()
# decide on suitable type for internal time keeping, 64-bit if possible
CHECK_INCLUDE_FILES(stdint.h    HAVE_STDINT_H)
CHECK_INCLUDE_FILES(inttypes.h  HAVE_INTTYPES_H)
IF (NOT (HAVE_STDINT_H OR HAVE_INTTYPES_H))
    IF (MSVC)
        # Some old Microsoft VC releases don't support unsigned long
        # long, but all we care about is support for unsigned __int64 on
        # MSVC, so test for presence of that type
        CHECK_TYPE_SIZE("unsigned __int64" U__INT64 BUILTIN_TYPES_ONLY)
    ELSEIF()
        CHECK_TYPE_SIZE("unsigned long long" ULONG_LONG BUILTIN_TYPES_ONLY)
    ENDIF()
ENDIF()

# The generated config.h is placed in the project's build directory, just to
# ensure that all CMake-generated files are kept away from the main source tree.
# As a result, the build directory must to be added to the include path list.
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_BINARY_DIR}/config.h)
INCLUDE_DIRECTORIES(BEFORE ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_DEFINITIONS(-DHAVE_CONFIG_H)
IF(WIN32)
    # we also have to generate freeglut.rc, which contains the version
    # number
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/freeglut.rc.in ${CMAKE_BINARY_DIR}/freeglut.rc)
    IF (MSVC AND NOT CMAKE_CL_64)
        # .def file only for 32bit Windows builds with Visual Studio
        CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/freeglutdll.def.in ${CMAKE_BINARY_DIR}/freeglutdll.def)
    ENDIF()
ENDIF()

IF(FREEGLUT_BUILD_SHARED_LIBS)
    ADD_LIBRARY(freeglut SHARED ${FREEGLUT_SRCS})
ENDIF()
IF(FREEGLUT_BUILD_STATIC_LIBS)
    ADD_LIBRARY(freeglut_static STATIC ${FREEGLUT_SRCS})
ENDIF()


SET(LIBNAME freeglut)
IF(WIN32)
    IF(FREEGLUT_REPLACE_GLUT)
        SET(LIBNAME glut)
    ENDIF()

    LIST(APPEND LIBS winmm)
    IF(FREEGLUT_BUILD_SHARED_LIBS)
        TARGET_COMPILE_DEFINITIONS(freeglut PRIVATE FREEGLUT_EXPORTS)
        SET_TARGET_PROPERTIES(freeglut PROPERTIES OUTPUT_NAME ${LIBNAME})
    ENDIF()
    IF(FREEGLUT_BUILD_STATIC_LIBS)
        TARGET_COMPILE_DEFINITIONS(freeglut_static PUBLIC FREEGLUT_STATIC)
        IF(FREEGLUT_REPLACE_GLUT)
            SET_TARGET_PROPERTIES(freeglut_static PROPERTIES OUTPUT_NAME ${LIBNAME})
        ENDIF()
        # need to set machine:x64 for linker, at least for VC10, and
        # doesn't hurt for older compilers:
        # http://public.kitware.com/Bug/view.php?id=11240#c22768
        IF (CMAKE_CL_64)
            SET_TARGET_PROPERTIES(freeglut_static PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
        ENDIF()
    ENDIF()
ELSE()
    # on UNIX we need to make sure:
    # - all shared libraries must have a soname/version, see :
    #   http://sourceware.org/autobook/autobook/autobook_91.html#SEC91
    #   http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
    #   Current: -version-info 12:0:9 -> 3.9.0
    #   Note: most platforms now prefer the latter major.minor.revision form
    #   (e.g. FreeBSD, cf. http://debbugs.gnu.org/cgi/bugreport.cgi?bug=8765),
    #   or special-cased FreeGLUT long ago (e.g. .so.4 on OpenBSD), so
    #   the lack of support for current:revision:age in CMake should
    #   not be a problem.
    # - the output library should be named glut so it'll be linkable with -lglut
    #   (unless FREEGLUT_REPLACE_GLUT is false).
    # - the shared library should link to the dependency libraries so that the user
    #   won't have to link them explicitly (they shouldn't have to know that we depend
    #   on Xrandr or Xxf86vm)
    IF(FREEGLUT_GLES)
        SET(LIBNAME freeglut-gles)
    ELSE()
        IF(FREEGLUT_REPLACE_GLUT)
            SET(LIBNAME glut)
        ENDIF()
    ENDIF()

    IF(FREEGLUT_BUILD_SHARED_LIBS)
      SET_TARGET_PROPERTIES(freeglut PROPERTIES VERSION ${SO_MAJOR}.${SO_MINOR}.${SO_REV} SOVERSION ${SO_MAJOR} OUTPUT_NAME ${LIBNAME})
    ENDIF()
    IF(FREEGLUT_BUILD_STATIC_LIBS)
      SET_TARGET_PROPERTIES(freeglut_static PROPERTIES OUTPUT_NAME ${LIBNAME})
    ENDIF()
ENDIF()
IF(FREEGLUT_BUILD_SHARED_LIBS)
    TARGET_LINK_LIBRARIES(freeglut ${LIBS})
    TARGET_COMPILE_DEFINITIONS(freeglut PUBLIC ${PUBLIC_DEFINITIONS})
ENDIF()
IF(FREEGLUT_BUILD_STATIC_LIBS)
    TARGET_LINK_LIBRARIES(freeglut_static ${LIBS})
    TARGET_COMPILE_DEFINITIONS(freeglut_static PUBLIC ${PUBLIC_DEFINITIONS})
ENDIF()
SET_TARGET_PROPERTIES(freeglut PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include)