/*
 * Copyright 2020 garciafa
 * This file is part of PprzLinkCPP
 *
 * PprzLinkCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PprzLinkCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ModemTester.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <QtWidgets/QApplication>
#include "MessagesMainWindow.h"

/** \file QtMessages.cpp
 *
 *
 */


int main(int argc, char** argv)
{
  QApplication app(argc,argv);

  pprzlink::MessageDictionary dict("/home/garciafa/paparazzi/var/messages.xml");

  MessagesMainWindow mainWindow(dict);

  app.setActiveWindow(&mainWindow);

  mainWindow.show();

  return app.exec();
}
