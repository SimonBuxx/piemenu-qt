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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <PieMenu.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// \brief Main window of the demo program for the PieMenuQt widget
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// \brief Constructor for the main window
    /// \param parent: Pointer to the parent widget
    MainWindow(QWidget *parent = nullptr);

    /// \brief Default destructor for the main window
    ~MainWindow(void) override;

protected:
    /// \brief Overridden event handler to open the pie menu
    /// \param event: Pointer to the mouse event
    void mouseReleaseEvent(QMouseEvent *event) override;

    /// \brief Initializes the pie menu using a default configuration
    void initPieMenu();

protected:
    /// \brief Pointer to the main window's UI
    Ui::MainWindow *ui;

    /// \brief Pointer to the pie menu widget
    PieMenu *pie_menu = nullptr;
};
#endif // MAINWINDOW_H
