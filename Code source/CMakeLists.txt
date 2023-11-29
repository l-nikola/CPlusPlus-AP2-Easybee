cmake_minimum_required(VERSION 3.5)

project(ap2v3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)

set(PROJECT_SOURCES
        initdb.h main.cpp images.qrc
        accueil.h accueil.cpp accueil.ui
        authentification.h authentification.cpp authentification.ui

        geranthub.h geranthub.cpp geranthub.ui

        compteurentrepot.h compteurentrepot.cpp
        assistantehub.h assistantehub.cpp assistantehub.ui
        stockentrepot.h stockentrepot.cpp stockentrepot.ui
        saisiecommande.h saisiecommande.cpp saisiecommande.ui
        misepaiement.h misepaiement.cpp misepaiement.ui

        compteur.h compteur.cpp
        receptioncontroller.h receptioncontroller.cpp receptioncontroller.ui
        receptioncommande.h receptioncommande.cpp receptioncommande.ui
        receptionhub.h receptionhub.cpp receptionhub.ui

        admin.h admin.cpp admin.ui
        adduser.h adduser.cpp adduser.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ap2v3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ap2v3 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ap2v3 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ap2v3
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ap2v3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ap2v3 PRIVATE Qt6::Sql)

set_target_properties(ap2v3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ap2v3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ap2v3)
endif()
