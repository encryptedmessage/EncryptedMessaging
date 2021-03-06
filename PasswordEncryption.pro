######################################################################
# Automatically generated by qmake (3.1) Mon Feb 26 20:57:16 2018
######################################################################

TEMPLATE = app
TARGET = PasswordEncryption
INCLUDEPATH += .
QT += core gui
QT += widgets

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += Characters.h \
           CommonWindow.h \
           Conversions.h \
           Cryption.h \
           Decryption.h \
           Demo.h \
           Encryption.h \
           FileNameRetrieval.h \
           FolderStructure.h \
           GenerateDate.h \
           GenerateKeys.h \
           GeneratePasswordFileName.h \
           Key.h \
           KeyManagementWindow.h \
           KeyRetrieval.h \
           MainWindow.h \
           Password.h \
           PasswordManagementWindow.h \
	   SaveFile.h \
           TimeInformation.h \
           ViewingWindow.h
SOURCES += Cryption.cpp \
           Decryption.cpp \
           Encryption.cpp \
           FileNameRetrieval.cpp \
           FolderStructure.cpp \
           GeneratePasswordFileName.cpp \
           KeyManagementWindow.cpp \
           KeyRetrieval.cpp \
           Main.cpp \
           MainWindow.cpp \
           PasswordManagementWindow.cpp \
	   SaveFile.cpp
