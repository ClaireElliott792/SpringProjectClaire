/****************************************************************************
basic OpenGL box2d spring system project 
modified from :-
http://qt-project.org/doc/qt-5.0/qtgui/openglwindow.html 
Macey, J. (2022) 'NCCA/Box2D', published on github. https://github.com/NCCA/Box2D Accessed on May 2023.
****************************************************************************/
#include <QtGui/QGuiApplication>
#include <iostream>
#include "NGLScene.h"

int main(int argc, char **argv)
{
  QGuiApplication app(argc, argv);
  QSurfaceFormat format;
  format.setSamples(4);
  #if defined(__APPLE__)
    format.setMajorVersion(4);
    format.setMinorVersion(1);
  #else
    format.setMajorVersion(4);
    format.setMinorVersion(3);
  #endif
  
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  NGLScene window;
  window.setFormat(format);
  window.resize(1024, 720);
  window.show();

  return app.exec();
}