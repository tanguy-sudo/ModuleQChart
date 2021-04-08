#include "graphiques.hpp"
#include <QApplication>
#include <QTranslator>
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QTranslator translator;
  if(translator.load(QLocale::system(), "Graphiques", "_", a.applicationDirPath(), ".qm")){
     a.installTranslator(&translator);
  }

  graphiques w;
  w.show();

  return a.exec();
}
