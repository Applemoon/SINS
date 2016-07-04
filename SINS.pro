TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    quaternion.cpp \
    matrix3x3.cpp \
    matrix3x1.cpp \
    helper.cpp \
    matrix4x4.cpp \
    matrix.cpp \
    testdata.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    quaternion.h \
    matrix3x3.h \
    matrix3x1.h \
    helper.h \
    matrix4x4.h \
    matrix.h \
    testdata.h

