// Automatically generated C++ file on Thu Dec  4 14:04:36 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD inv_park_.cpp kernel32.lib

#include <math.h>
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
#undef d
#undef q
#undef o
#undef alpha
#undef beta
#undef zero
#undef theta

extern "C" __declspec(dllexport) void inv_park_(void **opaque, double t, union uData *data)
{
   double  d     = data[0].d; // input
   double  q     = data[1].d; // input
   double  o     = data[2].d; // input
   double  theta = data[3].d; // input
   double &alpha = data[4].d; // output
   double &beta  = data[5].d; // output
   double &zero  = data[6].d; // output

// Implement module evaluation code here:

}

inline void inverse_park(double d, double q, double V0,
                         double theta,
                         double &alpha, double &beta, double &zero)
{
    const double c = cos(theta);
    const double s = sin(theta);

    // inverse Park is the transpose of the forward Park matrix
    alpha =  d * c - q * s;
    beta  =  d * s + q * c;
    zero =  V0;       // zero-sequence passes straight through
}
