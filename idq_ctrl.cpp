// Automatically generated C++ file on Thu Dec  4 07:52:30 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD idq_ctrl.cpp kernel32.lib

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
#undef Id
#undef Iq
#undef Id_ref
#undef Iq_ref
#undef Vd_cmd
#undef Vq_cmd
#undef Vbusp
#undef Vbusn

struct sIDQ_CTRL
{
  // declare the structure here
    double int_d;
    double int_q;
    double Kp_d, Ki_d;
    double Kp_q, Ki_q;
    bool   init;
};

extern "C" __declspec(dllexport) void idq_ctrl(struct sIDQ_CTRL **opaque, double t, union uData *data)
{
   double  Id     = data[0].d; // input
   double  Iq     = data[1].d; // input
   double  Id_ref = data[2].d; // input
   double  Iq_ref = data[3].d; // input
   double  Vbusp  = data[4].d; // input
   double  Vbusn  = data[5].d; // input
   double &Vd_cmd = data[6].d; // output
   double &Vq_cmd = data[7].d; // output

   if(!*opaque)
   {
      *opaque = (struct sIDQ_CTRL *) malloc(sizeof(struct sIDQ_CTRL));
      bzero(*opaque, sizeof(struct sIDQ_CTRL));
   }
   struct sIDQ_CTRL *inst = *opaque;

// Implement module evaluation code here:
    if (!inst->init) {
        inst->Kp_d = 0.1;   // TODO: tune
        inst->Ki_d = 50.0;  // TODO: tune
        inst->Kp_q = 0.1;
        inst->Ki_q = 50.0;
        inst->int_d = 0.0;
        inst->int_q = 0.0;
        inst->init  = true;
    }
        double dt = 0.0;
    if (CKTdelta && *CKTdelta > 0.0)
        dt = *CKTdelta;

    // Current errors
    double e_d = Id_ref - Id;
    double e_q = Iq_ref - Iq;

    // Integrate
    inst->int_d += inst->Ki_d * e_d * dt;
    inst->int_q += inst->Ki_q * e_q * dt;

    // PI outputs
    Vd_cmd = inst->Kp_d * e_d + inst->int_d;
    Vq_cmd = inst->Kp_q * e_q + inst->int_q;

    // Vdc-based saturation
    double Vmax = 0.5 * (Vbusp - Vbusn);   // simple first pass
    double mag  = sqrt(Vd_cmd*Vd_cmd + Vq_cmd*Vq_cmd);

    if (mag > Vmax && mag > 0.0) {
        double scale = Vmax / mag;
        Vd_cmd *= scale;
        Vq_cmd *= scale;
        // optional anti-windup tweak here
    }

}

extern "C" __declspec(dllexport) void Destroy(struct sIDQ_CTRL *inst)
{
   free(inst);
}
