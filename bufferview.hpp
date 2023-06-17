#pragma once

#include <QWidget>

class BufferView : public QWidget
{
    Q_OBJECT

    /*
     * store pixel data for QImage
     */
    std::vector<std::uint8_t> m_buffer;
    QImage m_image;

protected:
    void run();

    virtual void paintEvent(QPaintEvent *event) override;

public:
    BufferView(QWidget *parent = nullptr);
    ~BufferView();

    void set_image(const QImage &image);

    void set_image(const QString &file_name);

    void set_gray_buffer(std::vector<std::uint8_t> &&buffer, const std::size_t width, const std::size_t height);
};
