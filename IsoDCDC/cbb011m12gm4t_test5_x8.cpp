// Automatically generated C++ file on Fri Nov 21 13:50:35 2025
//
// To build with Digital Mars C++ Compiler: 
//
//    dmc -mn -WD cbb011m12gm4t_test5_x8.cpp kernel32.lib

#include <malloc.h>

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

struct sCBB011M12GM4T_TEST5_X8
{
  // declare the structure here
};

extern "C" __declspec(dllexport) void cbb011m12gm4t_test5_x8(struct sCBB011M12GM4T_TEST5_X8 **opaque, double t, union uData *data)
{

   if(!*opaque)
   {
      *opaque = (struct sCBB011M12GM4T_TEST5_X8 *) malloc(sizeof(struct sCBB011M12GM4T_TEST5_X8));
      bzero(*opaque, sizeof(struct sCBB011M12GM4T_TEST5_X8));
   }
   struct sCBB011M12GM4T_TEST5_X8 *inst = *opaque;

// Implement module evaluation code here:

}

extern "C" __declspec(dllexport) void Destroy(struct sCBB011M12GM4T_TEST5_X8 *inst)
{
   free(inst);
}
