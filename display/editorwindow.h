#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QWidget>

namespace Ui {
class EditorWindow;
}

class EditorWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit EditorWindow(QWidget *parent = 0);
    ~EditorWindow();
    
private slots:
    void on_newElementButton_clicked();

    void on_zoomInButton_clicked();

    void on_zoomOutButton_clicked();

    void saveRequested();

    void on_removeElementButton_clicked();

public slots:
    void clearProject();

private:
    Ui::EditorWindow *ui;
};

#endif // EDITORWINDOW_H
