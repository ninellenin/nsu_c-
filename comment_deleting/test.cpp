#include <iostream>

#include "comment_parser.h"

using std::cin;
using std::cout;

int main()
{
    CommentParser parser;

    parser.delete_comments(cin, cout);
    return 0;
}

