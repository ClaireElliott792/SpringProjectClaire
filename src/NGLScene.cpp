#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <iostream>

float angle;

short CATEGORY_GROUND = 0x0001;
short CATEGORY_SPRING = 0x0002;
short CATEGORY_BALL = 0x0004;

NGLScene::NGLScene()
{
  setTitle("Spring Project");
}

NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_width = _w * devicePixelRatio();
  m_height = _h * devicePixelRatio();
}

void NGLScene::initializeGL()
{
  ngl::NGLInit::initialize();

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  ngl::ShaderLib::use("nglDiffuseShader");
  ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 0.0f, 1.0f);
  ngl::ShaderLib::setUniform("lightPos", 0.2f, 0.2f, 1.0f);
  ngl::ShaderLib::setUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);

  glViewport(0, 0, width(), height());
  m_projection = ngl::ortho(-40, 40, -20, 20, 0.1f, 10.0f);
  ngl::Vec3 from(0, 0, 1);
  ngl::Vec3 to(0, 0, 0);
  ngl::Vec3 up(0, 1, 0);
  m_view = ngl::lookAt(from, to, up);
  b2Vec2 gravity(0.0f, -20.0f);
  m_world.reset(new b2World(gravity));

  // float springAngle;
  // int springCompression;

  // std::cout << "Spring angle?" << std::endl;
  // std::cin >> springAngle;
  // std::cout << "Spring compression?" << std::endl;
  // std::cin >> springCompression;

  //ground
  b2BodyDef groundBodyDef;
  groundBodyDef.angularDamping = 0.3f;
  groundBodyDef.position.Set(0.0f, -20.0f);
  b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  // groundBox.filter.categoryBits = CATEGORY_GROUND;
  groundBox.SetAsBox(80.0f, 2.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);

  // spring
  b2BodyDef springDef;
  springDef.type = b2_dynamicBody;
  springDef.position.Set(-38.0f, -17.0f);
  m_spring = m_world->CreateBody(&springDef);
  m_spring->SetFixedRotation(false);


  b2PolygonShape dynamicSpring;
  dynamicSpring.SetAsBox(12.0f, 2.0f);
  b2FixtureDef fixtureDef1;
  fixtureDef1.shape = &dynamicSpring;
  // fixtureDef1.filter.categoryBits = CATEGORY_SPRING;
  fixtureDef1.filter.maskBits = 0;
  m_spring->CreateFixture(&fixtureDef1);
  

  angle = 45 * 0.0174533;

  // ball 
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(-36.5f, -15.5f);
  m_body = m_world->CreateBody(&bodyDef);

  // int force = springCompression * 10;
  // std::cout << angle << std::endl;
  // float x_force = fabs(force * cos(angle));
  // float y_force = fabs(force * sin(angle));

  // std::cout << x_force << std::endl;
  // std::cout << y_force << std::endl;

  // m_body->SetLinearVelocity(b2Vec2(x_force, y_force));
  m_body->SetLinearDamping(0.1f);
  m_body->SetAngularVelocity(0);
  m_body->SetFixedRotation(false);

  b2CircleShape dynamicBox;
  // dynamicBox.m_p.Set(1.0f, 1.0f);
  dynamicBox.m_radius = 0.5f;
  b2FixtureDef fixtureDef2;
  fixtureDef2.shape = &dynamicBox;
  fixtureDef2.density = 0.3f;
  fixtureDef2.friction = 0.3f;
  fixtureDef2.restitution = 0.7f;
  // fixtureDef2.filter.categoryBits = CATEGORY_BALL;
  // fixtureDef2.filter.maskBits = 0;
  m_body->CreateFixture(&fixtureDef2);

  // startTimer(10);
}

void NGLScene::loadMatricesToShader()
{
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  MVP = m_projection * m_view * m_transform.getMatrix();
  normalMatrix = m_view * m_transform.getMatrix();
  normalMatrix.inverse().transpose();
  ngl::ShaderLib::setUniform("MVP", MVP);
  ngl::ShaderLib::setUniform("normalMatrix", normalMatrix);
}

void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_width, m_height);
  ngl::ShaderLib::use("nglDiffuseShader");

  // draw floor
  m_transform.reset();
  {
    ngl::ShaderLib::setUniform("Colour", 0.0f, 1.0f, 0.0f, 1.0f);
    m_transform.setScale(80.0, 3.0, 0.1);
    m_transform.setPosition(0, -20, 0);
    loadMatricesToShader();
    ngl::VAOPrimitives::draw("cube");
  }

  // draw spring
  m_transform.reset();
  {
    b2Vec2 position = m_spring->GetPosition();

    ngl::ShaderLib::setUniform("Colour", 1.0f, 1.0f, 0.0f, 0.0f);
    m_transform.setScale(12.0, 2, 0.1);
    m_transform.setPosition(position.x, position.y, 0);
    m_transform.setRotation(0, 0, (angle*57.2958));
    loadMatricesToShader();
    ngl::VAOPrimitives::draw("cube");
  }

  // draw object fired
  m_transform.reset();
  {
    b2Vec2 position = m_body->GetPosition();

    ngl::ShaderLib::setUniform("Colour", 1.0f, 0.0f, 0.0f, 1.0f);
    // m_transform.setScale(1.0f, 1.0f, 0.1f);
    m_transform.setPosition(position.x, position.y, 0);
    m_transform.setRotation(0, 0, 0);
    loadMatricesToShader();
    ngl::VAOPrimitives::draw("football");
  }
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent(QMouseEvent *_event)
{
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent(QMouseEvent *_event)
{
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent(QMouseEvent *_event)
{
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  m_keysPressed += (Qt::Key)_event->key();

  float x;
  float y;
  float hypothenuse;
  float x_dist;
  float y_dist;
  float spring_compression;
  float x_force;
  float y_force;

  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape:
    QGuiApplication::exit(EXIT_SUCCESS);
    break;
  case Qt::Key_Left:
    angle = angle + 0.01;

    x_dist = m_body->GetPosition().x + 38;
    y_dist = m_body->GetPosition().y + 17;

    hypothenuse = sqrt((y_dist * y_dist) + (x_dist * x_dist));

    x = -38 + (cos(angle)*hypothenuse);
    y = -17 + (sin(angle)*hypothenuse);

    m_body->SetTransform(b2Vec2(x, y), 0);
    m_spring->SetTransform(m_spring->GetPosition(), angle);

    break;
  case Qt::Key_Right:
    if (angle < 0)
    break;

    angle = angle - 0.01;

    x_dist = m_body->GetPosition().x + 38;
    y_dist = m_body->GetPosition().y + 17;

    hypothenuse = sqrt((y_dist * y_dist) + (x_dist * x_dist));

    x = -38 + (cos(angle)*hypothenuse);
    y = -17 + (sin(angle)*hypothenuse);

    m_body->SetTransform(b2Vec2(x, y), 0);

    m_spring->SetTransform(m_spring->GetPosition(), angle);
    break;
  case Qt::Key_Up:
    x = m_body->GetPosition().x + fabs(0.1 * cos(angle));
    y = m_body->GetPosition().y + fabs(0.1 * sin(angle));
    // std::cout << y << std::endl;
    if (y < -14.5)
      m_body->SetTransform(b2Vec2(x, y), angle);
    break;
  case Qt::Key_Down:
    x = m_body->GetPosition().x - fabs(0.1 * cos(angle));
    y = m_body->GetPosition().y - fabs(0.1 * sin(angle));
    if (y > -17.5)
      m_body->SetTransform(b2Vec2(x, y), angle);
    break;
  // turn on wirframe rendering
  case Qt::Key_W:
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    break;
  // turn off wire frame
  case Qt::Key_S:
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    break;
  // show full screen
  case Qt::Key_F:
    showFullScreen();
    break;
  // show windowed
  case Qt::Key_N:
    showNormal();
    break;

  case Qt::Key_P:
    spring_compression = 20 + m_body->GetPosition().y;

    x_force = spring_compression * cos(angle) * 10;
    y_force = spring_compression * sin(angle) * 10;

    std::cout << x_force << std::endl;
    std::cout << y_force << std::endl;

    m_body->SetLinearVelocity(b2Vec2(x_force, y_force));

    startTimer(10);
  break;

  default:
    break;
  }
  // finally update the GLWindow and re-draw
  // if (isExposed())

  update();
}

void NGLScene::keyReleaseEvent(QKeyEvent *_event)
{
  m_keysPressed -= (Qt::Key)_event->key();
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  auto timeStep = 1.0f / 300.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;
  m_world->Step(timeStep, velocityIterations, positionIterations);
  // process all the key presses
  b2Vec2 move(0.0f, 0.0f);

  // std::cout << m_body->GetPosition().x << std::endl;
  // std::cout << m_body->GetWorldCenter().x << std::endl;
  // std::cout << m_body->GetPosition().y << std::endl;
  // std::cout << m_body->GetWorldCenter().y << std::endl;

  m_body->ApplyForce(move, m_body->GetWorldCenter(), true);

  // constrain to window by bouncing!
  b2Vec2 pos = m_body->GetPosition();
  b2Vec2 dir = m_body->GetLinearVelocity();
  // reverse
  if ((pos.x <= -39 || pos.x > 39))
  {
    dir = -dir;
    m_body->SetLinearVelocity(dir);
  }

  update();
}
