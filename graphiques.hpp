#ifndef GRAPHIQUES_HPP
#define GRAPHIQUES_HPP

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QMainWindow>
#include <QFileDialog>
#include <QIcon>
#include <QMessageBox>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include <QPainter>
#include "drawgraph.hpp"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QtMath>
namespace Ui {
  class graphiques;
}

class graphiques : public QMainWindow
{
  Q_OBJECT

public:
  graphiques(QWidget *parent = nullptr);
  ~graphiques();

private slots:
    void newFile();
    void about();
    void aboutGraph();
    void loadGraph();
    void save();
    void on_pushButtonFont_clicked();
    void on_pushButtonCouleurUne_clicked();
    void on_pushButtonCouleurDeux_clicked();
    void on_pushButtonCouleurTrois_clicked();
    void on_pushButtonCouleurFond_clicked();
    void on_pushButtonCouleurAxes_clicked();

private:
  Ui::graphiques *ui;

  void createActions();
  void createMenu();
  void loadFile(const QString &filename);

  QAction *_loadFileAction;
  QAction *_quitAction;
  QAction *_drawGraphAction;
  QAction *_saveGraphAction;
  QAction *_aboutQtAction;
  QAction *_aboutGraphAction;

  drawGraph *_drawGraph;

};

#endif // GRAPHIQUES_HPP
