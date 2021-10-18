

#include "stdio.h"
#include <iostream>
#include "systemc.h"
#include <memory>
#include "pkt.h"
#include "pkt_sender.h"
#include "pkt_receiver.h"
#include "pkt_switch.h"
#include "pkt_sch.h"
using namespace std;


int sc_main(int argc, char *argv[])
{
   sc_signal<pkt> pkt_in0;
   sc_signal<pkt> pkt_in1;
   sc_signal<pkt> pkt_out0;

   
//   string pkt_sender_outfile_str = "pkt_sender_outfile0.log";
//   char * pkt_sender_filename0 = (char*)pkt_sender_outfile_str.c_str();
   char * pkt_sender_filename0 = (char*)"pkt_sender_outfile0.log";
   char * pkt_sender_filename1 = (char*)"pkt_sender_outfile1.log";

   sc_clock clock1("CLOCK1", 10, SC_NS, 0.5, 0.0, SC_NS);

   pkt_sender pkt_sender0("PKT_SENDER0");
   pkt_sender0.pkt_out(pkt_in0);
   pkt_sender0.CLK(clock1);
   pkt_sender0.pkt_inprt = 0;
   pkt_sender0.pkt_sender_filename = pkt_sender_filename0;

   pkt_sender pkt_sender1("PKT_SENDER1");
   pkt_sender1.pkt_out(pkt_in1);
   pkt_sender1.CLK(clock1);
   pkt_sender1.pkt_inprt = 1;
   pkt_sender1.pkt_sender_filename = pkt_sender_filename1;

   pkt_switch pkt_switch_top("PKT_SWTICH_TOP");
   pkt_switch_top.clock1(clock1);
   pkt_switch_top.in0(pkt_in0);
   pkt_switch_top.in1(pkt_in1);
   pkt_switch_top.out0(pkt_out0);

   pkt_receiver pkt_receiver0("PKT_RECEIVER0");
   pkt_receiver0.pkt_in(pkt_out0);

   sc_start(0, SC_NS);

   // create trace file
   sc_trace_file *tf = sc_create_vcd_trace_file("Packet");
   sc_trace(tf, clock1, "CLK1");
   sc_trace(tf, pkt_in0, "PKT_IN0");
   sc_trace(tf, pkt_in1, "PKT_IN1");
   sc_trace(tf, pkt_out0, "PKT_OUT0");

   sc_start(0.001,SC_MS);

   // close trace file
   sc_close_vcd_trace_file(tf);

   return 0;
}