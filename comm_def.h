#ifndef __COMM_DEF_H__
#define __COMM_DEF_H__

#include <stdio.h>
#include <memory>
#include <string.h>
#include <array>
#include <vector>
#include <deque>
#include <map>
#include <assert.h>
#include "systemc.h"
using namespace std;
////////////////////////////////////////////////////////
// Project： SystemC虚拟项目
// Module:   commdef
// Description: 全局定义文件
// Group：预研组
// Author: Newton
// Date: 2021.10.14 第一版
// Hierarchy : 编号，索引公共库
////////////////////////////////////////////////////////
const int g_freq  = 100; //100M HZ
const int g_inter_num =4;

struct s_pkt_desc
{
   int  type;  //0 packet 1 cell
   int  fid;   //flow id，对应Flow号，和激励对应
   int  sid;   //用于三元组匹配
   int  did;   //用于三元组匹配
   int  fsn;
   int  len;    //包长度
   int  pri;    //报文优先级
   int  sport;  //源端口号，与ing入口侧端口对应 
   int  dport;  //目的端口号，与engress出口侧端口对应
   int  qid;   //queue 号，队列号，对应ing/sch里的que号
   int  vldl;  //有效报文长度，只有cell状态下有意义
   int  csn;   //cell切片号， 只有cell状态下有意义
   int  sop;   //首切片，只有cell状态下有意义
   int  eop;   //尾切片，只有cell状态下有意义
   s_pkt_desc()
   {
      type =-1;
      fid  =-1;
      sid  =-1;
      did  =-1;
      fsn  =-1;
      len  =-1;
      pri  =-1;
      sport   =-1;
      dport   =-1;
      qid     =-1;
      vldl    =-1;
      csn     =-1;
      sop     =-1;
      eop     =-1;
   }

   inline bool operator == (const s_pkt_desc& rhs) const
   {
     return (rhs.type == type && rhs.fid == fid && rhs.sid == sid && rhs.did == did && rhs.fsn == fsn && \
     rhs.len == len && rhs.pri == pri && rhs.sport == sport && rhs.dport == dport && rhs.qid == qid && rhs.vldl == vldl && \
     rhs.csn == csn && rhs.sop == sop && rhs.eop == eop);
   } 
}; 

//inline  ostream& operator << ( ostream& os, const s_pkt_desc& /* a */ )
//{
//    os << "streaming of struct pkt not implemented";
//    return os;
//}
//
//inline void  sc_trace( sc_trace_file* tf, const s_pkt_desc& a, const std::string& name )
//{
//    sc_trace( tf, a.sport, name + ".data" );
//}

inline  ostream& operator << ( ostream& os, const s_pkt_desc&  a )
{
//    os << "streaming of struct pkt not implemented";
    os << "@" << sc_time_stamp() << "["
         << "typ:" << (a.type)
         << ",fid:" << (a.fid)
         << ",sid:" << (a.sid)
         << ",did:" << (a.did)
         << ",fsn:" << (a.fsn)
         << ",len:" << (a.len)
         << ",pri:" << (a.pri)
         << ",spt:" << (a.sport)
         << ",dpt:" << (a.dport)
         << ",qid:" << (a.qid)
         << ",vld:" << (a.vldl)
         << ",csn:" << (a.csn)
         << ",sop:" << (a.sop)
         << ",eop:" << (a.eop)
         << "]" << endl;
    return os;
}

//inline void  sc_trace( sc_trace_file* tf, const s_pkt_desc& a, const std::string& name )
//{
//    sc_trace( tf, a.sport, name + ".data" );
//}

inline void
#if defined(SC_API_VERSION_STRING)
    sc_trace( sc_trace_file* tf, const s_pkt_desc& a, const std::string& name )
#else
    sc_trace( sc_trace_file* tf, const s_pkt_desc& a, const sc_string& name )
#endif
{
  sc_trace( tf, a.type,  name + ".type" );
  sc_trace( tf, a.fid,   name + ".fid"  );
  sc_trace( tf, a.sid,   name + ".sid"  );
  sc_trace( tf, a.did,   name + ".did"  );
  sc_trace( tf, a.fsn,   name + ".fsn"  );
  sc_trace( tf, a.len,   name + ".len"  );
  sc_trace( tf, a.pri,   name + ".pri"  );
  sc_trace( tf, a.sport, name + ".sport");
  sc_trace( tf, a.dport, name + ".dport");
  sc_trace( tf, a.qid,   name + ".qid"  );
  sc_trace( tf, a.vldl,  name + ".vldl" );
  sc_trace( tf, a.csn,   name + ".csn"  );
  sc_trace( tf, a.sop,   name + ".sop"  );
  sc_trace( tf, a.eop,   name + ".eop"  );
}

// fid映射规则表内容
struct s_flow_rule
{
   int sid;
   int did;
   int len;
   int pri;
   int sport;
   int dport;
   int qid;
   int len2add;
   int flow_speed;
   s_flow_rule()
   {
      sid =-1;
      did =-1;
      len =-1;
      pri =-1;
      sport =-1;
      dport =-1;
      qid =-1;
      len2add =-1;
      flow_speed =-1;
   }
};


//hash规则表KEY值
struct s_hash_rule_key
{
   int sid;
   int did;
   int pri;
   s_hash_rule_key()
   {
      sid =-1;
      did =-1;
      pri =-1;
   }

   inline bool operator == (const s_hash_rule_key& rhs) const
   {
     return (rhs.sid == sid && rhs.did == did && rhs.pri == pri );
   } 

   inline bool operator < (const s_hash_rule_key& rhs) const
   {
     return !(rhs.sid == sid && rhs.did == did && rhs.pri == pri );
   } 
};

//定义两个别名，用于que队列表和port端口表
typedef int s_tab_que;
typedef int s_tab_port;

//fid映射规则表项,key fid,查表得到映射表
extern vector<s_flow_rule>  g_flow_rule_tab;
//Hash规则表项，查表得到fid号
extern map<s_hash_rule_key, int>  g_hash_rule_tab;

//que_rule规则表项，查表得到rr_weight号,key为qid号
extern vector<s_tab_que>  g_que_rule_tab;

//port_rule规则表项，查表得到port_speed号,key为port号
extern vector<s_tab_port>  g_port_rule_tab;

//产生全局时钟计数器
extern int g_cycle_cnt;

//产生全局配置
class glb_cfg_c
{
   public:
   glb_cfg_c();
};


#define  ASSERT(A)  (assert(A))

#endif