#include "buffer.h"

Buffer::Buffer(int capacity):
    capacity_(capacity),
    current_(0)
{
    buf_ = new char[capacity_];
}

Buffer::~Buffer()
{
    delete []buf_;
}

InputBuffer::InputBuffer(std::istream &input, int capacity):
    Buffer(capacity),
    input_(input),
    size_(0)
{
}

char InputBuffer::get()
{
    if (current_ >= size_) {
        input_.read(buf_, capacity_);
        current_ = 0;
        size_ = input_.gcount();
    }
    if (size_) {
        return buf_[current_++];
    } else {
        return 0;
    }
}


bool InputBuffer::get(char &c)
{
    c = get();

    if (c) {
        return true;
    }

    return false;
}

char InputBuffer::peek()
{
    if (current_ < size_){
        return buf_[current_];
    }
    return input_.peek();
}

OutputBuffer::OutputBuffer(std::ostream &output, int capacity):
    Buffer(capacity),
    output_(output)
{
}

void OutputBuffer::put(char c)
{
    if (current_ < capacity_) {
        buf_[current_++] = c;
    } else {
        output_.write(buf_, capacity_);
        current_ = 0;
    }
}

void OutputBuffer::flush()
{
    output_.write(buf_, current_);
    current_ = 0;
}

OutputBuffer::~OutputBuffer()
{
    flush();
}
