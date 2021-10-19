

#ifndef __PKT_RECEIVER_H__
#define __PKT_RECEIVER_H__

#include "systemc.h"
#include "comm_def.h"
#include "pkt.h"

struct pkt_receiver: sc_module
{
  std::array<sc_in<pkt_desc>, NO_PORTS >  pkt_in;
  sc_in<int> in_clk_cnt;
  int first;
  ofstream pkt_receiver_file;
  SC_CTOR(pkt_receiver)
  {
		pkt_receiver_file.open("pkt_receiver_file.log");
    SC_THREAD(pkt_receiver_prc);
    dont_initialize();
    sensitive << pkt_in[0];
    sensitive << pkt_in[1];
    sensitive << pkt_in[2];
    sensitive << pkt_in[3];
    first = 1;
  }
  void pkt_receiver_prc();
   ~pkt_receiver()
	{
		pkt_receiver_file.flush();
		pkt_receiver_file.close();
	}
};

#endif// _PKT_RECEIVER_H_