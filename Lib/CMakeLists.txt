
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

add_subdirectory (Tests)
add_subdirectory (.Config)

add_subdirectory (Common)
add_subdirectory (Game)
add_subdirectory (Engine)
add_subdirectory (Interface)

if ( ENABLE_WIN32 )
  add_subdirectory (Win32)
endif()

