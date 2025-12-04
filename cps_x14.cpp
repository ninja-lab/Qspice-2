// Automatically generated C++ file on Thu Dec  4 13:01:06 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD cps_x14.cpp kernel32.lib


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
#undef in
#undef out

extern "C" __declspec(dllexport) void cps_x14(void **opaque, double t, union uData *data)
{
   long long int in  = data[0].i64; // input
   bool         &out = data[1].b  ; // output

// Implement module evaluation code here:

}
