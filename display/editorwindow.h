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
    
private:
    Ui::EditorWindow *ui;
};

#endif // EDITORWINDOW_H