///////////////////////////////////////////////////
//
//	Hamish Carr
//	January, 2018
//
//	------------------------
//	RenderWidget.h
//	------------------------
//
//	The main widget that shows the geometry
//
///////////////////////////////////////////////////

#ifndef _GEOMETRIC_WIDGET_H
#define _GEOMETRIC_WIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QDateTime>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iostream>
#include <thread>
#include "MousePick.h"
#include "MasterWidget.h"
#include "Simulation.h"
#include "camera.h"
#include "screenRecord.h"
#include "RGBAImage.h"

class RenderWidget : public QGLWidget
	{ // class RenderWidget
	Q_OBJECT
	public:

	// our parent
	MasterWidget *parentWidget;

	// the whole simulation scene
	Simulation * sim;

	// for resolving clicks on the screen to 3D coordinates
	MousePick *mousePicker;

	// for making points locked in place
	bool lockHeld;

	// translation in window x,y
	GLfloat lastX, lastY;

	// which button was last pressed
	int whichButton;

	// for reading/writing/reseting a file
	QString newFileName;
	string  curFileName;
	QString newTexName;

	float size;

	// can be changed by scrolling
	float zoom;

	// playback options
	float cTime;
	float startTime;
	int renderFrame;
	bool paused;
	float playbackSpeed;

	// camera options
	bool fwd;
	bool lft;
	bool rht;
	bool bkw;
	bool upp;
	bool dwn;

	// time options
	QDateTime thisTime;
	QDateTime lastTime;

	// screen
	float screenW;
	float screenH;

	// Lights
	const GLfloat lightMatrix[16] = {1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1.};
	const GLfloat light_position[4] = {0.0, 0.0, 1.0, 0.0};

	// Camera
	Camera camera;
	bool movingCamera;

	// Mouse
	float mouseLastX;
	float mouseLastY;

	// texture stuff
	GLuint textureID;
	RGBAImage texture;

	// screen recording
	ScreenRecord * screenRecord;
	bool doScreenRecording;
	int maxFrames;
	int framerate;

	// Action
	RenderWidget(char *filename, char *texFilename, MasterWidget *parent);

	// destructor
	~RenderWidget();

	// allowing the camera to zoom in
	void updatePerspective();

	// loads a texutre
	void TransferTexture();

	// called when OpenGL context is set up
	void initializeGL();
	// called every time the widget is resized
	void resizeGL(int w, int h);
	// called every time the widget needs painting
	void paintGL();

	// mouse-handling
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

	// Resizing functions
	QSize minimumSizeHint();
	QSize sizeHint();

	// gui controls
	public slots:
		void loadOBJButtonPressed();
		void loadTexButtonPressed();
		void saveButtonPressed();
		void reset();
		void timerUpdate();

	}; // class RenderWidget

#endif
