#include "test_main.hpp"

int main(void) {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

TEST(Parser_Test, Test_1) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "primitives/Cube.obj";
  obj = pars->ParsingFile(filename);
  obj->s21_move_x(0.0);
  delete pars;
}

TEST(Parser_Test_bad, Test_2) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "test_files/Cube_bad.obj";
  obj = pars->ParsingFile(filename);
  obj->s21_move_x(0.0);
  delete pars;
}

TEST(Parser_Test_simp, Test_3) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "test_files/cube_simple.obj";
  obj = pars->ParsingFile(filename);
  obj->s21_move_x(0.0);
  delete pars;
}

TEST(Transform_Test_move, Test_4) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "primitives/Cube.obj";
  obj = pars->ParsingFile(filename);
  obj->s21_move_x(0.0);
  obj->s21_move_x(2.0);
  obj->s21_move_x(-2.0);
  obj->s21_move_y(0.0);
  obj->s21_move_y(2.0);
  obj->s21_move_y(-2.0);
  obj->s21_move_z(0.0);
  obj->s21_move_z(2.0);
  obj->s21_move_z(-2.0);
  delete pars;
}

TEST(Transform_Test_rot, Test_5) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "primitives/Cube.obj";
  obj = pars->ParsingFile(filename);
  obj->s21_rotate_x(0.0);
  obj->s21_rotate_x(2.0);
  obj->s21_rotate_x(-2.0);
  obj->s21_rotate_y(0.0);
  obj->s21_rotate_y(2.0);
  obj->s21_rotate_y(-2.0);
  obj->s21_rotate_z(0.0);
  obj->s21_rotate_z(2.0);
  obj->s21_rotate_z(-2.0);
  delete pars;
}

TEST(Transform_Test_scal, Test_6) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "primitives/Cube.obj";
  obj = pars->ParsingFile(filename);
  obj->s21_scale(0.0);
  obj->s21_scale(2.0);
  obj->s21_scale(-2.0);
  delete pars;
}

TEST(Transform_Test_get_index, Test_7) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "primitives/Cube.obj";
  obj = pars->ParsingFile(filename);
  obj->get_i_arrey_size();
  obj->get_index_array();
  obj->get_index_array(2);
  delete pars;
}

TEST(Transform_Test_get_vertex, Test_8) {
  s21::s21_obj *obj;
  s21::s21_parser *pars = new s21::s21_parser();
  char filename[] = "primitives/Cube.obj";
  obj = pars->ParsingFile(filename);
  obj->get_v_arrey_size();
  obj->get_vertex_array();
  obj->get_vertex_array(2);
  delete pars;
}