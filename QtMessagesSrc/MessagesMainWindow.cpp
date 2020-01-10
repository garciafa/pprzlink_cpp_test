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

/** \file MessagesMainWindow.cpp
 *
 *
 */


#include <iostream>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTabBar>
#include <QtWidgets/QVBoxLayout>
#include <QVariant>
#include "MessagesMainWindow.h"
#include "QMessagesList.h"

MessagesMainWindow::MessagesMainWindow(pprzlink::MessageDictionary & msgDict, QWidget *parent, const Qt::WindowFlags &flags) : QMainWindow(parent, flags), dict(msgDict)
{
  link = std::make_unique<pprzlink::IvyLink>(dict,"Messages Qt");
  auto telemetryMsgs = dict.getMsgsForClass("telemetry");
  for (auto msg : telemetryMsgs)
  {
    using std::placeholders::_1;
    using std::placeholders::_2;
    link->BindMessage(msg,std::bind(&MessagesMainWindow::gotMessage,this,_1,_2));
  }
  makeGUI();
}

void MessagesMainWindow::makeGUI()
{
  tabs = new QTabWidget(this);
  setCentralWidget(tabs);
  setWindowTitle("Messages Qt");
}

void MessagesMainWindow::gotMessage(std::string ac_id, pprzlink::Message msg)
{
  if (acIdToTab.find(ac_id)==acIdToTab.end())
  {
    QMessagesList * list = new QMessagesList(ac_id);
    int tab=tabs->addTab(list,ac_id.c_str());
    acIdToTab[ac_id]=tab;
  }
  int tab=acIdToTab[ac_id];
  ((QMessagesList *)tabs->widget(tab))->newMessage(msg);
}

MessagesMainWindow::~MessagesMainWindow()
{
  delete tabs;
}
