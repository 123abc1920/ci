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

    ui/view/studentwindow/studentwindow.cpp
    ui/view/studentwindow/studentwindow.h
    ui/view/studentwindow/studentwindow.ui

    ui/view/filterwindow/filterwindow.cpp
    ui/view/filterwindow/filterwindow.h
    ui/view/filterwindow/filterwindow.ui

    ui/view/resultwindow/resultwindow.cpp
    ui/view/resultwindow/resultwindow.h
    ui/view/resultwindow/resultwindow.ui

    viewmodel/MainViewModel.h
    viewmodel/MainViewModel.cpp
    viewmodel/StudentViewModel.h
    viewmodel/StudentViewModel.cpp
    viewmodel/FilterViewModel.h
    viewmodel/FilterViewModel.cpp
    viewmodel/ResultViewModel.h
    viewmodel/ResultViewModel.cpp

    service/FileReader.cpp
    service/FileReader.h
    service/Logger.cpp
    service/Logger.h

    repository/InMemoryRepository.cpp
    repository/InMemoryRepository.h
    repository/SubjectsRepository.cpp
    repository/SubjectsRepository.h

    model/Student.h
    model/Student.cpp
    model/Query.cpp
    model/Query.h
)

target_include_directories(Task4 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/service
    ${CMAKE_CURRENT_SOURCE_DIR}/repository
    ${CMAKE_CURRENT_SOURCE_DIR}/model
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/mainwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/studentwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/filterwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/ui/view/resultwindow
    ${CMAKE_CURRENT_SOURCE_DIR}/viewmodel
)

target_link_libraries(Task4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Task4 PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)

include(GNUInstallDirs)
install(TARGETS Task4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
