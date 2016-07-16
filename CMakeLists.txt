
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##
##    要求するツールのバージョンを指定する。
##

cmake_minimum_required (VERSION  3.0.2)

##
##    パッケージの情報を指定する。
##

project (FairyShogi)
set (serial  "0.0.0")

##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

option (ENABLE_WIN32  "Enable Win32 API."  OFF)

set (CMAKE_C_FLAGS    "-std=c++11")
set (CMAKE_CXX_FLAGS  "-std=c++11")
set (FSHOGI_INCLUDE_DIR  "Include/FairyShogi")
set (SOURCE_INCLUDE_DIR  "${PROJECT_SOURCE_DIR}/${FSHOGI_INCLUDE_DIR}")
set (BINARY_INCLUDE_DIR  "${PROJECT_BINARY_DIR}/${FSHOGI_INCLUDE_DIR}")

##
##    Project Name Space.
##

set (FAIRYSHOGI_CNF_NAMESPACE  fairyshogi_ns)

if ( ENABLE_WIN32 )
  set (FAIRYSHOGI_CNF_WIN32_API  1)
else()
  set (FAIRYSHOGI_CNF_WIN32_API  0)
endif()

##
##    Check Header Files.
##

include (CheckIncludeFiles)
check_include_files (stdint.h  HAVE_STDINT_H)

##
##    Check Types.
##

include (CheckTypeSize)

check_type_size (uint8_t  UINT8_T)
if (HAVE_UINT8_T)
  set (FAIRYSHOGI_CNF_UINT8_T  uint8_t)
else()
  if (MSVC OR BORLAND)
    set (uint8_t  "unsigned char")
  endif()
  set (FAIRYSHOGI_CNF_UINT8_T  ${uint8_t})
  message ("Set uint8_t : ${uint8_t}")
endif()

check_type_size (uint32_t  UINT32_T)
if (HAVE_UINT32_T)
  set (FAIRYSHOGI_CNF_UINT32_T  uint32_t)
else()
  if (MSVC OR BORLAND)
    set (uint32_t  "unsigned int")
  endif()
  set (FAIRYSHOGI_CNF_UINT32_T  ${uint32_t})
  message ("Set uint32_t : ${uint32_t}")
endif()

##
##    Check Compiler Features.
##

include (${PROJECT_SOURCE_DIR}/CheckConstExpr.cmake)
if ( CNF_CXX_CONSTEXPR_ENABLED )
  set (FAIRYSHOGI_CNF_CONSTEXPR  1)
else()
  set (FAIRYSHOGI_CNF_CONSTEXPR  0)
endif()

include (${PROJECT_SOURCE_DIR}/CheckOverride.cmake)
if ( CNF_CXX_OVERRIDE_ENABLED )
  set (FAIRYSHOGI_CNF_OVERRIDE  1)
else()
  set (FAIRYSHOGI_CNF_OVERRIDE  0)
endif()

##----------------------------------------------------------------
##
##    設定を書き込んだファイルを生成。
##

set (FAIRYSHOGI_CNF_EXTRA  1)

configure_file (
"${SOURCE_INCLUDE_DIR}/.Config/ConfiguredFairyShogi.h.in"
"${BINARY_INCLUDE_DIR}/.Config/ConfiguredFairyShogi.h")

configure_file (
"${SOURCE_INCLUDE_DIR}/.Config/ExtraConfig.h.cmake.in"
"${BINARY_INCLUDE_DIR}/.Config/ExtraConfig.h")

##
##    インクルードパスの設定。
##

include_directories ("${PROJECT_SOURCE_DIR}/Include")
include_directories ("${PROJECT_BINARY_DIR}/Include")

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

add_subdirectory (Lib)
add_subdirectory (Bin)

