#include "drawgraph.hpp"
drawGraph::drawGraph(QWidget *parent, int hauteur, int largeur): QWidget(parent), _pixmap(nullptr), _pen(),
    _hauteur(hauteur), _largeur(largeur), _distanceZeroY(0), _distanceZeroX(0), _margeY(20), _margeX(20){

  initDefaultPixMap(largeur, hauteur);

}

drawGraph::~drawGraph(){
    delete _pixmap;
}

void drawGraph::initDefaultPixMap(int largeur, int hauteur) {
    setMinimumSize(largeur, hauteur);
    if(_pixmap) {
        delete _pixmap;
    }
    _pixmap = new QPixmap(this->size());
    QPainter painter(_pixmap);
    painter.fillRect(rect(), Qt::white);
}

void drawGraph::drawP(int pasX, int pasY, QTableWidget *table, const QColor &couleurUne, const QColor &couleurDeux, const QColor &couleurTrois) {
    QPainter painter(_pixmap);
    QVector<QColor> vecColor;
    vecColor.push_back(couleurUne);
    vecColor.push_back(couleurDeux);
    vecColor.push_back(couleurTrois);
    _pen.setWidth(5);

    int j = 0;
    for(int row = 0; row < table->rowCount(); ++row) {
        QStringList lignes;
        for(int col=0; col < table->columnCount(); ++col) {
            lignes << table->item(row, col)->text();
        }
        for(int i = 1; i < lignes.count(); i++) {
            _pen.setColor(vecColor[j]);
            painter.setPen(_pen);
            if(j == 2) j=0;
            else j++;
            double x = lignes[0].toDouble();
            double y = lignes[i].toDouble();
            double distanceX = _distanceX / (QString::number(pasX)).toDouble();
            double distanceY = _distanceY /  (QString::number(pasY)).toDouble();
            painter.drawPoint((_distanceZeroX+_margeX)+x*distanceX, ((_hauteur-(_distanceZeroY+_margeY))-(y*distanceY)));
        }
        j=0;
    }

    update();
}

void drawGraph::drawB(int pasX, int pasY, QTableWidget *table, const QColor &couleurUne, const QColor &couleurDeux, const QColor &couleurTrois){
    QPainter painter(_pixmap);
    QVector<QColor> vecColor;
    vecColor.push_back(couleurUne);
    vecColor.push_back(couleurDeux);
    vecColor.push_back(couleurTrois);
    _pen.setWidth(1);

    int j = 0;
    for(int row = 0; row < table->rowCount(); ++row) {
        QStringList lignes;
        for(int col=0; col < table->columnCount(); ++col) {
            lignes << table->item(row, col)->text();
        }
        for(int i = 1; i < lignes.count(); i++) {
            _pen.setColor(vecColor[j]);
            painter.setPen(_pen);
            if(j == 2) j=0;
            else j++;
            double x = lignes[0].toDouble();
            double y = lignes[i].toDouble();
            double distanceX = _distanceX / (QString::number(pasX)).toDouble();
            double distanceY = _distanceY /  (QString::number(pasY)).toDouble();
            painter.drawLine(QPoint((_distanceZeroX+_margeX)+x*distanceX, _hauteur-(_distanceZeroY+_margeY)), QPoint((_distanceZeroX+_margeX)+x*distanceX, ((_hauteur-(_distanceZeroY+_margeY))-(y*distanceY))));
        }
        j=0;
    }

    update();
}

void drawGraph::drawL(int pasX, int pasY, QTableWidget *table, const QColor &couleurUne, const QColor &couleurDeux, const QColor &couleurTrois){
    QPainter painter(_pixmap);
    QVector<QColor> vecColor;
    vecColor.push_back(couleurUne);
    vecColor.push_back(couleurDeux);
    vecColor.push_back(couleurTrois);
    _pen.setWidth(1);

    int j = 0;
    QStringList lastPoints;
    for(int i = 0; i < table->columnCount(); ++i) {
        lastPoints << table->item(0, i)->text();
    }

    for(int row = 0; row < table->rowCount(); ++row) {
        QStringList lignes;
        for(int col=0; col < table->columnCount(); ++col) {
            lignes << table->item(row, col)->text();
        }
        for(int i = 1; i < lignes.count(); i++) {
            _pen.setColor(vecColor[j]);
            painter.setPen(_pen);
            if(j == 2) j=0;
            else j++;
            double x = lignes[0].toDouble();
            double y = lignes[i].toDouble();
            double distanceX = _distanceX / (QString::number(pasX)).toDouble();
            double distanceY = _distanceY /  (QString::number(pasY)).toDouble();
            double xLast = lastPoints[0].toDouble();
            double yLast = lastPoints[i].toDouble();

            painter.drawLine(QPoint((_distanceZeroX+_margeX)+xLast*distanceX, ((_hauteur-(_distanceZeroY+_margeY))-(yLast*distanceY))), QPoint((_distanceZeroX+_margeX)+x*distanceX, ((_hauteur-(_distanceZeroY+_margeY))-(y*distanceY))));
        }
        j=0;
        lastPoints = lignes;
    }

    update();
}

void drawGraph::setGraph(int largeur,
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
                         bool stateGrille)
{
    if(_pixmap) {
        delete _pixmap;
    }
    _largeur = largeur;
    _hauteur = hauteur;
    _margeX = margeX;
    _margeY = margeY;
    setMinimumSize(largeur, hauteur);
    _pixmap = new QPixmap(largeur, hauteur);
    QPainter painter(_pixmap);
    painter.fillRect(rect(), font);

    //position et taille du watermark
    QRectF target(largeur-400.0, 30.0, 400.0, 400.0);
    QRectF source(0.0, 0.0, 900.0, 900.0);
    //lien du watermark
    QImage image(":/img/watermark.png");
    //QImage image("../JOUVIN_Tanguy_Projet/docs_projet/watermark.png");
    // on dessine le watermark
    painter.drawImage(target, image, source);

    _pen.setColor(axes);
    _pen.setWidth(1);
    painter.setPen(_pen);
    painter.setFont(QFont(styleName, styleSize));

    // calcul dernière valeur sur l'axe des X
    int endValueX, valX = 0;
    while(true){
        endValueX = valX;
        if(maxX < 0){
                break;
        }else{
            valX += pasX;
            if(endValueX >= maxX)
                break;
        }
    }
    // calcul première valeur sur l'axe des X
    int beginValueX, valX_ = 0;
    while(true){
        beginValueX = valX_;
        if(minX < 0){
            valX_ -= pasX;
            if(beginValueX <= minX)
                break;
        }else{
            break;
        }
    }
    // calcul dernière valeur sur l'axe des Y
    int endValueY, valY = 0;
    while(true){
        endValueY = valY;
        if(maxY < 0){
                break;
        }else{
            valY += pasY;
            if(endValueY >= maxY)
                break;
        }
    }
    // calcul première valeur sur l'axe des Y
    int beginValueY, valY_ = 0;
    while(true){
        beginValueY = valY_;
        if(minY < 0){
            valY_ -= pasY;
            if(beginValueY <= minY)
                break;
        }else{
            break;
        }
    }

    //calcul le nombres d'espace entre le beginValueX et endValueX
    float nombreEspaceValeurX= 0.0;
    for(int i = beginValueX ; i < endValueX ; i += pasX) {
        ++nombreEspaceValeurX;
    }
    //calcul le nombres d'espace entre le beginValueY et endValueY
    float nombreEspaceValeurY= 0.0;
    for(int i = beginValueY ; i < endValueY ; i += pasY) {
        ++nombreEspaceValeurY;
    }

    _distanceX = (largeur - (2*margeX)) / nombreEspaceValeurX;
    _distanceY = (hauteur - (2*margeY)) / nombreEspaceValeurY;

    //distance par rapport à zero Y
    double distanceZeroY = 0.0;
    for(int i = 0 ; i > beginValueY ; i -= pasY) {
        if(beginValueY > 0)
            break;
        else{
            distanceZeroY += _distanceY;
        }
    }
    _distanceZeroY = distanceZeroY;

    //distance par rapport à zero X
    double distanceZeroX = 0.0;
    for(int i = 0 ; i > beginValueX ; i -= pasX) {
        if(beginValueX > 0)
            break;
        else{
            distanceZeroX += _distanceX;
        }
    }
    _distanceZeroX = distanceZeroX;

    double distanceParcouruX = 0.0, distanceParcouruY = 0.0, coordonneeXZero = 0.0;
    for(int i = beginValueX ; i <= endValueX ; i += pasX) {
        if(stateGrille) painter.drawLine(QPoint(distanceParcouruX+margeX, margeY), QPoint(distanceParcouruX+margeX, hauteur-margeY));
        painter.drawText(distanceParcouruX+margeX, hauteur-(distanceZeroY+margeY), styleSize, styleSize, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(i));
        if(i == 0){
            coordonneeXZero = distanceParcouruX+margeX;
            for(int j = beginValueY ; j <= endValueY ; j += pasY){
                if(j !=0){
                    if(stateGrille) painter.drawLine(QPoint(margeX, hauteur-(distanceParcouruY+margeY)), QPoint(largeur-margeX, hauteur-(distanceParcouruY+margeY)));
                    painter.drawText(distanceParcouruX+margeX+4, hauteur-(distanceParcouruY+margeY), styleSize+20, styleSize, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(j));
                }
                distanceParcouruY += _distanceY;
            }
        }
        distanceParcouruX += _distanceX;
    }
    _pen.setWidth(3);
    painter.setPen(_pen);
    painter.drawLine(QPoint(margeX, hauteur-(distanceZeroY+margeY)), QPoint(largeur-margeX, hauteur-(distanceZeroY+margeY)));
    painter.drawLine(QPoint(coordonneeXZero, hauteur-margeY), QPoint(coordonneeXZero, 0+margeY));

    update();
}

void drawGraph::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, *_pixmap);
}

QPixmap* drawGraph::getPixmap() const{
    return this->_pixmap;
}
