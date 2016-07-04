
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
##    設定を書き込んだファイルを生成。
##

configure_file (
"${SOURCE_INCLUDE_DIR}/.Config/ConfiguredFairyShogi.h.in"
"${BINARY_INCLUDE_DIR}/.Config/ConfiguredFairyShogi.h")

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

