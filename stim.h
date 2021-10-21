

#ifndef __STIM_H__
#define __STIM_H__

#include "systemc.h"
#include "comm_def.h" 
#include <string>
#include <iostream>


struct stim: sc_module
{
  //端口
  sc_in<int> in_clk_cnt;
  std::array<sc_out<s_pkt_desc>, g_inter_num > out_pkt_stim;  
//  int   pkt_inprt;
  char* pkt_sender_filename;

  //信号
  std::array<s_pkt_desc, g_inter_num > pkt_desc_tmp;  

  SC_CTOR(stim)
  {
    for(int i=0; i < g_inter_num; i++)
    {
      pkt_desc_tmp[i].type    = -1;
      pkt_desc_tmp[i].fid     = -1;
      pkt_desc_tmp[i].sid     = -1;
      pkt_desc_tmp[i].did     = -1;
      pkt_desc_tmp[i].fsn     = -1;
      pkt_desc_tmp[i].len     = -1;
      pkt_desc_tmp[i].pri     = -1;
      pkt_desc_tmp[i].sport   = -1;
      pkt_desc_tmp[i].dport   = -1;
      pkt_desc_tmp[i].qid     = -1;
      pkt_desc_tmp[i].vldl    = -1;
      pkt_desc_tmp[i].csn     = -1;
      pkt_desc_tmp[i].sop     = false;
      pkt_desc_tmp[i].eop     = false;
    }

    SC_THREAD(stim_prc);
    sensitive << in_clk_cnt;
  }
  void stim_prc();
};


#endif // _STIM_H_