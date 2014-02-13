
#pragma once

#include <QList>
#include <QSize>

#include "OpenGLFunctions.h"
#include "AbstractCoordinateProvider.h"

class QStringList;
class QOpenGLShaderProgram;

class Camera;


class AbstractPainter : public AbstractCoordinateProvider
    , protected OpenGLFunctions
{
public:
    // ToDo: perhaps come up with better identifers here.
    enum PaintMode
    {
        PaintMode0
    ,   PaintMode1
    ,   PaintMode2
    ,   PaintMode3
    ,   PaintMode4
    ,   PaintMode5
    ,   PaintMode6
    ,   PaintMode7
    ,   PaintMode8
    ,   PaintMode9
    };

public:
    AbstractPainter();
    virtual ~AbstractPainter();

    void setCamera(Camera * camera);
    Camera * camera();

    /** return list of mandatory extensions (verify results in fatal if one is
        not supported).
    */
    virtual const QStringList & extensions() const;

    /** this should setup the opengl state and allocate all required static 
        resources (context is 3.2 core for this one).
    */
    virtual bool initialize() = 0;

    /** returns wether m_context is nullptr or not
    */
    bool isValid() const;

    virtual void show();
    virtual void hide();

    virtual void paint(float timef) = 0;
    virtual void resize(int width, int height) = 0;

    virtual void update() = 0;
    virtual void update(const QList<QOpenGLShaderProgram *> & programs) = 0;

    void setMode(PaintMode mode);
    PaintMode mode() const;

    // AbstractCoordinateProvider interface

    virtual const float depthAt(const QPointF & windowCoordinates);

    virtual const QVector3D objAt(
        const QPointF & windowCoordinates);
    const QVector3D objAt(
        const QPointF & windowCoordinates
    ,   const float depth);
    const QVector3D objAt(
        const QPointF & windowCoordinates
    ,   const float depth
    ,   const QMatrix4x4 & viewProjectionInverted);

protected:
    Camera * m_camera;
    PaintMode m_mode;
};
