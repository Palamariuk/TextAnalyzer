#ifndef FREQUENCY_H
#define FREQUENCY_H

#include <QDialog>

#include "text.h"
#include "textanalyzer.h"
#include "NoLettersException.h"

namespace Ui {
class Frequency;
}

class Frequency : public QDialog
{
    Q_OBJECT

public:
    explicit Frequency(Text _text);
    ~Frequency();

private slots:
    void on_btAllFrequency_clicked();

    void on_btFrequency_clicked();

private:
    Ui::Frequency *ui;

    Text text;
    TextAnalyzer analyzer;
};

#endif // FREQUENCY_H
