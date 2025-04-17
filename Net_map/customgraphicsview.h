#pragma once

#include <QGraphicsView>
#include <QWheelEvent>

class CustomGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    explicit CustomGraphicsView(QWidget* parent = nullptr)
        : QGraphicsView(parent)
    {
        setDragMode(QGraphicsView::ScrollHandDrag);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setRenderHint(QPainter::Antialiasing);
    }

protected:
    void wheelEvent(QWheelEvent* event) override {
        if (event->modifiers() & Qt::ControlModifier) {
            const double zoomFactor = 1.15;

            if (event->angleDelta().y() > 0)
                scale(zoomFactor, zoomFactor);
            else
                scale(1.0 / zoomFactor, 1.0 / zoomFactor);

            event->accept();  // bloque la propagation qui causerait un scroll
        }
        else {
            QGraphicsView::wheelEvent(event);
        }
    }
};
