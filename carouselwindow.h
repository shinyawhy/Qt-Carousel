#ifndef CAROUSELWINDOW_H
#define CAROUSELWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QDebug>

class CarouselWindow : public QWidget
{
    Q_OBJECT

public:
    CarouselWindow(QWidget *parent = NULL);
    ~CarouselWindow();

    void setImageList(QStringList imageList);
    void addImage(QString image);

    void setButtonVisible(bool visible);
    void setButtonColor(QColor buttonColor);

    void startPlay();
private:
    void initChangeImageButton();
private:
    QList<QString> m_imageList;
    QList<QPushButton*> m_pButtonChangeImageList;
    QWidget* m_buttonBackWidget;
    QColor m_buttonBackColor;
};

#endif // CAROUSELWINDOW_H
