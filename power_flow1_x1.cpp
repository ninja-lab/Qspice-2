// Automatically generated C++ file on Mon Nov 17 13:01:00 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD power_flow1_x1.cpp kernel32.lib

#include <malloc.h>

extern "C" __declspec(dllexport) void (*Display)(const char *format, ...)       = 0; // works like printf()
extern "C" __declspec(dllexport) void (*EXIT)(const char *format, ...)          = 0; // print message like printf() but exit(0) afterward
extern "C" __declspec(dllexport) const double *DegreesC                         = 0; // pointer to current circuit temperature
extern "C" __declspec(dllexport) const int *StepNumber                          = 0; // pointer to current step number
extern "C" __declspec(dllexport) const int *NumberSteps                         = 0; // pointer to estimated number of steps
extern "C" __declspec(dllexport) const char* const *InstanceName                = 0; // pointer to address of instance name
extern "C" __declspec(dllexport) const char *QUX                                = 0; // path to QUX.exe
extern "C" __declspec(dllexport) const bool *ForKeeps                           = 0; // pointer to whether being evaluated non-hypothetically
extern "C" __declspec(dllexport) const bool *HoldICs                            = 0; // pointer to whether instance initial conditions are being held
extern "C" __declspec(dllexport) const void *GUI_HWND                           = 0; // pointer to Window handle of QUX.exe
extern "C" __declspec(dllexport) const double *CKTtime                          = 0;
extern "C" __declspec(dllexport) const double *CKTdelta                         = 0;
extern "C" __declspec(dllexport) const int *IntegrationOrder                    = 0;
extern "C" __declspec(dllexport) const char *InstallDirectory                   = 0;
extern "C" __declspec(dllexport) double (*EngAtof)(const char **string)         = 0;
extern "C" __declspec(dllexport) const char *(*BinaryFormat)(unsigned int data)                          = 0; // BinaryFormat(0x1C) returns "0b00011100"
extern "C" __declspec(dllexport) const char *(*EngFormat   )(double x, const char *units, int numDgts)   = 0; // EngFormat(1e-6, "s", 6) returns "1µs"
extern "C" __declspec(dllexport) int (*DFFT)(struct sComplex *u, bool inv, unsigned int N, double scale) = 0; // Discrete Fast Fourier Transform
extern "C" __declspec(dllexport) void (*bzero)(void *ptr, unsigned int count)   = 0;

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
#undef Va
#undef Vb
#undef Vc
#undef Vdc_p
#undef Vdc_n
#undef Pcomm
#undef mode
#undef Qcomm

struct sPOWER_FLOW1_X1
{
  // declare the structure here
};

extern "C" __declspec(dllexport) void power_flow1_x1(struct sPOWER_FLOW1_X1 **opaque, double t, union uData *data)
{
   double  Va    = data[0].d; // input
   double  Vb    = data[1].d; // input
   double  Vc    = data[2].d; // input
   double  Pcomm = data[3].d; // input
   int     mode  = data[4].i; // input
   double  Qcomm = data[5].d; // input
   double &Vdc_p = data[6].d; // output
   double &Vdc_n = data[7].d; // output

   if(!*opaque)
   {
      *opaque = (struct sPOWER_FLOW1_X1 *) malloc(sizeof(struct sPOWER_FLOW1_X1));
      bzero(*opaque, sizeof(struct sPOWER_FLOW1_X1));
   }
   struct sPOWER_FLOW1_X1 *inst = *opaque;

// Implement module evaluation code here:

}

extern "C" __declspec(dllexport) void Destroy(struct sPOWER_FLOW1_X1 *inst)
{
   free(inst);
}
