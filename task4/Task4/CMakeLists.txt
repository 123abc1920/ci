cmake_minimum_required(VERSION 3.16)

project(Task4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Task4
    main.cpp
    ui/view/mainwindow/mainwindow.cpp
    ui/view/mainwindow/mainwindow.h
    ui/view/mainwindow/mainwindow.ui

    service/FileReader.cpp
    service/FileReader.h
    service/Logger.cpp
    service/Logger.h

    repository/InMemoryRepository.cpp
    repository/InMemoryRepository.h

    model/Student.h
    model/Student.cpp
    model/Query.cpp
    model/Query.h
)

target_link_libraries(Task4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Task4 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Task4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
