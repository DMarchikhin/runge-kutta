#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QStandardItemModel"
#include "QStandardItem"

#include <iostream>
#include <vector>
#include <cmath>
#include "differential-equation.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
        double x0 = 0;
        double xMax = 1;
        double y0 = 0;
        double e = 0.0005;

        DifferentialEquation eq(x0, xMax, y0, e);

        std::vector<DifferentialEquation::Point> analyticalSolution = eq.GetAnalyticalSolution();
        std::vector<DifferentialEquation::Point> rungeKuttaSolution = eq.GetRungeKuttaSolution();

        // График //
        ui->widget->clearGraphs();

        int n = analyticalSolution.size();

        QVector<double> xAnalytical(n), yAnalytical(n), xRungeKutta(n), yRungeKutta(n);

        for (int i = 0; i < n; ++i) {
            xAnalytical[i] = analyticalSolution[i].x;
            yAnalytical[i] = analyticalSolution[i].y;
        }

        for (int i = 0; i < n; ++i) {
            xRungeKutta[i] = rungeKuttaSolution[i].x;
            yRungeKutta[i] = rungeKuttaSolution[i].y;
        }

        // включить отображение легенды
        ui->widget->legend->setVisible(true);

        ui->widget->addGraph();
        ui->widget->graph(0)->setData(xAnalytical, yAnalytical);

        // подписать график
        ui->widget->graph(0)->setName("Аналитическое решение");

        ui->widget->addGraph();

        ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));
        ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

        ui->widget->graph(1)->setData(xRungeKutta, yRungeKutta);

        // подписать график
        ui->widget->graph(1)->setName("Решение Рунге-Кутта");

        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("y");

        ui->widget->xAxis->setRange(x0, xMax);

        double yMin = yAnalytical[0] < yRungeKutta[0] ? yAnalytical[0] : yRungeKutta[0],
               yMax = yAnalytical[0] > yRungeKutta[0] ? yAnalytical[0] : yRungeKutta[0];
        for (int i = 1; i < n; i++) {
            if (yAnalytical[i] < yMin || yRungeKutta[i] < yMin) {
                yMin = yAnalytical[i] < yRungeKutta[i] ? yAnalytical[i] : yRungeKutta[i];
            }
            if (yAnalytical[i] > yMax || yRungeKutta[i] > yMax) {
                yMax = yAnalytical[i] > yRungeKutta[i] ? yAnalytical[i] : yRungeKutta[i];
            }
        }
        ui->widget->yAxis->setRange(yMin, yMax);

        ui->widget->replot();



        // Таблица //
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
        horizontalHeader.append("x");
        horizontalHeader.append("приближенное решение");
        horizontalHeader.append("точное решение");
        horizontalHeader.append("погрешность");

        //QStringList verticalHeader;
        //verticalHeader.append("x");
        //verticalHeader.append("приближенное решение");
        //verticalHeader.append("точное решение");
        //verticalHeader.append("погрешность");

        model->setHorizontalHeaderLabels(horizontalHeader);
        //model->setVerticalHeaderLabels(verticalHeader);

        int step = 0.1 / eq.RungeRule(0.1);

        for (int i = 0; i * step < n; i++) {
            item = new QStandardItem(QString::number(analyticalSolution[i * step].x));
            model->setItem(i, 0, item);
            //model->setItem(0, i, item);

            item = new QStandardItem(QString::number(rungeKuttaSolution[i * step].y, 'g', 10));
            model->setItem(i, 1, item);
            //model->setItem(1, i, item);

            item = new QStandardItem(QString::number(analyticalSolution[i * step].y, 'g', 10));
            model->setItem(i, 2, item);
            //model->setItem(2, i, item);

            item = new QStandardItem(QString::number(std::abs(analyticalSolution[i * step].y - rungeKuttaSolution[i * step].y), 'g', 7));
            model->setItem(i, 3, item);
            //model->setItem(3, i, item);
        }

        std::cout << analyticalSolution[analyticalSolution.size() - 1].x << std::endl;
        std::cout << analyticalSolution[analyticalSolution.size() - 1].y << std::endl;

        ui->tableView->setModel(model);

        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();

}
