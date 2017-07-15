#include <QPainter>
#include <QMutexLocker>
#include "attitudeindicator.h"
#include "imgres.h"
#include "logutil.h"
#include "config.h"

AttitudeIndicator::AttitudeIndicator(QWidget *parent)
    : QWidget(parent),
      FGDataConsumer(),
      FGDataUpdater(),
      ai_pitch(0.0),
      ai_pitch_offset(0.0),
      ai_roll(0.0),
      k_offset(this, IMG_K_AI_OFFSET)
{
    load_img();
    k_offset.setGeometry(10, 240, 50, 50);
    QObject::connect(&k_offset, SIGNAL(rotated(Knob::direcrion)),
                     this, SLOT(update_offset(Knob::direcrion)));
}

void AttitudeIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen = QPen(QColor(255, 255, 255, 255));
    QBrush brush = QBrush(QColor(255, 255, 255, 255));
    const int h = this->height();
    const int w = this->width();

    ai_pitch = get_data_by_key(FGDATA_AI_PITCH, ai_pitch);
    ai_pitch_offset = get_data_by_key(FGDATA_AI_OFFSET, ai_pitch_offset);
    ai_roll = get_data_by_key(FGDATA_AI_ROLL, ai_roll);

    // setup painter
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.translate(QPoint(w / 2, h / 2));

    // draw background horizon
    painter.save();
    painter.rotate(-ai_roll);
    painter.fillRect(-w / 2, -h / 2, w, h / 2, QColor(90, 160, 250, 255)); // the blue sky
    painter.fillRect(-w / 2, 0, w, h / 2, QColor(200, 130, 70, 255)); // the brown ground
    painter.restore();

    // draw horizon2
    painter.save();
    painter.rotate(-ai_roll);
    painter.translate(0, pitch_to_translate());
    painter.drawPixmap(-w / 2, -h / 2, *img_horizon2);
    painter.restore();

    // draw horizon3
    painter.save();
    painter.rotate(-ai_roll);
    painter.drawPixmap(-w / 2, -h / 2, *img_horizon3);
    painter.restore();

    // draw plane and frame
    painter.drawPixmap(-w / 2, -h / 2, *img_plane);
    painter.drawPixmap(-w / 2, -h / 2, *img_frame);
}

void AttitudeIndicator::update_offset(Knob::direcrion d)
{
    ai_pitch_offset = get_data_by_key(FGDATA_AI_OFFSET, ai_pitch_offset);

    if (d == Knob::LEFT) {
        set_data_by_key(FGDATA_AI_OFFSET, ai_pitch_offset - 0.1);
    } else if (d == Knob::RIGHT) {
        set_data_by_key(FGDATA_AI_OFFSET, ai_pitch_offset + 0.1);
    }
}

void AttitudeIndicator::load_img()
{
    QMutexLocker l(&img_lock);
    if (loaded) {
        return;
    }

    img_horizon2 = new QPixmap(Config::img_prefix + IMG_AI_HORIZON2);
    if (img_horizon2->isNull()) {
        LOGE("Failed to load ai h2");
    }

    img_horizon3 = new QPixmap(Config::img_prefix + IMG_AI_HORIZON3);
    if (img_horizon3->isNull()) {
        LOGE("Failed to load ai h3");
    }

    img_frame = new QPixmap(Config::img_prefix + IMG_AI_FRAME);
    if (img_frame->isNull()) {
        LOGE("Failed to load ai frame");
    }

    img_plane = new QPixmap(Config::img_prefix + IMG_AI_PLANE);
    if (img_plane->isNull()) {
        LOGE("Failed to load ai plane");
    }

    loaded = true;
}

QMutex AttitudeIndicator::img_lock;
bool AttitudeIndicator::loaded = false;
QPixmap * AttitudeIndicator::img_horizon2 = NULL;
QPixmap * AttitudeIndicator::img_horizon3 = NULL;
QPixmap * AttitudeIndicator::img_plane = NULL;
QPixmap * AttitudeIndicator::img_frame = NULL;
