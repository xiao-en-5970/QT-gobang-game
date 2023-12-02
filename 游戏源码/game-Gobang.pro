QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    gamesence.cpp \
    main.cpp \
    mainsence.cpp \
    move.cpp \
    piece.cpp \
    piece_label.cpp \
    setting.cpp \
    text_message.cpp

HEADERS += \
    button.h \
    gamesence.h \
    mainsence.h \
    move.h \
    piece.h \
    piece_label.h \
    score.h \
    setting.h \
    text_message.h

FORMS += \
    mainsence.ui \
    text_message.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res_image.qrc \
    res_music.qrc


