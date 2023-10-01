//
// Created by awalol on 2023/9/30.
//

#ifndef LYRICPARSER_LYRICPARSER_H
#define LYRICPARSER_LYRICPARSER_H

#include <vector>
#include "string"
#include "Line.h"

using namespace std;

namespace LyricParser {
    vector<Line> parser(string lyric);

    Line getCurrentLine(long time);

    Word getCurrentWord(const Line &line, long time);
}

#endif
