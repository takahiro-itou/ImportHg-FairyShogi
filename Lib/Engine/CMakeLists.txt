
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "Engine")
Set (MODULE_OUTPUT_NAME    "Engine")
Set (MODULE_TITLE          "Engine")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
        EngineBase.cpp
        EngineImplements.cpp
        EngineLevel0.cpp
        EngineLevel1.cpp
        EngineLevel2.cpp
        EngineLevel3.cpp
        EngineLevel4.cpp
)

Set (INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/EngineBase.h
)

Set (MODULE_NEEDS_LIBRARIES
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}Game
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

Add_Library(fsgEngine  ${LIBRARY_SOURCE_FILES})

