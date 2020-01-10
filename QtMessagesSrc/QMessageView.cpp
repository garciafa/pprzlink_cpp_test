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

/** \file QMessageView.cpp
 *
 *
 */


#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <iostream>
#include "QMessageView.h"

QMessageView::QMessageView(const pprzlink::Message &message,QWidget *parent) : QWidget(parent),message(message)
{
  setLayout(new QVBoxLayout());
  for (int field = 0; field < message.getDefinition().getNbFields(); ++field)
  {
    QWidget *container = new QWidget(this);
    container->setLayout(new QHBoxLayout());

    QPushButton*but = new QPushButton(container);
    but->setText(message.getDefinition().getField(field).getName().c_str());

    QLabel* value = new QLabel(container);

    std::stringstream sstr;
    auto val = this->message.getRawValue(field);
    val.setOutputInt8AsInt(true);
    sstr << val;

    value->setText(sstr.str().c_str());
    fieldValues.push_back(value);

    container->layout()->addWidget(but);
    container->layout()->addWidget(value);

    layout()->addWidget(container);
  }
  QWidget *widget = new QWidget(this);
  widget->setSizePolicy(QSizePolicy::Policy::Expanding,QSizePolicy::Policy::Expanding);
  layout()->addWidget(widget);
  setMessage(message);
}

void QMessageView::setMessage(const pprzlink::Message &message)
{
  QMessageView::message = message;
  for (int field = 0; field < message.getDefinition().getNbFields(); ++field)
  {
    QLabel *value = fieldValues[field];

    std::stringstream sstr;
    auto val = this->message.getRawValue(field);
    val.setOutputInt8AsInt(true);
    sstr << val;

    value->setText(sstr.str().c_str());
  }

  // TODO Set the icon to a green light when received and fade it slowly
}
