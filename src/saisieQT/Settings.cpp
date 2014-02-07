#include "Settings.h"

cSettingsDlg::cSettingsDlg(QWidget *parent, cParameters *params) : QDialog(parent), Ui::settingsDialog()
{
    setupUi(this);

    setWindowFlags(Qt::Tool/*Qt::Dialog | Qt::WindowStaysOnTopHint*/);

    _parameters = params;
    _oldParameters = *params;

    refresh();

    setUpdatesEnabled(true);
}

cSettingsDlg::~cSettingsDlg()
{}

void cSettingsDlg::setParameters(cParameters &params)
{
    if (!_parameters)
        _parameters = new cParameters();

     _parameters = &params;
}

void cSettingsDlg::on_NBF_x_spinBox_valueChanged(int value)
{
    int y = _parameters->getNbFen().y();
    _parameters->setNbFen(QPoint(value, y));
}

void cSettingsDlg::on_NBF_y_spinBox_valueChanged(int value)
{
    int x = _parameters->getNbFen().x();
    _parameters->setNbFen(QPoint(x, value));
}

void cSettingsDlg::on_WindowWidth_spinBox_valueChanged(int value)
{
    int y = _parameters->getSzFen().height();
    _parameters->setSzFen(QSize(value, y));
}

void cSettingsDlg::on_WindowHeight_spinBox_valueChanged(int value)
{
    int x = _parameters->getSzFen().width();
    _parameters->setSzFen(QSize(x, value));
}

void cSettingsDlg::on_LineThickness_doubleSpinBox_valueChanged(double val)
{
    _parameters->setLineThickness(val);
}

void cSettingsDlg::on_PointDiameter_doubleSpinBox_valueChanged(double val)
{
    _parameters->setPointDiameter(val);
}

void cSettingsDlg::on_PointSize_doubleSpinBox_valueChanged(double val)
{
    _parameters->setPointSize(val);
}

void cSettingsDlg::on_GammaDoubleSpinBox_valueChanged(double val)
{
    _parameters->setGamma(val);
}

void cSettingsDlg::on_zoomWin_spinBox_valueChanged(int val)
{
    _parameters->setZoomWindowValue(val);
}

void cSettingsDlg::on_RadiusSpinBox_valueChanged(int val)
{
    _parameters->setSelectionRadius(val);
}

void  cSettingsDlg::on_okButton_clicked()
{
    on_applyButton_clicked();

    _parameters->write();

    accept();
}

void cSettingsDlg::on_cancelButton_clicked()
{
    emit hasChanged(false);

    reject();
}

void cSettingsDlg::on_applyButton_clicked()
{
    emit hasChanged(_parameters->getNbFen() != _oldParameters.getNbFen());
}

void cSettingsDlg::on_resetButton_clicked()
{
    _parameters->read();

    refresh();
}

void cSettingsDlg::refresh()
{
    NBF_x_spinBox->setValue(_parameters->getNbFen().x());
    NBF_y_spinBox->setValue(_parameters->getNbFen().y());

    WindowWidth_spinBox->setValue( _parameters->getSzFen().width());
    WindowHeight_spinBox->setValue(_parameters->getSzFen().height());

    LineThickness_doubleSpinBox->setValue(_parameters->getLineThickness());
    PointDiameter_doubleSpinBox->setValue(_parameters->getPointDiameter());
    PointSize_doubleSpinBox->setValue(_parameters->getPointSize());
    GammaDoubleSpinBox->setValue(_parameters->getGamma());

    zoomWin_spinBox->setValue(_parameters->getZoomWindowValue());
    PrefixTextEdit->setText(_parameters->getDefPtName());
    RadiusSpinBox->setValue(_parameters->getSelectionRadius());

    update();
}

cParameters::cParameters():
    _openFullScreen(false),
    _position(QPoint(100,100)),
    _nbFen(QPoint(1,1)),
    _szFen(QSize(800,600)),
    _linethickness(2.f),
    _pointDiameter(2.f),
    _pointSize(5.f),
    _gamma(1.f),
    _zoomWindow(3.f),
    _ptName(QString("100")),
    _radius(50)
{}

cParameters& cParameters::operator =(const cParameters &params)
{
    _openFullScreen = params._openFullScreen;
    _position       = params._position;
    _nbFen          = params._nbFen;
    _szFen          = params._szFen;

    _linethickness  = params._linethickness;
    _pointDiameter  = params._pointDiameter;
    _pointSize      = params._pointSize;
    _gamma          = params._gamma;

    _zoomWindow     = params._zoomWindow;
    _ptName         = params._ptName;
    _radius         = params._radius;

    return *this;
}

void cParameters::read()
{
     QSettings settings(QApplication::organizationName(), QApplication::applicationName());

#ifdef _DEBUG
    cout << "settings location: " << settings.fileName().toStdString().c_str() << endl;
#endif

     settings.beginGroup("MainWindow");
     setNbFen(settings.value("NbFen", QPoint(1, 1)).toPoint());
     setFullScreen(settings.value("openInFullScreen", false).toBool());
     setPosition(settings.value("pos", QPoint(200, 200)).toPoint());
     setSzFen(settings.value("size", QSize(800, 600)).toSize());   
     settings.endGroup();

     settings.beginGroup("Misc");
     setDefPtName(settings.value("defPtName", QString("100")).toString());
     setZoomWindowValue(settings.value("zoom", 3).toInt());
     settings.endGroup();
}

void cParameters::write()
{
     QSettings settings(QApplication::organizationName(), QApplication::applicationName());

     settings.beginGroup("MainWindow");
     settings.setValue("size",              getSzFen()      );
     settings.setValue("pos",               getPosition()   );
     settings.setValue("NbFen",             getNbFen()      );
     settings.setValue("openInFullScreen",  getFullScreen() );
     settings.endGroup();

     settings.beginGroup("Drawing settings");
     settings.setValue("linethickness", getLineThickness()  );
     settings.setValue("pointdiameter", getPointDiameter()  );
     settings.setValue("pointsize",     getPointSize()      );
     settings.setValue("gamma",         getGamma()          );
     settings.endGroup();

     settings.beginGroup("Misc");
     settings.setValue("defPtName", getDefPtName()          );
     settings.setValue("zoom",      getZoomWindowValue()    );
     settings.setValue("radius",    getSelectionRadius()    );
     settings.endGroup();
}
