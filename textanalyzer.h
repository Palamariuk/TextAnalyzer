#ifndef TEXTANALYZER_H
#define TEXTANALYZER_H

#include "text.h"

#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <map>

class TextAnalyzer {
public:
    /*Конструктори*/
    TextAnalyzer() = default;
    TextAnalyzer(Text text);

    /*Деструктор*/
    virtual ~TextAnalyzer() = default;

    /*Методи доступу до полів*/
    [[nodiscard]] inline const Text &text() const {return text_;}

    inline void setText(const Text &text) {text_ = text;}

    /*Методи розділення тексту на складові у вектор стрічок*/
    QVector<QString> splitIntoSentences();
    QVector<QString> splitIntoWords();

    /*Методи отримання однакових складових тексту у вектор стрічок*/
    QVector<QString> getIdenticalSentences();
    QVector<QString> getIdenticalProperNames();

    /*Метод знаходження всіх входжень підстрічки в текст*/
    QVector<int> findAll(QString substring);

    /*Метод знаходження всіх слів та їх позиції у тексті*/
    QVector<QPair<QString, int>> getWordsPositions();

    /*Методи обчислення кількості символів/букв/слів/речень у тексті*/
    [[nodiscard]] int computeNumberOfSymbol(char symbol);
    [[nodiscard]] int computeNumberOfLetters();
    [[nodiscard]] int computeNumberOfWords();
    [[nodiscard]] int computeNumberOfSentences();

    /*Методи обчислення мінімальної/максимальної довжини слів у тексті*/
    [[nodiscard]] int computeMinWordsLength();
    [[nodiscard]] int computeMaxWordsLength();

    /*Методи обчислення середньої довжини слів/речень у тексті*/
    [[nodiscard]] double computeAverageWordsLength();
    [[nodiscard]] double computeAverageSentencesLength();

    /*Метод створення нового тексту з кількостями повторень слів*/
    Text generateRepeatNumbers();

private:
    Text text_;
};

#endif // TEXTANALYZER_H
