

#ifndef __PKT_SENDER_H__
#define __PKT_SENDER_H__

#include "systemc.h"
#include "pkt.h"
#include <string>
#include <iostream>

struct pkt_sender: sc_module
{
  sc_out<pkt> pkt_out;
  sc_in_clk   CLK;
  int   pkt_inprt;
  char* pkt_sender_filename;

  SC_CTOR(pkt_sender)
  {
    SC_THREAD(pkt_sender_prc);
    sensitive << CLK.pos();
  }
  void pkt_sender_prc();
};

#if 0
class packet_gen_module: public sc_module
{
  public: 
    vector<sc_fifo_out<TRANS> *> output;
    sc_in_clk clk;
    int m_cycle_cnt;
    int m_packet_id;
    SC_HAS_PROCESS(packet_gen_module);
    global_config_c *m_cfg;
    comm_stat_bw            *m_bw_stat;
    
  public:
    packet_gen_module(string name, global_config_c *glb_cfg);
    void packet_gen_process();
    vector<comm_shape_func *> packet_shape;
    

};
#endif//if 0

#endif