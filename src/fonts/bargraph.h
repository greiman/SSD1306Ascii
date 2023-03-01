// Added by jonathanmlang

#ifndef BARGRAPH_H
#define BARGRAPH_H

GLCDFONTDECL(bargraph) = {
    0x0, 0x1, // size of one indicates fixed font width and no pixel padding
    0x01, // width
    0x08, // height
    0x61, // first char  a
    0x05, // char count 7

0xFE,  // a | //large bar line
0x7C,  // b l //smaller bar line
0x00,  // c   // gap
0x82,  // d : // empty bar
0x44,  // e thin : //narrow empty bar

};

#endif
