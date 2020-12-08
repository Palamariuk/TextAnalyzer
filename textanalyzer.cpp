#include "textanalyzer.h"

TextAnalyzer::TextAnalyzer(Text text):
    text_(text){}

QVector<QString> TextAnalyzer::splitIntoSentences()
{
    return text_.text().split(QRegExp("[.?!]\\s*"),
                              Qt::SkipEmptyParts).toVector();
}

QVector<QString> TextAnalyzer::splitIntoWords()
{
    return text_.text().split(QRegExp("\\W"),
                              Qt::SkipEmptyParts).toVector();
}

QVector<QPair<QString, int>> TextAnalyzer::getWordsPositions()
{
    QString text = text_.text();
    QVector<QString> words = splitIntoWords();

    QVector<QPair<QString, int>> wordsWithPos;
    int pos = 0;
    for(; words.length() > 0; ){
        QString word = words[0];
        words.pop_front();
        pos = text.indexOf(word, pos);
        wordsWithPos.push_back(QPair<QString, int>(word, pos));
        pos += word.length();
    }

    return wordsWithPos;
}

QVector<QString> TextAnalyzer::getIdenticalSentences()
{
    auto sentences = splitIntoSentences();
    std::map<QString, size_t> repeats;
    QVector<QString> repeatedSentences;

    for(auto sentence: sentences){
        repeats[sentence]++;
    }

    for(auto sentence: repeats){
        if(sentence.second > 1){
            repeatedSentences.push_back(sentence.first);
        }
    }

    return repeatedSentences;
}

QVector<QString> TextAnalyzer::getIdenticalProperNames()
{
    QFile file(":/Resourses/Dictionary/proper_names.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "File is not opened.";
    }

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();

    auto words = splitIntoWords();

    words.erase(std::partition(words.begin(), words.end(),
                               [](const QString word){return word[0].isUpper();}),
                words.end());

    std::map<QString, size_t> repeats;
    QVector<QString> repeatedWords;

    for(auto word: words){
        repeats[word]++;
    }

    for(auto word: repeats){
        if(word.second > 1){
            repeatedWords.push_back(word.first);
        }
    }

    QVector<QString> properNames;

    for(auto word: repeatedWords){
        if(json[word].toString().toInt()){
            properNames.push_back(word);
        }
    }

    return properNames;
}

QVector<int> TextAnalyzer::findAll(QString substring)
{
    QString text = text_.text();

    QVector<int> positions;

    int pos = 0;
    while ((pos = text.indexOf(substring, pos)) != -1) {
        positions.push_back(pos);
        pos += substring.length();
    }

    return positions;
}

int TextAnalyzer::computeNumberOfLetters()
{
    return text_.text().count(QRegExp("[a-zA-z]"));
}

double TextAnalyzer::computeAverageWordsLength()
{
    double sum = 0;
    auto words = splitIntoWords();
    for(auto word: words){
        sum += word.length();
    }
    return (sum / words.size());
}

double TextAnalyzer::computeAverageSentencesLength()
{
    double sum = 0;
    auto sentences = splitIntoSentences();
    for(QString sentence: sentences){
        sum += sentence.length();
    }
    return (sum / sentences.size());
}

int TextAnalyzer::computeNumberOfSymbol(char symbol)
{
    return text_.text().count(symbol);
}

Text TextAnalyzer::generateRepeatNumbers()
{
    auto words = getWordsPositions();
    auto text = text_.text();
    std::map<QString, size_t> repeats;

    size_t offset = 0;
    for(auto word: words){
        repeats[word.first]++;
        QString number = "<b style='color:gray'>("+
                QString::number(repeats[word.first])+")</b>";
        text.insert(word.second + word.first.length() + offset, number);
        offset += number.length();
    }
    text.replace("\n", "<br>");

    return Text(text);
}

int TextAnalyzer::computeNumberOfWords()
{
    return splitIntoWords().size();
}

int TextAnalyzer::computeNumberOfSentences()
{
    return splitIntoSentences().size();
}

int TextAnalyzer::computeMinWordsLength()
{
    auto words = splitIntoWords();

    int minLen = std::min_element(words.begin(), words.end(), [](QString a, QString b){
            return a.length() < b.length();
    })->length();

    return minLen;
}

int TextAnalyzer::computeMaxWordsLength()
{
    auto words = splitIntoWords();

    int maxLen = std::max_element(words.begin(), words.end(), [](QString a, QString b){
        return a.length() < b.length();
    })->length();

    return maxLen;
}


