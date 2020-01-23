#include <iostream>

#include <QDir>
#include <QImage>

const QString DIR(QDir::currentPath() + "/");
const int COLS = 10;
const int ROWS = 7;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Need exactly one argument! Please provide the name of the file." << std::endl;
        return 1;
    }

    QString source = QString::fromLatin1(argv[1], strlen(argv[1]));
    std::cout << "Parsing file " << source.toStdString() << ".jpg" << std::endl;
    QString destination(DIR + source);
    QImage image(destination + ".jpg");
    if(image.isNull())
    {
        std::cout << "Error reading image!" << std::endl;
        return 2;
    }

    if(QDir(destination).exists())
    {
        std::cout << "Folder with this name already exists!" << std::endl;
        return 3;
    }

    bool success = QDir(DIR).mkdir(source);
    if(!success)
    {
        std::cout << "Error creating directory." << std::endl;
        return 4;
    }

    int width = image.width() / COLS;
    int height = image.height() / ROWS;
    int counter = 0;
    for(int i = 0; i < ROWS; ++i)
    {
        for(int k = 0; k < COLS; ++k)
        {
            QImage card = image.copy(k * width, i * height, width, height);

            ++counter;
            success = card.save(destination + "/" + QString::number(counter) + ".jpg");
            if(success)
            {
                std::cout << "Card " << QString::number(counter).toStdString() << " saved successfully" << std::endl;
            }
            else
            {
                std::cout << "Error saving card " << QString::number(counter).toStdString() << std::endl;
            }
        }
    }

    return 0;
}
