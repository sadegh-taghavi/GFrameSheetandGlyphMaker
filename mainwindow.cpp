#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>
#include <QGraphicsObject>
#include <QFileDialog>
#include <QQuickItem>
#include <QColorDialog>
#include <QFontDialog>
#include <QFile>
#include <qmath.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:/Main.qml"));
    ui->graphicsView->setScene( &m_scene );
    on_BGNDImageFileReloadMaker_clicked();
    m_scene.setBackgroundBrush( QBrush(Qt::transparent) );
    m_backgroundColor = Qt::black;
    ui->BGNDImageFileMaker->setText(QDir::currentPath() + "/background.png");
    on_BGNDImageFileReloadMaker_clicked();
    m_font = QFont("Arial",28);
    ui->FontMaker->setText( m_font.family() );
    redrawMaker();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    on_FrameSheetFileReloadViewer_clicked();
    on_BGNDImageFileReloadViewer_clicked();
}

void MainWindow::on_StopViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("running",false);
}

void MainWindow::on_BFViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QVariant returnedValue;
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "bF",Q_RETURN_ARG(QVariant, returnedValue));
}

void MainWindow::on_NFViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QVariant returnedValue;
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "nF",Q_RETURN_ARG(QVariant, returnedValue));
}

void MainWindow::on_X1Viewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameRate",ui->FrameRateViewer->value());
    ui->XS->setText( "1X" );
}

void MainWindow::on_X2Viewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameRate",2.0f * ui->FrameRateViewer->value());
    ui->XS->setText( "2X" );
}

void MainWindow::on_X4Viewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameRate",4.0f * ui->FrameRateViewer->value());
    ui->XS->setText( "4X" );
}

void MainWindow::on_D12Viewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameRate",0.5f * ui->FrameRateViewer->value());
    ui->XS->setText( "1/2X" );
}

void MainWindow::on_D14Viewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameRate",0.25f * ui->FrameRateViewer->value());
    ui->XS->setText( "1/4X" );
}

void MainWindow::on_FrameRateViewer_valueChanged(int arg1)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameRate",arg1);
}

void MainWindow::on_FramesViewer_valueChanged(int arg1)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameCount",arg1);
}

void MainWindow::on_LoopPlaybackViewer_toggled(bool checked)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("loops",(checked ? -1: 1 ));
}

void MainWindow::on_ReversePlaybackViewer_toggled(bool checked)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("reverse",checked);
}

void MainWindow::on_InterpolateFramesViewer_toggled(bool checked)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("interpolate",checked);
}

void MainWindow::on_FrameHeightViewer_currentIndexChanged(const QString &arg1)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameHeight",arg1.toInt());
}

void MainWindow::on_FrameWidthViewer_currentIndexChanged(const QString &arg1)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("frameWidth",arg1.toInt());
}

void MainWindow::on_PauseViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("paused",true);
}

void MainWindow::on_PlayViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QVariant returnedValue;
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "playForce",Q_RETURN_ARG(QVariant, returnedValue));
}

void MainWindow::on_BGNDImageFileReloadViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("bGNDSource", "" );
    ui->quickWidget->rootObject()->setProperty("bGNDSource", QUrl::fromLocalFile(ui->BGNDImageFileViewer->text()) );
}

void MainWindow::on_FrameSheetFileReloadViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("source", "" );
    ui->quickWidget->rootObject()->setProperty("source", QUrl::fromLocalFile(ui->FrameSheetFileViewer->text()) );
}

void MainWindow::on_FrameSheetFileBrowseViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open framesheet image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if( fileName.isEmpty() )
        return;
    ui->FrameSheetFileViewer->setText(fileName);
    ui->quickWidget->rootObject()->setProperty("source", QUrl::fromLocalFile(fileName) );
}

void MainWindow::on_BGNDImageViewer_toggled(bool arg1)
{
    if( !ui->quickWidget->rootObject() )
        return;
    ui->quickWidget->rootObject()->setProperty("bGNDVisible",arg1);
}

void MainWindow::on_BGNDImageFileBrowseViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open background image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if( fileName.isEmpty() )
        return;
    ui->BGNDImageFileViewer->setText(fileName);
    ui->quickWidget->rootObject()->setProperty("bGNDSource", QUrl::fromLocalFile(fileName) );
}

void MainWindow::on_BGNDColorViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QColorDialog cd;
    if( cd.exec() == QColorDialog::Accepted )
    {
        m_backgroundColor = cd.selectedColor();
        ui->quickWidget->rootObject()->setProperty("bGNDColor", cd.selectedColor() );
        QString qss = QString("background-color: %1").arg(cd.selectedColor().name());
        ui->BGNDColorViewer->setStyleSheet(qss);
    }
}

void MainWindow::on_ZoomInViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QVariant returnedValue;
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "zoomIn",Q_RETURN_ARG(QVariant, returnedValue));
}

void MainWindow::on_Zoom11Viewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QVariant returnedValue;
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "zoom11",Q_RETURN_ARG(QVariant, returnedValue));
}

void MainWindow::on_ZoomOutViewer_clicked()
{
    if( !ui->quickWidget->rootObject() )
        return;
    QVariant returnedValue;
    QMetaObject::invokeMethod(ui->quickWidget->rootObject(), "zoomOut",Q_RETURN_ARG(QVariant, returnedValue));
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
        if( index == 1 )
        {
            ui->quickWidget->setSource( QUrl::fromLocalFile("") );
            redrawMaker();
        }
        else
            ui->quickWidget->setSource(QUrl("qrc:/Main.qml"));
}

//Maker--------------------------------------------------------------

void MainWindow::redrawMaker()
{
    m_scene.clear();
    m_itemsCode.clear();
    loadPart1();
    loadPart2();
    int sw = ui->SheetWidthMaker->currentText().toInt();
    int sh = ui->SheetHeightMaker->currentText().toInt();
    int fw = ui->FrameWidthMaker->currentText().toInt();
    int fh = ui->FrameHeightMaker->currentText().toInt();
    int xCount =  sw / fw;
    int yCount =  sh / fh;
    int index = 0;
    int counter = 0;
    m_scene.setSceneRect( 0, 0,sw  ,sh  );

    if( ui->MakerCoreTab->currentIndex() )
    {
        float rc = ceil( sqrtf( (float)calculateCount() ) );
        if( !rc || !ui->unicodeCodesMaker->count() )
            return;
        float mw = ( float )sw / rc;
        m_scene.setFont( m_font );
        int code = 0;
        int baseIndex = 0;
        QList<QVariant> lchars = ui->unicodeCodesMaker->item( baseIndex )->data(Qt::UserRole).toList();
        code = lchars[0].toInt();

        for ( int yy = 0; yy < rc; ++yy )
        {
            for ( int xx = 0; xx < rc; ++xx )
            {
                if( code > lchars[1].toInt() )
                {
                    ++baseIndex;
                    if( baseIndex >= ui->unicodeCodesMaker->count() )
                        return;
                    lchars = ui->unicodeCodesMaker->item( baseIndex )->data(Qt::UserRole).toList();
                    code = lchars[0].toInt();

                }
                QGraphicsTextItem *item = new QGraphicsTextItem( QString( code ) );
                item->setFont( m_font );
                item->setDefaultTextColor( Qt::white );
                qreal w = item->boundingRect().width();
                qreal h = item->boundingRect().height();
                item->setPos( ( float )xx * mw - ( w * 0.5f ) + ( mw * 0.5f ), ( float )yy * mw - ( h * 0.5f ) + ( mw * 0.5f ) );
                m_itemsCode.push_back( item );
                m_scene.addItem( item );
                code++;
            }
        }
    }else
    {
        if( ui->Part2Maker->isChecked() )
        {
            if( ui->Part2PlaceP1P2Maker->isChecked() )
            {
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart2.size() )
                            break;
                        if( counter < ui->Part2FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part2FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        m_itemsPart2[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart2[index] );
                        ++index;
                        ++counter;
                    }
                }
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart1.size() )
                            break;
                        if( counter < ui->Part1FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part1FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        m_itemsPart1[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart1[index] );
                        ++index;
                        ++counter;
                    }
                }
            }else if( ui->Part2PlaceP2P1Maker->isChecked() )
            {
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart1.size() )
                            break;
                        if( counter < ui->Part1FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part1FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        m_itemsPart1[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart1[index] );
                        ++index;
                        ++counter;
                    }
                }
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart2.size() )
                            break;
                        if( counter < ui->Part2FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part2FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        m_itemsPart2[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart2[index] );
                        ++index;
                        ++counter;
                    }
                }
            }else if( ui->Part2LerpP1P2Maker->isChecked() )
            {
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart2.size() )
                            break;
                        if( counter < ui->Part2FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part2FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        if( counter >= ui->Part1FrameFromMaker->value() - 1 &&
                                counter <= ui->Part1FrameToMaker->value() - 1 )
                           m_itemsPart2[index]->setOpacity(0.5f);
                        m_itemsPart2[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart2[index] );
                        ++index;
                        ++counter;
                    }
                }
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart1.size() )
                            break;
                        if( counter < ui->Part1FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part1FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        if( counter >= ui->Part2FrameFromMaker->value() - 1 &&
                                counter <= ui->Part2FrameToMaker->value() - 1 )
                           m_itemsPart1[index]->setOpacity(0.5f);
                        m_itemsPart1[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart1[index] );
                        ++index;
                        ++counter;
                    }
                }
            }else
            {
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart1.size() )
                            break;
                        if( counter < ui->Part1FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part1FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        if( counter >= ui->Part2FrameFromMaker->value() - 1 &&
                                counter <= ui->Part2FrameToMaker->value() - 1 )
                           m_itemsPart1[index]->setOpacity(0.5f);
                        m_itemsPart1[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart1[index] );
                        ++index;
                        ++counter;
                    }
                }
                counter = index = 0;
                for( int yy = 0; yy < yCount; ++yy )
                {
                    for( int xx = 0; xx < xCount; ++xx )
                    {
                        if( index >= m_itemsPart2.size() )
                            break;
                        if( counter < ui->Part2FrameFromMaker->value() - 1 )
                        {
                            ++counter;
                            continue;
                        }
                        if( counter > ui->Part2FrameToMaker->value() - 1 )
                        {
                            ++counter;
                            break;
                        }
                        if( counter >= ui->Part1FrameFromMaker->value() - 1 &&
                                counter <= ui->Part1FrameToMaker->value() - 1 )
                           m_itemsPart2[index]->setOpacity(0.5f);
                        m_itemsPart2[index]->setPos( ( float )xx * fw,
                                                     ( float )yy * fh);
                        m_scene.addItem( m_itemsPart2[index] );
                        ++index;
                        ++counter;
                    }
                }
            }
        }else
        {
            counter = index = 0;
            for( int yy = 0; yy < yCount; ++yy )
            {
                for( int xx = 0; xx < xCount; ++xx )
                {
                    if( index >= m_itemsPart1.size() )
                        break;
                    if( counter < ui->Part1FrameFromMaker->value() - 1 )
                    {
                        ++counter;
                        continue;
                    }
                    if( counter > ui->Part1FrameToMaker->value() - 1 )
                    {
                        ++counter;
                        break;
                    }
                    m_itemsPart1[index]->setPos( ( float )xx * fw,
                                                 ( float )yy * fh);
                    m_scene.addItem( m_itemsPart1[index] );
                    ++index;
                    ++counter;
                }
            }
        }
    }
}

QString MainWindow::createZeroString(int i_value)
{
    QString str;
    for( int i = 0; i < i_value; ++i )
        str += "0";
    return str;
}

void MainWindow::loadPart1()
{
    m_itemsPart1.clear();
    QString baseFile = ui->Part1BaseImageMaker->text();
    int lenLAstE = baseFile.lastIndexOf("/");
    int cl = -1;
    for( int i = 0; i < baseFile.length(); ++i )
    {
        if( baseFile.at(i + lenLAstE) >= '0' && baseFile.at(i + lenLAstE) <= '9' )
        {
            cl = i + lenLAstE;
            break;
        }
    }
    if( cl < 0 )
        return;
    QString baseNumTxt = baseFile.mid( cl, baseFile.length() - cl - 4 );
    int baseNum = baseNumTxt.toInt();
    QString baseFileCr = baseFile.left( cl );
    QString ext = baseFile.right(4);
    for( int i = baseNum; i < baseNum + ui->Part1FrameCountMaker->value(); ++i )
    {
        QString numValStr = createZeroString(
                    baseNumTxt.length() - QString::number(i).length() ) + QString::number(i);
        QGraphicsItem *gi = new QGraphicsPixmapItem(QPixmap(baseFileCr + numValStr + ext));
        m_itemsPart1.push_back( gi );
    }
}

void MainWindow::loadPart2()
{
    m_itemsPart2.clear();
    QString baseFile = ui->Part2BaseImageMaker->text();
    int lenLAstE = baseFile.lastIndexOf("/");
    int cl = -1;
    for( int i = 0; i < baseFile.length(); ++i )
    {
        if( baseFile.at(i  + lenLAstE) >= '0' && baseFile.at(i + lenLAstE) <= '9' )
        {
            cl = i + lenLAstE;
            break;
        }
    }
    if( cl < 0 )
        return;
    QString baseNumTxt = baseFile.mid( cl, baseFile.length() - cl - 4 );
    int baseNum = baseNumTxt.toInt();
    QString baseFileCr = baseFile.left( cl );
    QString ext = baseFile.right(4);
    for( int i = baseNum; i < baseNum + ui->Part2FrameCountMaker->value(); ++i )
    {
        QString numValStr = createZeroString(
                    baseNumTxt.length() - QString::number(i).length() ) + QString::number(i);
        QGraphicsItem *gi = new QGraphicsPixmapItem(QPixmap(baseFileCr + numValStr + ext));
        m_itemsPart2.push_back( gi );
    }
}

QString MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName( this, "Save sheet", "", "PNG file(*.png)" );
    if ( fileName.isEmpty() )
        return fileName;
    int width = ui->SheetWidthMaker->currentText().toInt();
    int height = ui->SheetHeightMaker->currentText().toInt();
    QImage img( width, height, QImage::Format_ARGB32 );
    img.fill( Qt::transparent );

    QPainter p( &img );
    p.setRenderHint( QPainter::SmoothPixmapTransform, true );
    p.setRenderHint( QPainter::TextAntialiasing, true );
    p.setRenderHint( QPainter::HighQualityAntialiasing, true );
    p.setRenderHint( QPainter::Antialiasing, true );
    m_scene.render( &p );
    p.end();
    img.save( fileName );

    if( ui->MakerCoreTab->currentIndex() )
    {
        float rc = ceil( sqrtf( (float)calculateCount() ) );

        QFile file( fileName.left( fileName.length() - 3 ) + "des" );
        file.open( QIODevice::WriteOnly );
        int count = (int)rc;
        file.write(( char * )&count, sizeof( int ));
        for ( int i = 0; i < m_itemsCode.size(); ++i )
        {
            ushort ch = m_itemsCode[i]->toPlainText().at(0).unicode();
            file.write( ( char * )&ch, sizeof( ushort ) );
            float val = ( m_itemsCode[ i ]->boundingRect().width() / m_font.pointSizeF() ) * 0.5f;
            file.write( ( char * )&val, sizeof( float ) );
        }
        file.close();
    }

    ui->statusBar->showMessage( "Successfully saved!", 5000 );
    return fileName;
}

void MainWindow::on_SaveMaker_clicked()
{
    saveFile();
}

void MainWindow::on_SaveAndViewMaker_clicked()
{
    QString fileName = saveFile();
    if( fileName.isEmpty() )
        return;
    int sw = ui->SheetWidthMaker->currentText().toInt();
    int sh = ui->SheetHeightMaker->currentText().toInt();
    int fw = ui->FrameWidthMaker->currentText().toInt();
    int fh = ui->FrameHeightMaker->currentText().toInt();
    int xCount =  sw / fw;
    int yCount =  sh / fh;
    ui->FrameSheetFileViewer->setText( fileName );
    ui->FrameWidthViewer->setCurrentIndex( ui->FrameWidthMaker->currentIndex() );
    ui->FrameHeightViewer->setCurrentIndex( ui->FrameHeightMaker->currentIndex() );
    ui->FramesViewer->setValue( xCount * yCount);
    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::on_SheetWidthMaker_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    redrawMaker();
}

void MainWindow::on_SheetHeightMaker_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    redrawMaker();
}

void MainWindow::on_Part1BaseImageBrowseMaker_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open part1 base frame image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if( fileName.isEmpty() )
        return;
    ui->Part1BaseImageMaker->setText(fileName);
    redrawMaker();
}

void MainWindow::on_Part1BaseImageReloadMaker_clicked()
{
    redrawMaker();
}

void MainWindow::on_Part2BaseImageBrowseMaker_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open part2 base frame image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if( fileName.isEmpty() )
        return;
    ui->Part2BaseImageMaker->setText(fileName);
    redrawMaker();
}

void MainWindow::on_Part2BaseImageReloadMaker_clicked()
{
    redrawMaker();
}

void MainWindow::on_Part2Maker_toggled(bool arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_Part2LerpP2P1Maker_toggled(bool checked)
{
    Q_UNUSED(checked);
    redrawMaker();
}

void MainWindow::on_Part2PlaceP1P2Maker_toggled(bool checked)
{
    Q_UNUSED(checked);
    redrawMaker();
}

void MainWindow::on_Part1FrameCountMaker_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_Part2FrameCountMaker_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_BGNDImageFileBrowseMaker_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open viewer background image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if( fileName.isEmpty() )
        return;
    ui->BGNDImageFileMaker->setText(fileName);
    on_BGNDImageFileReloadMaker_clicked();
}

void MainWindow::on_BGNDImageFileReloadMaker_clicked()
{
     m_trasparentBrush.setTextureImage( QImage( ui->BGNDImageFileMaker->text() ) );
     ui->graphicsView->setBackgroundBrush( m_trasparentBrush );
}

void MainWindow::on_BGNDImageMaker_toggled(bool arg1)
{
    if( arg1 )
    {
        on_BGNDImageFileReloadMaker_clicked();
    }else
    {
        m_trasparentBrush.setTextureImage( QImage("") );
        ui->graphicsView->setBackgroundBrush( m_trasparentBrush );
    }

}

void MainWindow::on_FrameWidthMaker_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    redrawMaker();
}

void MainWindow::on_FrameHeightMaker_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    redrawMaker();
}

void MainWindow::on_Part2LerpP1P2Maker_toggled(bool checked)
{
    Q_UNUSED(checked);
    redrawMaker();
}

void MainWindow::on_Part2PlaceP2P1Maker_toggled(bool checked)
{
    Q_UNUSED(checked);
    redrawMaker();
}

void MainWindow::on_Part1FrameFromMaker_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_Part1FrameToMaker_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_Part2FrameFromMaker_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_Part2FrameToMaker_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    redrawMaker();
}

void MainWindow::on_quickWidget_statusChanged(const QQuickWidget::Status &arg1)
{
    if( arg1 == QQuickWidget::Ready )
    {
        on_FrameRateViewer_valueChanged(ui->FrameRateViewer->value());
        on_FramesViewer_valueChanged(ui->FramesViewer->value());
        on_LoopPlaybackViewer_toggled(ui->LoopPlaybackViewer->isChecked());
        on_ReversePlaybackViewer_toggled(ui->ReversePlaybackViewer->isChecked());
        on_InterpolateFramesViewer_toggled(ui->InterpolateFramesViewer->isChecked());
        on_FrameHeightViewer_currentIndexChanged(ui->FrameHeightViewer->currentText());
        on_FrameWidthViewer_currentIndexChanged(ui->FrameWidthViewer->currentText());
        on_BGNDImageFileReloadViewer_clicked();
        on_FrameSheetFileReloadViewer_clicked();
        on_BGNDImageViewer_toggled(ui->BGNDImageViewer->isChecked());
        ui->quickWidget->rootObject()->setProperty("bGNDColor", m_backgroundColor );
    }
}

void MainWindow::on_MakerCoreTab_currentChanged(int index)
{
    if( index )
    {
        ui->SaveAndViewMaker->setEnabled( false );
        ui->FrameWidthMaker->setEnabled( false );
        ui->FrameHeightMaker->setEnabled( false );
    }else
    {
        ui->SaveAndViewMaker->setEnabled( true );
        ui->FrameWidthMaker->setEnabled( true );
        ui->FrameHeightMaker->setEnabled( true );
    }
    redrawMaker();
}

void MainWindow::on_AddCodeMaker_clicked()
{
    if( ( ui->UnicodeToMaker->value() - ui->UnicodeFromMaker->value() ) <= 0   )
        return ;
    QListWidgetItem *item = new QListWidgetItem(ui->unicodeCodesMaker);
    item->setText( ui->CaptionMaker->text() + " " + QString::number( ui->UnicodeFromMaker->value() ) +
                   " To " + QString::number( ui->UnicodeToMaker->value() ) );
    QList<QVariant> li;
    li.push_back( ui->UnicodeFromMaker->value() );
    li.push_back( ui->UnicodeToMaker->value() );
    item->setData(Qt::UserRole, li );
    ui->CaptionMaker->clear();
    ui->UnicodeFromMaker->setValue( 0 );
    ui->UnicodeToMaker->setValue( 0 );
    redrawMaker();
}

void MainWindow::on_RemoveCodeMaker_clicked()
{
    QListWidgetItem *item = ui->unicodeCodesMaker->currentItem();
    if( !item )
        return;
    delete item;
    redrawMaker();
}

void MainWindow::on_UpCodeMaker_clicked()
{
    int currentRow = ui->unicodeCodesMaker->currentRow();
    if (currentRow == 0)
        return;
    QListWidgetItem * currentItem = ui->unicodeCodesMaker->takeItem( currentRow );
    ui->unicodeCodesMaker->insertItem( currentRow - 1, currentItem );
    ui->unicodeCodesMaker->setCurrentRow( currentRow - 1 );

    redrawMaker();
}

void MainWindow::on_DownCodeMaker_clicked()
{
    int currentRow = ui->unicodeCodesMaker->currentRow();
    if ( currentRow >= ui->unicodeCodesMaker->count() - 1 )
        return;
    QListWidgetItem * currentItem = ui->unicodeCodesMaker->takeItem( currentRow );
    ui->unicodeCodesMaker->insertItem( currentRow + 1, currentItem );
    ui->unicodeCodesMaker->setCurrentRow( currentRow + 1 );

    redrawMaker();
}

void MainWindow::on_FontSelectMaker_clicked()
{
    QFontDialog fd;
    fd.setCurrentFont(m_font);
    if( fd.exec() )
    {
        m_font = fd.selectedFont();
        ui->FontMaker->setText( m_font.family() );
        redrawMaker();
    }
}

int MainWindow::calculateCount()
{
    int count = 0;
    for( int i = 0; i < ui->unicodeCodesMaker->count(); ++i )
    {
        QList<QVariant> lchars = ui->unicodeCodesMaker->item(i)->data(Qt::UserRole).toList();
        count += ( lchars[1].toInt() - lchars[0].toInt() );
    }
    return count;
}
