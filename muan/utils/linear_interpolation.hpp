#include <algorithm>
#include "third_party/aos/common/die.h"

namespace muan {
namespace utils {

template <typename T>
LinearInterpolation<T>::LinearInterpolation(std::vector<std::pair<double, T>> data) {
  if (data.size() < 2) {
    ::aos::Die("Interpolate requires 2 or more control points");
  }
  data_ = data;
  std::sort(data_.begin(), data_.end(), ComparePoints);
}

template <typename T>
T LinearInterpolation<T>::operator()(double x) const {
  // Unable to compare pair<double, T> with double. This fills the second
  // element in the pair.
  std::pair<double, T> temp;
  temp.first = x;
  // Upper bound returns the smallest number > x. Subtracting 1 gives the greatest
  // number <= x.
  auto lower_bounds_index = std::upper_bound(data_.begin(), data_.end(), temp, ComparePoints) - 1;
  // Lower bound returns the smallest number >= x, for some reason.
  auto upper_bounds_index = std::lower_bound(data_.begin(), data_.end(), temp, ComparePoints);

  if (lower_bounds_index == data_.end() || upper_bounds_index == data_.end()) {
    ::aos::Die("An interpolation is only defined between the lowest and highest x-values");
  }
  double x0 = lower_bounds_index->first;
  double x1 = upper_bounds_index->first;
  T y0 = lower_bounds_index->second;
  T y1 = upper_bounds_index->second;

  // Obtained as the solution to (y-y0)/(x-x0) = (y1-y0)/(x1-x0)
  T y;
  if (x0 == x1) {
    y = y0;
  } else {
    y = y0 + (x - x0) * (y1 - y0) / (x1 - x0);
  }
  return y;
}

template <typename T>
void LinearInterpolation<T>::AddControlPoint(std::pair<double, T> point) {
  if (data_.size() == 0) {
    data_.push_back(point);
  } else if (point.first > data_[data_.size() - 1].first) {
    data_.push_back(point);
  } else {
    auto location = std::upper_bound(data_.begin(), data_.end(), point, ComparePoints);
    data_.insert(location, point);
  }
}

template <typename T>
double LinearInterpolation<T>::lower_boundary() const {
  return data_[0].first;
}

template <typename T>
double LinearInterpolation<T>::upper_boundary() const {
  return data_[data_.size() - 1].first;
}

template <typename T>
bool LinearInterpolation<T>::ComparePoints(const std::pair<double, T> &a, const std::pair<double, T> &b) {
  return a.first < b.first;
}

} // utils

}  // muan
