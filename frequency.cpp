#include "frequency.h"
#include "ui_frequency.h"
#include <QMessageBox>

Frequency::Frequency(Text _text): ui(new Ui::Frequency)
{
    ui->setupUi(this);

    text = _text;
    analyzer.setText(text);
    ui->tbFrequency->resizeColumnsToContents();
}

Frequency::~Frequency()
{
    delete ui;
}

void Frequency::on_btAllFrequency_clicked()
{
    int letters = analyzer.computeNumberOfLetters();
    if(!letters){
        QMessageBox::critical(this, "No Letters Error", NoLettersException().what());
    } else {
        ui->tbFrequency->setRowCount(26);
        for(char letter = 'A'; letter <= 'Z'; letter++){
            ui->tbFrequency->setItem(letter - 'A', 0, new QTableWidgetItem(QString(letter)));
            double frequency = (analyzer.computeNumberOfSymbol(letter) + analyzer.computeNumberOfSymbol(tolower(letter))) * 100.0 / letters;
            ui->tbFrequency->setItem(letter - 'A', 1, new QTableWidgetItem(QString::number(frequency, 'g', 3) + "%"));
        }
    }
}

void Frequency::on_btFrequency_clicked()
{
    double frequency;

    try {
        int numLetters = analyzer.computeNumberOfLetters();
        if(!numLetters) throw NoLettersException();

        QString qsLetter = ui->leLetter->text();
        char letter = qsLetter.toStdString()[0];
        frequency = analyzer.computeNumberOfSymbol(letter) * 100.0 / numLetters;

    } catch (NoLettersException& error) {
        frequency = 0;
        QMessageBox::critical(this, "No Letters Error", error.what());
    }

    ui->leFrequency->setText(QString::number(frequency, 'g', 3) + "%");
}
