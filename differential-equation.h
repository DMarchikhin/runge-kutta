//
//  differential-equation.h
//
//
//  Created by Dmitry Marchikhin on 06.05.16.
//
//

#ifndef ____differential_equation__
#define ____differential_equation__

#include <vector>

class DifferentialEquation {
public:
  DifferentialEquation(double x, double xMax, double y, double e);

  struct Point {
    double x;
    double y;
  };

  std::vector<Point> GetAnalyticalSolution() const;
  std::vector<Point> GetRungeKuttaSolution() const;

  double RungeRule(double h) const;

private:
  double x_, xMax_, y_, e_;

  double OriginalEqution_(double x, double y) const;

  double AnalyticalSolution_(double x) const;

  double RungeEquation_(double x, double y, double h) const;
};

#endif /* defined(____differential_equation__) */
