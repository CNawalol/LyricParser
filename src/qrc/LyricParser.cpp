//
// Created by awalol on 2023/9/30.
//
#include "LyricParser.h"
#include "string"
#include "regex"
#include "Line.h"

using namespace std;

namespace LyricParser {
    regex qrcRegex(R"((\[\d+,\d+\])(.+))", regex_constants::multiline); // Group1:时间  Group2:内容
    regex wordTimeRegex(R"((.+?)\((\d+),(\d+)\))"); // Group1:单词 Group2:开始时间 Group3:持续时间
    vector<Line> lines;

    vector<Line> parser(string lyric) {
        sregex_iterator lineIterator(lyric.begin(), lyric.end(), qrcRegex);
        sregex_iterator end(lyric.begin(), lyric.end(), qrcRegex);

        for (; lineIterator != end; lineIterator++) {
            const smatch &lineMatches = *lineIterator;

            string ts = lineMatches[1]; // 行时间点
            string lineContent = lineMatches[2]; // 单词和词时间点

            // 词处理
            sregex_iterator wordIterator(lineContent.begin(), lineContent.end(), wordTimeRegex);
            vector<Word> words;
            for (; wordIterator != end; wordIterator++) {
                const smatch& wordMatches = *wordIterator;

                Word word;
                word.word = wordMatches[1]; // 单词
                word.startTime = stol(wordMatches[2]); // 单词开始时间
                word.duration = stol(wordMatches[3]); // 单词持续时间

                words.emplace_back(word);
            }

            // 行处理
            Line line;
            sscanf(ts.c_str(), "[%ld,%ld]", &line.startTime, &line.duration); // Group1:开始时间 Group2:持续时间
            line.words = words;
            lines.emplace_back(line);
        }

        return lines;
    }

    Line getCurrentLine(long time) {
        Line currentLine = Line();
        for (Line line: lines) {
            if (line.startTime <= time) {
                currentLine = line;
            }
        }
        return currentLine;
    }

    Word getCurrentWord(const Line &line, long time) {
        Word currentWord = Word();
        for (const Word &word: line.words) {
            if (word.startTime <= time) {
                currentWord = word;
            }
        }
        return currentWord;
    }
}