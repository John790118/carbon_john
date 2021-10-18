

#ifndef __PKT_RECEIVER_H__
#define __PKT_RECEIVER_H__

#include "systemc.h"
#include "pkt.h"

struct pkt_receiver: sc_module
{
  sc_in<pkt> pkt_in;
  int first;
  ofstream pkt_receiver_file;
  SC_CTOR(pkt_receiver)
  {
		pkt_receiver_file.open("pkt_receiver_file.log");
    SC_THREAD(pkt_receiver_prc);
    dont_initialize();
    sensitive << pkt_in;
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