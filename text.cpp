#include "text.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

Text::Text(QString text):
    text_(text){}

Text::Text(QString file, QString text):
    file_(file), text_(text){}

Text::Text(const Text &other):
    file_(other.file_), text_(other.text_){}

void Text::readFromFile(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        throw FileOpenningException();
    }

    file_ = fileName;
    QTextStream in(&file);

    in >> (*this);

    isSaved_ = true;

    file.close();
}

void Text::saveToFile(QString fileName)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QFile::Text)) {
        throw FileSavingException();
    }

    file_ = fileName;
    QTextStream out(&file);

    out << *(this);

    isSaved_ = true;

    file.close();

}

void Text::clearAll()
{
    text_.clear();
    file_.clear();
    isSaved_ = false;
}

/*Friend functions*/

void operator>>(QTextEdit *textEdit, Text &text){
    text.text_ = textEdit->toPlainText();
}

void operator<<(QTextEdit *textEdit, Text &text){
    textEdit->setText(text.text_);
}

QTextStream &operator<<(QTextStream &out, Text &text)
{
    out << text.text_;
    return out;
}

QTextStream &operator>>(QTextStream &in, Text &txt)
{
    txt.text_ = in.readAll();
    txt.isSaved_ = true;
    return in;
}
