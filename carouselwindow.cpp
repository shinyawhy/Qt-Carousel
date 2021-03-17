#include "carouselwindow.h"

CarouselWindow::CarouselWindow(QWidget *parent)
    : QWidget(parent)
    , m_buttonBackColor(Qt::white),m_currentImageIndex(0)
{
      this->setFixedSize(QSize(650, 650));
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
}

CarouselWindow::~CarouselWindow()
{

}

void CarouselWindow::setImageList(QStringList imageList)
{
    m_imageList = imageList;
}

void CarouselWindow::addImage(QString image)
{
    m_imageList.append(image);
}

void CarouselWindow::setButtonVisible(bool visible)
{
        m_buttonBackWidget->setVisible(visible);
}

void CarouselWindow::setButtonColor(QColor buttonColor)
{
    m_buttonBackColor = buttonColor;
}

void CarouselWindow::startPlay()
{
    initChangeImageButton();
    initImage();
    initWindows();
}

void CarouselWindow::initChangeImageButton()
{
    //== 按钮BackWidget;
    m_buttonBackWidget = new QWidget(this);
    m_buttonBackWidget->setStyleSheet(".QWidget{background:transparent;}");

    QButtonGroup* changeButtonGroup = new QButtonGroup;
    QHBoxLayout* hLayout = new QHBoxLayout(m_buttonBackWidget);
    QPushButton* leftButton = new QPushButton(m_buttonBackWidget);
    QPushButton* rightButton = new QPushButton(m_buttonBackWidget);
    hLayout->addStretch(1);
    hLayout->addWidget(leftButton);
    hLayout->addStretch(1);
    for (int i = 0; i < m_imageList.count(); i++)
    {
        QPushButton* pButton = new QPushButton;
        pButton->setFixedSize(QSize(20, 20));
        pButton->setCheckable(true);
        pButton->setStyleSheet(QString("QPushButton{background:rgb(%1, %2, %3);border-radius:6px;margin:3px;}\
                                       QPushButton:checked{border-radius:9px;margin:0px;}")
                                       .arg(m_buttonBackColor.red()).arg(m_buttonBackColor.green()).arg(m_buttonBackColor.blue()));
        changeButtonGroup->addButton(pButton, i);
        m_pButtonChangeImageList.append(pButton);
        hLayout->addWidget(pButton);
    }
    hLayout->addStretch(1);
    hLayout->addWidget(rightButton);
    hLayout->addStretch(1);
    hLayout->setSpacing(10);
    hLayout->setMargin(0);

    connect(rightButton, SIGNAL(clicked()), this, SLOT(onRightButtonClicked()));
    connect(leftButton, SIGNAL(clicked()), this, SLOT(onLeftButtonClicked()));
//    connect(changeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onImageSwitchButtonClicked(int)));
}

void CarouselWindow::initImage()
{
    //== 轮播图片PicWidget
    m_imageWidget = new QWidget(this);
    m_imageWidget->setStyleSheet(".QWidget{background:transparent;}");

    int imageWidth = m_imageWidget->geometry().width();
    int imageHeight = m_imageWidget->geometry().height();

    int center_y = this->height() / 2 - imageHeight / 2;
    int center_x = this->width() / 4/* - imageWidth * 3 / 2*/;

    // 根据图片数量生成相对数量的label并放入队列中
    for (int i = 0; i < m_imageList.size(); i++)
    {
        QLabel* label = new QLabel(m_imageWidget);
        m_imageLabel.append(label);
    }

    if(m_currentImageIndex == m_imageList.size() - 1)
    {
        m_nextLabel = m_imageLabel.at(0);
        m_nextLabel->setPixmap(QPixmap(":/pic/"+ QString::number(0)));
    }
    else
    {
        m_nextLabel = m_imageLabel.at(m_currentImageIndex + 1);
        m_nextLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_currentImageIndex + 2)));
    }

    m_nextLabel->setGeometry(center_x - this->width() / 8, m_buttonBackWidget->geometry().height() * 3 / 2,
                             this->width() / 2, this->height()- m_buttonBackWidget->geometry().height() * 5);
    m_nextLabel->setScaledContents(true);
    m_nextLabel->setAlignment(Qt::AlignCenter);


    if(m_currentImageIndex == 0)
    {
        m_preLabel = m_imageLabel.at(m_imageList.size() - 1);
        m_preLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_imageList.size() - 1)));
    }
    else
    {
        m_preLabel = m_imageLabel.at(m_currentImageIndex - 1);
        m_preLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_currentImageIndex)));
    }
    m_preLabel->setGeometry(center_x + this->width() / 8, m_buttonBackWidget->geometry().height() * 3 / 2,
                            this->width() / 2, this->height()- m_buttonBackWidget->geometry().height() * 5);
    m_preLabel->setScaledContents(true);
    m_preLabel->setAlignment(Qt::AlignCenter);

    // currentlabel
    m_currentLabel = m_imageLabel.at(m_currentImageIndex);
    m_currentLabel->setGeometry(center_x, m_buttonBackWidget->geometry().height() / 2,
                                this->width() / 2, this->height()- m_buttonBackWidget->geometry().height() * 3);
    m_currentLabel->setScaledContents(true);
    m_currentLabel->setAlignment(Qt::AlignCenter);
    m_currentLabel->setPixmap(QPixmap(":/pic/"+ QString::number((m_currentImageIndex + 1))));
    m_currentLabel->raise();


}

void CarouselWindow::initWindows()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_imageWidget);
    mainLayout->addWidget(m_buttonBackWidget);
    mainLayout->setStretch(0,1);
    mainLayout->setContentsMargins(0, 0, 0, 30);
}

void CarouselWindow::onRightButtonClicked()
{
    m_opacityAnimation = new QPropertyAnimation(m_currentLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_currentLabel->geometry());
    m_opacityAnimation->setEndValue(m_preLabel->geometry());
    m_opacityAnimation->start();


    m_opacityAnimation = new QPropertyAnimation(m_nextLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_nextLabel->geometry());
    m_opacityAnimation->setEndValue(m_currentLabel->geometry());
    m_opacityAnimation->start();

    // 是最后一张
    if(m_currentImageIndex == m_imageList.size() - 1)
    {
        m_currentImageIndex = 0;
    }
    else
    {
        m_currentImageIndex++;
    }

    // used-pre
    if(m_currentImageIndex == 0)
    {
        m_usedLabel = m_imageLabel.at(m_imageList.size() - 2);
        m_usedLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_imageList.size() - 2)));
    }
    else if(m_currentImageIndex == 1)
    {
        m_usedLabel = m_imageLabel.at(m_imageList.size() - 1);
        m_usedLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_imageList.size() - 1)));
    }
    else
    {
        m_usedLabel = m_imageLabel.at(m_currentImageIndex - 2);
        m_usedLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_currentImageIndex - 1)));
    }
    m_usedLabel->setGeometry(this->width() / 4, m_buttonBackWidget->geometry().height() *3 / 2,
                                this->width() / 2, this->height()- m_buttonBackWidget->geometry().height() * 5);
    m_usedLabel->setScaledContents(true);
    m_usedLabel->setAlignment(Qt::AlignCenter);

    m_opacityAnimation = new QPropertyAnimation(m_preLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_preLabel->geometry());
    m_opacityAnimation->setEndValue(m_usedLabel->geometry());
    m_opacityAnimation->start();
    // ready-next
    if(m_currentImageIndex == m_imageList.size() - 1)
    {
        m_readyLabel = m_imageLabel.at(1);
        m_readyLabel->setPixmap(QPixmap(":/pic/"+ QString::number(1)));
    }
    else if (m_currentImageIndex == m_imageList.size() - 2)
    {
        m_readyLabel = m_imageLabel.at(0);
        m_readyLabel->setPixmap(QPixmap(":/pic/"+ QString::number(0)));
    }
    else
    {
        m_readyLabel = m_imageLabel.at(m_currentImageIndex + 1);
        m_readyLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_currentImageIndex + 2)));
    }
    m_readyLabel->setGeometry(this->width() / 4 + this->width() * 3 / 16, m_buttonBackWidget->geometry().height() * 2,
                              this->width() / 8, this->height()- m_buttonBackWidget->geometry().height() * 6);
    m_readyLabel->setScaledContents(true);
    m_readyLabel->setAlignment(Qt::AlignCenter);

    m_opacityAnimation = new QPropertyAnimation(m_readyLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_readyLabel->geometry());
    m_opacityAnimation->setEndValue(m_nextLabel->geometry());
    m_opacityAnimation->start();



    initImage();

}

void CarouselWindow::onLeftButtonClicked()
{
    m_opacityAnimation = new QPropertyAnimation(m_currentLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_currentLabel->geometry());
    m_opacityAnimation->setEndValue(m_nextLabel->geometry());
    m_opacityAnimation->start();

    m_opacityAnimation = new QPropertyAnimation(m_preLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_preLabel->geometry());
    m_opacityAnimation->setEndValue(m_currentLabel->geometry());
    m_opacityAnimation->start();

    m_opacityAnimation = new QPropertyAnimation(m_nextLabel, "geometry");
    m_opacityAnimation->setDuration(1000);
    m_opacityAnimation->setEasingCurve(QEasingCurve::OutCubic);
    m_opacityAnimation->setStartValue(m_nextLabel->geometry());
    m_opacityAnimation->setEndValue(m_preLabel->geometry());
    m_opacityAnimation->start();

    if(m_currentImageIndex == m_imageList.size() - 1)
    {
        m_usedLabel = m_imageLabel.at(1);
        m_usedLabel->setPixmap(QPixmap(":/pic/"+ QString::number(1)));
    }
    else if (m_currentImageIndex == m_imageList.size() - 2)
    {
        m_usedLabel = m_imageLabel.at(0);
        m_usedLabel->setPixmap(QPixmap(":/pic/"+ QString::number(0)));
    }
    else
    {
        m_usedLabel = m_imageLabel.at(m_currentImageIndex + 2);
        m_usedLabel->setPixmap(QPixmap(":/pic/"+ QString::number(m_currentImageIndex + 3)));
    }
    m_usedLabel->setGeometry(this->width() / 4, m_buttonBackWidget->geometry().height() / 2,
                                this->width() / 2, this->height()- m_buttonBackWidget->geometry().height() * 3);
    m_usedLabel->setScaledContents(true);
    m_usedLabel->setAlignment(Qt::AlignCenter);
    // 是第一张
    if(m_currentImageIndex == 0)
    {
        m_currentImageIndex == m_imageList.size() - 1;
    }
    else
    {
        m_currentImageIndex--;
    }
    initImage();

}

void CarouselWindow::onImageSwitchButtonClicked()
{

}
