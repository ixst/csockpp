#ifndef CSOCKPP_LINUX_TYPE_HH__
#define CSOCKPP_LINUX_TYPE_HH__

#include <sys/socket.h>


namespace csockpp {
namespace linux_ {

enum class Type {
#ifdef SOCK_STREAM
  kStream = SOCK_STREAM,
#endif
#ifdef SOCK_DGRAM
  kDatagram = SOCK_DGRAM,
#endif
#ifdef SOCK_SEQPACKET
  kSequencePacket = SOCK_SEQPACKET,
#endif
#ifdef SOCK_RAW
  kRaw = SOCK_RAW,
#endif
#ifdef SOCK_RDM
  kRdm = SOCK_RDM,
#endif
#ifdef SOCK_DCCP
  kDccp = SOCK_DCCP,
#endif
#ifdef SOCK_PACKET
  kPacket = SOCK_PACKET,
#endif

};

}
}


#endif
