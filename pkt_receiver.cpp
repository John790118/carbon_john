

#include <stdlib.h>
#include <time.h>
#include "pkt.h"
#include "comm_def.h"
#include "pkt_receiver.h" 

void pkt_receiver :: pkt_receiver_prc()
{
    std::array<sc_out<pkt_desc>, NO_PORTS > temp_val; 
//    ofstream pkt_receiver_file; 

    while(1)
    {
        //if first packet,open new outfile
//        if (first == 1)
//        {
//            pkt_receiver_file.open("pkt_receiver_file.log");
//            first = 0;
//        }
//        else
//        {
//            pkt_receiver_file.open("pkt_receiver_file.log",ios::out | ios::app);
//        }
        for(int i=0; i < NO_PORTS; i++)
        {
            temp_val[i] = pkt_in[i].read();
            cout << "@" << in_clk_cnt << "_clks stim receive =>:"
                << temp_val[i];
            pkt_receiver_file << "@" << in_clk_cnt << "_clks stim receive =>:"
                << temp_val[i];
        }

        //cout << "               ........................" << endl;
        //cout << "               New Packet Received" << endl;
        //cout << "               Packet ID:      " << "Ox" << hex << temp_val.pkt_id << endl;
        //cout << "               Packet inport:  " << "Ox" << hex << temp_val.pkt_inprt << endl;
        //cout << "               Packet outport: " << "Ox" << hex << temp_val.pkt_outprt << endl;
        //cout << "               Packet Length:  " << "Ox" << hex << temp_val.pkt_len << endl;
        //cout << "               Packet DMAC:    " << "Ox" << hex << temp_val.pkt_dst_mac << endl;
        //cout << "               Packet SMAC:    " << "Ox" << hex << temp_val.pkt_src_mac << endl;
        //cout << "               Packet Type:    " << "Ox" << hex << temp_val.pkt_type << endl;

        //pkt_receiver_file << "               ........................" << endl;
        //pkt_receiver_file << "               New Packet Received" << endl;
        //pkt_receiver_file << "               Packet ID:      " << "Ox" << hex << temp_val.pkt_id << endl;
        //pkt_receiver_file << "               Packet inport:  " << "Ox" << hex << temp_val.pkt_inprt << endl;
        //pkt_receiver_file << "               Packet outport: " << "Ox" << hex << temp_val.pkt_outprt << endl;
        //pkt_receiver_file << "               Packet Length:  " << "Ox" << hex << temp_val.pkt_len << endl;
        //pkt_receiver_file << "               Packet DMAC:    " << "Ox" << hex << temp_val.pkt_dst_mac << endl;
        //pkt_receiver_file << "               Packet SMAC:    " << "Ox" << hex << temp_val.pkt_src_mac << endl;
        //pkt_receiver_file << "               Packet Type:    " << "Ox" << hex << temp_val.pkt_type << endl;
        
//        pkt_receiver_file.close();

        wait();
    }

}

