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
#include <QComboBox>

class RenderWidget;

class MasterWidget : public QWidget
{
    Q_OBJECT

public:
    MasterWidget(char *filename, char *texFilename, QWidget *parent);

    void keyPressEvent(QKeyEvent* event); // so we can escape to quit
    void keyReleaseEvent(QKeyEvent* event); // so we can control our camera nicely

    void wheelEvent(QWheelEvent* event); // zooms in/out

    bool shiftHeld;

private:
    QSlider *createSlider();

    RenderWidget *renderWidget;
    QPushButton  *loadOBJButton;
    QPushButton  *loadTexButton;
    QTimer       *timer;
    QCheckBox    *windCheck;
    QCheckBox    *wireframeCheck;
    QCheckBox    *texturesCheck;
    QCheckBox    *verletCheck;
    QCheckBox    *recordCheck;
    QSpinBox     *sphereSpinBox;
    QSpinBox     *sphereFrictionSpinBox;
    QSpinBox     *windSpeedSpinBox;
    QSpinBox     *gravitySpinBox;
    QSpinBox     *springConstSpinBox;
    QSpinBox     *dampConstSpinBox;
    QSpinBox     *updatesSpinBox;
    QSpinBox     *maxFramesSpinBox;
    QComboBox    *sceneSelector;

// playback controls
public slots:
  void pause();
  void play();
  void stop();
  void playPause();
  void toggleWireframe();
  void toggleTextures();
  void toggleWind();
  void toggleRecord();
  void toggleVerlet();
  void sphereFrictionUpdate(int i);
  void sphereSpinUpdate(int i);
  void gravityUpdate(int i);
  void windSpeedUpdate(int i);
  void springConstUpdate(int i);
  void dampConstUpdate(int i);
  void updatesUpdate(int i);
  void maxFramesUpdate(int i);
  void updateScene(int i);

};

#endif
