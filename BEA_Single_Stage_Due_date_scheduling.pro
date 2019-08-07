TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BEA.cpp \
    Problem.cpp \
    Schedule.cpp

HEADERS += \
    BEA.hpp \
    Problem.hpp \
    Schedule.hpp \
    test/testBEA.hpp \
    test/testProblem.hpp \
    test/testSchedule.hpp

DISTFILES += \
    input/testinput.txt \
    input/Kopanos2009cs1.txt \
    input/Kopanos2009cs2.txt
