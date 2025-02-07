#ifndef S21_PARSER_HPP
#define S21_PARSER_HPP

#include <float.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define S21_PI 3.14159265358979323846
#define MAX_VERTICES 1000000

namespace s21 {

typedef struct {
  double min_x;
  double min_y;
  double min_z;
  double max_x;
  double max_y;
  double max_z;
} Min_Max_t;

class s21_panic {
 public:
  enum { OK, INCORRECTFILE, INCORRECTDATA, MEMORYERROR };
  s21_panic() {}
  ~s21_panic() {}

  void check(int err);
  void panic(int err);
};

class s21_obj {
 private:
  int v_array_size;
  int i_array_size;
  std::vector<double>* vertex_array;
  std::vector<int>* index_array;

 public:
  s21_obj();
  ~s21_obj();

  void s21_rotate_x(double angle);
  void s21_rotate_y(double angle);
  void s21_rotate_z(double angle);

  void s21_scale(double scale_value);

  void s21_move_x(double value);
  void s21_move_y(double value);
  void s21_move_z(double value);

  int get_v_arrey_size() const;
  int get_i_arrey_size() const;
  std::vector<double>* get_vertex_array() const;
  std::vector<int>* get_index_array() const;
  double get_vertex_array(int i);
  int get_index_array(int i);

  void set_v_arrey_size(int value);
  void set_i_arrey_size(int value);
  void set_vertex_array(double value);
  void set_index_array(int value);
};

class s21_parser
{
private:
  s21_obj* obj;
  s21_panic* error;

public:
  s21_parser();
  ~s21_parser();

  void ParseEdge(std::string str);
  void ParseVertex(std::string str, Min_Max_t* lim);
  void ParseData(std::ifstream& File);
  s21::s21_obj* ParsingFile(char* filename);

  s21_obj* GetObj();
};

}  // namespace s21

#endif  // S21_PARSER