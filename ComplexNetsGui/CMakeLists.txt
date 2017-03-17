aux_source_directory(inc SRC_LIST)

include_directories(BEFORE ..)

file(GLOB HEADERS "**/*.h")

add_executable(complexnetspp MACOSX_BUNDLE
  ./inc/GnuplotConsole.h
  ./inc/GrapherUtils.h
  ./inc/GraphLoadingValidationDialog.h
  ./inc/LogBinningPolicy.h
  ./inc/mainwindow.h
  ./inc/ui_mainwindow.h
  ./src/GnuplotConsole.cpp
  ./src/GraphLoadingValidationDialog.cpp
  ./src/main.cpp
  ./src/mainwindow.cpp
)

qt5_use_modules(complexnetspp Core Widgets)

target_link_libraries(complexnetspp ComplexNets ComplexNetsCmd)

#if(APPLE)
#  include(cmake/modules/DeployQt5.cmake)
#  install_qt5_executable(ComplexNetsPP)
#endif()
