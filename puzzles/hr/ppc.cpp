
#define foreach(ARR, VAR) for (int VAR = 0; VAR < ARR.size(); VAR++)
#define FUNCTION(NAME, OP) \
void NAME(int& a, int b) {\
    a = a OP b ? a : b;\
}

#define INF 10000000
#define toStr(inside) #inside

#define io \
int a;\
std::cin >> a;\
v[i] = a;
