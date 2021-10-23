

#ifndef __STIM_H__
#define __STIM_H__

#include "systemc.h"
#include "comm_def.h" 
#include <string>
#include <iostream>
#define SEND_FILE_NUM 32
#define FLOW_RULE_TAB_SIZE 16

struct stim: sc_module
{
  //端口
  sc_in<int> in_clk_cnt;
  std::array<sc_out<s_pkt_desc>, g_inter_num> out_pkt_stim;  
//  int   pkt_inprt;
  char* pkt_sender_filename;

  //信号
//  std::array<s_pkt_desc, g_inter_num> pkt_desc_tmp;  
  s_pkt_desc pkt_desc_tmp;  

  //std::array<array<s_pkt_desc, FLOW_RULE_TAB_SIZE>,g_inter_num> fifo_regs;
  //std::array<bool,g_inter_num> fifo_full;
  //std::array<bool,g_inter_num> fifo_empty;
  //std::array<int,g_inter_num>  fifo_pntr;

  SC_CTOR(stim)
  {
    pkt_desc_tmp.type    = -1;
    pkt_desc_tmp.fid     = -1;
    pkt_desc_tmp.sid     = -1;
    pkt_desc_tmp.did     = -1;
    pkt_desc_tmp.fsn     = -1;
    pkt_desc_tmp.len     = -1;
    pkt_desc_tmp.pri     = -1;
    pkt_desc_tmp.sport   = -1;
    pkt_desc_tmp.dport   = -1;
    pkt_desc_tmp.qid     = -1;
    pkt_desc_tmp.vldl    = -1;
    pkt_desc_tmp.csn     = -1;
    pkt_desc_tmp.sop     = false;
    pkt_desc_tmp.eop     = false;

    SC_THREAD(stim_prc);
    sensitive << in_clk_cnt;
  }
  void stim_prc();

};

struct port_fifo
{
  std::array<s_pkt_desc, FLOW_RULE_TAB_SIZE> regs;
  bool full;
  bool empty;
  int  pntr;

  port_fifo()
  {
    full = false;
    empty = true;
    pntr = 0;
  }

  void pkt_in(const s_pkt_desc& data_pkt);

  s_pkt_desc pkt_out();

  s_pkt_desc pkt_pre_val();
};

struct token_bucket
{
  int token;

  token_bucket()
  {
    token = 0;
  }

  void add_token(const int& add_token_val);

  void sub_token(const int& sub_token_val);

  int read_token();
};

#endif // _STIM_H_