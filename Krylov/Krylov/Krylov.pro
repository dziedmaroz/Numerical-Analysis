HEADERS += \
    gauss/gauss.h \
    krylov.h

LIBS += -L/usr/lib/ -lgsl

SOURCES += \
    gauss/gauss.cpp \
    krylov.cpp \
    main.cpp
