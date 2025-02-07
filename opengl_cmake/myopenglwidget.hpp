#ifndef MYOPENGLWIDGET_HPP
#define MYOPENGLWIDGET_HPP

#include <QOpenGLWidget>
#include <QWidget>

#include "../common/s21_parser.hpp"

struct settings_t {
  double vp_color_r, vp_color_g, vp_color_b, vp_color_a;
  double l_color_r, l_color_g, l_color_b;
  double v_color_r, v_color_g, v_color_b;
  int line_type;
  int projection_type;
  int vertex_type;
  double vertex_size, line_size;
};

class myOpenGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  myOpenGLWidget(QWidget *parent = nullptr);
  ~myOpenGLWidget();
  void set_vp_color(double r, double g, double b, double a);
  void set_line_color(double r, double g, double b);
  void set_vertex_color(double r, double g, double b);
  void move_x(double value);
  void move_y(double value);
  void move_z(double value);
  void rotate_x(double angle);
  void rotate_y(double angle);
  void rotate_z(double angle);
  void scale_model(double scale_value);
  void parse_obj(char *fileName);
  void set_line_type(int type);
  void set_projection_type(int type);
  void set_vertex_type(int type);
  void set_vertex_size(double value);
  void set_line_size(double value);
  int get_verteces_count();
  int get_edges_count();
  int get_line_type();
  int get_projection_type();  // 1 - ortho, 2 - perspective
  int get_vertex_type();  // 0 - dont print vertex points, 1 - round, 2 - cube
  void save_settings();
  void load_settings();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void perspective();

 private:
  s21::s21_obj *obj;
  settings_t settings;
  double proj_x, proj_y, proj_z;
};

#endif  // MYOPENGLWIDGET_H
