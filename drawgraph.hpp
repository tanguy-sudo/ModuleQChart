#ifndef DRAWGRAPH_H
#define DRAWGRAPH_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QLabel>
#include <QGuiApplication>
#include <QTableWidget>
class drawGraph : public QWidget
{
    Q_OBJECT
public:
    drawGraph(QWidget *parent = nullptr, int hauteur = 600, int largeur = 800);
    ~drawGraph() override;
    void drawP(int pasX, int pasY, QTableWidget *table, const QColor &couleurUne, const QColor &couleurDeux, const QColor &couleurTrois);
    void drawB(int pasX, int pasY, QTableWidget *table, const QColor &couleurUne, const QColor &couleurDeux, const QColor &couleurTrois);
    void drawL(int pasX, int pasY, QTableWidget *table, const QColor &couleurUne, const QColor &couleurDeux, const QColor &couleurTrois);
    void setGraph(int largeur,
                  int hauteur,
                  int margeX,
                  int margeY,
                  const QColor &font,
                  const QColor &axes,
                  int pasX,
                  int pasY,
                  int minX,
                  int minY,
                  int maxX ,
                  int maxY,
                  const QString &styleName,
                  qreal styleSize,
                  bool stateGrille);
    QPixmap* getPixmap() const;
protected:
    void paintEvent(QPaintEvent *) override;

private:
    void initDefaultPixMap(int largeur, int hauteur);
    QPixmap *_pixmap;
    QPen _pen;
    QLabel *_label;
    double _distanceX;
    double _distanceY;
    int _hauteur;
    int _largeur;
    double _distanceZeroY;
    double _distanceZeroX;
    int _margeY;
    int _margeX;
};

#endif // DRAWGRAPH_H
