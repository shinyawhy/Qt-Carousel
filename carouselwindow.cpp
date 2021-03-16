#include "carouselwindow.h"

CarouselWindow::CarouselWindow(QWidget *parent)
    : QWidget(parent)
    , m_buttonBackColor(Qt::white)
{

    // 按钮BackWidget;
    m_buttonBackWidget = new QWidget;
    m_buttonBackWidget->setStyleSheet(".QWidget{background:transparent;}");

    this->setFixedSize(QSize(450, 650));
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
}

void CarouselWindow::initChangeImageButton()
{
    QButtonGroup* changeButtonGroup = new QButtonGroup;
    QHBoxLayout* hLayout = new QHBoxLayout(m_buttonBackWidget);
    hLayout->addStretch();
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
    hLayout->addStretch();
    hLayout->setSpacing(10);
    hLayout->setMargin(0);


    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(m_buttonBackWidget);
    mainLayout->setContentsMargins(0, 0, 0, 30);
}
