#ifndef _sine_h
#define _sine_h

const int8_t sin_8_table[256] PROGMEM = {
    0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48,
    51, 54, 57, 59, 62, 65, 67, 70, 73, 75, 78, 80, 82, 85, 87, 89,
    91, 94, 96, 98, 100, 102, 103, 105, 107, 108, 110, 112, 113, 114, 116, 117,
    118, 119, 120, 121, 122, 123, 123, 124, 125, 125, 126, 126, 126, 126, 126, 127,
    126, 126, 126, 126, 126, 125, 125, 124, 123, 123, 122, 121, 120, 119, 118, 117,
    116, 114, 113, 112, 110, 108, 107, 105, 103, 102, 100, 98, 96, 94, 91, 89,
    87, 85, 82, 80, 78, 75, 73, 70, 67, 65, 62, 59, 57, 54, 51, 48,
    45, 42, 39, 36, 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0,
    -3, -6, -9, -12, -15, -18, -21, -24, -27, -30, -33, -36, -39, -42, -45, -48,
    -51, -54, -57, -59, -62, -65, -67, -70, -73, -75, -78, -80, -82, -85, -87, -89,
    -91, -94, -96, -98, -100, -102, -103, -105, -107, -108, -110, -112, -113, -114, -116, -117,
    -118, -119, -120, -121, -122, -123, -123, -124, -125, -125, -126, -126, -126, -126, -126, -127,
    -126, -126, -126, -126, -126, -125, -125, -124, -123, -123, -122, -121, -120, -119, -118, -117,
    -116, -114, -113, -112, -110, -108, -107, -105, -103, -102, -100, -98, -96, -94, -91, -89,
    -87, -85, -82, -80, -78, -75, -73, -70, -67, -65, -62, -59, -57, -54, -51, -48,
    -45, -42, -39, -36, -33, -30, -27, -24, -21, -18, -15, -12, -9, -6, -3};

const int8_t tri_8_table[256] PROGMEM = {
    -127, -125, -123, -121, -119, -117, -115, -113, -111, -109, -107, -105, -103, -101, -99, -97, -95,
    -93, -91, -89, -87, -85, -83, -81, -79, -77, -75, -73, -71, -69, -67, -65, -63,
    -61, -59, -57, -55, -53, -51, -49, -47, -45, -43, -41, -39, -37, -35, -33, -31,
    -29, -27, -25, -23, -21, -19, -17, -15, -13, -11, -9, -7, -5, -3, -1, 1,
    3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33,
    35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65,
    67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97,
    99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 125,
    123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101, 99, 97, 95, 93,
    91, 89, 87, 85, 83, 81, 79, 77, 75, 73, 71, 69, 67, 65, 63, 61,
    59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31, 29,
    27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1, -1, -3,
    -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29, -31, -33, -35,
    -37, -39, -41, -43, -45, -47, -49, -51, -53, -55, -57, -59, -61, -63, -65, -67,
    -69, -71, -73, -75, -77, -79, -81, -83, -85, -87, -89, -91, -93, -95, -97, -99,
    -101, -103, -105, -107, -109, -111, -113, -115, -117, -119, -121, -123, -125, -127
};

inline int8_t sine(uint8_t i)
{
    return pgm_read_byte(&sin_8_table[i]);
}

inline int8_t saw(uint8_t i)
{
    return i - 127;
}

inline int8_t square(uint8_t i)
{
    return i < 127 ? -127 : 127;
}

inline int8_t triangle(uint8_t i)
{
    return pgm_read_byte(&tri_8_table[i]);
}

#endif