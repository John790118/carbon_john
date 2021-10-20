

#include "stdio.h"
#include <iostream>
#include "systemc.h"
//#include <memory>
#include "pkt_receiver.h"
#include "pkt_switch.h"
#include "pkt_sch.h"
#include "switch_clk.h"
#include "stim.h"
#include "comm_def.h"
using namespace std;


int sc_main(int argc, char *argv[])
{
   std::array<sc_signal<pkt_desc>, NO_PORTS >   pkt_in;
//   std::array<sc_signal<pkt_desc>, NO_PORTS >   pkt_in1;
//   std::array<sc_signal<pkt_desc>, NO_PORTS >   pkt_out0;
   sc_signal<int>       in_clk_cnt;
   
//   string pkt_sender_outfile_str = "pkt_sender_outfile0.log";
//   char * pkt_sender_filename0 = (char*)pkt_sender_outfile_str.c_str();
   char *pkt_sender_filename = (char*)"pkt_sender_outfile.log";
//   char *pkt_sender_filename1 = (char*)"pkt_sender_outfile1.log";

   sc_clock clock1("CLOCK1", 10, SC_NS, 0.5, 0.0, SC_NS);

   switch_clk in_clk_cnt_inst("CLK_CNT_INST");
   in_clk_cnt_inst.in_clk_cnt(in_clk_cnt);
   in_clk_cnt_inst.CLK(clock1);

   stim stim("MOD_STIM");
   stim.in_clk_cnt(in_clk_cnt);
   for(int i=0; i<NO_PORTS; i++)
      stim.out_pkt_stim[i](pkt_in[i]);
   stim.pkt_inprt = 0;
   stim.pkt_sender_filename = pkt_sender_filename;

   //stim stim1("STIM1");
   //stim1.in_clk_cnt(in_clk_cnt);
   //stim1.out_pkt_stim(pkt_in1);
   //stim1.pkt_inprt = 1;
   //stim1.pkt_sender_filename = pkt_sender_filename1;

   //pkt_switch pkt_switch_top("PKT_SWTICH_TOP");
   //pkt_switch_top.clock1(clock1);
   //pkt_switch_top.in0(pkt_in0);
   //pkt_switch_top.in1(pkt_in1);
   //pkt_switch_top.out0(pkt_out0);

   pkt_receiver pkt_receiver0("PKT_RECEIVER0");
   for(int i=0; i<NO_PORTS; i++)
      pkt_receiver0.pkt_in[i](pkt_in[i]);
   pkt_receiver0.in_clk_cnt(in_clk_cnt);

   sc_start(0, SC_NS);

   // create trace file
   sc_trace_file *tf = sc_create_vcd_trace_file("Packet");
   sc_trace(tf, clock1, "CLK1");
   sc_trace(tf, pkt_in[0], "PKT_IN[0]");
   sc_trace(tf, pkt_in[1], "PKT_IN[1]");
   sc_trace(tf, pkt_in[2], "PKT_IN[2]");
   sc_trace(tf, pkt_in[3], "PKT_IN[3]");
//   sc_trace(tf, pkt_in1, "PKT_IN1");
//   sc_trace(tf, pkt_out0, "PKT_OUT0");

   sc_start(0.001,SC_MS);

   // close trace file
   sc_close_vcd_trace_file(tf);

   return 0;
}