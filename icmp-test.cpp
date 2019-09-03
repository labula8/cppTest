#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <string.h>
 
#define PACKET_SIZE     4096
#define MAX_WAIT_TIME   5
#define PACKET_NUMS     3
 
char               sendpacket[PACKET_SIZE];
char               recvpacket[PACKET_SIZE];
int                sockfd, datalen = 56;
struct timeval     tvrecv;
struct sockaddr_in dest_addr;
struct sockaddr_in from;
 
unsigned short checkSum(unsigned short *addr, int len);
int pack(int pack_no);
int unpack(char *buf, int len);
void subTime(struct timeval *out, struct timeval *in);
 
 
int main(int argc, char *argv[]) {
    int            i, n;
    int            nsend     = 0;
    int            nreceived = 0;
    struct hostent *host;
    unsigned long  inaddr    = 0l;
 
    // 生成使用ICMP的原始 socket
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
        perror("socket error");
        exit(1);
    }
 
    // 设置目标服务器的地址
    dest_addr.sin_family = AF_INET;
 
    // 判断命令行参数是主机名还是 IP，并获取 ping 的目标到 dest_addr
    if (inaddr = inet_addr(argv[1]) == INADDR_NONE) {
        // 主机名
        if ((host = gethostbyname(argv[1])) == NULL) {
            perror("gethostbyname error");
            exit(1);
        }
        memcpy((char *) &dest_addr.sin_addr, host->h_addr, host->h_length);
 
    } else {
        // 输入 IP
        memcpy((char *) &dest_addr, (char *) &inaddr, host->h_length);
    }
 
    // 输出主机名解析得到的 IP 等信息
    printf("PING %s(%s): %d bytes data in ICMP packets.\n", argv[1], inet_ntoa(dest_addr.sin_addr), datalen);
 
    // 发送和接收报文
    for (i = 0; i < PACKET_NUMS; ++i) {
        nsend++;                        // 发送序号自增
 
        // 发送报文
        int packetsize = pack(nsend);
        if (sendto(sockfd, sendpacket, packetsize, 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr)) < 0) {
            perror("sendto error");
            continue;
        }
 
        // 接收报文
        int fromlen = sizeof(from);
        if ((n = recvfrom(sockfd, recvpacket, sizeof(recvpacket), 0, (struct sockaddr *) &from, &fromlen)) < 0) {
            perror("recvfrom error");
            continue;
        }
        gettimeofday(&tvrecv, NULL);
        if (unpack(recvpacket, n) == -1) {
            continue;
        }
        nreceived++;
        sleep(1);
    }
 
    // 输出统计信息
    printf("\n--------------------%s ping statistics-------------------\n", argv[1]);
    printf("%d packets transmitted, %d received , %%%d lost\n", nsend, nreceived, (nsend - nreceived) / nsend * 100);
    close(sockfd);
    return 0;
}
 
 
/**
 * 校验和算法
 * @param addr 待校验数据地址
 * @param size 待校验部分的长度
 * @return 校验和
 */
unsigned short checkSum(unsigned short *addr, int size) {
 
    unsigned int sum = 0;
 
    // 将整个 ICMP 报文按 16 位分割求和
    while (size > 1) {
        sum += *addr++;
        size -= 2;
    }
 
    // 当 ICMP 报文为奇数个字节时，会留下最后 1 个字节，需处理
    if (size == 1) {
        sum += *(unsigned char *) addr;
    }
 
    // 当和大于 16 位时，需要将左边的高位加到低位上
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
 
    return ~sum;
}
 
/**
 * 手动构建 ICMP 报头
 * @param pack_no
 * @return
 */
int pack(int pack_no) {
    struct icmp    *icmp;
    struct timeval *tval;
    icmp = (struct icmp *) sendpacket;
    icmp->icmp_type  = ICMP_ECHO;       // ICMP 回送请求
    icmp->icmp_code  = 0;
    icmp->icmp_cksum = 0;               // 校验和字段
    icmp->icmp_seq   = pack_no;         // ICMP 报文的发送顺序
    icmp->icmp_id    = getpid();        // 使用 PID 唯一标识 ICMP 报文
    int packsize = 8 + datalen;
    tval = (struct timeval *) icmp->icmp_data;
    gettimeofday(tval, NULL);           // 记录发送时间
    icmp->icmp_cksum = checkSum((unsigned short *) icmp, packsize); // 校验
    return packsize;                    // UDP 数据报的长度在 sendto 中需要使用
}
 
/**
 * 手动拆解 ICMP 报头
 * @param buf   报文地址
 * @param len   报文长度
 * @return
 */
int unpack(char *buf, int len) {
    int            iphdrlen;
    struct ip      *ip;
    struct icmp    *icmp;
    struct timeval *tvsend;
    double         rtt;
    ip       = (struct ip *) buf;
    iphdrlen = ip->ip_hl << 2;                      // IP 数据报的头部长度 header length
    icmp     = (struct icmp *) (buf + iphdrlen);    // 越过 ICMP 差错报文的 IP 数据报首部，获取差错报文
    len      -= iphdrlen;                           // ICMP 报文长度是 IP 数据报长度减 IP 头部长度
 
    // 接收到的 ICMP 报文应大于 8 字节
    if (len < 8) {
        return -1;
    }
 
    // 接收同样标志 PID 的 ICMP 回送响应
    if ((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == getpid())) {
        tvsend = (struct timeval *) icmp->icmp_data;
        subTime(&tvrecv, tvsend);
        rtt = tvrecv.tv_sec * 1000 + tvrecv.tv_usec / 1000;     // RTT 时间单位为毫秒
 
        printf("%d byte from %s: icmp_seq=%u ttl=%d rtt=%.3f ms\n", len, inet_ntoa(from.sin_addr), icmp->icmp_seq, ip->ip_ttl, rtt);
    } else {
        return -1;
    }
}
 
/**
 * 计算两个时间差
 * @param out 发送时间
 * @param in  接收时间
 */
void subTime(struct timeval *out, struct timeval *in) {
    if ((out->tv_usec -= in->tv_usec) < 0) {
        --out->tv_sec;
        out->tv_usec += 1000000;
    }
    out->tv_sec -= in->tv_sec;
}