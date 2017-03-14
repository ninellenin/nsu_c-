#include "comment_parser.h"

void CommentParser::delete_comments(istream &input, ostream &output)
{
    char current;
    InputBuffer input_buffer(input, 1024);
    OutputBuffer output_buffer(output, 1024);

    while (current = input_buffer.get()) {
        if ('/' == current) {
            skip_new_line(input_buffer);

            char next = input_buffer.peek();
            if (next == '*') {
                input_buffer.get();
                skip_multiline_comment(input_buffer);
                continue;
            } else if (next == '/') {
                input_buffer.get();
                skip_line_comment(input_buffer);
                continue;
            }
        } else {
            output_buffer.put(current);
        }
        if ('\"' == current) {
            parse_string(input_buffer, output_buffer);
        }
    }
}

 void CommentParser::skip_new_line(InputBuffer &input)
 {
    while (input.peek() == '\\') {
     //get '\'
     input.get();
     //get '\n'
     input.get();
    }
}

void CommentParser::skip_line_comment(InputBuffer &input)
{
    char current;
    char next;

    do {
        next = input.peek();
        if (next == '\n') {
            return;
        }
        if (next == '\\') {
            skip_new_line(input);
        }
    } while (input.get(current));
}

void CommentParser::skip_multiline_comment(InputBuffer &input)
{
    char current;

    while(input.get(current)) {
        if (current == '*') {
            skip_new_line(input);
            if (input.peek() == '/') {
                input.get();

                return;
            }
        }
    }
}

void CommentParser::parse_string(InputBuffer &input, OutputBuffer &output)
{
    char current;

    while (input.get(current)) {
        output.put(current);
        if (current == '\"') {
            return;
        }
    }
}
