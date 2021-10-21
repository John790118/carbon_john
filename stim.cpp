

#include <stdlib.h>
#include <time.h>
#include "stim.h"
#include "comm_def.h"
#define SEND_FILE_CYCLE 4
#define FLOW_RULE_TAB_SIZE 16

void stim :: stim_prc()
{
    int pkt_send_count;
    int send_pkt_port;

    //vector<s_flow_rule>  g_flow_rule_tab;
    s_flow_rule a;
    for(int fid=0; fid<FLOW_RULE_TAB_SIZE; fid++)
    {
        a.sid       = fid*4;
        a.did       = 0;
        a.len       = 64;
        a.pri       = 0;
        a.sport     = fid % g_inter_num;
        a.dport     = 0;
        a.qid       = 0;
        a.len2add   = 1;
        a.flow_speed= 13;

        g_flow_rule_tab.push_back(a);
    }
 
    ofstream pkt_sender_file;
//    pkt_sender_file.open("pkt_sender_file.log");
    pkt_sender_file.open(pkt_sender_filename);

    pkt_send_count = 0;

    srand((unsigned)time(NULL));
    wait(8);
//    while(1)
    while(pkt_send_count++ < SEND_FILE_CYCLE)
    {
        for(int fid=0; fid < FLOW_RULE_TAB_SIZE; fid++)
        {
            send_pkt_port = g_flow_rule_tab[fid].sport;

            pkt_desc_tmp[send_pkt_port].type = 0;
            pkt_desc_tmp[send_pkt_port].fid  = -1;
            pkt_desc_tmp[send_pkt_port].sid  = g_flow_rule_tab[fid].sid;
            pkt_desc_tmp[send_pkt_port].did  = g_flow_rule_tab[fid].did;
            pkt_desc_tmp[send_pkt_port].fsn  = pkt_send_count;
            pkt_desc_tmp[send_pkt_port].len  = g_flow_rule_tab[fid].len;
            pkt_desc_tmp[send_pkt_port].pri  = g_flow_rule_tab[fid].pri;
            pkt_desc_tmp[send_pkt_port].sport= g_flow_rule_tab[fid].sport;
            pkt_desc_tmp[send_pkt_port].dport= -1;
            pkt_desc_tmp[send_pkt_port].qid  = -1;
            pkt_desc_tmp[send_pkt_port].vldl = -1;
            pkt_desc_tmp[send_pkt_port].csn  = -1;
            pkt_desc_tmp[send_pkt_port].sop  = false;
            pkt_desc_tmp[send_pkt_port].eop  = false;

            //output pkt_data
            out_pkt_stim[send_pkt_port].write(pkt_desc_tmp[send_pkt_port]);
            cout << "@" << in_clk_cnt << "_clks stim sent =>:"
                 << pkt_desc_tmp[send_pkt_port] << endl;
            pkt_sender_file << "@" << in_clk_cnt << "_clks stim sent =>:"
                 << pkt_desc_tmp[send_pkt_port];
        }
        wait();

        // wait for 1 to 3 clock periods
        //wait(1+(rand()%3));

    }

    pkt_sender_file.close();
}

#if 0
#include "packet_gen.h"
//激励包长应从顶层获取，先配置固定256B，稍后再改
packet_gen_module::packet_gen_module(string name, global_config_c *glb_cfg):sc_module(name)
{

    m_cycle_cnt =0;
    m_packet_id =0;
    m_cfg = glb_cfg;
    
    output.resize(g_m_inter_num);
    for(int i=0; i < g_m_inter_num; i++)
    {
        output[i] =new sc_fifo_out<TRANS>;
    }
    //init shape
    packet_shape.resize(g_m_inter_num);
    for(int i=0; i < g_m_inter_num; i++)
    {
        packet_shape[i] = new comm_shape_func(1000, 9620, 13, 10);
    }

    //stat
    string debug_file = name + string("_debug.log");
    m_bw_stat =new comm_stat_bw(m_cfg, debug_file,g_m_inter_num);
    
    SC_METHOD(packet_gen_process);
    sensitive << clk.pos();

    

}
void packet_gen_module::packet_gen_process()
{
   m_cycle_cnt++;   
   //stat
   if((m_cycle_cnt !=0) && (m_cycle_cnt % (m_cfg->stat_period *100) ==0))
   {
       m_bw_stat->print_bw_info(m_cycle_cnt);
   }
   
   //填桶
    if((m_cycle_cnt !=0) &&(m_cycle_cnt % 10 ==0))
    {
        for(int i=0; i < g_m_inter_num; i++)
        {
            packet_shape[i]->add_token(13);  //10cc填充13个
        }    
    }
    
   //4端口轮询
   for(int i=0; i < g_m_inter_num; i++)
   {
        if(packet_shape[i]->shape_status(256)) //包长是否够
        {
            m_packet_id++;  
            TRANS new_trans(new trans_type);
            new_trans->packet_id = m_packet_id;
            new_trans->port_id =i;
            new_trans->packet_len = 256;
            new_trans->valid_len =  256;
            new_trans->is_sop = true;
            new_trans->is_eop = true;
            output[i]->nb_write(new_trans);
            //stat
            m_bw_stat->record_bw_info(i, new_trans->valid_len, true);
        }
   }   
}
#endif//if 0