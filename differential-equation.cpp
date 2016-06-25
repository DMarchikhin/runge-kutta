//
//  differential-equation.cpp
//
//
//  Created by Dmitrii Marchikhin on 06.05.16.
//
//

#include "differential-equation.h"
#include <cmath>

DifferentialEquation::DifferentialEquation(double x, double xMax, double y, double e)
  : x_(x), xMax_(xMax), y_(y), e_(e)
{}


double DifferentialEquation::OriginalEqution_(double x, double y) const {
  return x * x * (y * y + 1);
}


double DifferentialEquation::AnalyticalSolution_(double x) const {
  return std::tan(std::pow(x, 3) / 3);
}


double DifferentialEquation::RungeEquation_(double x, double y, double h) const {
  double k1, k2, k3, k4;

  k1 = this->OriginalEqution_(x, y);
  k2 = this->OriginalEqution_(x + h / 2, y + (h / 2) * k1);
  k3 = this->OriginalEqution_(x + h / 2, y + (h / 2) * k2);
  k4 = this->OriginalEqution_(x + h, y + h * k3);

  return y + (1.0 / 6) * h * (k1 + 2 * k2 + 2 * k3 + k4);
}


double DifferentialEquation::RungeRule(double h) const {
  double prevStep, nextStep, yPrev, yNext;

  prevStep = nextStep = h;

  do {
    prevStep = nextStep;
    nextStep = nextStep / 2;
    yPrev = this->RungeEquation_(this->x_, this->y_, prevStep);
    yNext = this->RungeEquation_(this->x_, this->y_, nextStep);
  } while ( (1.0 / 15) * std::abs(yNext - yPrev) >= this->e_ );

  return nextStep;
}


std::vector<DifferentialEquation::Point> DifferentialEquation::GetAnalyticalSolution() const {

  std::vector<DifferentialEquation::Point> res;

  DifferentialEquation::Point p = {this->x_, this->y_};

  double h = this->RungeRule(0.1);

  while (p.x <= this->xMax_ + 0.001) {

    p.y = this->AnalyticalSolution_(p.x);

    res.push_back(p);

    p.x += h;
  }

  return res;
}


std::vector<DifferentialEquation::Point> DifferentialEquation::GetRungeKuttaSolution() const {
  std::vector<DifferentialEquation::Point> res;
  DifferentialEquation::Point p = {this->x_, this->y_};

  double h = this->RungeRule(0.1);

  while (p.x <= this->xMax_  + 0.001) {

    res.push_back(p);

    p.y = this->RungeEquation_(p.x, p.y, h);
    p.x += h;
  }

  return res;
}







