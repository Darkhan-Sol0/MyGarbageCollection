#include "s21_parser.hpp"

#include <stdio.h>

s21::s21_obj::s21_obj()
    : v_array_size(0),
      i_array_size(0),
      vertex_array(nullptr),
      index_array(nullptr) {
        this->vertex_array = new std::vector<double>;
        this->index_array = new std::vector<int>;
      }

s21::s21_obj::~s21_obj() {
  if (this->vertex_array != nullptr) {
    delete this->vertex_array;
    this->vertex_array = nullptr;
  } 
  if (this->index_array != nullptr) {
    delete this->index_array;
    this->index_array = nullptr;
  }
  this->i_array_size = 0;
  this->v_array_size = 0;
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

void s21::s21_obj::set_v_arrey_size(int value) { this->v_array_size = value; }
void s21::s21_obj::set_i_arrey_size(int value) { this->i_array_size = value; }
void s21::s21_obj::set_vertex_array(double value) { this->vertex_array->push_back(value); }
void s21::s21_obj::set_index_array(int value) { this->index_array->push_back(value); }

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


s21::s21_parser::s21_parser() : obj(nullptr) {}
s21::s21_parser::~s21_parser() {
  if (this->obj != nullptr) {
    delete this->obj;
    this->obj = nullptr;
  }
}

void s21::s21_parser::ParseEdge(std::string str) {
  std::istringstream iss(str.substr(2));
  std::string var;
  unsigned index_f = 0;
  bool is_index_f = true;

  while (iss >> var) {
    int index = std::stol(var);
    index -= 1;

    if (is_index_f) {
      index_f = index;
      this->GetObj()->set_index_array(index);
      is_index_f = false;
    } else {
      this->GetObj()->set_index_array(index);
      this->GetObj()->set_index_array(index);
    }
  }
  this->GetObj()->set_index_array(index_f);
}

void s21::s21_parser::ParseVertex(std::string str, Min_Max_t *lim) {
  double x = 0.0, y = 0.0, z = 0.0;
  std::string var;
  std::stringstream ss;
  ss << str;
  ss >> var >> x >> y >> z;

  // LCOV_EXCL_START
  if (x == INFINITY || y == INFINITY || z == INFINITY)
    this->error->check(s21_panic::INCORRECTDATA);
  // LCOV_EXCL_STOP
  this->GetObj()->set_vertex_array(x);
  this->GetObj()->set_vertex_array(y);
  this->GetObj()->set_vertex_array(z);

  lim->min_x = std::min(lim->min_x, x);
  lim->min_y = std::min(lim->min_y, y);
  lim->min_z = std::min(lim->min_z, z);

  lim->max_x = std::max(lim->max_x, x);
  lim->max_y = std::max(lim->max_y, y);
  lim->max_z = std::max(lim->max_z, z);
}

void s21::s21_parser::ParseData(std::ifstream &File) {
  Min_Max_t lim = {FLT_MAX, FLT_MAX, FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX};
  std::string str;
  while (std::getline(File, str)) {
    if (str.substr(0, 2) == "v ") {
      ParseVertex(str, &lim);
    } else if (str.substr(0, 2) == "f ") {
      ParseEdge(str);
    }
  }
  this->GetObj()->s21_move_x(-((lim.min_x + lim.max_x) / 2));
  this->GetObj()->s21_move_y(-((lim.min_y + lim.max_y) / 2));
  this->GetObj()->s21_move_z(-((lim.min_z + lim.max_z) / 2));
  this->GetObj()->set_v_arrey_size(this->GetObj()->get_vertex_array()->size());
  this->GetObj()->set_i_arrey_size(this->GetObj()->get_index_array()->size());
}

s21::s21_obj* s21::s21_parser::ParsingFile(char *filename) {
  if (this->obj != nullptr) {
    delete this->obj;
    this->obj = nullptr;
  }
  this->obj = new s21_obj();
  std::ifstream File(filename);
  if (!File)
    // LCOV_EXCL_START
    this->error->check(s21_panic::INCORRECTFILE);
  // LCOV_EXCL_STOP
  else {
    ParseData(File);
    File.close();
  }
  return this->obj;
}

s21::s21_obj* s21::s21_parser::GetObj() { return this->obj; }