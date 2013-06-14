﻿#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Engine(new cEngine)
{
    ui->setupUi(this);

    m_glWidget = new GLWidget(this,m_Engine->getData());

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_glWidget);

    ui->OpenglLayout->setLayout(layout);

    connectActions();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_glWidget;
    delete m_Engine;
}

bool MainWindow::checkForLoadedEntities()
{
    bool loadedEntities = true;
    m_glWidget->displayNewMessage(QString()); //clear (any) message in the middle area

    if (!m_glWidget->hasCloudLoaded())
    {
        m_glWidget->displayNewMessage("Drag & drop .ply file(s) on the window to load them!");
        loadedEntities = false;
    }

    return loadedEntities;
}

void MainWindow::addFiles(const QStringList& filenames)
{
    if (filenames.size())
    {
        #ifdef _DEBUG
            printf("adding files %s", filenames[0]);
        #endif

        m_Engine->loadClouds(filenames);

        m_glWidget->setData(m_Engine->getData());

        m_glWidget->updateGL();

        //set default working directory as first file folder
        QFileInfo fi(filenames[0]);
        QDir Dir = fi.dir();
        Dir.cdUp();
        m_Engine->setDir(Dir);

        checkForLoadedEntities();
    }
}

void MainWindow::toggleFullScreen(bool state)
{
    if (state)
        showFullScreen();
    else
        showNormal();
    m_glWidget->updateGL();
}

void MainWindow::toggleShowBall(bool state)
{
    m_glWidget->showBall(state);
}

void MainWindow::toggleShowAxis(bool state)
{
    m_glWidget->showAxis(state);
}

void MainWindow::toggleShowMessages(bool state)
{
    m_glWidget->showMessages(state);
}

void MainWindow::togglePointsSelection(bool state)
{
    if (state)
    {
        m_glWidget->setInteractionMode(GLWidget::SEGMENT_POINTS);

        if (m_glWidget->hasCloudLoaded()&&m_glWidget->showMessages())
        {
            m_glWidget->displayNewMessage(QString());
            m_glWidget->displayNewMessage("Selection mode",GLWidget::UPPER_CENTER_MESSAGE);
            m_glWidget->displayNewMessage("Left click: add contour point / Right click: close / Echap: delete polyline",GLWidget::LOWER_CENTER_MESSAGE);
            m_glWidget->displayNewMessage("Space: keep points inside polyline / Suppr: keep points outside polyline",GLWidget::LOWER_CENTER_MESSAGE);
        }
    }
    else
    {
        m_glWidget->setInteractionMode(GLWidget::TRANSFORM_CAMERA);

        if (m_glWidget->hasCloudLoaded()&&m_glWidget->showMessages())
        {
            m_glWidget->clearPolyline();
            m_glWidget->displayNewMessage(QString());
            m_glWidget->displayNewMessage("Move mode",GLWidget::UPPER_CENTER_MESSAGE);
            m_glWidget->displayNewMessage("Left click: rotate viewpoint / Right click: translate viewpoint",GLWidget::LOWER_CENTER_MESSAGE);
        }
    }
}

void MainWindow::doActionDisplayShortcuts()
{
    QMessageBox msgBox;
    QString text;
    text += "Shortcuts:\n\n";
    text += "F2: full screen\n";
    text += "F3: show axis\n";
    text += "F4: show ball\n";
    text += "F5: show help messages\n";
    text += "F6: move mode / selection mode\n";
    text += "\n";
    text += "Key +/-: increase/decrease point size\n";
    text += "\n";
    text += "Selection mode:\n";
    text += "    - Left click : add a point to polyline\n";
    text += "    - Right click: close polyline\n";
    text += "    - Echap: delete polyline\n";
    text += "    - Space bar: keep points inside polyline\n";
    text += "    - Suppr: keep points outside polyline\n";
    text += "    - Ctrl+Z: undo all past selections\n";
    text += "\n";
    text += "Ctrl+O: open camera(s) file(s)\n";
    text += "Ctrl+E: export mask(s) file(s)\n";
    text += "Ctrl+S: open camera(s) and export mask(s)\n";

    msgBox.setText(text);
    msgBox.exec();
}

void MainWindow::connectActions()
{
    connect(m_glWidget,	SIGNAL(filesDropped(const QStringList&)), this,	SLOT(addFiles(const QStringList&)));

    connect(m_glWidget,	SIGNAL(mouseWheelRotated(float)),      this, SLOT(echoMouseWheelRotate(float)));

    connect(ui->actionFullScreen,       SIGNAL(toggled(bool)), this, SLOT(toggleFullScreen(bool)));
    connect(ui->actionShow_axis,        SIGNAL(toggled(bool)), this, SLOT(toggleShowAxis(bool)));
    connect(ui->actionShow_ball,        SIGNAL(toggled(bool)), this, SLOT(toggleShowBall(bool)));
    connect(ui->actionShow_help_messages,SIGNAL(toggled(bool)), this, SLOT(toggleShowMessages(bool)));

    connect(ui->actionHelpShortcuts,    SIGNAL(triggered()),   this, SLOT(doActionDisplayShortcuts()));

    connect(ui->actionSetViewTop,		SIGNAL(triggered()),   this, SLOT(setTopView()));
    connect(ui->actionSetViewBottom,	SIGNAL(triggered()),   this, SLOT(setBottomView()));
    connect(ui->actionSetViewFront,		SIGNAL(triggered()),   this, SLOT(setFrontView()));
    connect(ui->actionSetViewBack,		SIGNAL(triggered()),   this, SLOT(setBackView()));
    connect(ui->actionSetViewLeft,		SIGNAL(triggered()),   this, SLOT(setLeftView()));
    connect(ui->actionSetViewRight,		SIGNAL(triggered()),   this, SLOT(setRightView()));

    //"Points selection" menu
    connect(ui->actionTogglePoints_selection, SIGNAL(toggled(bool)), this, SLOT(togglePointsSelection(bool)));

    connect(ui->actionLoad_camera,		SIGNAL(triggered()),   this, SLOT(loadCameras()));
    connect(ui->actionExport_mask,		SIGNAL(triggered()),   this, SLOT(exportMasks()));
    connect(ui->actionLoad_and_Export,	SIGNAL(triggered()),   this, SLOT(loadAndExport()));
}

void MainWindow::setTopView()
{
    m_glWidget->setView(TOP_VIEW);
}

void MainWindow::setBottomView()
{
    m_glWidget->setView(BOTTOM_VIEW);
}

void MainWindow::setFrontView()
{
    m_glWidget->setView(FRONT_VIEW);
}

void MainWindow::setBackView()
{
    m_glWidget->setView(BACK_VIEW);
}

void MainWindow::setLeftView()
{
    m_glWidget->setView(LEFT_VIEW);
}

void MainWindow::setRightView()
{
    m_glWidget->setView(RIGHT_VIEW);
}

void MainWindow::echoMouseWheelRotate(float wheelDelta_deg)
{
    GLWidget* sendingWindow = dynamic_cast<GLWidget*>(sender());
    if (!sendingWindow)
        return;

    sendingWindow->onWheelEvent(wheelDelta_deg);
}

void MainWindow::on_actionUndo_triggered()
{
     m_glWidget->undoAll();
}

void MainWindow::loadCameras()
{
    m_Engine->loadCameras();
}

void MainWindow::exportMasks()
{
    m_Engine->doMasks();
}

void MainWindow::loadAndExport()
{
    loadCameras();
    exportMasks();
}


