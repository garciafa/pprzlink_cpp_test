HEADERS = MessagesMainWindow.h  QMessagesList.h  QMessageView.h ../C++/share/src/ivyqtloop.h
SOURCES = MessagesMainWindow.cpp  QMessagesList.cpp  QMessageView.cpp  QtMessages.cpp ../C++/share/src/ivyqtloop.cpp

QMAKE_CXXFLAGS += --std=c++17 -Wall -fPIC -flto
QMAKE_LFLAGS += -Wl,-rpath,${PWD}/C++/lib
                 
INCLUDEPATH = ../C++/include
INCLUDEPATH = ../C++/include
LIBS = -L../C++/lib -lpprzlink++ -livy -lpthread -ltinyxml2

QT += widgets

DESTDIR = ..
