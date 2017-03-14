#ifndef COMMENT_PARSER_H
#define COMMENT_PARSER_H
#include <iostream>
#include <stack>

#include "buffer.h"

using std::istream;
using std::ostream;
using std::stack;

class CommentParser
{
private:
    void skip_new_line(InputBuffer &input);
    void skip_line_comment(InputBuffer &input);
    void skip_multiline_comment(InputBuffer &input);
    void parse_string(InputBuffer &buffer, OutputBuffer &output);

public:
    void delete_comments(istream &input, ostream &output);

};

#endif // COMMENT_PARSER_H
