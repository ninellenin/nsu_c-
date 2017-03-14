#ifndef BUFFER_H
#define BUFFER_H

#include <istream>
#include <ostream>

class Buffer {
protected:
    int capacity_;
    char *buf_;
    int current_;
public:
    Buffer(int capacity);
    ~Buffer();
};

class InputBuffer : public Buffer {
private:
    std::istream &input_;
    int size_;
public:
    InputBuffer(std::istream &input, int capacity);
    char get();
    bool get(char &c);
    char peek();
};

class OutputBuffer : public Buffer {
private:
    std::ostream &output_;
public:
    OutputBuffer(std::ostream &output, int capacity);
    ~OutputBuffer();
    void put(char c);
    void flush();
};

#endif // BUFFER_H
