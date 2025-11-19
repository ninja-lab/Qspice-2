// Automatically generated C++ file on Tue Nov 18 16:18:52 2025
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD pll_test.cpp kernel32.lib

#include <malloc.h>
#include <math.h>

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

struct CPS_PLL {
    double theta;     // angle estimate [rad]
    double omega;     // freq estimate [rad/s]
    double xi;        // PI integrator state
    double last_t;    // last time stamp
};


// int DllMain() must exist and return 1 for a process to load the .DLL
// See https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain for more information.
int __stdcall DllMain(void *module, unsigned int reason, void *reserved) { return 1; }

// #undef pin names lest they collide with names in any header file(s) you might include.
#undef Va
#undef Vb
#undef Vc
#undef freq
#undef w

struct sPLL_TEST
{
  // declare the structure here
  CPS_PLL pll;      // per-instance PLL state
};

//user function forward declarations
// forward declaration (if you want one)
static void pll_step(CPS_PLL &pll,
                     double Va, double Vb, double Vc, double t_now);

extern "C" __declspec(dllexport) void pll_test(struct sPLL_TEST **opaque, double t, union uData *data)
{
   double  Va    = data[0].d; // input
   double  Vb    = data[1].d; // input
   double  Vc    = data[2].d; // input
   double &theta = data[3].d; // output
   double &freq  = data[4].d; // output

   if(!*opaque)
   {
      *opaque = (struct sPLL_TEST *) malloc(sizeof(struct sPLL_TEST));
      bzero(*opaque, sizeof(struct sPLL_TEST));
      (*opaque)->pll.theta  = 0.0;
      (*opaque)->pll.omega  = 0.0;//2.0 * M_PI * 60.0;
      (*opaque)->pll.last_t = t;
    }
    sPLL_TEST *inst = *opaque;

    pll_step(inst->pll, Va, Vb, Vc, t);

    theta = inst->pll.theta;
    freq  = inst->pll.omega / (2.0 * M_PI);  // Hz




}
static void pll_step(CPS_PLL &pll, double Va, double Vb, double Vc, double t_now)
{
    const double OMEGA_NOM = 2.0 * M_PI * 60.0; // 60 Hz nominal
    const double TWO_PI = 2.0 * M_PI;
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


    // 4) Normalized error: e ˜ angle error when locked
    double Vmag = sqrt(Vd*Vd + Vq*Vq) + 1e-6; // avoid div0
    double e = -Vq / Vmag; // minus sign so positive rotation ? positive freq

    // 5) PI controller in continuous-time form
   // Choose natural frequency and damping, then Kp, Ki:
   // char poly: s^2 + Kp s + Ki = 0 ? ?_n^2 = Ki, 2 ? ?_n = Kp
   const double OMEGA_N = 2.0 * M_PI * 20.0; // ~20 Hz natural freq
   const double ZETA = 0.707; // damping

   const double Ki = OMEGA_N * OMEGA_N;
   const double Kp = 2.0 * ZETA * OMEGA_N;

   pll.xi += Ki * e * Ts; // integral of error (?? integral term)
   double delta_omega = Kp * e + pll.xi;
   pll.omega = OMEGA_NOM + delta_omega;
   // Optional clamp to keep things sane while tuning
   double omega_min = 2.0 * M_PI * 45.0;
   double omega_max = 2.0 * M_PI * 75.0;
   if (pll.omega < omega_min) pll.omega = omega_min;
   if (pll.omega > omega_max) pll.omega = omega_max;
    // integrate theta
    pll.theta += pll.omega * Ts;

    if (pll.theta >= TWO_PI) pll.theta -= TWO_PI;
    if (pll.theta <  0.0)    pll.theta += TWO_PI;
}
extern "C" __declspec(dllexport) void Destroy(struct sPLL_TEST *inst)
{
   free(inst);
}
