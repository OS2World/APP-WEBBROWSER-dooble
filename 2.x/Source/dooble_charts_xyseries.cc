/*
** Copyright (c) 2008 - present, Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from Dooble without specific prior written permission.
**
** DOOBLE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** DOOBLE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "dooble_charts_property_editor_xyseries.h"
#include "dooble_charts_xyseries.h"

const QString dooble_charts_xyseries::s_chart_properties_strings[] =
  {
   tr("Color"),
   tr("Name"),
   tr("Opacity"),
   tr("Points Visible"),
   tr("Points Labels Clipping"),
   tr("Points Labels Color"),
   tr("Points Labels Font"),
   tr("Points Labels Format"),
   tr("Points Labels Visible"),
   tr("Use OpenGL"),
   tr("Visible"),
   tr("X-Axis"),
   tr("Labels Format"),
   tr("Maximum"),
   tr("Minimum"),
   tr("Minor Tick Count"),
   tr("Tick Anchor"),
   tr("Tick Count"),
   tr("Tick Interval"),
   tr("Tick Type"),
   tr("Y-Axis"),
   tr("Labels Format"),
   tr("Maximum"),
   tr("Minimum"),
   tr("Minor Tick Count"),
   tr("Tick Anchor"),
   tr("Tick Count"),
   tr("Tick Interval"),
   tr("Tick Type"),
   QString("")
  };

dooble_charts_xyseries::dooble_charts_xyseries(QWidget *parent):
  dooble_charts(parent)
{
#ifdef DOOBLE_QTCHARTS_PRESENT
  m_chart->addAxis(m_x_axis = new QValueAxis(this), Qt::AlignBottom);
  m_chart->addAxis(m_y_axis = new QValueAxis(this), Qt::AlignLeft);
  m_chart->addSeries(m_series = new QLineSeries(this));
#endif
  m_property_editor = new dooble_charts_property_editor_xyseries
    (m_ui.properties, this);
#ifdef DOOBLE_QTCHARTS_PRESENT
  m_series->attachAxis(m_x_axis);
  m_series->attachAxis(m_y_axis);
#endif
  connect(m_property_editor->model(),
	  SIGNAL(itemChanged(QStandardItem *)),
	  this,
	  SLOT(slot_item_changed(QStandardItem *)));
}

dooble_charts_xyseries::~dooble_charts_xyseries()
{
}

QHash<dooble_charts::Properties, QVariant> dooble_charts_xyseries::
properties(void) const
{
  QHash<dooble_charts::Properties, QVariant> properties
    (dooble_charts::properties());

#ifdef DOOBLE_QTCHARTS_PRESENT
  auto series = qobject_cast<QLineSeries *> (m_series);
  auto x_axis = qobject_cast<QValueAxis *> (m_x_axis);

  properties[dooble_charts::XY_SERIES_COLOR] = series->color();
  properties[dooble_charts::XY_SERIES_NAME] = series->name();
  properties[dooble_charts::XY_SERIES_OPACITY] = series->opacity();
  properties[dooble_charts::XY_SERIES_POINTS_VISIBLE] = series->pointsVisible();
  properties[dooble_charts::XY_SERIES_POINT_LABELS_CLIPPING] =
    series->pointLabelsClipping();
  properties[dooble_charts::XY_SERIES_POINT_LABELS_COLOR] =
    series->pointLabelsColor();
  properties[dooble_charts::XY_SERIES_POINT_LABELS_FONT] =
    series->pointLabelsFont();
  properties[dooble_charts::XY_SERIES_POINT_LABELS_FORMAT] =
    series->pointLabelsFormat();
  properties[dooble_charts::XY_SERIES_POINT_LABELS_VISIBLE] =
    series->pointLabelsVisible();
  properties[dooble_charts::XY_SERIES_USE_OPENGL] = series->useOpenGL();
  properties[dooble_charts::XY_SERIES_VISIBLE] = series->isVisible();
  properties[dooble_charts::XY_SERIES_X_AXIS_LABEL_FORMAT] = x_axis->
    labelFormat();
  properties[dooble_charts::XY_SERIES_X_AXIS_MAX] = x_axis->max();
  properties[dooble_charts::XY_SERIES_X_AXIS_MIN] = x_axis->min();
  properties[dooble_charts::XY_SERIES_X_AXIS_MINOR_TICK_COUNT] = x_axis->
    minorTickCount();
  properties[dooble_charts::XY_SERIES_X_AXIS_TICK_ANCHOR] = x_axis->
    tickAnchor();
  properties[dooble_charts::XY_SERIES_X_AXIS_TICK_COUNT] = x_axis->tickCount();
  properties[dooble_charts::XY_SERIES_X_AXIS_TICK_INTERVAL] = x_axis->
    tickInterval();
  properties[dooble_charts::XY_SERIES_X_AXIS_TICK_TYPE] = tick_type_to_string
    (x_axis->tickType());
#endif
  return properties;
}

#ifdef DOOBLE_QTCHARTS_PRESENT
QString dooble_charts_xyseries::tick_type_to_string
(const QValueAxis::TickType tick_type)
{
  switch(tick_type)
    {
    case QValueAxis::TicksDynamic:
      {
	return tr("Dynamic");
      }
    default:
      {
	return tr("Fixed");
      }
    }
}
#endif

void dooble_charts_xyseries::slot_item_changed(QStandardItem *item)
{
  if(!item)
    return;

  dooble_charts::slot_item_changed(item);
}
