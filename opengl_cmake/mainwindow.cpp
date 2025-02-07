#include "mainwindow.hpp"

#include "./ui_mainwindow.h"
// #include "mainwindow.moc"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setFixedSize(900, 700);

  if (ui->openGLWidget->get_projection_type())
    ui->radioButton_ortho->setChecked(true);
  else
    ui->radioButton_persp->setChecked(true);

  if (ui->openGLWidget->get_vertex_type() == 0)
    ui->radioButton_none->setChecked(true);
  else if (ui->openGLWidget->get_vertex_type() == 1)
    ui->radioButton_dot->setChecked(true);
  else
    ui->radioButton_cube->setChecked(true);

  if (ui->openGLWidget->get_line_type())
    ui->checkbox_strip_line->setChecked(true);

  this->timer = new QTimer(0);
  connect(timer, SIGNAL(timeout()), this, SLOT(make_gif()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_button_scale_inc_clicked() {
  double scale_value = 1.1;
  ui->openGLWidget->scale_model(scale_value);
  ui->openGLWidget->update();
}

void MainWindow::on_button_scale_dec_clicked() {
  double scale_value = 0.9;
  ui->openGLWidget->scale_model(scale_value);
  ui->openGLWidget->update();
}

void MainWindow::on_actionOpen_file_triggered() {
  QString QS_filename = QFileDialog::getOpenFileName(
      this, "Select file", "/home/", "obj files (*.obj);;");

  std::string std_fileName = QS_filename.toStdString();

  char *fileName = (char *)std_fileName.c_str();
  ui->openGLWidget->parse_obj(fileName);
  int vertex_count = ui->openGLWidget->get_verteces_count();
  int edges_count = ui->openGLWidget->get_edges_count();
  ui->statusbar->showMessage("File name: " + QS_filename +
                             " vertex count: " + QString::number(vertex_count) +
                             " edges count: " + QString::number(edges_count));
  ui->openGLWidget->update();
}

void MainWindow::on_actionExit_program_triggered() { close(); }

void MainWindow::on_checkbox_strip_line_stateChanged() {
  if (ui->checkbox_strip_line->isChecked())
    ui->openGLWidget->set_line_type(1);
  else
    ui->openGLWidget->set_line_type(0);
  ui->openGLWidget->update();
}

void MainWindow::on_button_mov_inc_x_clicked() {
  ui->openGLWidget->move_x(0.1);
  ui->openGLWidget->update();
}

void MainWindow::on_button_mov_inc_y_clicked() {
  ui->openGLWidget->move_y(0.1);
  ui->openGLWidget->update();
}

void MainWindow::on_button_mov_inc_z_clicked() {
  ui->openGLWidget->move_z(0.1);
  ui->openGLWidget->update();
}

void MainWindow::on_button_mov_dec_x_clicked() {
  ui->openGLWidget->move_x(-0.1);
  ui->openGLWidget->update();
}

void MainWindow::on_button_mov_dec_y_clicked() {
  ui->openGLWidget->move_y(-0.1);
  ui->openGLWidget->update();
}

void MainWindow::on_button_mov_dec_z_clicked() {
  ui->openGLWidget->move_z(-0.1);
  ui->openGLWidget->update();
}

void MainWindow::on_actionCube_triggered() {
  char cube[] = "primitives/Cube.obj";
  ui->openGLWidget->parse_obj(cube);
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_ortho_clicked(bool checked) {
  if (checked) {
    ui->openGLWidget->set_projection_type(1);
  }
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_persp_clicked(bool checked) {
  if (checked) {
    ui->openGLWidget->set_projection_type(0);
  }
  ui->openGLWidget->update();
}

void MainWindow::on_button_rot_inc_x_clicked() {
  ui->openGLWidget->rotate_x(5.0);
  ui->openGLWidget->update();
}

void MainWindow::on_button_rot_dec_x_clicked() {
  ui->openGLWidget->rotate_x(-5.0);
  ui->openGLWidget->update();
}

void MainWindow::on_button_rot_inc_y_clicked() {
  ui->openGLWidget->rotate_y(5.0);
  ui->openGLWidget->update();
}

void MainWindow::on_button_rot_dec_y_clicked() {
  ui->openGLWidget->rotate_y(-5.0);
  ui->openGLWidget->update();
}

void MainWindow::on_button_rot_inc_z_clicked() {
  ui->openGLWidget->rotate_z(5.0);
  ui->openGLWidget->update();
}

void MainWindow::on_button_rot_dec_z_clicked() {
  ui->openGLWidget->rotate_z(-5.0);
  ui->openGLWidget->update();
}

void MainWindow::on_radioButton_dot_clicked(bool checked) {
  if (checked) {
    ui->openGLWidget->set_vertex_type(1);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_radioButton_cube_clicked(bool checked) {
  if (checked) {
    ui->openGLWidget->set_vertex_type(2);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_radioButton_none_clicked(bool checked) {
  if (checked) {
    ui->openGLWidget->set_vertex_type(0);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_button_set_l_color_clicked() {
  QColor l_color = QColorDialog::getColor(Qt::white, this, "Set line color");
  if (l_color.isValid()) {
    double r = l_color.redF();
    double g = l_color.greenF();
    double b = l_color.blueF();
    ui->openGLWidget->set_line_color(r, g, b);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_button_set_bg_color_clicked() {
  QColor vp_color =
      QColorDialog::getColor(Qt::white, this, "Set background color");
  if (vp_color.isValid()) {
    double r = vp_color.redF();
    double g = vp_color.greenF();
    double b = vp_color.blueF();
    double a = vp_color.alphaF();
    ui->openGLWidget->set_vp_color(r, g, b, a);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_button_set_v_color_clicked() {
  QColor v_color = QColorDialog::getColor(Qt::white, this, "Set vertex color");
  if (v_color.isValid()) {
    double r = v_color.redF();
    double g = v_color.greenF();
    double b = v_color.blueF();
    ui->openGLWidget->set_vertex_color(r, g, b);
    ui->openGLWidget->update();
  }
}

void MainWindow::on_button_inc_v_size_clicked() {
  ui->openGLWidget->set_vertex_size(0.5);
  ui->openGLWidget->update();
}

void MainWindow::on_button_dec_v_size_clicked() {
  ui->openGLWidget->set_vertex_size(-0.5);
  ui->openGLWidget->update();
}

void MainWindow::on_actionSphere_triggered() {
  char sphere[] = "primitives/Sphere.obj";
  ui->openGLWidget->parse_obj(sphere);
  ui->openGLWidget->update();
}

void MainWindow::on_actionIcosphere_triggered() {
  char icosphere[] = "primitives/Icosphere.obj";
  ui->openGLWidget->parse_obj(icosphere);
  ui->openGLWidget->update();
}

void MainWindow::on_actionCone_triggered() {
  char cone[] = "primitives/Cone.obj";
  ui->openGLWidget->parse_obj(cone);
  ui->openGLWidget->update();
}

void MainWindow::on_actionCylinder_triggered() {
  char cylinder[] = "primitives/Cylinder.obj";
  ui->openGLWidget->parse_obj(cylinder);
  ui->openGLWidget->update();
}

void MainWindow::on_actionMonkey_triggered() {
  char monkey[] = "primitives/Monkey.obj";
  ui->openGLWidget->parse_obj(monkey);
  ui->openGLWidget->update();
}

void MainWindow::on_button_dec_l_size_clicked() {
  ui->openGLWidget->set_line_size(-0.5);
  ui->openGLWidget->update();
}

void MainWindow::on_button_inc_l_size_clicked() {
  ui->openGLWidget->set_line_size(0.5);
  ui->openGLWidget->update();
}

void MainWindow::on_button_scrshot_clicked() {
  QImage img = ui->openGLWidget->grabFramebuffer();
  img.save("screenshot.jpeg");
  img.save("screenshot.bmp");
  QMessageBox msg;
  msg.information(0, "", "Screenshot success!");
}

void MainWindow::on_button_gif_clicked() {
  ui->button_gif->setDisabled(true);
  gif_frame = new QGifImage;
  gif_frame->setDefaultDelay(10);
  timer->setInterval(100);
  timer->start();
  frames_counter = 0;
}

void MainWindow::make_gif() {
  frames_counter++;
  QImage img = ui->openGLWidget->grabFramebuffer();
  QSize img_size(640, 480);
  QImage scaled_img = img.scaled(img_size);
  gif_frame->addFrame(scaled_img);
  if (frames_counter >= 50) {
    timer->stop();
    gif_frame->save("latest.gif");
    QMessageBox msg;
    msg.information(0, "", "gif created");
    delete gif_frame;
    ui->button_gif->setEnabled(true);
  }
}
