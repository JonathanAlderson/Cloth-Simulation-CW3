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

#include "MasterWidget.h"
#include "RenderWidget.h"

MasterWidget::MasterWidget(char *filename, char *texFilename, QWidget *parent)
{
    std::cout << "Master Widget Init" << '\n';

    // Setup the Render Widget, passing the filename
    renderWidget = new RenderWidget(filename, texFilename, this);
    renderWidget->setParent(this);

    // Timer for running animation
    timer = new QTimer(this);

    // default value
    shiftHeld = false;
    renderWidget->dwn = false;
    renderWidget->upp = false;

    // GUI Layout

    // Save/Load
    QGroupBox   *saveLoadGroup     = new QGroupBox(tr("Save/Load"));
    QPushButton *loadOBJButton     = new QPushButton("Load OBJ", this);
    QPushButton *loadTexButton     = new QPushButton("Load Texture", this);
    QPushButton *saveButton        = new QPushButton("Save", this);
                 sceneSelector     = new QComboBox();
    QVBoxLayout *saveLoadLayout    = new QVBoxLayout;


    sceneSelector->addItem("Empty Scene");
    sceneSelector->addItem("SS1 - Free Fall Sphere");
    sceneSelector->addItem("SS2 - Fixed Corners");
    sceneSelector->addItem("SS3 - Spinning Sphere");
    sceneSelector->addItem("SS3 - Wind Blowing");
    sceneSelector->addItem("Waving Flag");

    saveLoadLayout->addWidget(loadOBJButton);
    saveLoadLayout->addWidget(loadTexButton);
    saveLoadLayout->addWidget(saveButton);
    saveLoadLayout->addWidget(sceneSelector);
    saveLoadGroup ->setLayout(saveLoadLayout);

    // Settings
    QGroupBox   *settingsGroup           = new QGroupBox(tr("Settings"));
                 wireframeCheck          = new QCheckBox();
                 windCheck               = new QCheckBox();
                 texturesCheck           = new QCheckBox();
                 verletCheck             = new QCheckBox();
                 sphereSpinBox           = new QSpinBox();
    QLabel      *sphereSpinSpeedLabel    = new QLabel(tr("Spin Speed"));
                 sphereFrictionSpinBox   = new QSpinBox();
    QLabel      *sphereFrictionLabel     = new QLabel(tr("Sphere Friction"));
                 windSpeedSpinBox        = new QSpinBox();
    QLabel      *windSpeedSpinBoxLabel   = new QLabel(tr("Wind Speed"));
                 gravitySpinBox          = new QSpinBox();
    QLabel      *gravitySpinBoxLabel     = new QLabel(tr("Gravity"));
                 springConstSpinBox      = new QSpinBox();
    QLabel      *springConstSpinBoxLabel = new QLabel(tr("Spring Constant"));
                 dampConstSpinBox        = new QSpinBox();
    QLabel      *dampConstSpinBoxLabel   = new QLabel(tr("Spring Dampening"));
                 updatesSpinBox          = new QSpinBox();
    QLabel      *updateSpinBoxLabel      = new QLabel(tr("Updates Per Frame"));
    QVBoxLayout *settingsLayout          = new QVBoxLayout;

    windCheck            ->setText("Show Wind");
    wireframeCheck       ->setText("Wireframe");
    texturesCheck        ->setText("Textures");
    verletCheck          ->setText("Verlet");
    sphereSpinBox        ->setRange(0, 1000);
    sphereSpinBox        ->setSingleStep(1);
    sphereSpinBox        ->setValue(1);
    sphereFrictionSpinBox->setRange(0, 1000);
    sphereFrictionSpinBox->setSingleStep(1);
    sphereFrictionSpinBox->setValue(1);
    windSpeedSpinBox     ->setRange(0, 1000);
    windSpeedSpinBox     ->setSingleStep(1);
    windSpeedSpinBox     ->setValue(0);
    gravitySpinBox       ->setRange(0, 1000);
    gravitySpinBox       ->setSingleStep(1);
    gravitySpinBox       ->setValue(10);
    springConstSpinBox   ->setRange(0, 1000);
    springConstSpinBox   ->setSingleStep(5);
    springConstSpinBox   ->setValue(100);
    dampConstSpinBox     ->setRange(0, 1000);
    dampConstSpinBox     ->setSingleStep(1);
    dampConstSpinBox     ->setValue(10);
    updatesSpinBox       ->setRange(1, 100);
    updatesSpinBox       ->setSingleStep(5);
    updatesSpinBox       ->setValue(10);


    settingsLayout->addWidget(windCheck);
    settingsLayout->addWidget(wireframeCheck);
    settingsLayout->addWidget(texturesCheck);
    settingsLayout->addWidget(verletCheck);
    settingsLayout->addWidget(sphereSpinSpeedLabel);
    settingsLayout->addWidget(sphereSpinBox);
    settingsLayout->addWidget(sphereFrictionLabel);
    settingsLayout->addWidget(sphereFrictionSpinBox);
    settingsLayout->addWidget(windSpeedSpinBoxLabel);
    settingsLayout->addWidget(windSpeedSpinBox);
    settingsLayout->addWidget(gravitySpinBoxLabel);
    settingsLayout->addWidget(gravitySpinBox);
    settingsLayout->addWidget(springConstSpinBoxLabel);
    settingsLayout->addWidget(springConstSpinBox);
    settingsLayout->addWidget(dampConstSpinBoxLabel);
    settingsLayout->addWidget(dampConstSpinBox);
    settingsLayout->addWidget(updateSpinBoxLabel);
    settingsLayout->addWidget(updatesSpinBox);
    settingsGroup ->setLayout(settingsLayout);

    // playback
    // play, pause, stop, etc.
    QGroupBox   *playbackButtonsGroup  = new QGroupBox(tr("Playback Buttons"));
    QHBoxLayout *playbackButtonsLayout = new QHBoxLayout;
    QPushButton *stopButton            = new QPushButton;
    QPushButton *playButton            = new QPushButton;
    QPushButton *pauseButton           = new QPushButton;

    stopButton       ->setIcon(QIcon("../icons/stop.png"));
    playButton       ->setIcon(QIcon("../icons/play.png"));
    pauseButton      ->setIcon(QIcon("../icons/pause.png"));

    playbackButtonsLayout->addWidget(stopButton);
    playbackButtonsLayout->addWidget(playButton);
    playbackButtonsLayout->addWidget(pauseButton);
    playbackButtonsGroup ->setLayout(playbackButtonsLayout);

    // all ui group
    QGroupBox   *allUI       = new QGroupBox("Options");
    QVBoxLayout *allUILayout = new QVBoxLayout;

    allUILayout->addWidget(saveLoadGroup);
    allUILayout->addWidget(settingsGroup);
    allUILayout->addWidget(playbackButtonsGroup);
    allUI      ->setLayout(allUILayout);
    allUI      ->setMaximumWidth(300);

    // render box group
    QGroupBox   *renderGroup       = new QGroupBox("Render");
    QVBoxLayout *renderGroupLayout = new QVBoxLayout;

    renderGroupLayout->addWidget(renderWidget);
    renderGroup      ->setLayout(renderGroupLayout);
    renderGroup      ->setMinimumWidth(600);
    renderGroup      ->setMinimumHeight(600);

    // Master layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(renderGroup, 0, 1);
    mainLayout->addWidget(allUI, 0, 0);
    setLayout(mainLayout);

    // Set the Title
    setWindowTitle(tr("Cloth Sim"));

    // Keyboard Shortcuts
    QShortcut *playShortcut        = new QShortcut(QKeySequence("space"), this);
    QShortcut *stopShortcut        = new QShortcut(QKeySequence(Qt::Key_Backspace), this);

    // connecting keyboard shortcuts
    QObject::connect(playShortcut,        SIGNAL(activated()), this, SLOT(playPause()));
    QObject::connect(stopShortcut,        SIGNAL(activated()), this, SLOT(stop()));

    // Connecting
    connect(loadOBJButton,         SIGNAL(pressed()),                renderWidget, SLOT(loadOBJButtonPressed()));
    connect(loadTexButton,         SIGNAL(pressed()),                renderWidget, SLOT(loadTexButtonPressed()));
    connect(saveButton,            SIGNAL(pressed()),                renderWidget, SLOT(saveButtonPressed()));
    connect(sphereSpinBox,         SIGNAL(valueChanged(int)),        this,      SLOT(sphereSpinUpdate(int)));
    connect(sphereFrictionSpinBox, SIGNAL(valueChanged(int)),        this,      SLOT(sphereFrictionUpdate(int)));
    connect(windSpeedSpinBox,      SIGNAL(valueChanged(int)),        this,      SLOT(windSpeedUpdate(int)));
    connect(gravitySpinBox,        SIGNAL(valueChanged(int)),        this,      SLOT(gravityUpdate(int)));
    connect(springConstSpinBox,    SIGNAL(valueChanged(int)),        this,      SLOT(springConstUpdate(int)));
    connect(dampConstSpinBox,      SIGNAL(valueChanged(int)),        this,      SLOT(dampConstUpdate(int)));
    connect(updatesSpinBox,        SIGNAL(valueChanged(int)),        this,      SLOT(updatesUpdate(int)));
    connect(sceneSelector,         SIGNAL(currentIndexChanged(int)), this,      SLOT(updateScene(int)));
    connect(stopButton,            SIGNAL(pressed()),                this,         SLOT(stop()));
    connect(playButton,            SIGNAL(pressed()),                this,         SLOT(play()));
    connect(pauseButton,           SIGNAL(pressed()),                this,         SLOT(pause()));
    connect(timer,                 SIGNAL(timeout()),                renderWidget, SLOT(timerUpdate()));
    connect(windCheck,             SIGNAL(pressed()),                this,         SLOT(toggleWind()));
    connect(wireframeCheck,        SIGNAL(pressed()),                this,         SLOT(toggleWireframe()));
    connect(texturesCheck,         SIGNAL(pressed()),                this,         SLOT(toggleTextures()));
    connect(verletCheck,           SIGNAL(pressed()),                this,         SLOT(toggleVerlet()));

    timer->start(1);
}

// Default slider params
QSlider *MasterWidget::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

// Escape to quit and camera start moving
void MasterWidget::keyPressEvent(QKeyEvent* event)
{
  switch(event->key())
  {
    // Quit Program
    case Qt::Key_Escape:
      QCoreApplication::quit();
      break;

    ////////////////////////////////////////////
    //  CAMERA MOVEMENT
    ///////////////////////////////////////////

    // Move Camera Forwards
    case Qt::Key_W:
      if(shiftHeld){ renderWidget->upp = true; }
      else         { renderWidget->fwd = true; }
      break;
    // Move Camera Left
    case Qt::Key_A:
      renderWidget->lft = true;
      break;
    // Move Camera Backwards
    case Qt::Key_S:
      if(shiftHeld){ renderWidget->dwn = true; }
      else         { renderWidget->bkw = true; }
      break;
    // Move Camera Right
    case Qt::Key_D:
      renderWidget->rht = true;
      break;
    // Turn shift on and off
    case Qt::Key_Shift:
      shiftHeld = true;
      break;
    // Turn lock key on and off
    case Qt::Key_L:
      renderWidget->lockHeld = true;
      break;
  }

  // Default
  QWidget::keyPressEvent(event);
}

// for stopping camera movement
void MasterWidget::keyReleaseEvent(QKeyEvent* event)
{
  switch(event->key())
  {
    ////////////////////////////////////////////
    //  CAMERA MOVEMENT
    ///////////////////////////////////////////
    // Quit Program
    case Qt::Key_Escape:
      QCoreApplication::quit();
      break;
    // Move Camera Forwards
    case Qt::Key_W:
      renderWidget->upp = false;
      renderWidget->fwd = false;
      break;
    // Move Camera Left
    case Qt::Key_A:
      renderWidget->lft = false;
      break;
    // Move Camera Backwards
    case Qt::Key_S:
      renderWidget->dwn = false;
      renderWidget->bkw = false;
      break;
    // Move Camera Right
    case Qt::Key_D:
      renderWidget->rht = false;
      break;

    // bool for rotation and movement locking
    case Qt::Key_Shift:
      shiftHeld = false;
      renderWidget->upp = false;
      renderWidget->dwn = false;
      break;
    // Turn lock key on and off
    case Qt::Key_L:
      renderWidget->lockHeld = false;
      break;
  }

  // Default
  QWidget::keyReleaseEvent(event);
}

// Zooming in/out
void MasterWidget::wheelEvent(QWheelEvent* event)
{
  QPoint numDegrees = event->angleDelta();

  if(numDegrees.y() > 0)
  {
    if(renderWidget->zoom < 2.){ renderWidget->camera.ProcessMouseScroll(1);}
  }
  else
  {
    if(renderWidget->zoom > 0.1){ renderWidget->camera.ProcessMouseScroll(-1); }
  }

  renderWidget->updatePerspective();
  renderWidget->updateGL();

}

// Pauses The Current Animation
void MasterWidget::pause()
{
  renderWidget->paused = true;
}

// Plays The Current Animation
void MasterWidget::play()
{
  renderWidget->paused = false;
}


// Changes the boolean
void MasterWidget::playPause()
{
  bool p = renderWidget->paused;
  if(p){ renderWidget->paused = false; return; }
  else{ renderWidget->paused = true; return; }
}

// resets the scene to how it was at the start
void MasterWidget::stop()
{
  // remember these as once we reset they will be forgotten
  bool oldTex  = renderWidget->sim->cloth->useTextures;
  bool oldWire = renderWidget->sim->cloth->wireframeRender;
  renderWidget->reset();

  // reset to what they were
  renderWidget->sim->cloth->useTextures = oldTex;
  renderWidget->sim->cloth->wireframeRender = oldWire;

  // update screen
  renderWidget->sim->Render(renderWidget->sim->cFrame, &(renderWidget->camera));
  renderWidget->updateGL();

}

// changes the rendering mode for the cloth
void MasterWidget::toggleWireframe()
{
  if(renderWidget->sim->cloth->wireframeRender == 0)
  {
    renderWidget->sim->cloth->wireframeRender = 1;
    renderWidget->sim->cloth->useTextures = 0;
    wireframeCheck->setChecked(true);
    texturesCheck->setChecked(false);
  }
  else
  {
    renderWidget->sim->cloth->wireframeRender = 0;
    wireframeCheck->setChecked(false);
  }
}

// changes the rendering mode to include textures
void MasterWidget::toggleTextures()
{
  if(renderWidget->sim->cloth->useTextures == 0)
  {
    renderWidget->sim->cloth->useTextures = 1;
    renderWidget->sim->cloth->wireframeRender = 0;
    texturesCheck->setChecked(true);
    wireframeCheck->setChecked(false);
  }
  else
  {
    renderWidget->sim->cloth->useTextures = 0;
    texturesCheck->setChecked(false);
  }
}

// turns the wind on or off
void MasterWidget::toggleWind()
{
  if(renderWidget->sim->wind->show == false)
  {
    // enable control
    renderWidget->sim->wind->show = true;
    windCheck->setChecked(true);
  }
  else
  {
    renderWidget->sim->wind->show = false;
    windCheck->setChecked(false);
  }
}

// turns on and off verlet intergration
void MasterWidget::toggleVerlet()
{
  if(renderWidget->sim->intergration == EULER)
  {
    renderWidget->sim->intergration = VERLET;
    verletCheck->setChecked(true);
  }
  else
  {
    renderWidget->sim->intergration = EULER;
    verletCheck->setChecked(false);
  }
}

// updates the sphere friction
void MasterWidget::sphereFrictionUpdate(int i)
{
  renderWidget->sim->sphereFriction = i;

  sphereFrictionSpinBox->setValue(i);
}

// update sphere rotation
void MasterWidget::sphereSpinUpdate(int i)
{
  renderWidget->sim->sphereSpin = (float)i;

  sphereSpinBox->setValue(i);
}

// update the wind speed
void MasterWidget::windSpeedUpdate(int i)
{
  renderWidget->sim->wind->speed = (float)i;

  windSpeedSpinBox->setValue(i);
}

// update gravity of the simulation
void MasterWidget::gravityUpdate(int i)
{
  renderWidget->sim->cloth->UpdateGravity((float)i);

  gravitySpinBox->setValue(i);
}

// update springConst of the simulation
void MasterWidget::springConstUpdate(int i)
{
  for(unsigned int j = 0; j < renderWidget->sim->cloth->springs.size(); j++)
  {
    renderWidget->sim->cloth->springs[j].springConst = (float) i;
  }

  springConstSpinBox->setValue(i);
}

// update dampConst of the simulation
void MasterWidget::dampConstUpdate(int i)
{
  for(unsigned int j = 0; j < renderWidget->sim->cloth->springs.size(); j++)
  {
    renderWidget->sim->cloth->springs[j].dampingConst = (float) i;
  }

  dampConstSpinBox->setValue(i);
}

// the amount of times per frame we do a simlulation
void MasterWidget::updatesUpdate(int i)
{
  renderWidget->sim->updatesPerFrame = i;

  updatesSpinBox->setValue(i);
}


// changes the whole scene and everything to do with it!
// This whole part could be easily saved into differnet files and such but for the time being, we are just going to do it this way
void MasterWidget::updateScene(int i)
{
  std::cout << "Updating Scene: " << i << '\n';

  // clear everything and reset what we need to
  renderWidget->sim->spheres.clear();
  renderWidget->sim->planes.clear();
  delete renderWidget->sim->cloth;
  renderWidget->zoom = 1.0;
  renderWidget->cTime = 0.;
  renderWidget->renderFrame = 0;




  // load a default cloth
  if(i == 0)
  {
    // init cloth with obj file
    renderWidget->sim = new Simulation("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/objFiles/cloth-10x10.obj");

    std::cout << "Did it1" << '\n';
  }

  // Horizontal cloth floating on sphere
  if(i == 1)
  {
    renderWidget->sim = new Simulation("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/objFiles/clothR-10x10.obj");
    renderWidget->sim->AddSphere(0.5, 0., Cartesian3(0., -2., 0.), 2.);
    renderWidget->sim->AddPlane(Cartesian3(0., -5., 0.), 6., 6., 1.);

    gravityUpdate(10);
    windSpeedUpdate(0);
    springConstUpdate(400);
    dampConstUpdate(10);
    updatesUpdate(50);
  }

  // Horizontal Cloth Fixed Edges
  if(i == 2)
  {
    renderWidget->sim = new Simulation("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/objFiles/lockedCorners.obj");

    gravityUpdate(10);
    windSpeedUpdate(0);
    springConstUpdate(700);
    dampConstUpdate(50);
    updatesUpdate(50);
  }

  // Rotating Spheres
  if(i == 3)
  {
    renderWidget->sim = new Simulation("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/objFiles/clothR-20x20.obj");

    renderWidget->sim->AddSphere(0.5, 5., Cartesian3(0., -2., 0.), 2.);
    gravityUpdate(10);
    windSpeedUpdate(0);
    springConstUpdate(7000);
    dampConstUpdate(50);
    updatesUpdate(50);
  }


  // Hanging and blowing in the wind
  if(i == 4)
  {
    renderWidget->sim = new Simulation("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/objFiles/lockedCorners.obj");

    gravityUpdate(10);
    windSpeedUpdate(5);
    springConstUpdate(700);
    dampConstUpdate(50);
    updatesUpdate(50);

    if(renderWidget->sim->wind->show == false)
    {
      toggleWind();
    }
  }

  // Waving flag blowing in the wind
  if(i == 5)
  {
    renderWidget->sim = new Simulation("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/objFiles/wavingFlag.obj");

    std::ifstream textureStream("/home/sc17j3a/Documents/University/Animation And Simulation/animation-cw3-cloth-sim/textures/unionJack.ppm");
    renderWidget->texture.ReadPPM(textureStream);
    renderWidget->TransferTexture();

    gravityUpdate(3);
    windSpeedUpdate(20);
    springConstUpdate(1000);
    dampConstUpdate(50);
    updatesUpdate(50);

    if(renderWidget->sim->wind->show == false)
    {
      toggleWind();
    }


  }


  // find new global positions
  renderWidget->sim->FindGlobalPosition(&(renderWidget->camera));
  renderWidget->mousePicker = new MousePick(&(renderWidget->sim->globalPositions), 1.0);

  // update the screen
  renderWidget->updateGL();
  renderWidget->paintGL();
}
