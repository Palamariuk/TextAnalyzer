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
    TextAnalyzer() = default;
    TextAnalyzer(Text text);

    virtual ~TextAnalyzer() = default;

    [[nodiscard]] inline const Text &text() const {return text_;}

    inline void setText(const Text &text) {text_ = text;}

    QVector<QString> splitIntoSentences();
    QVector<QString> splitIntoWords();
    QVector<QPair<QString, int>> getWordsPositions();

    QVector<QString> getIdenticalSentences();
    QVector<QString> getIdenticalProperNames();

    QVector<int> findAll(QString substring);

    [[nodiscard]] int computeNumberOfSymbol(char symbol);
    [[nodiscard]] int computeNumberOfLetters();
    [[nodiscard]] int computeNumberOfWords();
    [[nodiscard]] int computeNumberOfSentences();

    [[nodiscard]] int computeMinWordsLength();
    [[nodiscard]] int computeMaxWordsLength();

    [[nodiscard]] double computeAverageWordsLength();
    [[nodiscard]] double computeAverageSentencesLength();

    Text generateRepeatNumbers();

private:
    Text text_;
};

#endif // TEXTANALYZER_H
