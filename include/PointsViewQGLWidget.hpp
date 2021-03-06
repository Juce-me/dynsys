#pragma once

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTime>
#include <QTimer>

#include "Camera.hpp"
#include "Locus.hpp"
#include "Preferences.hpp"
#include "VideoEncoder.hpp"
#include "Window.hpp"

class PointsViewQGLWidget : public QGLWidget {
public:
    explicit PointsViewQGLWidget(QWidget *parent = nullptr);
    ~PointsViewQGLWidget() = default;

    void clearAll();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void setCurrentTime(const int currentTime_);

    void addNewLocus(QVector<QVector3D> &&points);

    void setPreferences(const Preferences::Preferences *prefs);

    bool startVideoRecording(const QString &filename);

    void endVideoRecording(std::function<void(int)> callback);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;


private:
    Q_OBJECT

    const Preferences::Preferences *prefs;

    Locus::LocusController locusController;

    Camera::KeyboardAndMouseController cameraController;

    VideoEncoder::VideoEncoder videoEncoder;

    size_t currentTime;
};
