/**
  * filelines.h
  */

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class FileLines
{
public:
    FileLines();
    explicit FileLines(const std::string& path);

    /**
     * @brief refresh
     * @return
     */
    bool refresh();
    /**
     * @brief refresh
     * @param path
     * @return
     */
    bool refresh(const std::string& path);

    /**
     * @brief save
     * @return
     */
    bool save();
    /**
     * @brief save
     * @param path
     * @return
     */
    bool save(const std::string& path);


    int total() const;

    /**
     * @brief append add a new line to the end
     * @param line
     * @return
     */
    int append(const std::string& line);

    /**
     * @brief clear all lines
     */
    void clear();

    /**
     * @brief insertBefore insert a new line before the line at linenumber
     * @param linenumber the linenumber
     * @param text the text will be inserted
     * @return
     */
    bool insertBefore(int linenumber, const std::string& text);

    /**
     * @brief insertAfter
     * @param linenumber
     * @param text
     * @return
     */
    bool insertAfter(int linenumber, const std::string& text);

    /**
     * @brief remove remove a line at linenumber
     * @param linenumber
     * @return   text of the removed line
     */
    std::string remove(int linenumber);

    /**
     * @brief remove remove 'number' lines from 'start' line;
     * @param start
     * @param number
     * @return  the removed lines
     */
    FileLines remove(int start, int number);

    void assign(std::initializer_list<std::string> list);
    template<class Iterator>
    void assign(Iterator first, Iterator last) {
        _lines.assign(first, last);
    }

    std::string tostring() const;


    /**
     * @brief operator []
     * @param linenumer
     * @return
     */
    std::string& operator[](int linenumer);
    const std::string& operator [](int linenumber) const;


    /**save
     * for using like std::xxx
     */
    using iterator = std::vector<std::string>::iterator;
    iterator begin();
    iterator end();

    using const_iterator = std::vector<std::string>::const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    using reverse_iterator = std::vector<std::string>::reverse_iterator;
    reverse_iterator rbegin();
    reverse_iterator rend();

    using const_reverse_iterator = std::vector<std::string>::const_reverse_iterator;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

private:
    std::string _rpath; //read from file
    std::string _wpath; //write to file
    std::vector<std::string> _lines;
};
