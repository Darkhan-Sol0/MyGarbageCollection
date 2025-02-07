#include "s21_parser.hpp"

#include <stdio.h>

s21::s21_obj::s21_obj()
    : v_array_size(0),
      i_array_size(0),
      vertex_array(nullptr),
      index_array(nullptr),
      error() {}

s21::s21_obj::~s21_obj() {
  delete this->vertex_array;
  delete this->index_array;
  this->i_array_size = 0;
  this->v_array_size = 0;
}

void s21::s21_obj::ParseEdge(std::string str) {
  std::istringstream iss(str.substr(2));
  std::string var;
  unsigned index_f = 0;
  bool is_index_f = true;

  while (iss >> var) {
    int index = std::stol(var);
    index -= 1;

    if (is_index_f) {
      index_f = index;
      this->index_array->push_back(index);
      is_index_f = false;
    } else {
      this->index_array->push_back(index);
      this->index_array->push_back(index);
    }
  }
  this->index_array->push_back(index_f);
}

void s21::s21_obj::ParseVertex(std::string str, Min_Max_t *lim) {
  double x = 0.0, y = 0.0, z = 0.0;
  std::string var;
  std::stringstream ss;
  ss << str;
  ss >> var >> x >> y >> z;

  // LCOV_EXCL_START
  if (x == INFINITY || y == INFINITY || z == INFINITY)
    this->error->check(s21_panic::INCORRECTDATA);
  // LCOV_EXCL_STOP
  this->vertex_array->push_back(x);
  this->vertex_array->push_back(y);
  this->vertex_array->push_back(z);

  lim->min_x = std::min(lim->min_x, x);
  lim->min_y = std::min(lim->min_y, y);
  lim->min_z = std::min(lim->min_z, z);

  lim->max_x = std::max(lim->max_x, x);
  lim->max_y = std::max(lim->max_y, y);
  lim->max_z = std::max(lim->max_z, z);
}

void s21::s21_obj::ParseData(std::ifstream &File) {
  Min_Max_t lim = {FLT_MAX, FLT_MAX, FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX};
  std::string str;
  while (std::getline(File, str)) {
    if (str.substr(0, 2) == "v ") {
      ParseVertex(str, &lim);
    } else if (str.substr(0, 2) == "f ") {
      ParseEdge(str);
    }
  }
  s21_move_x(-((lim.min_x + lim.max_x) / 2));
  s21_move_y(-((lim.min_y + lim.max_y) / 2));
  s21_move_z(-((lim.min_z + lim.max_z) / 2));
  this->v_array_size = this->vertex_array->size();
  this->i_array_size = this->index_array->size();
}

void s21::s21_obj::ParsingFile(char *filename) {
  this->vertex_array = new std::vector<double>;
  this->index_array = new std::vector<int>;
  std::ifstream File(filename);
  if (!File)
    // LCOV_EXCL_START
    this->error->check(s21_panic::INCORRECTFILE);
  // LCOV_EXCL_STOP
  else {
    ParseData(File);
    File.close();
  }

  // std::cout << this->get_v_arrey_size() << std::endl;
  // for (int i = 0; i < this->get_v_arrey_size(); i +=3)
  // if (i % 3 == 0){
  //   std::cout << i / 3 << ") ";
  //   std::cout << this->get_vertex_array(i) << " "
  //   << this->get_vertex_array(i + 1) << " "
  //   << this->get_vertex_array(i + 2) << std::endl;
  // }
  // std::cout << std::endl << this->get_i_arrey_size() << std::endl;
  // int temp = -1;
  // int ed = 0;
  // for (int i = 0; i < this->get_i_arrey_size(); i++) {
  //   if (temp < 0) {
  //     ed++;
  //     std::cout << ed << ") ";
  //   }
  //   std::cout << this->get_index_array(i) << " ";
  //   if (temp < 0) temp = this->get_index_array(i);
  //   else if (this->get_index_array(i) == temp) {
  //     std::cout << std::endl;
  //     temp = -1;
  //   }
  // }
  // std::cout << std::endl << std::endl;
}

void s21::s21_obj::s21_rotate_x(double angle) {
  double angle_rad = angle * (S21_PI / 180.0);
  double cos_a = cos(angle_rad);
  double sin_a = sin(angle_rad);
  for (int i = 0; i < this->v_array_size; i += 3) {
    double temp_y = this->vertex_array->at(i + 1);
    double temp_z = this->vertex_array->at(i + 2);
    this->vertex_array->at(i + 1) = cos_a * temp_y - sin_a * temp_z;
    this->vertex_array->at(i + 2) = sin_a * temp_y + cos_a * temp_z;
  }
}

void s21::s21_obj::s21_rotate_y(double angle) {
  double angle_rad = angle * (S21_PI / 180.0);
  double cos_a = cos(angle_rad);
  double sin_a = sin(angle_rad);
  for (int i = 0; i < this->v_array_size; i += 3) {
    double temp_x = this->vertex_array->at(i);
    double temp_z = this->vertex_array->at(i + 2);
    this->vertex_array->at(i) = cos_a * temp_x - sin_a * temp_z;
    this->vertex_array->at(i + 2) = sin_a * temp_x + cos_a * temp_z;
  }
}

void s21::s21_obj::s21_rotate_z(double angle) {
  double angle_rad = angle * (S21_PI / 180.0);
  double cos_a = cos(angle_rad);
  double sin_a = sin(angle_rad);
  for (int i = 0; i < this->v_array_size; i += 3) {
    double temp_x = this->vertex_array->at(i);
    double temp_y = this->vertex_array->at(i + 1);
    this->vertex_array->at(i) = cos_a * temp_x - sin_a * temp_y;
    this->vertex_array->at(i + 1) = sin_a * temp_x + cos_a * temp_y;
  }
}

void s21::s21_obj::s21_scale(double scale_value) {
  if (scale_value != 0.0)
    for (int i = 0; i < this->v_array_size; i++)
      this->vertex_array->at(i) *= scale_value;
}

void s21::s21_obj::s21_move_x(double value) {
  // if (value != 0.0)
    for (int i = 0; i < this->v_array_size; i += 3)
      this->vertex_array->at(i) += value;
}

void s21::s21_obj::s21_move_y(double value) {
  // if (value != 0.0)
    for (int i = 0; i < this->v_array_size; i += 3)
      this->vertex_array->at(i + 1) += value;
}

void s21::s21_obj::s21_move_z(double value) {
  // if (value != 0.0)
    for (int i = 0; i < this->v_array_size; i += 3)
      this->vertex_array->at(i + 2) += value;
}

int s21::s21_obj::get_v_arrey_size() const { return this->v_array_size; }

int s21::s21_obj::get_i_arrey_size() const { return this->i_array_size; }

std::vector<double> *s21::s21_obj::get_vertex_array() const {
  return this->vertex_array;
}

std::vector<int> *s21::s21_obj::get_index_array() const {
  return this->index_array;
}

double s21::s21_obj::get_vertex_array(int i) { return this->vertex_array->at(i); }

int s21::s21_obj::get_index_array(int i) { return this->index_array->at(i); }

// LCOV_EXCL_START
void s21::s21_panic::check(int err) {
  if (err == OK)
    return;
  else
    this->panic(err);
}

void s21::s21_panic::panic(int err) {
  switch (err) {
    case INCORRECTFILE:
      throw std::out_of_range("Bad file");
      break;
    case INCORRECTDATA:
      throw std::out_of_range("Incorrect data");
      break;
    case MEMORYERROR:
      throw std::out_of_range("Memory error");
      break;
    default:
      break;
  }
}
// LCOV_EXCL_STOP