
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

Set     (PROJECT_NAME      FairyShogi)
Set     (serial            "0.0.0")

Project (${PROJECT_NAME}   VERSION  1.0.0)

##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

Enable_Testing ()

Set (COMMON_CMAKE_DIR      "${PROJECT_SOURCE_DIR}/.CMake")
Set (INCTOP_DIR_NAME       "Include")
Set (LIBTOP_DIR_NAME       "Lib")
Set (INCPKG_DIR_NAME       "${PROJECT_NAME}")
Set (PACKAGE_INCLUDE_DIR   "${INCTOP_DIR_NAME}/${INCPKG_DIR_NAME}")

Set (INCTOP_SOURCE_DIR     "${PROJECT_SOURCE_DIR}/${INCTOP_DIR_NAME}")
Set (INCTOP_BINARY_DIR     "${PROJECT_BINARY_DIR}/${INCTOP_DIR_NAME}")
Set (LIBTOP_SOURCE_DIR     "${PROJECT_SOURCE_DIR}/${LIBTOP_DIR_NAME}")
Set (LIBTOP_BINARY_DIR     "${PROJECT_BINARY_DIR}/${LIBTOP_DIR_NAME}")

Set (INCLUDE_SOURCE_DIR    "${INCTOP_SOURCE_DIR}/${INCPKG_DIR_NAME}")
Set (INCLUDE_BINARY_DIR    "${INCTOP_BINARY_DIR}/${INCPKG_DIR_NAME}")


set (FSHOGI_INCLUDE_DIR  "Include/FairyShogi")

##----------------------------------------------------------------
##
##    ビルド環境の検査。
##

##
##    Check Compiler Features.
##

Include (${COMMON_CMAKE_DIR}/EnableCxx11.cmake)

Include (${COMMON_CMAKE_DIR}/CheckConstExpr.cmake)
Include (${COMMON_CMAKE_DIR}/CheckNullPtr.cmake)
Include (${COMMON_CMAKE_DIR}/CheckOverride.cmake)
Include (${COMMON_CMAKE_DIR}/CheckStaticAssert.cmake)

##
##    Check Target.
##

Option (ENABLE_WIN32  "Enable Win32 API."  ON)
If ( ENABLE_WIN32 )
  Set (FAIRYSHOGI_CNF_WIN32_API  1)
Else()
  Set (FAIRYSHOGI_CNF_WIN32_API  0)
EndIf()

##
##    Check Header Files.
##

Include (CheckIncludeFiles)
Check_Include_Files (stdint.h  HAVE_STDINT_H)

##
##    Check Types.
##

Include (${COMMON_CMAKE_DIR}/CheckStdInt.cmake)

##
##    Project Name Space.
##

Set (FAIRYSHOGI_CNF_NAMESPACE  fairyshogi_ns)

##----------------------------------------------------------------
##
##    インクルードパスの設定。
##

Include_Directories ("${PROJECT_SOURCE_DIR}/Include")
Include_Directories ("${PROJECT_BINARY_DIR}/Include")

##----------------------------------------------------------------
##
##    設定を書き込んだファイルを生成。
##

Set (FAIRYSHOGI_CNF_EXTRA  1)

Configure_File (
    "${INCLUDE_SOURCE_DIR}/.Config/ConfiguredFairyShogi.h.in"
    "${INCLUDE_BINARY_DIR}/.Config/ConfiguredFairyShogi.h"
)

Configure_File (
    "${INCLUDE_SOURCE_DIR}/.Config/ExtraConfig.h.cmake.in"
    "${INCLUDE_BINARY_DIR}/.Config/ExtraConfig.h"
)

##----------------------------------------------------------------
##
##    パッケージコンフィグレーション。
##

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

Add_SubDirectory (Lib)
Add_SubDirectory (Bin)

