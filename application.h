#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStatusBar>
#include <QTextEdit>
#include <QDebug>

#include "text.h"
#include "textanalyzer.h"
#include "frequency.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Application; }
QT_END_NAMESPACE

class Application : public QMainWindow
{
    Q_OBJECT

public:
    Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_openFile_triggered();

    void on_saveFile_triggered();

    void on_saveFileAs_triggered();

    void on_closeFile_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_textEdit_textChanged();

    void on_clearFormatting_triggered();

    void on_btAdvansedStatistics_clicked();

    void on_getAverageLength_triggered();

    void on_showLongestWords_triggered();

    void on_showShortestWords_triggered();

    void on_getLetterFrequency_triggered();

    void on_showIdSentences_triggered();

    void on_repeatNumbers_triggered();

    void on_showIdProperNames_triggered();

    void highlightText(QTextEdit* te, QColor color, size_t begin, size_t length);

    void highlightWordsByLength(QTextEdit* te, QVector<QPair<QString, int>> words, int len);

    void highlightAllOccures(QTextEdit* te, TextAnalyzer analyzer, QVector<QString> substrings);

private:
    Ui::Application *ui;

    Text *text = nullptr;
};
#endif // APPLICATION_H
