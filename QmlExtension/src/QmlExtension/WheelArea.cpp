#include <QmlExtension/WheelArea.h>

WheelArea::WheelArea(QDeclarativeItem *parent /*= 0*/) : QDeclarativeItem(parent)
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
