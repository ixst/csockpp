#ifndef CSOCKPP_LINUX_ADDRESS_FAMILY_HH__
#define CSOCKPP_LINUX_ADDRESS_FAMILY_HH__

#include <sys/socket.h>


namespace csockpp {
namespace linux_ {

enum class AddressFamily {
#ifdef AF_UNSPEC
  kUnspec = AF_UNSPEC,
#endif
#ifdef AF_LOCAL
  kLocal = AF_LOCAL,
#endif
#ifdef AF_UNIX
  kUnix = AF_UNIX,
#endif
#ifdef AF_FILE
  kFile = AF_FILE,
#endif
#ifdef AF_INET
  kInet = AF_INET,
#endif
#ifdef AF_AX25
  kAx25 = AF_AX25,
#endif
#ifdef AF_IPX
  kIpx = AF_IPX,
#endif
#ifdef AF_NETROM
  kNetRom = AF_NETROM,
#endif
#ifdef AF_APPLETALK
  kAppletalk = AF_APPLETALK,
#endif
#ifdef AF_BRIDGE
  kBridge = AF_BRIDGE,
#endif
#ifdef AF_ATMPVC
  kAtmPvc = AF_ATMPVC,
#endif
#ifdef AF_X25
  kX25 = AF_X25,
#endif
#ifdef AF_INET6
  kInet6 = AF_INET6,
#endif
#ifdef AF_ROSE
  kRose = AF_ROSE,
#endif
#ifdef AF_DECnet
  kDecNet = AF_DECnet,
#endif
#ifdef AF_NETBEUI
  kNetBeui = AF_NETBEUI,
#endif
#ifdef AF_SECURITY
  kSecurity = AF_SECURITY,
#endif
#ifdef AF_KEY
  kKey = AF_KEY,
#endif
#ifdef AF_NETLINK
  kNetLink = AF_NETLINK,
#endif
#ifdef AF_ROUTE
  kRoute = AF_ROUTE,
#endif
#ifdef AF_PACKET
  kPacket = AF_PACKET,
#endif
#ifdef AF_ASH
  kAsh = AF_ASH,
#endif
#ifdef AF_ECONET
  kEcoNet = AF_ECONET,
#endif
#ifdef AF_ATMSVC
  kAtmSvc = AF_ATMSVC,
#endif
#ifdef AF_RDS
  kRds = AF_RDS,
#endif
#ifdef AF_IRDA
  kIrda = AF_IRDA,
#endif
#ifdef AF_PPPOX
  kPPPoX = AF_PPPOX,
#endif
#ifdef AF_WANPIPE
  kWanPipe = AF_WANPIPE,
#endif
#ifdef AF_LLC
  kLlc = AF_LLC,
#endif
#ifdef AF_IB
  kIb = AF_IB,
#endif
#ifdef AF_MPLS
  kMpls = AF_MPLS,
#endif
#ifdef AF_CAN
  kCan = AF_CAN,
#endif
#ifdef AF_TIPC
  kTipc = AF_TIPC,
#endif
#ifdef AF_BLUETOOTH
  kBluetooth = AF_BLUETOOTH,
#endif
#ifdef AF_IUCV
  kIucv = AF_IUCV,
#endif
#ifdef AF_RXRPC
  kRxRpx = AF_RXRPC,
#endif
#ifdef AF_ISDN
  kIsdn = AF_ISDN,
#endif
#ifdef AF_PHONET
  kPhonet = AF_PHONET,
#endif
#ifdef AF_IEEE802154
  kIeee802154 = AF_IEEE802154,
#endif
#ifdef AF_CAIF
  kCaif = AF_CAIF,
#endif
#ifdef AF_ALG
  kAlg = AF_ALG,
#endif
#ifdef AF_NFC
  kNfc = AF_NFC,
#endif
#ifdef AF_VSOCK
  kVsock = AF_VSOCK,
#endif
#ifdef AF_KCM
  kKcm = AF_KCM,
#endif
#ifdef AF_QIPCRTR
  kQIpcRtr = AF_QIPCRTR,
#endif
#ifdef AF_SMC
  kSmc = AF_SMC,
#endif
#ifdef AF_XDP
  kXdp = AF_XDP,
#endif
#ifdef AF_MCTP
  kMctp = AF_MCTP,
#endif
#ifdef AF_MAX
  kMax = AF_MAX,
#endif

};

}
}


#endif
