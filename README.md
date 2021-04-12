# geocomb-c

c wrappers for using geocomb-cpp from c

## how to take care of duplicate struct & class names between c & c++?
- well, this time I prefixed all c++ duplicate class names of c struct names with CPP_ with search & replace, ended up having to do some manually.
- Need to find a better way to do this, maybe wrap with namespace, but this was a not-so-quick and easy fix, and it works...for now
