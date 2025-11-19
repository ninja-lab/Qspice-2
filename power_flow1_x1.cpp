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

struct CPS_PLL {
    double theta;     // angle estimate [rad]
    double omega;     // freq estimate [rad/s]
    double xi;        // PI integrator state
    double last_t;    // last time stamp
};
struct sPOWER_FLOW1_X1
{
  CPS_PLL pll;      // per-instance PLL state

};

//user function forward declarations
void pll_step(CPS_PLL, double, double, double, double);

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
              // initialize PLL to something sane
      (*opaque)->pll.theta  = 0.0;
      (*opaque)->pll.omega  = 2.0 * M_PI * 60.0;
      (*opaque)->pll.xi     = 0.0;
      (*opaque)->pll.last_t = t;
   }
   struct sPOWER_FLOW1_X1 *inst = *opaque;

// Implement module evaluation code here:


    // --- PLL in PQ mode ---
    if (mode == 1) { // say 1 = PQ
        pll_step(inst->pll, Va, Vb, Vc, t);
    }
    else if (mode == 2) {
        // UF mode: generate theta from freq command instead of PLL
        double Ts = t - inst->pll.last_t;
        if (Ts <= 0.0) Ts = 1e-6;
        inst->pll.last_t = t;
        inst->pll.omega  = 2.0 * M_PI * 60.0; // or from some f_cmd
        inst->pll.theta += inst->pll.omega * Ts;
        // wrap theta, etc.
    }

}


static void pll_step(CPS_PLL &pll, double Va, double Vb, double Vc, double t_now)
{
    double Ts = t_now - pll.last_t;
    if (Ts <= 0.0) Ts = 1e-6;
    pll.last_t = t_now;

    // Clarke
    double Valpha = (2.0/3.0) * ( Va - 0.5*Vb - 0.5*Vc );
    double Vbeta  = (2.0/3.0) * ( (sqrt(3.0)/2.0)*(Vb - Vc) );

    // Park
    double c = cos(pll.theta);
    double s = sin(pll.theta);
    double Vd =  Valpha * c + Vbeta * s;
    double Vq = -Valpha * s + Vbeta * c;

    // PI on Vq
    const double Kp = 100.0;
    const double Ki = 2000.0;
    double e = Vq;
    pll.xi   += Ki * e * Ts;
    pll.omega = 2.0 * M_PI * 60.0 + Kp*e + pll.xi;

    // integrate theta
    pll.theta += pll.omega * Ts;
    const double TWO_PI = 2.0 * M_PI;
    if (pll.theta >= TWO_PI) pll.theta -= TWO_PI;
    if (pll.theta <  0.0)    pll.theta += TWO_PI;
}


extern "C" __declspec(dllexport) void Destroy(struct sPOWER_FLOW1_X1 *inst)
{
   free(inst);
}
