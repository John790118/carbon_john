

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
   std::array<sc_signal<s_pkt_desc>, g_inter_num >   sig_pkt_in;
   sc_signal<int>       in_clk_cnt;
   
//   string pkt_sender_outfile_str = "pkt_sender_outfile0.log";
//   char * pkt_sender_filename0 = (char*)pkt_sender_outfile_str.c_str();
   char *pkt_sender_filename = (char*)"pkt_sender_file.log";

   sc_clock clock1("CLOCK1", 10, SC_NS, 0.5, 0.0, SC_NS);

   switch_clk in_clk_cnt_inst("CLK_CNT_INST");
   in_clk_cnt_inst.in_clk_cnt(in_clk_cnt);
   in_clk_cnt_inst.CLK(clock1);

   stim * mod_stim;
   mod_stim = new stim("MOD_STIM");
   mod_stim->in_clk_cnt(in_clk_cnt);
   for(int i=0; i<g_inter_num; i++)
      mod_stim->out_pkt_stim[i](sig_pkt_in[i]);
//   mod_stim->pkt_inprt = 0;
   mod_stim->pkt_sender_filename = pkt_sender_filename;

   pkt_receiver * pkt_receiver0;
   pkt_receiver0= new pkt_receiver("PKT_RECEIVER0");
   for(int i=0; i<g_inter_num; i++)
      pkt_receiver0->pkt_in[i](sig_pkt_in[i]);
   pkt_receiver0->in_clk_cnt(in_clk_cnt);

   sc_start(0, SC_NS);

   // create trace file
   sc_trace_file *tf = sc_create_vcd_trace_file("Packet");
   sc_trace(tf, clock1, "CLK1");
   sc_trace(tf, sig_pkt_in[0], "PKT_IN[0]");
//   sc_trace(tf, sig_pkt_in[1], "PKT_IN[1]");
//   sc_trace(tf, sig_pkt_in[2], "PKT_IN[2]");
//   sc_trace(tf, sig_pkt_in[3], "PKT_IN[3]");

   sc_start(0.001,SC_MS);

   // close trace file
   sc_close_vcd_trace_file(tf);

   return 0;
}