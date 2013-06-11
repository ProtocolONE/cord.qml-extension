#pragma once

#include <QtDeclarative\QDeclarativeItem>
#include <QtWidgets\QGraphicsSceneWheelEvent>

/*!
  \class WheelArea
  \brief Класс реализует возможность получать события о горизонтально/вертикальном скролле мышки.
  \author Ilya.Tkachenko
  \date 10.08.2012
*/
class WheelArea : public QDeclarativeItem
{
  Q_OBJECT
public:
  explicit WheelArea(QDeclarativeItem *parent = 0); 

protected:
  void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
  void verticalWheel(int delta);  
  void horizontalWheel(int delta);       
};