#pragma once
#include <ostream>

class String {
protected:
    class StrSharedPtr final
    {
    private:
        static char null_ter_str[2];
        char* string;
        size_t length;
        size_t capacity;
        size_t* refCount;
        void clean();
    public:
        StrSharedPtr() : StrSharedPtr("", 0, 0) {}

        StrSharedPtr(const char* str, size_t length_, size_t capacity_);

        StrSharedPtr(const StrSharedPtr& right_obj);

        StrSharedPtr& operator=(const StrSharedPtr& right_obj);

        size_t getLength() const;
        size_t getCapacity() const;
        size_t getCount() const;
        char* getString();
        const char* getString() const;

        void setLength(size_t len);

        ~StrSharedPtr();
    };

    String& insert_(const char* str, size_t pos, size_t length);
    size_t find_(const char* str, size_t pos, size_t length) const;

	StrSharedPtr str_shared_ptr;
public:
    String() = default;
    String(const char* str);
    String(const char* str, size_t n);
    String(size_t n, char c);
    String(const String& str) = default;
    String(const String& str, size_t pos, size_t len = npos);
    virtual ~String() = default;

    size_t size() const;
    size_t capacity() const;
    void reserve(size_t n = 0);
    void clear();
    bool empty() const;

    char& at(size_t pos);
    const char& at(size_t pos) const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    char& back();
    const char& back() const;

    char& front();
    const char& front() const;

    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String& operator+=(char c);

    String& operator=(const String& str) = default;
    String& operator=(const char* str);

    String& insert(size_t pos, const String& str);
    String& insert(size_t pos, const char* str);
    String& insert(size_t pos, size_t n, char c);

    String& erase(size_t pos = 0, size_t len = npos);

    String& replace(size_t pos, size_t len, const String& str);
    String& replace(size_t pos, size_t len, const char* str);
    String& replace(size_t pos, size_t len, size_t n, char c);

    void swap(String& str);
    const char* data() const;

    size_t find(const String& str, size_t pos = 0) const;
    size_t find(const char* str, size_t pos = 0) const;
    size_t find(char c, size_t pos = 0) const;

    String substr(size_t pos = 0, size_t len = npos) const;

    int compare(const String& str) const;
    int compare(const char* str) const;

    static const size_t npos = -1;

    size_t countRef() const;

    friend std::ostream& operator<<(std::ostream& out, const String& str);
};
