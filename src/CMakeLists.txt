# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2022 illusion <vladyslav.makarov1@nure.ua>


file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources.qrc)
qt_add_resources(RESOURCES resources.qrc)

add_executable(kirigami_db
    main.cpp
    about.cpp
    app.cpp

    cardlistviewsqlquerymodel.h
    cardlistviewsqlquerymodel.cpp

    resources.qrc
    ${RESOURCES}
    )
set(QT_QML_PATH ${_qt5Quick_install_prefix})
find_library(KIRIGAMI_PLUGIN KirigamiPlugin PATHS ${Kirigami2_INSTALL_PREFIX}/${KDE_INSTALL_QMLDIR}/org/kde/kirigami.2)
find_library(QUICK_PLUGIN qtquick2plugin PATHS ${QT_QML_PATH}/qml/QtQuick.2)
#find_library(LABS_PLATFORM_PLUGIN qtlabsplatformplugin PATHS ${QT_QML_PATH}/qml/Qt/labs/platform)
find_library(GRAPHEFFECTS_PLUGIN qtgraphicaleffectsplugin PATHS ${QT_QML_PATH}/qml/QtGraphicalEffects)
find_library(GRAPHEFFECTS_PRIVATE_PLUGIN qtgraphicaleffectsprivate PATHS ${QT_QML_PATH}/qml/QtGraphicalEffects/private)
find_library(QQC2_PLUGIN qtquickcontrols2plugin PATHS ${QT_QML_PATH}/qml/QtQuick/Controls.2)
find_library(QQC2_MATERIAL_PLUGIN qtquickcontrols2materialstyleplugin PATHS ${QT_QML_PATH}/qml/QtQuick/Controls.2/Material)
find_library(QQC2_UNIVERSAL_PLUGIN qtquickcontrols2universalstyleplugin PATHS ${QT_QML_PATH}/qml/QtQuick/Controls.2/Universal)
find_library(QLAYOUTS_PLUGIN qquicklayoutsplugin PATHS ${QT_QML_PATH}/qml/QtQuick/Layouts)
#find_library(QWINDOW_PLUGIN windowplugin PATHS ${QT_QML_PATH}/qml/QtQuick/Window.2)
find_library(QSHAPES_PLUGIN qmlshapesplugin PATHS ${QT_QML_PATH}/qml/QtQuick/Shapes)
find_library(QUICKSHAPES Qt5QuickShapes PATHS ${QT_LIBDIR})
find_library(QTEMPLATES_PLUGIN qtquicktemplates2plugin PATHS ${QT_QML_PATH}/qml/QtQuick/Templates.2)
find_library(QMODELS_PLUGIN modelsplugin PATHS ${QT_QML_PATH}/qml/QtQml/Models.2)



message("${Kirigami2_INSTALL_PREFIX}")

message("ALLLEEEEEEEEEEEERTTTTT")
message("${KDE_INSTALL_QMLDIR}")

target_link_libraries(kirigami_db PRIVATE
    KirigamiPlugin
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    #Qt5::QuickCompiler
    Qt5::Svg
    Qt5::Sql
    Qt5::QmlWorkerScript
    #KF5::I18n
    KF5::CoreAddons
    KF5::ConfigCore
    KF5::ConfigGui
    KF5::Kirigami2
    ${KIRIGAMI_PLUGIN}
    #${QUICK_PLUGIN}
	#${LABS_PLATFORM_PLUGIN}
	#${GRAPHEFFECTS_PLUGIN}
	#${GRAPHEFFECTS_PRIVATE_PLUGIN}
	#${QQC2_PLUGIN}
	#${QQC2_MATERIAL_PLUGIN}
	#${QQC2_UNIVERSAL_PLUGIN}
	#${QLAYOUTS_PLUGIN}
	#${QSHAPES_PLUGIN}
	#${QUICKSHAPES}
    #${QTEMPLATES_PLUGIN}
	#${QMODELS_PLUGIN}


)

get_target_property(QT_TARGET_TYPE Qt${QT_VERSION_MAJOR}::Core TYPE)
find_package(Qt5QmlImportScanner REQUIRED)

qt5_import_qml_plugins(${CMAKE_PROJECT_NAME})
#qt5_import_qml_plugins(KirigamiPlugin)

link_directories(${_qt5_install_prefix}/../)

#ecm_generate_qmltypes(org.kde.kirigami 2.4 DESTINATION <${KDE_INSTALL_QMLDIR}/org/kde/kirigami>)

#ecm_add_qml_module(KirigamiPlugin URI "org.kde.kirigami" VERSION 2.4)
#target_sources(kirigami_db PRIVATE KirigamiPlugin.cpp)
#ecm_target_qml_sources(ExampleModule SOURCES ExampleItem.qml)
#ecm_target_qml_sources(ExampleModule SOURCES AnotherExampleItem.qml VERSION 1.5)
#ecm_finalize_qml_module(KirigamiPlugin DESTINATION ${KDE_INSTALL_QMLDIR})

if(TARGET Qt5::QmlWorkerScript)
  target_link_libraries(kirigami_db PRIVATE Qt5::QmlWorkerScript KF5::Kirigami2)
endif()

if(TARGET KF5::Kirigami2)
  target_link_libraries(kirigami_db PRIVATE KF5::Kirigami2)
endif()

if (ANDROID)
    kirigami_package_breeze_icons(ICONS
        list-add
        help-about
        application-exit
        applications-graphics
    )
endif()

if (ANDROID)
    set(minimal_EXTRA_LIBS Qt5::AndroidExtras
    #FIXME: we shouldn't have to link to it but otherwise the lib won't be packaged on Android
    Qt5::QuickControls2)
else ()
#qstyle-based qqc2 style needs a QApplication
    set(minimal_EXTRA_LIBS Qt5::Widgets)
endif()

kirigami_package_breeze_icons(ICONS open-menu-symbolic document-decrypt folder-sync go-next go-previous go-up handle-left handle-right view-list-icons applications-graphics media-record-symbolic)

kconfig_add_kcfg_files(kirigami_db GENERATE_MOC kirigami_dbconfig.kcfgc)
install(TARGETS kirigami_db ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
