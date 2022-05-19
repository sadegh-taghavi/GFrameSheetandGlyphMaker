#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QQuickWidget>
#include <QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QBrush          m_trasparentBrush;
    QColor          m_backgroundColor;
    QGraphicsScene  m_scene;
    QList<QGraphicsItem *>	m_itemsPart1;
    QList<QGraphicsItem *>	m_itemsPart2;
    QList<QGraphicsTextItem *>      m_itemsCode;
    QFont                   m_font;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void resizeEvent(QResizeEvent * event);

private slots:
    void on_StopViewer_clicked();

    void on_BFViewer_clicked();

    void on_NFViewer_clicked();

    void on_X1Viewer_clicked();

    void on_X2Viewer_clicked();

    void on_X4Viewer_clicked();

    void on_D12Viewer_clicked();

    void on_D14Viewer_clicked();

    void on_FrameRateViewer_valueChanged(int arg1);

    void on_FramesViewer_valueChanged(int arg1);

    void on_LoopPlaybackViewer_toggled(bool checked);

    void on_ReversePlaybackViewer_toggled(bool checked);

    void on_InterpolateFramesViewer_toggled(bool checked);

    void on_PauseViewer_clicked();

    void on_PlayViewer_clicked();

    void on_FrameSheetFileBrowseViewer_clicked();

    void on_BGNDImageViewer_toggled(bool arg1);

    void on_BGNDImageFileBrowseViewer_clicked();

    void on_BGNDColorViewer_clicked();

    void on_FrameHeightViewer_currentIndexChanged(const QString &arg1);

    void on_FrameWidthViewer_currentIndexChanged(const QString &arg1);

    void on_BGNDImageFileReloadViewer_clicked();

    void on_FrameSheetFileReloadViewer_clicked();

    void on_ZoomInViewer_clicked();

    void on_Zoom11Viewer_clicked();

    void on_ZoomOutViewer_clicked();

    void on_tabWidget_currentChanged(int index);
//Maker--------------------------------------------------------------
    void redrawMaker();
    QString createZeroString( int i_value );
    void loadPart1();

    void loadPart2();

    QString saveFile();

    void on_SaveMaker_clicked();

    void on_SheetWidthMaker_currentIndexChanged(int index);

    void on_SheetHeightMaker_currentIndexChanged(int index);

    void on_SaveAndViewMaker_clicked();

    void on_Part1BaseImageBrowseMaker_clicked();

    void on_Part1BaseImageReloadMaker_clicked();

    void on_Part2BaseImageBrowseMaker_clicked();

    void on_Part2BaseImageReloadMaker_clicked();

    void on_Part2Maker_toggled(bool arg1);

    void on_Part2LerpP2P1Maker_toggled(bool checked);

    void on_Part2PlaceP1P2Maker_toggled(bool checked);

    void on_Part1FrameCountMaker_valueChanged(int arg1);

    void on_Part2FrameCountMaker_valueChanged(int arg1);

    void on_BGNDImageFileBrowseMaker_clicked();

    void on_BGNDImageFileReloadMaker_clicked();

    void on_BGNDImageMaker_toggled(bool arg1);

    void on_FrameWidthMaker_currentIndexChanged(int index);

    void on_FrameHeightMaker_currentIndexChanged(int index);

    void on_Part2LerpP1P2Maker_toggled(bool checked);

    void on_Part2PlaceP2P1Maker_toggled(bool checked);

    void on_Part1FrameFromMaker_valueChanged(int arg1);

    void on_Part1FrameToMaker_valueChanged(int arg1);

    void on_Part2FrameFromMaker_valueChanged(int arg1);

    void on_Part2FrameToMaker_valueChanged(int arg1);

    void on_quickWidget_statusChanged(const QQuickWidget::Status &arg1);

    void on_MakerCoreTab_currentChanged(int index);

    void on_AddCodeMaker_clicked();

    void on_RemoveCodeMaker_clicked();

    void on_UpCodeMaker_clicked();

    void on_DownCodeMaker_clicked();

    void on_FontSelectMaker_clicked();

    int calculateCount();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
