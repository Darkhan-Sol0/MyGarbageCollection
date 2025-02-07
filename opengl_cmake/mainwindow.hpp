#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gifimage/qgifimage.h>

#include <QCheckBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  QTimer *timer;
  QGifImage *gif_frame;
  int frames_counter;

 private slots:
  void make_gif();
  void on_actionOpen_file_triggered();
  void on_actionExit_program_triggered();
  void on_checkbox_strip_line_stateChanged();
  void on_button_scale_inc_clicked();
  void on_button_scale_dec_clicked();

  void on_button_mov_inc_x_clicked();

  void on_button_mov_inc_y_clicked();

  void on_button_mov_inc_z_clicked();

  void on_button_mov_dec_x_clicked();

  void on_button_mov_dec_y_clicked();

  void on_button_mov_dec_z_clicked();

  void on_actionCube_triggered();

  void on_radioButton_ortho_clicked(bool checked);

  void on_radioButton_persp_clicked(bool checked);

  void on_button_rot_inc_x_clicked();

  void on_button_rot_dec_x_clicked();

  void on_button_rot_inc_y_clicked();

  void on_button_rot_dec_y_clicked();

  void on_button_rot_inc_z_clicked();

  void on_button_rot_dec_z_clicked();

  void on_radioButton_dot_clicked(bool checked);

  void on_radioButton_cube_clicked(bool checked);

  void on_radioButton_none_clicked(bool checked);

  void on_button_set_l_color_clicked();

  void on_button_set_bg_color_clicked();

  void on_button_set_v_color_clicked();

  void on_button_inc_v_size_clicked();

  void on_button_dec_v_size_clicked();

  void on_actionSphere_triggered();

  void on_actionIcosphere_triggered();

  void on_actionCone_triggered();

  void on_actionCylinder_triggered();

  void on_actionMonkey_triggered();

  void on_button_dec_l_size_clicked();

  void on_button_inc_l_size_clicked();

  void on_button_scrshot_clicked();

  void on_button_gif_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
