#ifndef __STAT_H__
#define __STAT_H__

#include "systemc.h"
#include "comm_def.h"

#define FLOW_RULE_TAB_SIZE 16

struct stat: sc_module
{
  std::array<sc_in<s_pkt_desc>, G_INTER_NUM >  pkt_in;
  sc_in<int> in_clk_cnt;
  int first;
  ofstream pkt_receiver_file;
  SC_CTOR(stat)
  {
		pkt_receiver_file.open("pkt_receiver_file.log");
    SC_THREAD(stat_prc);
    dont_initialize();
    for(int i=0;i<G_INTER_NUM;i++)
    {
      sensitive << pkt_in[i];
    }

    first = 1;
  }
  void stat_prc();
   ~stat()
	{
		pkt_receiver_file.flush();
		pkt_receiver_file.close();
	}
};

#endif// __STAT_H__