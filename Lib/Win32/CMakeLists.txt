
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "Win32")
Set (MODULE_OUTPUT_NAME    "Win32")
Set (MODULE_TITLE          "Win32")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
        Animation.cpp
        BitmapImage.cpp
        BitmapResource.cpp
        DialogWindow.cpp
        MatchDialog.cpp
)

Set (INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/Animation.h
        ${INCLIB_SOURCE_DIR}/BitmapImage.h
        ${INCLIB_SOURCE_DIR}/BitmapResource.h
        ${INCLIB_SOURCE_DIR}/CommonResources.h
        ${INCLIB_SOURCE_DIR}/CommonResources.rc
        ${INCLIB_SOURCE_DIR}/DialogWindow.h
        ${INCLIB_SOURCE_DIR}/MatchDialog.h
)

Set (MODULE_NEEDS_LIBRARIES
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${COMMON_CMAKE_DIR}/BuildLibraryCommon.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

Add_SubDirectory (Tests)

