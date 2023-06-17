#include "bufferview.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BufferView w;

    {
        const std::size_t width  = 256;
        const std::size_t height = 256;
        std::vector<std::uint8_t> buffer;
        buffer.resize(width * height);

        std::uint8_t value = 0;

        for (std::size_t y = 0; y < height; y++)
        {
            for (std::size_t x = 0; x < width; x++)
            {
                buffer[(y * width) + x] = value;
            }
            value++;
        }

        w.set_gray_buffer(std::move(buffer), width, height);
    }

    w.show();

    return a.exec();
}
