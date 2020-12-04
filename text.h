#ifndef TEXT_H
#define TEXT_H

#include <QString>
#include <QTextStream>
#include <QTextEdit>

#include <FileOpenningException.h>
#include <FileSavingException.h>

class Text
{
public:
    Text() = default;
    Text(QString text_);
    Text(QString file_, QString text_);
    Text(const Text& other);

    ~Text() = default;

    void readFromFile(QString fileName);
    void saveToFile(QString fileName);
    void clearAll();

    inline void setFile(QString file){file_ = file;}
    inline void setData(QString text){text_ = text;}
    inline void setSaveStatus(bool status){isSaved_ = status;}

    [[nodiscard]] inline QString file(){return file_;}
    [[nodiscard]] inline QString text(){return text_;}
    [[nodiscard]] inline bool saved(){return isSaved_;}

private:
    QString file_;
    QString text_;
    bool isSaved_;

    friend QTextStream &operator>>(QTextStream& in, Text& text);
    friend QTextStream &operator<<(QTextStream& in, Text& text);

    friend void operator<<(QTextEdit* textEdit, Text& text);
    friend void operator>>(QTextEdit* textEdit, Text& text);
};

#endif // TEXT_H
