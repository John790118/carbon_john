
#ifndef _PKT_SCH_H_
#define _PKT_SCH_H_

#include "systemc.h"
#include "pkt.h"

struct pkt_sch : sc_module 
{
    sc_in_clk   clock1;
    sc_in<pkt>  in0;
    sc_in<pkt>  in1;
    sc_out<pkt>  out0;

    SC_CTOR(pkt_sch) 
     {
      SC_THREAD(pkt_sch_prc);
      sensitive << in0;
      sensitive << in1;
      sensitive << clock1.pos();
    }  

  void pkt_sch_prc();  
 
};
#endif // _PKT_SCH_H_
