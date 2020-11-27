#pragma once
#ifndef _FilePath_HPP_
#define _FilePath_HPP_

#include <string>

class FilePath
{
private:
    void format();

    std::string m_FilePath;

public:
#ifdef _WIN32
    static const char PATH_SEPARATOR = '\\';
#else
    static const char PATH_SEPARATOR = '/';
#endif

    FilePath() = default;
    FilePath(const char *filepath);
    FilePath(const std::string &filepath);

    inline operator std::string() const { return m_FilePath; }

    inline const std::string &str() const { return m_FilePath; }

    inline const char *c_str() const { return m_FilePath.c_str(); }

    inline bool empty() const { return m_FilePath.empty(); };

    /*! returns the path of a filepath */
    FilePath dirPath() const;

    /*! returns the file of a filepath  */
    std::string file() const;

    /*! returns the file extension */
    std::string ext() const;

    bool hasExt(const std::string &ext) const;

    /*! adds file extension */
    inline FilePath addExt(const std::string &ext = "") const { return FilePath(m_FilePath + ext); };

    /*! concatenates two filepaths to this/other */
    FilePath operator+(const FilePath &other) const;

    bool operator==(const FilePath &other) const;

    bool operator!=(const FilePath &other) const;

    /*! output operator */
    friend std::ostream &operator<<(std::ostream &cout, const FilePath &filepath)
    {
        return (cout << filepath.m_FilePath);
    }
};

#endif /* _FilePath_HPP_ */
