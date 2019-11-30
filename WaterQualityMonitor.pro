QT       += core gui  sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += serialport

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    qcustomplot.cpp \
    uis/varsettable.cpp \
    serialport/splisten.cpp \
    uis/curvefittingwidget.cpp \
    uis/processsetwidget.cpp \
    uis/examinetestwidget.cpp \
    datastruct/processdata.cpp \
    datastruct/vardata.cpp \
    datastruct/userdata.cpp \
    datastruct/logdata.cpp \
    datastruct/waterdb.cpp

HEADERS += \
    mainwidget.h \
    qcustomplot.h \
    uis/varsettable.h \
    serialport/splisten.h \
    uis/curvefittingwidget.h \
    uis/processsetwidget.h \
    uis/examinetestwidget.h \
    datastruct/processstruct.h \
    datastruct/processdata.h \
    datastruct/varstruct.h \
    datastruct/vardata.h \
    datas.h \
    datastruct/userstruct.h \
    datastruct/userdata.h \
    datastruct/logstruct.h \
    datastruct/logdata.h \
    datastruct/waterdb.h

FORMS += \
    mainwidget.ui \
    uis/varsettable.ui \
    uis/curvefittingwidget.ui \
    uis/processsetwidget.ui \
    uis/examinetestwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
