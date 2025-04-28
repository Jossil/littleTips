#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QApplication>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void toggleAlwaysOnTop();
    Qt::WindowFlags m_originalFlags;
    void addToDialog();
    bool mpos = false;
protected:
    // 事件过滤器
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (event->type() == QEvent::Enter) {
            if (!(QApplication::keyboardModifiers() & Qt::ControlModifier)) {
                if(mpos)
                    move(0,0);
                else
                    move(QApplication::primaryScreen()->availableGeometry().width() - width(), 0);
                mpos = !mpos;
            }
        }
        return QMainWindow::eventFilter(obj, event);
    }
};
#endif // MAINWINDOW_H
