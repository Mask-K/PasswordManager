cmake_minimum_required(VERSION 3.16)

project(PasswordManager VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(OpenSSL 1.1 REQUIRED)

qt_standard_project_setup()

qt_add_executable(appPasswordManager
    main.cpp
)

qt_add_qml_module(appPasswordManager
    URI PasswordManager
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES utils/saltGenerator.h
    SOURCES PasswordInfo.h
    SOURCES manager/passwordManager.h manager/passwordManager.cpp
    SOURCES authenticator/userAuthenticator.h authenticator/userAuthenticator.cpp
    SOURCES filemanager/fileManager.h filemanager/fileManager.cpp
    SOURCES utils/sha-256.h
    SOURCES encryption/Encryption.h
    SOURCES encryption/aesEncryption.h encryption/aesEncryption.cpp
    SOURCES utils/encryptionKeyGenerator.h
    SOURCES utils/constants.h
    QML_FILES PasswordsView.qml
    QML_FILES Menu.qml
    SOURCES
)

target_include_directories(appPasswordManager PRIVATE ${CMAKE_SOURCE_DIR}/utils)
target_include_directories(appPasswordManager PRIVATE ${CMAKE_SOURCE_DIR}/manager)
target_include_directories(appPasswordManager PRIVATE ${CMAKE_SOURCE_DIR}/authenticator)
target_include_directories(appPasswordManager PRIVATE ${CMAKE_SOURCE_DIR}/filemanager)
target_include_directories(appPasswordManager PRIVATE ${CMAKE_SOURCE_DIR}/encryption)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPasswordManager PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPasswordManager
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPasswordManager
    PRIVATE Qt6::Quick
    PUBLIC OpenSSL::Crypto
)

include(GNUInstallDirs)
install(TARGETS appPasswordManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
