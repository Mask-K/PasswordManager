cmake_minimum_required(VERSION 3.5)

project(test_aes LANGUAGES CXX)

enable_testing()

find_package(Threads REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(OpenSSL 1.1 REQUIRED)

# Перевірка і налаштування Google Test і Google Mock
if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message(FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

set(CMAKE_AUTOMOC ON)

include_directories(${GTestIncludes}
    ../encryption
    ../utils
    ../filemanager
    ../authenticator
    ../manager
    ../
)


set(SOURCE_FILES
    main.cpp
    unitTests/tst_test_aes.cpp
    unitTests/tst_utils.cpp
    unitTests/tst_filemanager.cpp
    integrationTests/tst_auth.cpp
    integrationTests/tst_passowordmanager.cpp
    ../encryption/aesEncryption.cpp
    ../utils/constants.h
    ../utils/encryptionKeyGenerator.h
    ../utils/saltGenerator.h
    ../utils/sha-256.h
    ../filemanager/fileManager.cpp
    ../authenticator/userAuthenticator.cpp
    ../PasswordInfo.h
    ../manager/passwordManager.cpp
)

add_executable(test_aes ${SOURCE_FILES} ${GTestFiles})
add_test(NAME test_aes COMMAND test_aes)
target_link_libraries(test_aes PRIVATE
    Threads::Threads
    Qt6::Core
    OpenSSL::Crypto
)
