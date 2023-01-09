/**
 * @file MainWindow.cpp
 * @author Simon Buchholz
 * @date 9 Jan 2023
 * @brief Demo program for the PieMenuQt widget
 *
 * The pie menu is fully customizable for arbitrary amounts of buttons,
 * disabled buttons, button icons and appearance parameters.
 * All button clicks are published as a Qt signal containing the
 * clicked button's index.
 *
 * When the pin/unpin button is activated, the pie menu can be pinned
 * to keep it open until it is manually or programmatically closed.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initPieMenu();

    QObject::connect(ui->button_count_slider, &QSlider::sliderMoved, this, [&](int32_t pos)
    {
        pie_menu->setButtonCount(pos);

        for (int32_t i = 0; i < pos; i++)
        {
            pie_menu->setButtonIcons(i, QIcon(":/icons/image-line-icon.png"), QIcon(":/icons/image-line-icon-disabled.png"));
        }

        pie_menu->update();

        ui->button_count_label->setText(QString::number(pos));
    });

    QObject::connect(ui->base_angle_slider, &QSlider::sliderMoved, this, [&](int32_t pos)
    {
        pie_menu->setBaseAngle(pos);
        pie_menu->update();

        ui->base_angle_label->setText(QString("%0°").arg(QString::number(pos)));
    });

    QObject::connect(ui->stroke_width_slider, &QSlider::sliderMoved, this, [&](int32_t pos)
    {
        pie_menu->setStrokeWidth(pos);
        pie_menu->update();

        ui->stroke_width_label->setText(QString("%0 px").arg(QString::number(pos)));
    });

    QObject::connect(ui->close_radius_slider, &QSlider::sliderMoved, this, [&](int32_t pos)
    {
        pie_menu->setCloseButtonRadius(pos);
        pie_menu->update();

        ui->close_button_radius_label->setText(QString("%0 px").arg(QString::number(pos)));

    });

    QObject::connect(ui->pin_radius_slider, &QSlider::sliderMoved, this, [&](int32_t pos)
    {
        pie_menu->setPinButtonRadius(pos);
        pie_menu->update();

        ui->pin_button_radius_label->setText(QString("%0 px").arg(QString::number(pos)));
    });

    QObject::connect(ui->alternate_colors_checkbox, &QCheckBox::clicked, this, [&](bool value)
    {
        pie_menu->setAlternateColors(value);
        pie_menu->update();
    });

    QObject::connect(ui->disable_button_checkbox, &QCheckBox::clicked, this, [&](bool value)
    {
        pie_menu->setButtonEnabled(0, !value);
        pie_menu->update();
    });
}

void MainWindow::initPieMenu()
{
    pie_menu = new PieMenu(ui->centralwidget);
    pie_menu->setCloseButtonIcon(QIcon(":/icons/close-line-icon.png"));
    pie_menu->setPinButtonIcon(QIcon(":/icons/pushpin-icon.png"));

    pie_menu->setButtonCount(4);

    for (int32_t i = 0; i < 4; i++)
    {
        pie_menu->setButtonIcons(i, QIcon(":/icons/image-line-icon.png"), QIcon(":/icons/image-line-icon-disabled.png"));
    }

    QObject::connect(pie_menu, &PieMenu::buttonClicked, this, [&](uint8_t index)
    {
        ui->label->setText(QString("You clicked button #%0").arg(index));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        pie_menu->display();
    }
    else
    {
        pie_menu->hideIfNotPinned();
    }

    QMainWindow::mouseReleaseEvent(event);
}
