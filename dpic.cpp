// Automatically generated C++ file on Fri Apr 26 19:36:54 2024
//
// To build with Digital Mars C++ Compiler:
//
//    dmc -mn -WD dpic.cpp kernel32.lib

#include <cmath>

const double
Vref=0,            // compensator reference voltage
Tau_z= 2.24e-5,    // compensator zero time constant
Tau_i= 2.24e-5;    // compensator gain time constant


double
Vik=0,             // current input voltage sample
Vik_1=0,           // previous input voltage sample
Vok=0,            // current output voltage  sample
Vok_1=0,          // previous output voltage measured sample
Errk= Vref,       // current error sample
Errk_1=0;         // previous error sample



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
#undef in0
#undef in1
#undef in2
#undef in3
#undef out0
#undef out1
#undef out2
#undef out3

extern "C" __declspec(dllexport) void dpic(void **opaque, double t, union uData *data)
{
   double  in0  = data[0].d; // input
   double  in1  = data[1].d; // input
   double  in2  = data[2].d; // input
   double  in3  = data[3].d; // input
   double  Tsp  = data[4].d; // input parameter
   double &out0 = data[5].d; // output
   double &out1 = data[6].d; // output
   double &out2 = data[7].d; // output
   double &out3 = data[8].d; // output

// Implement module evaluation code here:


// digital compensator loop

      // CLOCK = in3
      if ((in3>0.999)&&(in3<=1.001))  {
                                       Vik_1=  Vik;        // save previous input voltage sample
                                       Vok_1=  Vok;        // save previous output Voltage sample
                                       Errk_1= Errk;       // save previous Error sample

                                       Vik=  in0;          // load current input voltage sample
                                       Errk= Vref-Vik;     // calculate current error sample

                                       // calculate current output voltage

                                       Vok= Vok_1 + (Tau_z+0.5*Tsp)*Errk/Tau_i - (Tau_z-0.5*Tsp)*Errk_1/Tau_i ;

                                       // if (Dk>8) {Dk=8;} // Limiter
                                       // if (Dk<1) {Dk=1;} // Dmax=0.8, Dmin=0.1
                                      }

   out0=Vok;


}
