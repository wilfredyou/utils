
/**
 * filelines.cpp
 * #include "filelines.h"
 */


FileLines::FileLines() {}
FileLines::FileLines(const std::string &path): _rpath(path) {
    refresh();
}

bool FileLines::refresh()
{
    std::string line;
    if(_rpath.empty()) return false;
    std::ifstream in(_rpath);

    if(in.is_open()) {
        _lines.clear();
        while(std::getline(in, line)) {
            _lines.emplace_back(line);
        }
        in.close();
        return true;
    }
    return false;
}

bool FileLines::refresh(const std::string &path)
{
    _rpath.assign(path);
    return refresh();
}

int FileLines::total() const
{
    return _lines.size();
}


std::string& FileLines::operator [](int linenumber)
{
    return _lines[linenumber];
}

const std::string& FileLines::operator [](int linenumber) const
{
    return _lines[linenumber];
}

int FileLines::append(const std::string &line)
{
    _lines.emplace_back(line);
    return total();
}

bool FileLines::save()
{
    if(_wpath.empty()) {
        if(_rpath.empty()) return false;
        _wpath = _rpath;
    }

    std::ofstream out(_wpath);
    if(out.is_open()) {
        for(auto& line: _lines) {
            out << line << std::endl;
        }

        out.close();
        return true;
    }
    return false;
}

bool FileLines::save(const std::string &path)
{
    _wpath.assign(path);
    return save();
}

void FileLines::clear()
{
    _lines.clear();
}

bool FileLines::insertBefore(int linenumber, const std::string &text)
{
    if(total() <= linenumber) return false;
    _lines.insert(begin() + linenumber, text);
    return true;
}

bool FileLines::insertAfter(int linenumber, const std::string &text)
{
    if(total() <= linenumber) return false;
    if(linenumber == total() - 1) return append(text);
    _lines.insert(begin() + linenumber + 1, text);
}


void  FileLines::assign(std::initializer_list<std::string> list)
{
    _lines.assign(list);
}

std::string FileLines::tostring() const
{
    std::ostringstream oss;
    int last = total() - 1;
    oss << "[";
    for(int i = 0; i < last; ++i) {
        oss << '"' << _lines.at(i) << '"' << ',';
    }
    oss << '"' << _lines.at(last) << '"' << ']';
    return oss.str();
}

std::string FileLines::remove(int linenumber)
{
    std::string rtn;
    if(linenumber < total()) {
        rtn = _lines.at(linenumber);
        _lines.erase(begin() + linenumber);
    }
    return rtn;
}

FileLines FileLines::remove(int start, int number)
{
    FileLines newlines;
    if(total() <= start + number) {
        number = total() - start;
    }
    newlines.assign(begin() + start, begin() + start + number);

    _lines.erase(begin() + start, begin() + start + number);

    return newlines;
}


FileLines::iterator FileLines::begin()
{
    return _lines.begin();
}

FileLines::iterator FileLines::end()
{
    return _lines.end();
}

FileLines::const_iterator FileLines::begin() const
{
    return _lines.begin();
}

FileLines::const_iterator FileLines::end() const
{
    return _lines.end();
}
FileLines::const_iterator FileLines::cbegin() const
{
    return _lines.cbegin();
}

FileLines::const_iterator FileLines::cend() const
{
    return _lines.cend();
}

FileLines::reverse_iterator FileLines::rbegin()
{
    return _lines.rbegin();
}

FileLines::reverse_iterator FileLines::rend()
{
    return _lines.rend();
}

FileLines::const_reverse_iterator FileLines::rbegin() const
{
    return _lines.rbegin();
}

FileLines::const_reverse_iterator FileLines::rend()const
{
    return _lines.rend();
}

FileLines::const_reverse_iterator FileLines::crbegin() const
{
    return _lines.crbegin();
}

FileLines::const_reverse_iterator FileLines::crend() const
{
    return _lines.crend();
}

