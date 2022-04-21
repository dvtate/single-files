#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Gives file name without extension
/// \note Caller frees
char* barename( const char* path ) {
    if (!path) return NULL;

    unsigned l = 0;
    bool f = false;

    char* p = (char*)path + strlen(path);
    for (;;) {
        p--;
        if (f) l++;
        if (*p == '.')
            f = true;
        if (*p == '\\' || *p == '/' || p == path) {
        	if (!f)
        		return NULL;

            char* ret = new char[l + 1];
            memset( ret, '\0', l + 1 );
            memcpy( ret, p + 1, l - 1 );
            return ret;
	    }
    }
    return NULL;
}


int main(int argc, char** argv) {
    if (argc < 2) return -1;
    puts(barename(argv[1]));
}
