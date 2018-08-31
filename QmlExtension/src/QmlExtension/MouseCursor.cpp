#include <QmlExtension/MouseCursor.h>

#include <QtGui/QCursor>
#include <QtCore/QDebug>

namespace P1 {

  struct FindWindowInfo {
    unsigned long process_id;
    HWND best_handle;
  };

  BOOL isMainWindow(HWND handle)
  {   
    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
  }

  BOOL CALLBACK enumWindowsCallback(HWND handle, LPARAM lParam)
  {
    FindWindowInfo* data = reinterpret_cast<FindWindowInfo*>(lParam);
    unsigned long process_id = 0;
    GetWindowThreadProcessId(handle, &process_id);
    if (data->process_id != process_id || !isMainWindow(handle))
      return TRUE;

    data->best_handle = handle;
    return FALSE;   
  }

  HWND findMainWindow(unsigned long process_id)
  {
    FindWindowInfo data;
    data.process_id = process_id;
    data.best_handle = 0;
    EnumWindows(enumWindowsCallback, (LPARAM)&data);
    return data.best_handle;
  }

  MouseCursor::MouseCursor(QObject* parent) 
    : QObject(parent)
    , _mainWindow(0)
  {
  }

  MouseCursor::~MouseCursor()
  {
  }

  MouseCursor* MouseCursor::qmlAttachedProperties(QObject *obj)
  {
    return new MouseCursor(obj);
  }

  QPoint MouseCursor::mousePos()
  {
    return QCursor::pos();
  }

  Q_INVOKABLE QPoint MouseCursor::debugOnlyWindowPos()
  {
    if (!this->_mainWindow) 
      this->_mainWindow = findMainWindow(GetCurrentProcessId());
    
    POINT p = { 0, 0 };
    ClientToScreen(this->_mainWindow, &p);
    return QPoint(p.x, p.y);
  }

}