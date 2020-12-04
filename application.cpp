#include "application.h"
#include "ui_application.h"

#include "FileOpenningException.h"

Application::Application(QWidget *parent):
    QMainWindow(parent), ui(new Ui::Application){

    ui->setupUi(this);
    ui->statusbar->addPermanentWidget(ui->btAdvansedStatistics);
    text = new Text();
}

Application::~Application()
{
    delete ui;
}


void Application::on_openFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open some file");

    try {
        text->readFromFile(fileName);
    } catch (FileOpenningException& error){
        QMessageBox::warning(this, "File Openning Error", error.what());
        return;
    }

    ui->textEdit << (*text);

}

void Application::on_saveFile_triggered()
{
    ui->textEdit >> *(text);

    try {
        if(!(text->file().isEmpty())){
            text->saveToFile(text->file());
        } else {
            on_saveFileAs_triggered();
        }
    } catch (FileSavingException& error) {
        QMessageBox::warning(this, "File Saving Error", error.what());
        return;
    }

}

void Application::on_saveFileAs_triggered()
{
    try {
        QString fileName = QFileDialog::getSaveFileName(this, "Save as");
        text->saveToFile(fileName);
    } catch (FileSavingException& error) {
        QMessageBox::warning(this, "File Saving Error", error.what());
        return;
    }

}

void Application::on_closeFile_triggered()
{
    if(!text->saved()){
        QMessageBox warning;
        warning.setWindowTitle("Clearing text");
        warning.setIcon(QMessageBox::Warning);
        warning.setText("You forgot to save data.\n"
                        "Do you want to clear text without saving?");
        warning.setStandardButtons(QMessageBox::Cancel | QMessageBox::No |
                                   QMessageBox::Yes);

        int result = warning.exec();

        if(result == QMessageBox::Cancel){
            return;
        } else if(result == QMessageBox::No) {
            on_saveFile_triggered();
        }
    }

    ui->textEdit->clear();
    text->clearAll();
}

void Application::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Application::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Application::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Application::on_actionPaste_triggered()
{
    ui->textEdit->paste();
    on_clearFormatting_triggered();
}

void Application::on_textEdit_textChanged()
{
    text->setSaveStatus(false);
    QString message = "Total length: " +
            QString::number(ui->textEdit->toPlainText().length());
    ui->statusbar->showMessage(message);
}

void Application::on_clearFormatting_triggered()
{
    highlightText(ui->textEdit, Qt::white, 0, ui->textEdit->toPlainText().length());
}

void Application::highlightText(QTextEdit *textEdit, QColor color,
                                size_t begin, size_t length)
{
    int end = begin + length;

    QTextCharFormat format;
    format.setBackground(color);

    QTextCursor cursor(textEdit->document());
    cursor.setPosition(begin, QTextCursor::MoveAnchor);
    cursor.setPosition(end, QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
}

void Application::on_btAdvansedStatistics_clicked()
{
    ui->textEdit >> *(text);
    TextAnalyzer analyzer(*text);

    size_t nLetters = analyzer.computeNumberOfLetters();
    size_t nWords = analyzer.computeNumberOfWords();
    size_t nSentences = analyzer.computeNumberOfSentences();

    QString message = "Letters: " + QString::number(nLetters) +
            " | Words: " + QString::number(nWords) +
            " | Sentences: " + QString::number(nSentences);

    ui->statusbar->showMessage(message);
}

void Application::on_getAverageLength_triggered()
{
    ui->textEdit >> *(text);
    TextAnalyzer analyzer(*text);

    double averageWordsLength = analyzer.computeAverageWordsLength();
    double averageSentencesLength = analyzer.computeAverageSentencesLength();

    QMessageBox::information(this, "Information about average lengths",
                             "The average length of sentences = " +
                             QString::number(averageSentencesLength) + "\n" +
                             "The average length of words = " +
                             QString::number(averageWordsLength));
}

void Application::on_showLongestWords_triggered()
{
    on_clearFormatting_triggered();

    ui->textEdit >> *(text);
    TextAnalyzer analyzer(*text);

    highlightWordsByLength(ui->textEdit, analyzer.getWordsPositions(),
                           analyzer.computeMaxWordsLength());
}

void Application::on_showShortestWords_triggered()
{
    on_clearFormatting_triggered();

    ui->textEdit >> *(text);
    TextAnalyzer analyzer(*text);

    highlightWordsByLength(ui->textEdit, analyzer.getWordsPositions(),
                           analyzer.computeMinWordsLength());
}

void Application::highlightWordsByLength(QTextEdit *textEdit,
                                         QVector<QPair<QString, int>> words, int len)
{
    words.erase(std::partition(words.begin(), words.end(), [=](QPair<QString, int> str) {
        return str.first.length() == len;
    }), words.end());

    for(auto word: words){
        highlightText(textEdit, Qt::yellow, word.second, len);
    }
}

void Application::highlightAllOccures(QTextEdit *te, TextAnalyzer analyzer, QVector<QString> substrings)
{

    QVector<int> hues{0, 20, 40, 60, 80, 100, 120,
                     140, 160, 180, 200, 220, 240,
                     260, 280, 300, 320, 340};

    int ind = 0;
    for(auto substring: substrings){
        auto positions = analyzer.findAll(substring);
        auto color = QColor::fromHsl(hues[ind++ % 18], rand() % 156 + 100, 128);
        for(auto position: positions){
            highlightText(te, color, position, substring.length());
        }
    }
}

void Application::on_getLetterFrequency_triggered()
{
    Frequency frequency(*text);
    frequency.exec();
}

void Application::on_showIdSentences_triggered()
{
    on_clearFormatting_triggered();

    ui->textEdit >> *(text);
    TextAnalyzer analyzer(*text);

    auto sentences = analyzer.getIdenticalSentences();

    highlightAllOccures(ui->textEdit, analyzer, sentences);
}

void Application::on_repeatNumbers_triggered()
{
    if(!ui->textEdit->isReadOnly()){
        ui->textEdit >> *(text);
        TextAnalyzer analyzer(*text);
        Text result = analyzer.generateRepeatNumbers();
        ui->textEdit->setHtml(result.text());
        ui->textEdit->setReadOnly(true);
        ui->repeatNumbers->setText("Hide repeat numbers");
    } else {
        ui->textEdit << *(text);
        ui->textEdit->setReadOnly(false);
        ui->repeatNumbers->setText("Show repeat numbers");
    }
}

void Application::on_showIdProperNames_triggered()
{
    on_clearFormatting_triggered();

    ui->textEdit >> *(text);
    TextAnalyzer analyzer(*text);

    auto properNames = analyzer.getIdenticalProperNames();

    highlightAllOccures(ui->textEdit, analyzer, properNames);
}
