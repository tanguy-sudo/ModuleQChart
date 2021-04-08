#include "graphiques.hpp"
#include "ui_graphiques.h"
graphiques::graphiques(QWidget *parent) :
  QMainWindow (parent),
  ui(new Ui::graphiques)
{
  ui->setupUi(this);

  _drawGraph = new drawGraph(this, ui->spinBoxHauteur->value(), ui->spinBoxLargeur->value());
  ui->horizontalLayout->addWidget(_drawGraph);

  createActions();
  createMenu();

  ui->pushButtonCouleurUne->setStyleSheet("background-color: red;");
  ui->pushButtonCouleurDeux->setStyleSheet("background-color: green;");
  ui->pushButtonCouleurTrois->setStyleSheet("background-color: blue;");
  ui->pushButtonCouleurFond->setStyleSheet("background-color: white;");
  ui->pushButtonCouleurAxes->setStyleSheet("background-color: grey;");
}

graphiques::~graphiques()
{
  delete ui;
}

void graphiques::createActions() {

    _loadFileAction = new QAction(tr("Load"), this);
    _loadFileAction->setShortcut(QKeySequence::Open);
    _loadFileAction->setStatusTip(tr("load a data file to create a graph"));
    connect(_loadFileAction, &QAction::triggered, this, &graphiques::newFile);

    _quitAction = new QAction(tr("Exit"), this);
    _quitAction->setShortcut(QKeySequence::Quit | Qt::CTRL + Qt::Key_Q);
    _quitAction->setStatusTip(tr("exit the application"));
    connect(_quitAction, &QAction::triggered, this, &QApplication::quit);

    _drawGraphAction = new QAction(tr("Draw the graph"), this);
    _drawGraphAction->setStatusTip(tr("draw the graph using data file"));
    _drawGraphAction->setDisabled(true);
    connect(_drawGraphAction, &QAction::triggered, this, &graphiques::loadGraph);

    _saveGraphAction = new QAction(tr("Save graph as ..."), this);
    _saveGraphAction->setShortcut(tr("CTRL+SHIFT+S"));
    _saveGraphAction->setStatusTip(tr("save the graph"));
    _saveGraphAction->setDisabled(true);
    connect(_saveGraphAction, &QAction::triggered, this, &graphiques::save);

    _aboutQtAction = new QAction(tr("About Qt") ,this);
    _aboutQtAction->setStatusTip(tr("about Qt framework"));
    _aboutQtAction->setIcon(QIcon::fromTheme("help-about"));
    connect(_aboutQtAction, &QAction::triggered, this, &graphiques::about);

    _aboutGraphAction = new QAction(tr("About graphics"), this);
    _aboutGraphAction->setStatusTip(tr("about graphics"));
    _aboutGraphAction->setIcon(QIcon::fromTheme("help-about"));
    connect(_aboutGraphAction, &QAction::triggered, this, &graphiques::aboutGraph);

}

void graphiques::createMenu() {

    QMenu *fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(_loadFileAction);
    fileMenu->addAction(_quitAction);

    QMenu *graphMenu = menuBar()->addMenu(tr("Graph"));
    graphMenu->addAction(_drawGraphAction);
    graphMenu->addAction(_saveGraphAction);

    QMenu *AboutMenu = menuBar()->addMenu(QIcon::fromTheme("help-contents"), tr(""));
    AboutMenu->addAction(_aboutQtAction);
    AboutMenu->addAction(_aboutGraphAction);

}

void graphiques::save(){

    QString imagePath = QFileDialog::getSaveFileName(this, tr("Save graph as ..."), "", tr("PNG (*.png);;JPEG (*.jpg *.jpeg)" ));
    QStringList tabFile = imagePath.split("/");
    QString file = tabFile[tabFile.count()-1];
    QStringList tabF = file.split(".");

    // sous Linux l'extension doit être donnée dans le nom du fichier, je vérifie donc que le fichier est la bonne extension
    if(!imagePath.isEmpty()){
      if(tabF.count() == 1){
          QMessageBox::critical(this, tr("Extension error"), tr("The file name has no extension."));
        }
        else if(tabF[1] != "jpg" && tabF[1] != "jpeg" && tabF[1] != "png"){
            QMessageBox::critical(this, tr("Extension error"), tr("Wrong extension."));
        }else {
          if(!imagePath.isEmpty()){
              QImage imageObject = _drawGraph->getPixmap()->toImage();
              imageObject.save(imagePath);
          }
        }
    }

}

void graphiques::newFile() {

    QString filename = QFileDialog::QFileDialog::getOpenFileName(this, tr("Load a data file"), QString(), tr("*.csv"));
    if(!filename.isNull()){
        QStringList tabFile = filename.split("/");
        int nbr = tabFile.count();
        setWindowTitle(tr("Graph") + " [" + tabFile[nbr-1] + "]");
        loadFile(filename);
    }

}

void graphiques::about(){

    QMessageBox::aboutQt(this, tr("About Qt"));
}

void graphiques::aboutGraph(){

    QMessageBox::about(this, tr("About Qt"), tr("This application has been developed by Tanguy JOUVIN for a Qt project of L3 computer."));
}

void graphiques::loadFile(const QString &filename){
   ui->tableWidget->clear();
   ui->tableWidget->setRowCount(0);
   QFile data(filename);
    // On ouvre le fichier en lecture seule
    if(data.exists() && data.open(QIODevice::ReadOnly)) {
        QTextStream in(&data);
        this->_drawGraphAction->setDisabled(false);
        bool firstColonne = true;
        int row=0;
        while(!in.atEnd()) {
            QString ligne = in.readLine();
            QStringList enregistrement = ligne.split(',');
            if(firstColonne){
                QStringList entetes;
                for(int col=0; col<enregistrement.size(); ++col) {
                    entetes << enregistrement[col];
                }
                ui->tableWidget->setColumnCount(enregistrement.size());
                ui->tableWidget->setHorizontalHeaderLabels(entetes);
                firstColonne = false;
            }
            else{
                ui->tableWidget->insertRow(row);
                for(int col=0; col<enregistrement.size(); ++col) {
                    ui->tableWidget->setItem(row, col, new QTableWidgetItem(enregistrement[col]));
                }
                ++row;
            }
        }      
        data.close();
    }

}

void graphiques::on_pushButtonFont_clicked(){

    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont(), this);
    if(ok){
        ui->pushButtonFont->setText(font.family() + ", " + QString::number(font.pointSizeF()));
    }

}

void graphiques::on_pushButtonCouleurUne_clicked(){

    QColor newColor = QColorDialog::getColor(Qt::red, this, "");
    if(newColor.isValid()){
        QString qss = QString("background-color: %1").arg(newColor.name());
        ui->pushButtonCouleurUne->setStyleSheet(qss);
    }

}

void graphiques::on_pushButtonCouleurDeux_clicked(){

    QColor newColor = QColorDialog::getColor(Qt::green, this, "");
    if(newColor.isValid()){
        QString qss = QString("background-color: %1").arg(newColor.name());
        ui->pushButtonCouleurDeux->setStyleSheet(qss);
    }

}

void graphiques::on_pushButtonCouleurTrois_clicked(){

    QColor newColor = QColorDialog::getColor(Qt::blue, this, "");
    if(newColor.isValid()){
        QString qss = QString("background-color: %1").arg(newColor.name());
        ui->pushButtonCouleurDeux->setStyleSheet(qss);
    }

}

void graphiques::on_pushButtonCouleurFond_clicked(){

    QColor newColor = QColorDialog::getColor(Qt::white, this, "");
    if(newColor.isValid()){
        QString qss = QString("background-color: %1").arg(newColor.name());
        ui->pushButtonCouleurFond->setStyleSheet(qss);
    }

}

void graphiques::on_pushButtonCouleurAxes_clicked(){

    QColor newColor = QColorDialog::getColor(Qt::gray, this, "");
    if(newColor.isValid()){
        QString qss = QString("background-color: %1").arg(newColor.name());
        ui->pushButtonCouleurAxes->setStyleSheet(qss);
    }

}

void graphiques::loadGraph() {

    QStringList MaxValue;
    QStringList MinValue;
    //ui->tableWidget->setMinimumHeight(ui->spinBoxHauteur->value());
    for(int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        MaxValue << ui->tableWidget->item(0, col)->text();
        MinValue << ui->tableWidget->item(0, col)->text();
    }
    for(int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        QStringList lignes;
        for(int col=0; col < ui->tableWidget->columnCount(); ++col) {
            lignes << ui->tableWidget->item(row, col)->text();
        }
         for(int i = 0 ; i < lignes.count() ; i++){
             if(MaxValue[i].toDouble() < lignes[i].toDouble()){
                 MaxValue[i] = lignes[i];
             }
             if(MinValue[i].toDouble() > lignes[i].toDouble()){
                 MinValue[i] = lignes[i];
             }
         }
    }

    for(int i = 1 ; i < MaxValue.count() ; i++){
        if(MaxValue[1].toDouble() < MaxValue[i].toDouble()){
            MaxValue[1] = MaxValue[i];
        }
    }
    for(int i = 1 ; i < MinValue.count() ; i++){
        if(MinValue[1].toDouble() > MinValue[i].toDouble()){
            MinValue[1] = MinValue[i];
        }
    }
    int minX = qFloor(MinValue[0].toDouble());
    int minY = qFloor(MinValue[1].toDouble());
    int maxX = qCeil(MaxValue[0].toDouble());
    int maxY = qCeil(MaxValue[1].toDouble());

    QStringList font = ui->pushButtonFont->text().split(",");

     _drawGraph->setGraph(ui->spinBoxLargeur->value(),
                          ui->spinBoxHauteur->value(),
                          ui->spinBoxMargeX->value(),
                          ui->spinBoxMargeY->value(),
                          ui->pushButtonCouleurFond->palette().button().color(),
                          ui->pushButtonCouleurAxes->palette().button().color(),
                          ui->spinBoxPasX->value(), ui->spinBoxPasY->value(),
                          minX, minY, maxX, maxY,
                          font[0], font[1].toInt(),
                          ui->checkBoxGrille->checkState());

     if(ui->comboBoxType->currentText() == tr("Dots")){
         _drawGraph->drawP(ui->spinBoxPasX->value(), ui->spinBoxPasY->value(), ui->tableWidget,
                           ui->pushButtonCouleurUne->palette().button().color(),
                           ui->pushButtonCouleurDeux->palette().button().color(),
                           ui->pushButtonCouleurTrois->palette().button().color());
     }else if(ui->comboBoxType->currentText() == tr("Bars")){
         _drawGraph->drawB(ui->spinBoxPasX->value(), ui->spinBoxPasY->value(), ui->tableWidget,
                           ui->pushButtonCouleurUne->palette().button().color(),
                           ui->pushButtonCouleurDeux->palette().button().color(),
                           ui->pushButtonCouleurTrois->palette().button().color());
     }else if(ui->comboBoxType->currentText() == tr("Rows")){
         _drawGraph->drawL(ui->spinBoxPasX->value(), ui->spinBoxPasY->value(), ui->tableWidget,
                           ui->pushButtonCouleurUne->palette().button().color(),
                           ui->pushButtonCouleurDeux->palette().button().color(),
                           ui->pushButtonCouleurTrois->palette().button().color());
     }

    this->_saveGraphAction->setDisabled(false);

}
