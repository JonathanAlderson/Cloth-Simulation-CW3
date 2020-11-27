///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	MasterWidget.h
//	------------------------
//
//	The main widget that houses the GUI and the OpenGL
//
///////////////////////////////////////////////////

#ifndef _MASTER_WIDGET_H
#define _MASTER_WIDGET_H

#include <QGLWidget>
#include <QSlider>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QTimer>
#include <QSpinBox>
#include <QShortcut>
#include <QWheelEvent>
#include <QCoreApplication>
#include <QCheckBox>


class RenderWidget;

class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    MasterWidget(char *filename, QWidget *parent);

    void keyPressEvent(QKeyEvent* event); // so we can escape to quit
    void keyReleaseEvent(QKeyEvent* event); // so we can control our camera nicely

    void wheelEvent(QWheelEvent* event); // zooms in/out

    bool shiftHeld;

private:
    QSlider *createSlider();

    RenderWidget *renderWidget;
    QPushButton  *loadButton;
    QTimer       *timer;
    QSpinBox     *sphereSpinBox;
    QSpinBox     *sphereFrictionSpinBox;
    QSpinBox     *windSpeedSpinBox;
    QSpinBox     *gravitySpinBox;
    QCheckBox    *sphereCheck;
    QCheckBox    *windCheck;
    QCheckBox    *fixedCornersCheck;

// playback controls
public slots:
  void pause();
  void play();
  void stop();
  void playPause();
  void toggleSphere();
  void toggleWind();
  void toggleFixedCorners();
  void sphereFrictionUpdate(int i);
  void sphereSpinUpdate(int i);
  void gravityUpdate(int i);
  void windSpeedUpdate(int i);

};

#endif
