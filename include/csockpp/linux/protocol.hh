#ifndef CSOCKPP_LINUX_PROTOCOL_HH__
#define CSOCKPP_LINUX_PROTOCOL_HH__

#include <netinet/in.h>


namespace csockpp {
namespace linux_ {

enum class Protocol {
#ifdef IPPROTO_IP
  kIp = IPPROTO_IP,
#endif
#ifdef IPPROTO_ICMP
  kIcmp = IPPROTO_ICMP,
#endif
#ifdef IPPROTO_IGMP
  kIgmp = IPPROTO_IGMP,
#endif
#ifdef IPPROTO_IPIP
  kIpip = IPPROTO_IPIP,
#endif
#ifdef IPPROTO_TCP
  kTcp = IPPROTO_TCP,
#endif
#ifdef IPPROTO_EGP
  kEgp = IPPROTO_EGP,
#endif
#ifdef IPPROTO_PUP
  kPup = IPPROTO_PUP,
#endif
#ifdef IPPROTO_UDP
  kUdp = IPPROTO_UDP,
#endif
#ifdef IPPROTO_IDP
  kIdp = IPPROTO_IDP,
#endif
#ifdef IPPROTO_TP
  kTp = IPPROTO_TP,
#endif
#ifdef IPPROTO_DCCP
  kDccp = IPPROTO_DCCP,
#endif
#ifdef IPPROTO_IPV6
  kIpv6 = IPPROTO_IPV6,
#endif
#ifdef IPPROTO_RSVP
  kRsvp = IPPROTO_RSVP,
#endif
#ifdef IPPROTO_GRE
  kGre = IPPROTO_GRE,
#endif
#ifdef IPPROTO_ESP
  kEsp = IPPROTO_ESP,
#endif
#ifdef IPPROTO_AH
  kAh = IPPROTO_AH,
#endif
#ifdef IPPROTO_MTP
  kMtp = IPPROTO_MTP,
#endif
#ifdef IPPROTO_BEETPH
  kBeepth = IPPROTO_BEETPH,
#endif
#ifdef IPPROTO_ENCAP
  kEncap = IPPROTO_ENCAP,
#endif
#ifdef IPPROTO_PIM
  kPim = IPPROTO_PIM,
#endif
#ifdef IPPROTO_COMP
  kComp = IPPROTO_COMP,
#endif
#ifdef IPPROTO_SCTP
  kSctp = IPPROTO_SCTP,
#endif
#ifdef IPPROTO_UDPLITE
  kUdpLite = IPPROTO_UDPLITE,
#endif
#ifdef IPPROTO_MPLS
  kMpls = IPPROTO_MPLS,
#endif
#ifdef IPPROTO_ETHERNET
  kEthernet = IPPROTO_ETHERNET,
#endif
#ifdef IPPROTO_RAW
  kRaw = IPPROTO_RAW,
#endif
#ifdef IPPROTO_MPTCP
  kMpTcp = IPPROTO_MPTCP,
#endif
#ifdef IPPROTO_MAX
  kMax = IPPROTO_MAX,
#endif

};

}
}


#endif
