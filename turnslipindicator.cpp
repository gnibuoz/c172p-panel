#include <QPainter>
#include <QMutexLocker>
#include "turnslipindicator.h"
#include "imgres.h"
#include "logutil.h"
#include "config.h"

TurnSlipIndicator::TurnSlipIndicator(QWidget *parent)
    : QWidget(parent), FGDataConsumer(), turn(0.0), slip(0.0), spin(0.0)
{
    load_img();
}

void TurnSlipIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen = QPen(QColor(255, 255, 255, 255));
    QBrush brush = QBrush(QColor(160, 16, 16, 255));
    const int h = this->height();
    const int w = this->width();

    turn = get_data_by_key(FGDATA_TSI_TURN, turn);
    slip = get_data_by_key(FGDATA_TSI_SLIP, slip);
    spin = get_data_by_key(FGDATA_TSI_SPIN, spin);

    // setup painter
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.translate(QPoint(w / 2, h / 2));

    // draw white background for the ball
    painter.fillRect(-w / 2, 0, w, h / 2, QColor(255, 255, 255, 255));

    // draw spin indicator
    // the size is 20 pixel wide, 26 pixel high
    int gray = spin * 26;
    int red = 26 - gray;
    painter.fillRect(60, -30, 20, red, QColor(255, 70, 30, 255)); // red
    painter.fillRect(60, -30 + red, 20, gray, QColor(80, 80, 80, 255)); // gray

    // draw the slip ball
    int cx, cy;

    cx = -slip * 150;
    if (cx < -70) {
        cx = -70;
    } else if (cx > 70) {
        cx = 70;
    }
    cy = 50 + (cx > 0 ? cx : -cx) * 0.07;
    painter.drawEllipse(QPoint(cx, cy), 15, 15);

    // draw plate
    painter.drawPixmap(-w / 2, -h / 2, *img_plate);

    // draw plane
    painter.save();
    painter.rotate(turn_to_angle());
    painter.drawPixmap(-w / 2, -38, *img_plane);
    painter.restore();

    // draw frame
    painter.drawPixmap(-w / 2, -h / 2, *img_frame);
}

double TurnSlipIndicator::turn_to_angle()
{
    return turn * 20;
}

void TurnSlipIndicator::load_img()
{
    QMutexLocker l(&img_lock);
    if (loaded) {
        return;
    }

    img_frame = new QPixmap(Config::img_prefix + IMG_TSI_FRAME);
    if (img_frame->isNull()) {
        LOGE("Failed to load tsi frame");
    }

    img_plane = new QPixmap(Config::img_prefix + IMG_TSI_PLANE);
    if (img_plane->isNull()) {
        LOGE("Failed to load tsi plane");
    }

    img_plate = new QPixmap(Config::img_prefix + IMG_TSI_PLATE);
    if (img_plate->isNull()) {
        LOGE("Failed to load tsi plate");
    }

    loaded = true;
}

QMutex TurnSlipIndicator::img_lock;
bool TurnSlipIndicator::loaded = false;
QPixmap * TurnSlipIndicator::img_plane = NULL;
QPixmap * TurnSlipIndicator::img_frame = NULL;
QPixmap * TurnSlipIndicator::img_plate = NULL;
