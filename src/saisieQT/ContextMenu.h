#ifndef __CONTEXTMENUMANAGER__
#define __CONTEXTMENUMANAGER__

#include <QMenu>
#include <QSignalMapper>
#include <QIcon>
#include <QInputDialog>
#include <QDialogButtonBox>

#include <QWidget>
#include <QAction>

#include "3DObject.h"

typedef enum
{
  eAllWindow,
  eThisWindow,
  eThisPoint
} eSwitchImage;

class ContextMenu : public QWidget
{
    Q_OBJECT

public:
    ContextMenu(){}

    void createContextMenuActions();

    void setPolygon(cPolygon * poly){ _polygon = poly; }
    void setPos(QPointF pt) { _lastPosImage = pt; }

    cPolygon    *_polygon;

    QAction     *_AllW;
    QAction     *_ThisP;
    QAction     *_ThisW;

    QAction     *_validate;
    QAction     *_dubious;
    QAction     *_refuted;
    QAction     *_noSaisie;
    QAction     *_highLight;
    QAction     *_rename;

signals:

    void changeState(int state, int idPt);

    void changeName(QString oldName, QString newName);

    void changeImagesSignal(int idPt);

public slots:

    void setPointState(int state);

    void changeImages(int mode);

    void highlight();

    void rename();

private :

    QPointF                 _lastPosImage; //copy of QGLWidget's m_lastPosImage

    QSignalMapper*          _stateSignalMapper;
    QSignalMapper*          _switchSignalMapper;
};

#endif
