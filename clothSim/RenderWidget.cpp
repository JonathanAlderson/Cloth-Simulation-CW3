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

#include <math.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "RenderWidget.h"

// constructor
RenderWidget::RenderWidget(char *filename, char *texFilename, MasterWidget *parent)
	: QGLWidget(parent)
	{ // constructor
		this->parentWidget = parent;

		// load a new file
		if(strlen(filename) == 0){sim = new Simulation(); }
		else {sim = new Simulation(filename); }
		sim->FindGlobalPosition(&camera);

		// save the filename for reseting
		std::string stringFile(filename);
		curFileName = stringFile;

		// set default values
		whichButton = -1;

		// if we click on a point when this is active it becomes stationary
		lockHeld = false;

		// will change when scolling
		//size = bvh->boundingBoxSize;

		// setup the texture
		std::ifstream textureStream(texFilename);
		texture.ReadPPM(textureStream);

		// zoom amout
		zoom = 1.0;

		// timer Setup
		cTime = 0.;
		renderFrame = 0;
		paused = true;
		playbackSpeed = 1.0;

		// mouse position init
		mouseLastX = 0.;
		mouseLastY = 0.;

		// default camera values
		fwd = false;
		lft = false;
		rht = false;
		bkw = false;
		upp = false;
		dwn = false;

		// timing info
		thisTime = QDateTime::currentDateTimeUtc();
		lastTime = QDateTime::currentDateTimeUtc();

		// initialise the mouse clicker
		// todo mouse pick
		mousePicker = new MousePick(&(sim->globalPositions), 1.0);

		// Construct Camera with default values
		camera = Camera(glm::vec3(0.f, 0.f, 5.f));
		movingCamera = false;

		setMouseTracking(true);



    // Recording Setup
    // --------------------
		framerate = 60;
    maxFrames = 120;
		doScreenRecording = false;
    screenRecord = new ScreenRecord(1, maxFrames, framerate);
    std::thread startUp(&ScreenRecord::clearSections, screenRecord);
    startUp.join();


	} // constructor

// destructor
RenderWidget::~RenderWidget()
	{ // destructor
	// nothing yet
	} // destructor

// called when OpenGL context is set up
void RenderWidget::initializeGL()
{ // RenderWidget::initializeGL()
	// enable Z-buffering
	glEnable(GL_DEPTH_TEST);

	// set lighting parameters
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_BLEND);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	GLfloat lightPos0[] = {-2.f, 2.f, 2.f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	glColor3f(1., 1., 1.);

	// set the texture parameters
	glEnable(GL_TEXTURE_2D);

	// background is a nice blue
	glClearColor(189. / 255., 215. / 255., 217. / 255., 1.0);

	// setup the texutre so it can be sampled from
	TransferTexture();

} // RenderWidget::initializeGL()

// routine to transfer assets to GPU
// Hamish made this method
void RenderWidget::TransferTexture()
{ // TransferAssetsToGPU()
    // when this is called, it transfers assets to the GPU.
    // for now, it will only be to transfer the texture
    // this may not be efficient, but it supports arbitrary sizes best
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // create a texture ID (essentially a pointer)
    glGenTextures(1, &textureID);
    // now bind to it - i.e. all following code addresses this one
    glBindTexture(GL_TEXTURE_2D, textureID);
    // set these parameters to avoid dealing with mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // now transfer the image
    glTexImage2D(
        GL_TEXTURE_2D,      // it's a 2D texture
        0,                  // mipmap level of 0 (ie the largest one)
        GL_RGBA,            // we want the data stored as RGBA on GPU
        texture.width,      // width of the image
        texture.height,     // height of the image
        0,                  // width of border (in texels)
        GL_RGBA,            // format the data is stored in on CPU
        GL_UNSIGNED_BYTE,   // data type
        texture.block       // and a pointer to the data
        );
		glBindTexture(GL_TEXTURE_2D, textureID);
} // TransferAssetsToGPU()


// called every time the widget is resized
void RenderWidget::resizeGL(int w, int h)
	{ // RenderWidget::resizeGL()

	// save the size of the screen
	screenW = w;
	screenH = h;

	// reset the viewport
	glViewport(0, 0, w, h);

	// set projection matrix to be glOrtho based on zoom & window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	// compute the aspect ratio of the widget
	float aspectRatio = (float) w / (float) h;

	// depending on aspect ratio, set to accomodate a sphere of radius = diagonal without clipping
	gluPerspective(camera.Zoom, aspectRatio, 0.1, 1000.);

	std::cout << "ResizeGL" << '\n';
	} // RenderWidget::resizeGL()

void RenderWidget::updatePerspective()
{ // updatePerspective()
	std::cout << "Update gluPerspective" << '\n';
	float aspectRatio = (float) screenW / (float) screenH;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(camera.Zoom, aspectRatio, 0.1, 1000.);
} // updatePerspective()

// called every time the widget needs painting
void RenderWidget::paintGL()
	{ // RenderWidget::paintGL()
	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set lighting on
	glEnable(GL_LIGHTING);

	// set model view matrix based on stored translation, rotation &c.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set light position first
	// retrieve rotation from arcball & apply
	glMultMatrixf(lightMatrix);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// apply translation for interface control
	glLoadIdentity();

	// stop Qt stealing focus
	this->setFocus();

	// Apply Rotation From Camera
	GLfloat view[16];
	glm::mat4 viewIn = camera.GetViewMatrix();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{ // convert from Mat4 to float[16]
			view[i * 4 + j] = viewIn[i][j];
		}
	}
	glMultMatrixf(view);

	// translate based on animation
	// Cartesian3 min = bvh->minCoords;
	// Cartesian3 max = bvh->maxCoords;
	// float xTrans = (max.x + min.x) / 2.;
	// float yTrans = (max.y + min.y) / 2.;
	// float zTrans = min.z;

	//std::cout << xTrans << " " << yTrans << " " << zTrans << '\n';
	//glTranslatef(-xTrans, -yTrans, zTrans - 25.);

	// Render Simulation
	sim->Render(renderFrame, &camera);

	} // RenderWidget::paintGL()

// mouse-handling
void RenderWidget::mousePressEvent(QMouseEvent *event)
	{ // RenderWidget::mousePressEvent()
	// store the button for future reference
	whichButton = event->button();

	// find the minimum of height & width
	float size = (width() > height()) ? height() : width();

	float currX = (2.0 * event->x() - width()) / width();
	float currY = (height() - 2.0 * event->y() ) / height();

	// start moving the camera if we click
	if(whichButton == 1)
	{
		movingCamera = true;
	}
	camera.updateCameraVectors();

	//Perform Mouse Picking -1 if no match
	int clicked = mousePicker->click(currX, currY, &camera);

  // if clicked on nothign clear list
	if(clicked == -1)
	{
		sim->cloth->activePoint = -1;
	}
	else
	{
		sim->cloth->activePoint = clicked;
		// if we are holding the L button, make the point unable to be clicked
		if(lockHeld)
		{
			if(sim->cloth->points[clicked].fixed == true)
			{
				sim->cloth->points[clicked].fixed = false;
				sim->cloth->points[clicked].CalculateColour();
			}
			else
		  {
				sim->cloth->points[clicked].fixed = true;
				sim->cloth->points[clicked].CalculateColour();
			}

		}
	}

	// So we can see the newly highlighted joint
	updateGL();
	} // RenderWidget::mousePressEvent()

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{ // RenderWidget::mouseMoveEvent()
	// find the minimum of height & width
	float size = (width() > height()) ? height() : width();

	// TODO Mouse Move To Camera
	float currX = (2.0 * event->x() - width()) / width();
	float currY = (height() - 2.0 * event->y() ) / height();


	if(mousePicker->dragging == true)
	{
		Cartesian3 mouseMove = mousePicker->drag(currX, currY, &camera);

		mouseMove.x = -mouseMove.x;
		mouseMove.y = -mouseMove.y;

		// TODO make this a sensetivity
		//mouseMove = 1000.0;

		sim->cloth->ApplyForce(mouseMove);
		updateGL();

	}

	// only move the camera if we are not dragging
	if(mousePicker->dragging == false && movingCamera)
	{
		updateGL();
		camera.ProcessMouseMovement((mouseLastX - currX) * 200., (mouseLastY - currY) * 200.);
	}

	// Update
	mouseLastY = currY;
	mouseLastX = currX;



} // RenderWidget::mouseMoveEvent()


void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
	{ // RenderWidget::mouseReleaseEvent()
	// now either translate or rotate object or light


	mousePicker->dragging = false; // stop from dragging
	movingCamera = false; // camera will not move anymore

	} // RenderWidget::mouseReleaseEvent()

	QSize RenderWidget::minimumSizeHint()
	{
		return QSize(50, 50);
	}


	QSize RenderWidget::sizeHint()
	{
		return QSize(600, 600);
	}

// simply reloads the scene
void RenderWidget::reset()
{
	sim = new Simulation(curFileName.c_str());
	sim->FindGlobalPosition(&camera);
	// initialise the mouse clicker
	mousePicker = new MousePick(&(sim->globalPositions), 1.0);

	// reset the camera here
	updateGL();
	paintGL();
}


// Loads a new obj the user wants to see
void RenderWidget::loadOBJButtonPressed()
{
	newFileName = QFileDialog::getOpenFileName(this,
    tr("Open OBJ File"), "../objFiles", tr("OBJ Files (*.obj)"));

	// Debug
  std::cout << "Reading: ";
	std::cout << newFileName.toStdString() << '\n';

	curFileName = newFileName.toStdString();
	if(newFileName.toStdString().size() > 0)
	{
		// reset default values
		zoom = 1.0;
		cTime = 0.;
		renderFrame = 0;

		sim = new Simulation(newFileName.toStdString().c_str());
		sim->FindGlobalPosition(&camera);

	  sim->AddPlane(Cartesian3(0., -5., 0.), 12., 12., 1.);

		// initialise the mouse clicker
		mousePicker = new MousePick(&(sim->globalPositions), 1.0);

		// reset the camera here
		updateGL();
		paintGL();
	}
}

// Loads a new tex the user wants to see
void RenderWidget::loadTexButtonPressed()
{
	newTexName = QFileDialog::getOpenFileName(this,
    tr("Open Texture File"), "../textures", tr("Textures (*.ppm)"));

	// Debug
  std::cout << "Reading: ";
	std::cout << newTexName.toStdString() << '\n';

	if(newTexName.toStdString().length() > 0)
	{
		std::ifstream textureStream(newTexName.toStdString().c_str());
		texture.ReadPPM(textureStream);
		TransferTexture();

		// reset the camera here
		updateGL();
		paintGL();
	}

}

void RenderWidget::saveButtonPressed()
{
	// if we need to start playing the animation again
	bool reset = false;
	// pause the animation
	if(paused == false){ paused = true;; reset = true; }


	// get the filename
  QString fileName = QFileDialog::getSaveFileName(this,
                     tr("Save .obj File"), tr(".obj"),
                     tr("OBJ (*.obj)"));

	if(fileName.toStdString().length() > 0)
	{
		sim->SaveFile(fileName.toStdString());
	}

	if(reset)
	{
		paused = false;
	}
}


// Update the timer and calculate the current frame of animation
void RenderWidget::timerUpdate()
{

	// Control Camera Movement
	thisTime = QDateTime::currentDateTimeUtc();


	qint64 delta = lastTime.msecsTo(thisTime);

	bool updateNeeded = false;

	// Control Playback
	if(paused == false)
	{
		// MS Conversion
		cTime += delta * playbackSpeed;
		int thisRenderframe = (int)((cTime / ((1. / 60.) * 1000))) % (int)(sim->numFrame);

		// Only Update If We need To
		if(thisRenderframe != renderFrame)
		{
			for(int i = 0; i < sim->updatesPerFrame; i++)
			{
				sim->Update((1. / 60.) / sim->updatesPerFrame);
			}
			// actually redraw the screen
			updateNeeded = true;

			// increment frame
			renderFrame++;
		}
	}

	// Update Timer
	lastTime = thisTime;

	// update the frame if needed
	if(updateNeeded || paused == true)
	{
		// Do camera movement
		// so we only check this 60 times a second, instead of 1000
		if(fwd){ camera.ProcessKeyboard(FORWARD , delta / 300.); }
		if(lft){ camera.ProcessKeyboard(LEFT    , delta / 300.); }
		if(rht){ camera.ProcessKeyboard(RIGHT   , delta / 300.); }
		if(bkw){ camera.ProcessKeyboard(BACKWARD, delta / 300.); }
		if(upp){ camera.ProcessKeyboard(UP      , delta / 300.); }
		if(dwn){ camera.ProcessKeyboard(DOWN    , delta / 300.); }

		if(fwd || lft || rht || bkw || upp || dwn)
		{
			updateNeeded = true;
		}

		if(updateNeeded)
		{
			std::cout << "Updating" << '\n';

			// draw to the screen
			updateGL();

			// update the global positions
			sim->FindGlobalPosition(&camera);
			mousePicker->UpdateTargetPoints(&(sim->globalPositions));

			if(doScreenRecording && renderFrame <= maxFrames)
			{
				screenRecord->recordFrame(renderFrame);
				std::cout << "Record Frame " << renderFrame << '\n';
				if((int)renderFrame % 60 == 0 && renderFrame > 0){ std::cout << " Saving " << std::endl; std::thread addImagesThread(&ScreenRecord::imagesToVideoSegment, screenRecord); addImagesThread.join(); }
			}
		}

	}

	if(renderFrame == maxFrames)
	{
		if(doScreenRecording)
		{
			std::cout << "Saving Final Video" << '\n';
			std::thread compileVideoThread(&ScreenRecord::saveVideo, screenRecord);
			compileVideoThread.join();
			std::cout << "Saved" << '\n';
		}
	}
}
