TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    xor_linked_list.h \
    is_iterator_tester.h \
    xor_linked_list_test.h

