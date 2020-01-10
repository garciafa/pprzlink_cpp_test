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

/** \file QMessagesList.cpp
 *
 *
 */


#include <QtWidgets/QProxyStyle>
#include <QtWidgets/QStyleOptionTab>
#include "QMessagesList.h"
#include "QMessageView.h"

class CustomTabStyle : public QProxyStyle {
public:
  QSize sizeFromContents(ContentsType type, const QStyleOption* option,
                         const QSize& size, const QWidget* widget) const {
    QSize s = QProxyStyle::sizeFromContents(type, option, size, widget);
    if (type == QStyle::CT_TabBarTab) {
      s.transpose();
    }
    return s;
  }

  void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const {
    if (element == CE_TabBarTabLabel) {
      if (const QStyleOptionTab* tab = qstyleoption_cast<const QStyleOptionTab*>(option)) {
        QStyleOptionTab opt(*tab);
        opt.shape = QTabBar::RoundedNorth;
        QProxyStyle::drawControl(element, &opt, painter, widget);
        return;
      }
    }
    QProxyStyle::drawControl(element, option, painter, widget);
  }
};

QMessagesList::QMessagesList(const std::string &acId, QWidget *parent) : QTabWidget(parent), ac_id(acId)
{
  setTabPosition(QTabWidget::West);
  tabBar()->setStyle(new CustomTabStyle);
}

void QMessagesList::newMessage(pprzlink::Message const &msg)
{
  auto const & msgName = msg.getDefinition().getName();
  if (tabForMsgName.find(msgName)==tabForMsgName.end())
  {
    // Add a tab
    int tab = addTab(new QMessageView(msg),msgName.c_str());
    tabForMsgName[msgName]=tab;
  }
  else
  {
    ((QMessageView*)widget(tabForMsgName[msgName]))->setMessage(msg);
  }
}
