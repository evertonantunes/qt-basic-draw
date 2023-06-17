#include "bufferview.hpp"
#include <QDebug>
#include <QFile>
#include <QPainter>

void BufferView::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QPainter painter(this);

    if (m_image.isNull())
    {
        qInfo() << "no image to draw";
        return;
    }

    const QSize size  = this->size();
    const auto nimage = m_image.scaled(size, Qt::KeepAspectRatio);

    {
        QTransform tr;
        tr.translate((size.width() / 2.0f) - (nimage.width() / 2.0f), (size.height() / 2.0f) - (nimage.height() / 2.0f));
        painter.setTransform(tr, true);
    }

    painter.drawImage(QPoint(0, 0), nimage);
}

BufferView::BufferView(QWidget *parent)
    : QWidget(parent)
{
}

BufferView::~BufferView() {}

void BufferView::set_image(const QImage &image)
{
    m_image = image;
    update();
}

void BufferView::set_image(const QString &file_name)
{
    if (!QFile::exists(file_name))
    {
        qWarning() << "image not found: " << file_name;
        return;
    }

    QImage image(file_name);
    if (image.isNull())
    {
        qWarning() << "unable to load image: " << file_name;
        return;
    }
    set_image(image);
}

void BufferView::set_gray_buffer(std::vector<uint8_t> &&buffer, const std::size_t width, const std::size_t height)
{
    m_buffer = std::move(buffer);
    // QImage not duplicate pixel data
    QImage image(m_buffer.data(), width, height, width, QImage::Format_Grayscale8);
    if (image.isNull())
    {
        qWarning() << "unable to load image from buffer";
        return;
    }
    set_image(image);
}
