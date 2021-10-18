#ifndef __PKT_H__
#define __PKT_H__

#include "systemc.h"

#if 0
typedef struct pkt_struc
{
   sc_int<48>  pkt_dst_mac;
   sc_int<48>  pkt_src_mac;
   sc_int<16>  pkt_type;
   int         pkt_len;
   int         pkt_id;
   int         pkt_inprt;
   int         pkt_outprt;

   pkt_struc()
   {
      pkt_dst_mac = 0xDC71967DFCA4;
      pkt_src_mac = 0xDC71967DFCA1;
      pkt_type = 0x0800;
      pkt_len = 64; //include FCS,but not include 20byte preamble
   }
} PKT_STRC; 

typedef  std::shared_ptr<PKT_STRC>  PKT;
#endif//ifdef(0)

struct pkt
{
   sc_int<48>  pkt_dst_mac;
   sc_int<48>  pkt_src_mac;
   sc_int<16>  pkt_type;
   int         pkt_len;
   int         pkt_id;
   int         pkt_inprt;
   int         pkt_outprt;

   inline bool operator == (const pkt& rhs) const
   {
      return ( rhs.pkt_dst_mac == pkt_dst_mac
            && rhs.pkt_src_mac == pkt_src_mac
            && rhs.pkt_type    == pkt_type
            && rhs.pkt_len     == pkt_len
            && rhs.pkt_id      == pkt_id
            && rhs.pkt_inprt   == pkt_inprt
            && rhs.pkt_outprt  == pkt_outprt
            );
   }
};

inline 
ostream&
operator << (ostream& os, const pkt& /*a*/)
{
   os << "streaming of struct pkt not implemennted";
   return os;
}

inline 
void
#if defined(SC_API_VERSION_STRING)
   sc_trace( sc_trace_file* tf, const pkt& a, const std::string& name)
#else
   sc_trace( sc_trace_file* tf, const pkt& a, const sc_string& name)
#endif
{
   sc_trace( tf, a.pkt_dst_mac, name + ".pkt_dst_mac");
   sc_trace( tf, a.pkt_src_mac, name + ".pkt_src_mac");
   sc_trace( tf, a.pkt_type, name + ".pkt_type");
   sc_trace( tf, a.pkt_len, name + ".pkt_len");
   sc_trace( tf, a.pkt_id, name + ".pkt_id");
   sc_trace( tf, a.pkt_inprt, name + ".pkt_inprt");
   sc_trace( tf, a.pkt_outprt, name + ".pkt_outprt");
}

#endif//_PKT_H
