#pragma once

#include <QtWidgets\QGraphicsSceneWheelEvent>

#include <QtQuick/QQuickItem>

/*!
  \class WheelArea
  \brief Класс реализует возможность получать события о горизонтально/вертикальном скролле мышки.
  \author Ilya.Tkachenko
  \date 10.08.2012
*/
class WheelArea : public QQuickItem
{
  Q_OBJECT
public:
  explicit WheelArea(QQuickItem *parent = 0);

protected:
  void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
  void verticalWheel(int delta);  
  void horizontalWheel(int delta);       
};