#define _CRT_SECURE_NO_WARNINGS
#include"String.h"
#include<iostream>
#include<string>

using namespace std;

char String::StrSharedPtr::null_ter_str[] = "\0";

String::StrSharedPtr::StrSharedPtr(const char* str, size_t length_, size_t capacity_)
{
    if(length_ > capacity_)
    {
        throw invalid_argument("Length is invalid");
    }

    capacity = capacity_;
    refCount = new size_t(1);

    if (capacity_ == 0)
    {
        string = null_ter_str;
        length = 0;
    }
    else
    {
        string = new char[capacity + 1];
        memcpy(string, str, length_);
        setLength(length_);
    }
}

String::StrSharedPtr& String::StrSharedPtr::operator=(const String::StrSharedPtr& right_obj)
{
    if(this == &right_obj)
    {
        return *this;
    }
    clean();
    string = right_obj.string;
    refCount = right_obj.refCount;
    capacity = right_obj.capacity;
    length = right_obj.length;
    (*refCount)++;
    return *this;
}

String::StrSharedPtr::StrSharedPtr(const StrSharedPtr& right_obj)
{
    this->string = right_obj.string;
    this->refCount = right_obj.refCount;
    capacity = right_obj.capacity;
    length = right_obj.length;
    (*refCount)++;
}

size_t String::StrSharedPtr::getCapacity() const
{
    return capacity;
}

size_t String::StrSharedPtr::getLength() const
{
    return length;
}

size_t String::StrSharedPtr::getCount() const
{
    return *refCount;
}

char* String::StrSharedPtr::getString()
{
    return string;
}

const char* String::StrSharedPtr::getString() const
{
    return string;
}

void String::StrSharedPtr::setLength(size_t len)
{
    length = len;
    string[len] = '\0';
}

void String::StrSharedPtr::clean()
{
    if (*refCount == 1)
    {
        if (string != null_ter_str)
        {
            delete[] string;
        }
        delete refCount;
    }
    else
    {
        (*refCount)--;
    }
}

String::StrSharedPtr::~StrSharedPtr()
{
    clean();
}

String::String(const char* str)
{
    if(str == nullptr)
    {
        *this = String();
        return;
    }

    str_shared_ptr = StrSharedPtr(str, strlen(str), strlen(str));
}

String::String(const char* str, size_t n)
{
    if (str == nullptr || n == 0)
    {
        *this = String();
        return;
    }

    n = min(n, strlen(str));

    str_shared_ptr = StrSharedPtr(str, n, n);
}

String::String(size_t n, char c)
{
    if(n == 0)
    {
        *this = String();
        return;
    }

    str_shared_ptr = StrSharedPtr("", n, n);

    memset(str_shared_ptr.getString(), c, n);

    str_shared_ptr.getString()[n] = '\0';
}

String::String(const String& str, size_t pos, size_t len)
{
	if(pos > str.size())
    {
        throw out_of_range("Pos out of range");
    }

    len = min(str.size() - pos, len);

    str_shared_ptr = StrSharedPtr(str.data() + pos, len, len);
}

size_t String::size() const
{
    return str_shared_ptr.getLength();
}

size_t String::capacity() const
{
    return str_shared_ptr.getCapacity();
}

void String::reserve(size_t n)
{
    if (n <= str_shared_ptr.getCapacity())
    {
        return;
    }

    str_shared_ptr = StrSharedPtr(str_shared_ptr.getString(), str_shared_ptr.getLength(), n);
}

void String::clear()
{
    if(size() == 0)
    {
        return;
    }
    if(countRef() == 1)
    {
        str_shared_ptr.setLength(0);
        return;
    }
    str_shared_ptr = StrSharedPtr("", 0, 0);
}

bool String::empty() const
{
    return str_shared_ptr.getLength() == 0;
}

char& String::at(size_t pos)
{
    if (pos >= str_shared_ptr.getLength())
    {
        throw out_of_range("Out of range");
    }
	return (*this)[pos];
}

const char& String::at(size_t pos) const
{
    if (pos > str_shared_ptr.getLength())
    {
        throw out_of_range("Out of range");
    }

    return (*this)[pos];
}

char& String::operator[](size_t pos)
{
    if (countRef() > 1)
    {
        str_shared_ptr = StrSharedPtr(str_shared_ptr.getString(), str_shared_ptr.getLength(), str_shared_ptr.getCapacity());
    }

    return str_shared_ptr.getString()[pos];
}

const char& String::operator[](size_t pos) const
{
    return str_shared_ptr.getString()[pos];
}

char& String::back()
{
    if(empty())
    {
        throw out_of_range("Zero length");
    }

    return (*this)[size() - 1];
}

const char& String::back() const
{
    if (empty())
    {
        throw out_of_range("Zero length");
    }

    return (*this)[size() - 1];
}

char& String::front()
{
    if (empty())
    {
        throw out_of_range("Zero length");
    }

    return (*this)[0];
}

const char& String::front() const
{
    if (empty())
    {
        throw out_of_range("Zero length");
    }

	return (*this)[0];
}

String& String::operator+=(const String& str)
{
    insert_(str.data(), size(), str.size());
    return *this;
}

String& String::operator+=(const char* str)
{
    if(str == nullptr)
    {
        return  *this;
    }
    insert_(str, size(), strlen(str));
    return *this;
}

String& String::operator+=(char c)
{
    char buffer[2]{c, '\0'};

    insert_(buffer,size(), 1);

    return *this;
}

String& String::operator=(const char* str)
{
    if (str == nullptr)
    {
        str_shared_ptr = StrSharedPtr();
        return *this;
    }

    str_shared_ptr = StrSharedPtr(str, strlen(str), strlen(str));
    return *this;
}

String& String::insert_(const char* str, size_t pos, size_t length)
{
    if (pos > str_shared_ptr.getLength())
    {
        throw out_of_range("Pos out of range");
    }

    if (str == nullptr || length == 0)
    {
        return *this;
    }

    size_t new_size = size() + length;

    StrSharedPtr temp = StrSharedPtr(str_shared_ptr.getString(), new_size, new_size);

    memcpy(temp.getString() + pos, str, length);

    if (pos != size())
    {
        memcpy(temp.getString() + pos + length, data() + pos, size() - pos);
    }
    temp.setLength(new_size);

    str_shared_ptr = temp;
    return *this;
}

String& String::insert(size_t pos, const String& str)
{
    insert_(str.data(), pos, str.size());

    return *this;
}

String& String::insert(size_t pos, const char* str)
{
    if(str == nullptr)
    {
        return  *this;
    }
    insert_(str, pos, strlen(str));

    return *this;
}

String& String::insert(size_t pos, size_t n, char c)
{
    if (pos > size())
    {
        throw out_of_range("Pos out of range");
    }

    if(n == 0)
    {
        return *this;
    }

    size_t new_size = size() + n;

    StrSharedPtr temp = StrSharedPtr(str_shared_ptr.getString(), new_size, new_size);

    memset(temp.getString() + pos, c, n);
    
    if (pos != size())
    {
        memcpy(temp.getString() + pos + n, data() + pos, size() - pos);
    }

    str_shared_ptr = temp;

    return *this;
}

String& String::erase(size_t pos, size_t len)
{
    if (pos > size())
    {
        throw out_of_range("Pos out of range");
    }

    len = min(size() - pos, len);

    if(len == 0)
    {
        return *this;
    }

    if(pos + len == size() && countRef() == 1)
    {
        str_shared_ptr.setLength(pos);
        return *this;
    }

    size_t size_ = size() - len;

    StrSharedPtr temp = StrSharedPtr("", size_, size_);

    memcpy(temp.getString(), data(), pos);
    memcpy(temp.getString() + pos, data() + len + pos, size_ - pos);
    temp.setLength(size_);
    str_shared_ptr = temp;

    return *this;
}

String& String::replace(size_t pos, size_t len, const String& str)
{
    if (pos > size())
    {
        throw out_of_range("Pos out of range");
    }

    if (len == 0)
    {
        return *this;
    }

    erase(pos, len);

    return insert_(str.data(), pos, str.size());
}

String& String::replace(size_t pos, size_t len, const char* str)
{
    if (pos > size())
    {
        throw out_of_range("Pos out of range");
    }

    if(str == nullptr || len == 0)
    {
        return *this;
    }

    erase(pos, len);

    return insert_(str, pos, strlen(str));
}

String& String::replace(size_t pos, size_t len, size_t n, char c)
{
    if (pos > size())
    {
        throw out_of_range("Pos out of range");
    }

    if (len == 0)
    {
        return *this;
    }

    erase(pos, len);

    insert(pos, n, c);

    return *this;
}

void String::swap(String& str)
{
    std::swap(str_shared_ptr, str.str_shared_ptr);
}

const char* String::data() const
{
    return str_shared_ptr.getString();
}

size_t String::find_(const char* str, size_t pos, size_t length) const
{
    if (pos >= str_shared_ptr.getLength() || str == nullptr)
    {
        return npos;
    }

    if (str_shared_ptr.getLength() == 0)
    {
        return npos;
    }

    for (auto i = pos; i < str_shared_ptr.getLength() - length + 1; i++)
    {
    	if(memcmp(str_shared_ptr.getString() + i, str, length) == 0)
    	{
    		return i;
    	}
    }
    return npos;
}

size_t String::find(const String& str, size_t pos) const
{
    return find_(str.data(), pos, str.size());
}

size_t String::find(const char* str, size_t pos) const
{
    if(str == nullptr)
    {
        return npos;
    }
    return find_(str, pos, strlen(str));
}

size_t String::find(char c, size_t pos) const
{
    if (pos >= str_shared_ptr.getLength())
    {
        return npos;
    }
    for (auto i = pos; i < str_shared_ptr.getLength(); i++)
    {
        if (str_shared_ptr.getString()[i] == c)
        {
            return i;
        }
    }
    return 0;
}

String String::substr(size_t pos, size_t len) const
{
    if (pos > size())
    {
        throw out_of_range("Pos out of range");
    }

    if (len == 0)
    {
        return String{};
    }

    return String(*this, pos, len);
}

int String::compare(const String& str) const
{
    int temp = memcmp(data(), str.data(), min(size(), str.size()));

    if(temp == 0 && size() != str.size())
    {
        return size() > str.size() ? 1 : -1;
    }

    return temp;
}

int String::compare(const char* str) const
{
    if(str == nullptr)
    {
        return 1;
    }

    int temp =  memcmp(data(), str, min(size(), strlen(str)));

    if (temp == 0 && size() != strlen(str))
    {
        return size() > strlen(str) ? 1 : - 1;
    }

    return temp;
}

size_t String::countRef() const
{
    return str_shared_ptr.getCount();
}

ostream& operator<<(ostream& os, const String& str)
{
    os << str.data();
	return os;
}