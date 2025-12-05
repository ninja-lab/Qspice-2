// Automatically generated C++ file on Thu Dec  4 12:46:21 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD inv_clark.cpp kernel32.lib

#include <malloc.h>
#include <math.h>
extern "C" __declspec(dllexport) void (*bzero)(void *ptr, unsigned int count)   = 0;
// forward-declare the helper so you can call it
inline void inverse_clarke(double alpha, double beta, double zero,
                           double &a, double &b, double &c);
union uData
{
   bool b;
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i;
   unsigned int ui;
   float f;
   double d;
   long long int i64;
   unsigned long long int ui64;
   char *str;
   unsigned char *bytes;
};

// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef alpha
#undef beta
#undef zero
#undef a
#undef b
#undef c



extern "C" __declspec(dllexport) void inv_clark(void **opaque, double t, union uData *data)
{
   double  alpha = data[0].d; // input
   double  beta  = data[1].d; // input
   double  zero  = data[2].d; // input
   double &a     = data[3].d; // output
   double &b     = data[4].d; // output
   double &c     = data[5].d; // output



// Implement module evaluation code here:
   inverse_clarke(alpha, beta, zero, a, b, c);
}

// alpha-beta-0 -> abc
inline void inverse_clarke(double alpha, double beta, double zero,
                           double &a, double &b, double &c)
{
    // These are the exact inverse of the amplitude-invariant Clarke above
    a = alpha + zero;
    b = -0.5 * alpha + (sqrt(3.0) / 2.0) * beta + zero;
    c = -0.5 * alpha - (sqrt(3.0) / 2.0) * beta + zero;
}


