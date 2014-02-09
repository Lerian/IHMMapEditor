#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QWidget>

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();
    
private slots:
    void on_quitButton_clicked();

    void on_newMapButton_clicked();

    void on_loadMapButton_clicked();

signals:
    void quitButtonClicked();
    void newMapButtonClicked();
    void loadMapButtonClicked();
    void loadMap(QString mapFileName);

private:
    Ui::HomeWindow *ui;
};

#endif // HOMEWINDOW_H
