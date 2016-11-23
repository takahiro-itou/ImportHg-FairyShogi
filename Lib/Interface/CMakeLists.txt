
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "Interface")
Set (MODULE_OUTPUT_NAME    "Interface")
Set (MODULE_TITLE          "Interface")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
        ConsoleInterface.cpp
        GameController.cpp
        GraphicalInterface.cpp
        PixelMatrix.cpp
)

Set (INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/ConsoleInterface.h
        ${INCLIB_SOURCE_DIR}/GameController.h
        ${INCLIB_SOURCE_DIR}/GraphicalInterface.h
        ${INCLIB_SOURCE_DIR}/PixelMatrix.h
)

Set (MODULE_NEEDS_LIBRARIES
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}Engine
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


add_library(fsgInterface  ${LIBRARY_SOURCE_FILES})

