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

/** \file MessagesMainWindow.h
 *
 *
 */


#ifndef PPRZLINKCPP_MESSAGESMAINWINDOW_H
#define PPRZLINKCPP_MESSAGESMAINWINDOW_H

#include <memory>
#include <QtWidgets/QMainWindow>

#include <pprzlink/Message.h>
#include <pprzlink/IvyLink.h>

class MessagesMainWindow : public QMainWindow {
public:
  MessagesMainWindow(pprzlink::MessageDictionary & msgDict, QWidget *parent = nullptr, const Qt::WindowFlags &flags = 0);

  ~MessagesMainWindow();

public slots:
  void gotMessage(std::string ac_id, pprzlink::Message msg);

protected:
  void makeGUI();

  pprzlink::MessageDictionary &dict;
  std::unique_ptr<pprzlink::IvyLink> link;
  QTabWidget *tabs;
  std::map <std::string,int> acIdToTab;
};

#endif //PPRZLINKCPP_MESSAGESMAINWINDOW_H
