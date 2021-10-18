

#include <stdlib.h>
#include <time.h>
#include "pkt.h"
#include "pkt_sender.h" 
#define SEND_FILE_NUM 10

void pkt_sender::pkt_sender_prc()
{
    pkt pkt_data;

    int pkt_send_count;
    
    ofstream pkt_sender_file;
//    pkt_sender_file.open("pkt_sender_file.log");
    pkt_sender_file.open(pkt_sender_filename);

    pkt_data.pkt_id = 0;
    pkt_send_count = 0;

    srand((unsigned)time(NULL));
    wait(8);
//    while(1)
    while(pkt_send_count++ < SEND_FILE_NUM)
    {
        //define DMAC SMAC PKT_TYPE
        pkt_data.pkt_dst_mac    = 0xDC71967D0000 + rand()%255;
        pkt_data.pkt_src_mac    = 0xDC71967D0100 + rand()%255;
        pkt_data.pkt_type       = 0x0800;

        //define PKT_LEN, 64<=PKT_LEN<=1518
        pkt_data.pkt_len        = 18 + 46 + rand()%1500;

        //define PKT_ID
        pkt_data.pkt_id++;

        //define PKT_INPRT and PKT_OUTPRT
        pkt_data.pkt_inprt  = pkt_inprt;
        pkt_data.pkt_outprt = -1;

        //output pkt_data
        pkt_out.write(pkt_data);

        //print packet
        cout << "........................" << endl;
        cout << "New Packet Send" << endl;
        cout << "Pakcet ID:     " << "Ox" << hex << pkt_data.pkt_id << endl;
        cout << "Pakcet inport: " << "Ox" << hex << pkt_data.pkt_inprt << endl;
        cout << "Pakcet outport:" << "Ox" << hex << pkt_data.pkt_outprt << endl;
        cout << "Packet Length: " << "Ox" << hex << pkt_data.pkt_len << endl;
        cout << "Packet DMAC:   " << "Ox" << hex << pkt_data.pkt_dst_mac << endl;
        cout << "Packet SMAC:   " << "Ox" << hex << pkt_data.pkt_src_mac << endl;
        cout << "Packet Type:   " << "Ox" << hex << pkt_data.pkt_type << endl;

        pkt_sender_file << "........................" << endl;
        pkt_sender_file << "New Packet Send" << endl;
        pkt_sender_file << "Pakcet ID:     " << "Ox" << hex << pkt_data.pkt_id << endl;
        pkt_sender_file << "Pakcet inport: " << "Ox" << hex << pkt_data.pkt_inprt << endl;
        pkt_sender_file << "Pakcet outport:" << "Ox" << hex << pkt_data.pkt_outprt << endl;
        pkt_sender_file << "Packet Length: " << "Ox" << hex << pkt_data.pkt_len << endl;
        pkt_sender_file << "Packet DMAC:   " << "Ox" << hex << pkt_data.pkt_dst_mac << endl;
        pkt_sender_file << "Packet SMAC:   " << "Ox" << hex << pkt_data.pkt_src_mac << endl;
        pkt_sender_file << "Packet Type:   " << "Ox" << hex << pkt_data.pkt_type << endl;

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