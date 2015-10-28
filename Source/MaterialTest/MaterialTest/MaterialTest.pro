TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH += "/home/andi/Source/MaterialTest/MaterialTest/3rdParty/Material/modules"
#QML2_IMPORT_PATH += "/home/andi/Source/MaterialTest/MaterialTest/3rdParty/Material/modules"

#$$PWD/3rdParty/Material/modules/Material

# Default rules for deployment.
include(deployment.pri)

#export(QML2_IMPORT_PATH)

