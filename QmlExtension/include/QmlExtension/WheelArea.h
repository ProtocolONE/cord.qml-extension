#pragma once

#include <QtWidgets\QGraphicsSceneWheelEvent>

#include <QtQuick/QQuickItem>

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