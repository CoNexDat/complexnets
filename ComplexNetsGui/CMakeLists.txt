find_package(Qt5Widgets REQUIRED)

aux_source_directory(inc SRC_LIST)

file(GLOB HEADERS "**/*.h")

set(SOURCE_FILES
  ./inc/GnuplotConsole.h
  ./inc/GrapherUtils.h
  ./inc/GraphLoadingValidationDialog.h
  ./inc/LogBinningPolicy.h
  ./inc/mainwindow.h
  ./src/ui_mainwindow.h
  ./src/GnuplotConsole.cpp
  ./src/GraphLoadingValidationDialog.cpp
  ./src/main.cpp
  ./src/mainwindow.cpp
)

set(RESOURCE_FILES complexnets.qrc)

add_executable(${PROJECT_NAME} ${OS_BUNDLE}
  ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} ComplexNets ComplexNetsCmd Qt5::Core Qt5::Widgets)
