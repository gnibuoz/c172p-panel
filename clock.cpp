#include <QPainter>
#include <QString>
#include <QFont>
#include "clock.h"
#include "logutil.h"

Clock::Clock(QWidget * parent)
    : QWidget(parent)
{
}

void Clock::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen = QPen(QColor(255, 255, 255, 255));
    QBrush brush = QBrush(QColor(255, 0, 0, 255));

    QString gmt_time = get_data_by_key(FGDATA_CLOCK_INDICATED, "00:00:00");
    QString second = gmt_time.right(2);
    QString local_time = get_data_by_key(FGDATA_CLOCK_LOCAL_SHORT, "00:00");
    local_time = local_time + ":" + second;

    // setup painter
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    QFont f = painter.font();
    f.setBold(true);
    f.setStyleHint(QFont::Monospace);
    f.setFamily("Monospace");
    f.setPixelSize(25);
    painter.setFont(f);
    painter.setBrush(brush);

    painter.fillRect(0, 0, width(), height(), QColor(5, 0, 0));
    painter.drawText(10, 40, local_time);
}
