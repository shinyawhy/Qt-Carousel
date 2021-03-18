#ifndef CAROUSELWINDOW_H
#define CAROUSELWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
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

public slots:
    void onRightButtonClicked();
    void onLeftButtonClicked();
    void onImageSwitchButtonClicked();

private:
    void initChangeImageButton();
    void initImage();
    void initWindows();
    void updateImage();

private:

    QList<QString> m_imageList;
    QList<QPushButton*> m_pButtonChangeImageList;
    QList<QLabel*> m_imageLabel;

    QWidget* m_buttonBackWidget;
    QWidget* m_imageWidget;

    QColor m_buttonBackColor;

    QPropertyAnimation* m_opacityAnimation;

    int m_currentImageIndex;
    QLabel* m_currentLabel;
    QLabel* m_nextLabel;
    QLabel* m_preLabel;
    QLabel* m_usedLabel;   // 出现过的那张图
    QLabel* m_readyLabel;  // 准备出现的图
};

#endif // CAROUSELWINDOW_H
