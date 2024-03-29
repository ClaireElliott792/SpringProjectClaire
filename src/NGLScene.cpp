// Box2D Docuemntation, 'A 2D Physics Engine for Games', accessed on May 2023. https://box2d.org/documentation/ [online] 

#include <QMouseEvent>
#include <QGuiApplication>
#include "NGLScene.h"
#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <iostream>

#define ballY -15.5f
#define ballX -36.5f
#define springCenterX 38
#define springCenterY 17
#define angleChange 0.01
#define springLength 12

float angle;

NGLScene::NGLScene()
{
  setTitle("Spring Project");
}

NGLScene::~NGLScene()
{
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

  // create ground object
  b2BodyDef groundBodyDef;
  groundBodyDef.angularDamping = 0.3f;
  groundBodyDef.position.Set(0.0f, -20.0f);
  b2Body *groundBody = m_world->CreateBody(&groundBodyDef);
  b2PolygonShape groundBox;
  groundBox.SetAsBox(80.0f, 2.0f);
  groundBody->CreateFixture(&groundBox, 0.0f);

  // create spring object
  b2BodyDef springDef;
  springDef.type = b2_dynamicBody;
  springDef.position.Set(-38.0f, -17.0f);
  m_spring = m_world->CreateBody(&springDef);
  m_spring->SetFixedRotation(false);
  b2PolygonShape dynamicSpring;
  dynamicSpring.SetAsBox(springLength, 2.0f);
  b2FixtureDef fixtureDef1;
  fixtureDef1.shape = &dynamicSpring;
  // The following section is from :-
  // Ribon, A. (July 2011) 'Box2D Tutorial: Collision filtering', 'Aurelien Ribon's Dev Blog. [online]
  // Accessed [2023]
  // Available from https://aurelienribon.wordpress.com/2011/07/01/box2d-tutorial-collision-filtering/
  fixtureDef1.filter.maskBits = 0;
  // End citation
  m_spring->CreateFixture(&fixtureDef1);
  
  angle = 45 * 0.0174533;

  // create ball object
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(ballX, ballY);
  m_body = m_world->CreateBody(&bodyDef);
  m_body->SetLinearDamping(0.1f);
  m_body->SetAngularVelocity(0);
  m_body->SetFixedRotation(false);

  b2CircleShape dynamicBox;
  dynamicBox.m_radius = 0.5f;
  b2FixtureDef fixtureDef2;
  fixtureDef2.shape = &dynamicBox;
  fixtureDef2.density = 0.3f;
  fixtureDef2.friction = 0.3f;
  fixtureDef2.restitution = 0.7f;
  m_body->CreateFixture(&fixtureDef2);
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
    m_transform.setScale(springLength, 2, 0.1);
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
  float x_max;

  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape:
    QGuiApplication::exit(EXIT_SUCCESS);
    break;
  case Qt::Key_Left:
    if (angle > 1.57)
      break;
    angle = angle + angleChange;
    x_dist = m_body->GetPosition().x + springCenterX;
    y_dist = m_body->GetPosition().y + springCenterY;
    hypothenuse = sqrt((y_dist * y_dist) + (x_dist * x_dist));
    x = -springCenterX + (cos(angle)*hypothenuse);
    y = -springCenterY + (sin(angle)*hypothenuse);
    m_body->SetTransform(b2Vec2(x, y), 0);
    m_spring->SetTransform(m_spring->GetPosition(), angle);
    break;
  case Qt::Key_Right:
    if (angle < 0)
    break;
    angle = angle - angleChange;
    x_dist = m_body->GetPosition().x + springCenterX;
    y_dist = m_body->GetPosition().y + springCenterY;
    hypothenuse = sqrt((y_dist * y_dist) + (x_dist * x_dist));
    x = -38 + (cos(angle)*hypothenuse);
    y = -17 + (sin(angle)*hypothenuse);
    m_body->SetTransform(b2Vec2(x, y), 0);
    m_spring->SetTransform(m_spring->GetPosition(), angle);
    break;
  case Qt::Key_Up:
    x = m_body->GetPosition().x + fabs(0.1 * cos(angle));
    y = m_body->GetPosition().y + fabs(0.1 * sin(angle));
    x_max = sin(angle)*(springLength/2);
    if (y <= x_max - springCenterY - 0.1)
      m_body->SetTransform(b2Vec2(x, y), angle);
    break;
  case Qt::Key_Down:
    x = m_body->GetPosition().x - fabs(0.1 * cos(angle));
    y = m_body->GetPosition().y - fabs(0.1 * sin(angle));
    if (y >= (springCenterY+0.1) * -1)
      if  (x >= (springCenterX+0.1)  * -1)
        m_body->SetTransform(b2Vec2(x, y), angle);
    break;
  case Qt::Key_F:
    showFullScreen();
    break;
  case Qt::Key_P:
    spring_compression = fabs(m_body->GetPosition().y + 12);
    x_force = spring_compression * cos(angle) * 8;
    y_force = spring_compression * sin(angle) * 8;
    m_body->SetLinearVelocity(b2Vec2(x_force, y_force));
    startTimer(10);
  break;
  default:
    break;
  }
  update();
}

void NGLScene::keyReleaseEvent(QKeyEvent *_event)
{
  m_keysPressed -= (Qt::Key)_event->key();
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  auto timeStep = 1.0f / 100.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;
  m_world->Step(timeStep, velocityIterations, positionIterations);
  b2Vec2 move(0.0f, 0.0f);

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
