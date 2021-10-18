
#ifndef _PKT_SWITCH_H_
#define _PKT_SWITCH_H_

#include "systemc.h"
#include "pkt.h"
#include "pkt_sch.h"

struct pkt_switch : sc_module 
{
    sc_in_clk   clock1;
    sc_in<pkt>  in0;
    sc_in<pkt>  in1;
    sc_out<pkt>  out0;

    pkt_sch *pkt_sch_ins;

    SC_CTOR(pkt_switch) 
    {
      pkt_sch_ins = new pkt_sch("PKT_SCH");
      pkt_sch_ins->clock1(clock1);
      pkt_sch_ins->in0(in0);
      pkt_sch_ins->in1(in1);
      pkt_sch_ins->out0(out0);
    }  
    ~pkt_switch()
    {
      delete pkt_sch_ins;
    }

  void pkt_switch_prc();  
 
};
#endif // _PKT_SWITCH_H_
