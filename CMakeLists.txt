# SPDX-FileCopyrightText: 2022 illusion <vladyslav.makarov1@nure.ua>
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

project(kirigami_db VERSION 0.1)

include(FeatureSummary)

set(QT5_MIN_VERSION 5.15)
set(KF5_MIN_VERSION 5.83)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED CONFIG)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})


include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPoQmTools)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX KIRIGAMI_DB
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/version-kirigami_db.h"
)

find_package(Qt5 ${QT5_MIN_VERSION} REQUIRED COMPONENTS Core Quick Widgets Test Gui Qml QuickControls2 Svg Sql QmlImportScanner QmlWorkerScript Multimedia)
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Kirigami2 CoreAddons Config)

if (ANDROID)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/android/version.gradle.in ${CMAKE_BINARY_DIR}/version.gradle)
endif()

add_subdirectory(3rdparty)
add_subdirectory(src)


install(PROGRAMS org.kde.kirigami_db.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.kirigami_db.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
