

#ifndef __PKT_SENDER_H__
#define __PKT_SENDER_H__

#include "systemc.h"
#include "pkt.h"
#include "comm_def.h"
#include <string>
#include <iostream>

const int NO_PORTS =4;

struct stim: sc_module
{
  //端口
  sc_in<int> in_clk_cnt;
  std::array<sc_out<pkt_desc>, NO_PORTS > out_pkt_stim;  
  int   pkt_inprt;
  char* pkt_sender_filename;

  //信号
  std::array<pkt_desc, NO_PORTS > pkt_desc_tmp;  

  for(int i=0; i < NO_PORTS; i++)
  {
      pkt_desc_tmp[i].sid = i;
      pkt_desc_tmp[i].did = NO_PORTS-1-i;
      pkt_desc_tmp[i].fsn = 0;
      pkt_desc_tmp[i].len = 64;
      pkt_desc_tmp[i].pri = 0;
      pkt_desc_tmp[i].fid = i;
  }

  SC_CTOR(stim)
  {
    SC_THREAD(stim_prc);
    sensitive << in_clk_cnt;
  }
  void stim_prc();
};


#endif