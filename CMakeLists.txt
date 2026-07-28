cmake_minimum_required(VERSION 3.19)
project(HardwareTestExecutive LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(HardwareTestExecutive
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    Tests/basetest.h Tests/basetest.cpp
    Tests/rs422test.h Tests/rs422test.cpp
    Tests/cmemorytest.h Tests/cmemorytest.cpp
    Managers/CTestmanager.h Managers/CTestmanager.cpp
    Utilities/CLogger.h Utilities/CLogger.cpp
    Tests/testresult.h
)

target_link_libraries(HardwareTestExecutive
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS HardwareTestExecutive
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET HardwareTestExecutive
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
