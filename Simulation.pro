QT += sql

HEADERS += \
    vanne.h \
    reservoir.h \
    pompe.h \
    main.h \
    avion.h \
    mainwindow.h \
    fenetrepilote.h \
    identification.h \
    aide.h

SOURCES += \
    vanne.cpp \
    reservoir.cpp \
    pompe.cpp \
    main.cpp \
    avion.cpp \
    mainwindow.cpp \
    fenetrepilote.cpp \
    identification.cpp \
    aide.cpp

FORMS += \
    mainwindow.ui \
    fenetrepilote.ui \
    identification.ui \
    aide.ui

RESOURCES += \
    images.qrc

OTHER_FILES += \
    ../Simulation-build-desktop-Qt_4_8_1_dans_le_PATH__Syst_me__Release/Simulation \
    TO_DO-LIST.txt
