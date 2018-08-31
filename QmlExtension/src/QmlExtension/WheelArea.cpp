#include <QmlExtension/WheelArea.h>

WheelArea::WheelArea(QQuickItem *parent /*= 0*/) : QQuickItem(parent)
{
}

void WheelArea::wheelEvent(QGraphicsSceneWheelEvent *event)
{
  switch(event->orientation()) 
  {
  case Qt::Horizontal:
    emit horizontalWheel(event->delta());
    break;
  case Qt::Vertical:
    emit verticalWheel(event->delta());
    break;
  default:
    event->ignore();
    break;
  }
}
