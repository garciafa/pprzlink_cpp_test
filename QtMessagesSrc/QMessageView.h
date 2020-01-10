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

/** \file QMessageView.h
 *
 *
 */


#ifndef PPRZLINKCPP_QMESSAGEVIEW_H
#define PPRZLINKCPP_QMESSAGEVIEW_H

#include <QtWidgets/QLabel>
#include <pprzlink/Message.h>

class QMessageView : public QWidget {
public:
  QMessageView(const pprzlink::Message &message, QWidget *parent = nullptr);

  void setMessage(const pprzlink::Message &message);

protected:
  pprzlink::Message message;
  std::vector<QLabel*> fieldValues;
};

#endif //PPRZLINKCPP_QMESSAGEVIEW_H
